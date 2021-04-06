#include "mvApp.h"
#include "mvModule_Core.h"
#include "mvViewport.h"
#include "mvCallbackRegistry.h"
#include "mvInput.h"
#include <thread>
#include <future>
#include <chrono>
#include "mvThreadPool.h"
#include "mvAppItemCommons.h"
#include "mvProfiler.h"
#include <implot.h>
#include "mvEventListener.h"
#include "mvImGuiThemeScope.h"
#include "mvCallbackRegistry.h"
#include "mvTextureStorage.h"
#include "mvItemRegistry.h"
#include "mvLog.h"
#include "mvFontManager.h"

namespace Marvel {

	mvApp* mvApp::s_instance = nullptr;
	std::atomic_bool mvApp::s_started = false;


	// utility structure for realtime plot
	struct ScrollingBuffer {
		int MaxSize;
		int Offset;
		ImVector<ImVec2> Data;
		ScrollingBuffer() {
			MaxSize = 2000;
			Offset = 0;
			Data.reserve(MaxSize);
		}
		void AddPoint(float x, float y) {
			if (Data.size() < MaxSize)
				Data.push_back(ImVec2(x, y));
			else {
				Data[Offset] = ImVec2(x, y);
				Offset = (Offset + 1) % MaxSize;
			}
		}
		void Erase() {
			if (!Data.empty())
			{
				Data.shrink(0);
				Offset = 0;
			}
		}
	};

	mvApp* mvApp::GetApp()
	{
		mvLog::Init();

		if (s_instance)
			return s_instance;

		s_instance = new mvApp();
		return s_instance;
	}

	void mvApp::DeleteApp()
	{
		if (s_instance)
		{
			delete s_instance;
			s_instance = nullptr;
		}

		s_started = false;
	}

	void mvApp::SetAppStopped() 
	{ 

        GetApp()->getCallbackRegistry().stop();
        GetApp()->getCallbackRegistry().addCallback(nullptr, "null", nullptr);
        GetApp()->m_future.get();
		s_started = false; 
		auto viewport = s_instance->getViewport();
		if (viewport)
			viewport->stop();
	}

	void mvApp::cleanup()
	{
		getCallbackRegistry().stop();

		getCallbackRegistry().addCallback(nullptr, "null", nullptr);
      
		m_future.get();
		delete m_viewport;
		s_started = false;
	}

	mvApp::mvApp()
	{

		// info
        mvAppLog::Clear();
		mvAppLog::AddLog("[DearPyGui Version] %0s\n", mvApp::GetVersion());
		mvAppLog::AddLog("[DearImGui Version] %0s\n", IMGUI_VERSION);
        mvAppLog::AddLog("[Python Version] %0s\n", PY_VERSION);


		m_mainThreadID = std::this_thread::get_id();

#if defined(MV_DEBUG)
		new mvEventListener();
#endif // MV_PROFILE

		// create managers
		m_itemRegistry = CreateOwnedPtr<mvItemRegistry>();
		m_textureStorage = CreateOwnedPtr<mvTextureStorage>();
		m_themeManager = CreateOwnedPtr<mvThemeManager>();
        m_callbackRegistry = CreateOwnedPtr<mvCallbackRegistry>();
        m_fontManager = CreateOwnedPtr<mvFontManager>();

	}

    mvCallbackRegistry& mvApp::getCallbackRegistry()
    { 
        return *m_callbackRegistry; 
    }

	mvItemRegistry& mvApp::getItemRegistry() 
	{ 
		return *m_itemRegistry; 
	}

	mvTextureStorage& mvApp::getTextureStorage() 
	{ 
		return *m_textureStorage; 
	}

	mvThemeManager& mvApp::getThemeManager()
	{
		return *m_themeManager;
	}

	mvFontManager& mvApp::getFontManager()
	{
		return *m_fontManager;
	}

	mvApp::~mvApp()
	{
		m_itemRegistry->clearRegistry();

		mvApp::GetApp()->getTextureStorage().deleteAllTextures();

		mvLog::Cleanup();
	
	}

	void mvApp::turnOnDocking(bool shiftOnly, bool dockSpace)
	{ 
		m_docking = true; 
		m_dockingShiftOnly = shiftOnly; 
		m_dockingViewport = dockSpace;
	}

	void mvApp::render()
	{

		// update timing
		m_deltaTime = ImGui::GetIO().DeltaTime;
		m_time = ImGui::GetTime();
		ImGui::GetIO().FontGlobalScale = m_fontManager->getGlobalFontScale();

		if (m_dockingViewport)
			ImGui::DockSpaceOverViewport();

		mvEventBus::Publish(mvEVT_CATEGORY_APP, mvEVT_FRAME, {CreateEventArgument("FRAME", ImGui::GetFrameCount() )});

		mvAppLog::render();

		// route input callbacks
		mvInput::CheckInputs();

		//m_textureStorage->show_debugger();
		//m_fontManager->show_debugger();

        std::lock_guard<std::mutex> lk(m_mutex);
		mvEventBus::Publish(mvEVT_CATEGORY_APP, mvEVT_PRE_RENDER);
		mvEventBus::Publish(mvEVT_CATEGORY_APP, mvEVT_PRE_RENDER_RESET);
		mvEventBus::Publish(mvEVT_CATEGORY_APP, mvEVT_RENDER);
		mvEventBus::Publish(mvEVT_CATEGORY_APP, mvEVT_END_FRAME);

#if defined(MV_PROFILE) && defined(MV_DEBUG)
        //mvEventBus::ShowDebug();
		postProfile();
#endif // MV_PROFILE
	}

	bool mvApp::checkIfMainThread() const
	{
		if (std::this_thread::get_id() != m_mainThreadID)
		{
			int line = PyFrame_GetLineNumber(PyEval_GetFrame());
			PyErr_Format(PyExc_Exception,
				"DearPyGui command on line %d can not be called asynchronously", line);
			PyErr_Print();
			return false;
		}
		return true;
	}

	void mvApp::postProfile()
	{
		static std::map<std::string, ScrollingBuffer> buffers;
		static float t = 0;
		t += ImGui::GetIO().DeltaTime;

		const auto& results = mvInstrumentor::Get().getResults();

		for (const auto& item : results)
			buffers[item.first].AddPoint(t, item.second.count());

		//ImGui::SetNextWindowFocus();
		ImGui::SetNextWindowSize(ImVec2(500, 500), ImGuiCond_FirstUseEver);
		if (!ImGui::Begin("Profiling", nullptr))
		{
			ImGui::End();
			return;
		}

		static float history = 10.0f;
		ImGui::SliderFloat("History", &history, 1, 30, "%.1f s");

		static ImPlotAxisFlags rt_axis = ImPlotAxisFlags_NoTickLabels;
		ImPlot::SetNextPlotLimitsX(t - history, t, ImGuiCond_Always);
		if (ImPlot::BeginPlot("##Scrolling", nullptr, nullptr, ImVec2(-1, -1), 0, rt_axis, 0 | ImPlotAxisFlags_LockMin)) {

			for (const auto& item : results)
				ImPlot::PlotLine(item.first.c_str(), &buffers[item.first].Data[0].x, &buffers[item.first].Data[0].y, buffers[item.first].Data.size(), buffers[item.first].Offset, 2 * sizeof(float));
			ImPlot::EndPlot();
		}

		ImGui::End();

	}

	void mvApp::InsertParser(std::map<std::string, mvPythonParser>* parsers)
	{

		parsers->insert({ "end", mvPythonParser({
		}, "Ends a container.", "None", "Containers") });

		parsers->insert({ "enable_docking", mvPythonParser({
			{mvPythonDataType::KeywordOnly},
			{mvPythonDataType::Bool, "shift_only", "press shift for docking", "True"},
			{mvPythonDataType::Bool, "dock_space", "add explicit dockspace over viewport", "False"},
		}, "Decrements a texture.") });

		parsers->insert({ "is_dearpygui_running", mvPythonParser({
		}, "Checks if dearpygui is still running", "bool") });

		parsers->insert({ "setup_dearpygui", mvPythonParser({
		}, "Sets up DearPyGui for user controlled rendering. Only call once and you must call cleanup_deapygui when finished.") });

		parsers->insert({ "render_dearpygui_frame", mvPythonParser({
		}, "Renders a DearPyGui frame. Should be called within a user's event loop. Must first call setup_dearpygui outside of event loop.") });

		parsers->insert({ "cleanup_dearpygui", mvPythonParser({
		}, "Cleans up DearPyGui after calling setup_dearpygui.") });

		parsers->insert({ "stop_dearpygui", mvPythonParser({
		}, "Stops DearPyGui.") });

		parsers->insert({ "get_total_time", mvPythonParser({
		}, "Returns total time since app started.", "float") });

		parsers->insert({ "get_delta_time", mvPythonParser({
		}, "Returns time since last frame.", "float") });

		parsers->insert({ "get_dearpygui_version", mvPythonParser({
		}, "Returns the current version of Dear PyGui.", "str") });

	}

	PyObject* mvApp::end(PyObject* self, PyObject* args, PyObject* kwargs)
	{
		std::lock_guard<std::mutex> lk(mvApp::GetApp()->getMutex());
		mvApp::GetApp()->getItemRegistry().popParent();
		return GetPyNone();
	}

	PyObject* mvApp::enable_docking(PyObject* self, PyObject* args, PyObject* kwargs)
	{
		int shift_only = true;
		int dockspace = false;

		if (!(mvApp::GetApp()->getParsers())["enable_docking"].parse(args, kwargs, __FUNCTION__,
			&shift_only, &dockspace))
			return GetPyNone();

		mvApp::GetApp()->getCallbackRegistry().submit([=]()
			{
				mvApp::GetApp()->turnOnDocking(shift_only, dockspace);
			});

		return GetPyNone();
	}

	PyObject* mvApp::is_dearpygui_running(PyObject* self, PyObject* args, PyObject* kwargs)
	{
		return ToPyBool(mvApp::IsAppStarted());
	}

	PyObject* mvApp::setup_dearpygui(PyObject* self, PyObject* args, PyObject* kwargs)
	{
		Py_BEGIN_ALLOW_THREADS;
		mvLog::Init();

		if (mvApp::IsAppStarted())
		{
			ThrowPythonException("Cannot call \"setup_dearpygui\" while a Dear PyGUI app is already running.");
			return GetPyNone();
		}

		s_started = true;
		GetApp()->m_future = std::async(std::launch::async, []() {return GetApp()->m_callbackRegistry->runCallbacks(); });

		MV_CORE_INFO("application starting");

		Py_END_ALLOW_THREADS;

		return GetPyNone();
	}

	PyObject* mvApp::render_dearpygui_frame(PyObject* self, PyObject* args, PyObject* kwargs)
	{

		Py_BEGIN_ALLOW_THREADS;
		auto window = mvApp::GetApp()->getViewport();
		window->renderFrame();
		Py_END_ALLOW_THREADS;

		return GetPyNone();
	}

	PyObject* mvApp::cleanup_dearpygui(PyObject* self, PyObject* args, PyObject* kwargs)
	{
		Py_BEGIN_ALLOW_THREADS;
		mvApp::GetApp()->cleanup();
		mvApp::DeleteApp();
		mvEventBus::Reset();
		mvAppLog::Clear();
		Py_END_ALLOW_THREADS;

		return GetPyNone();
	}

	PyObject* mvApp::stop_dearpygui(PyObject* self, PyObject* args, PyObject* kwargs)
	{
		mvApp::StopApp();
		auto viewport = mvApp::GetApp()->getViewport();
		if (viewport)
			viewport->stop();
		return GetPyNone();
	}

	PyObject* mvApp::get_total_time(PyObject* self, PyObject* args, PyObject* kwargs)
	{
		std::lock_guard<std::mutex> lk(mvApp::GetApp()->getMutex());
		return ToPyFloat((float)mvApp::GetApp()->getTotalTime());
	}

	PyObject* mvApp::get_delta_time(PyObject* self, PyObject* args, PyObject* kwargs)
	{
		std::lock_guard<std::mutex> lk(mvApp::GetApp()->getMutex());
		return ToPyFloat(mvApp::GetApp()->getDeltaTime());

	}

	PyObject* mvApp::get_dearpygui_version(PyObject* self, PyObject* args, PyObject* kwargs)
	{
		return ToPyString(mvApp::GetApp()->GetVersion());
	}

}
