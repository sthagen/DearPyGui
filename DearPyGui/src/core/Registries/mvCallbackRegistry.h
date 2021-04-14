#pragma once
#include <mutex>
#include "mvThreadPool.h"
#include "mvApp.h"
#include "mvAppLog.h"
#include "mvEvents.h"

namespace Marvel {

	static PyObject* SanitizeCallback(PyObject* callback)
	{
		if (callback == Py_None)
			return nullptr;

		return callback;
	}

	class mvCallbackRegistry : public mvEventHandler
	{

		static constexpr const int s_MaxNumberOfCalls = 50;

		struct NewCallback
		{
			std::string sender;
			PyObject* callback;   // name of function to run
			PyObject* data;       // any data need by the function
		};

	public:

		static void InsertParser(std::map<std::string, mvPythonParser>* parsers);

		MV_CREATE_EXTRA_COMMAND(set_start_callback);
		MV_CREATE_EXTRA_COMMAND(set_accelerator_callback);
		MV_CREATE_EXTRA_COMMAND(set_exit_callback);
		MV_CREATE_EXTRA_COMMAND(set_mouse_move_callback);
		MV_CREATE_EXTRA_COMMAND(set_mouse_drag_callback);
		MV_CREATE_EXTRA_COMMAND(set_mouse_click_callback);
		MV_CREATE_EXTRA_COMMAND(set_mouse_down_callback);
		MV_CREATE_EXTRA_COMMAND(set_mouse_double_click_callback);
		MV_CREATE_EXTRA_COMMAND(set_key_down_callback);
		MV_CREATE_EXTRA_COMMAND(set_key_press_callback);
		MV_CREATE_EXTRA_COMMAND(set_key_release_callback);
		MV_CREATE_EXTRA_COMMAND(set_mouse_release_callback);
		MV_CREATE_EXTRA_COMMAND(set_resize_callback);
		MV_CREATE_EXTRA_COMMAND(set_mouse_wheel_callback);

		MV_START_EXTRA_COMMANDS
			MV_ADD_EXTRA_COMMAND(set_start_callback);
			MV_ADD_EXTRA_COMMAND(set_accelerator_callback);
			MV_ADD_EXTRA_COMMAND(set_exit_callback);
			MV_ADD_EXTRA_COMMAND(set_mouse_move_callback);
			MV_ADD_EXTRA_COMMAND(set_mouse_drag_callback);
			MV_ADD_EXTRA_COMMAND(set_mouse_click_callback);
			MV_ADD_EXTRA_COMMAND(set_mouse_down_callback);
			MV_ADD_EXTRA_COMMAND(set_mouse_double_click_callback);
			MV_ADD_EXTRA_COMMAND(set_key_down_callback);
			MV_ADD_EXTRA_COMMAND(set_key_press_callback);
			MV_ADD_EXTRA_COMMAND(set_key_release_callback);
			MV_ADD_EXTRA_COMMAND(set_mouse_release_callback);
			MV_ADD_EXTRA_COMMAND(set_resize_callback);
			MV_ADD_EXTRA_COMMAND(set_mouse_wheel_callback);
		MV_END_EXTRA_COMMANDS

	public:

		mvCallbackRegistry();

		bool onEvent   (mvEvent& event) override;
		bool onFrame   (mvEvent& event);
		bool onEndFrame(mvEvent& event);
		bool onInputs  (mvEvent& event);
		bool onRender  (mvEvent& event);

		void runTasks();

        void runCallback      (PyObject* callback, const std::string& sender, PyObject* data = nullptr);
        void addCallback      (PyObject* callback, const std::string& sender, PyObject* data);
		
		bool runCallbacks();

		void stop() { m_running = false; }

		template<typename F, typename ...Args>
		std::future<typename std::invoke_result<F, Args...>::type> submit(F f)
		{

			typedef typename std::invoke_result<F, Args...>::type result_type;
			std::packaged_task<result_type()> task(std::move(f));
			std::future<result_type> res(task.get_future());

			if (mvApp::IsAppStarted())
				m_tasks.push(std::move(task));
			else
				task();

			return res;
		}

		template<typename F, typename ...Args>
		std::future<typename std::invoke_result<F, Args...>::type> submitCallback(F f)
		{

			if (m_callCount > s_MaxNumberOfCalls)
			{
				mvAppLog::LogWarning("Too many callbacks already in the queue.");
				return {};
			}

			m_callCount++;

			typedef typename std::invoke_result<F, Args...>::type result_type;
			std::packaged_task<result_type()> task(std::move(f));
			std::future<result_type> res(task.get_future());

			m_calls.push(std::move(task));

			return res;
		}

		//-----------------------------------------------------------------------------
        // Callbacks
        //----------------------------------------------------------------------------- 
        void setResizeCallback          (PyObject* callback) { m_resizeCallback = SanitizeCallback(callback); }
        void setMouseMoveCallback       (PyObject* callback) { m_mouseMoveCallback = SanitizeCallback(callback); }
        void setOnCloseCallback         (PyObject* callback) { m_onCloseCallback = SanitizeCallback(callback); }
        void setOnStartCallback         (PyObject* callback) { m_onStartCallback = SanitizeCallback(callback); }
        void setAcceleratorCallback     (PyObject* callback) { m_acceleratorCallback = SanitizeCallback(callback); }
        void setMouseClickCallback      (PyObject* callback) { m_mouseClickCallback = SanitizeCallback(callback); }
        void setMouseDownCallback       (PyObject* callback) { m_mouseDownCallback = SanitizeCallback(callback); }
        void setMouseDoubleClickCallback(PyObject* callback) { m_mouseDoubleClickCallback = SanitizeCallback(callback); }
        void setMouseReleaseCallback    (PyObject* callback) { m_mouseReleaseCallback = SanitizeCallback(callback); }
        void setMouseWheelCallback      (PyObject* callback) { m_mouseWheelCallback = SanitizeCallback(callback); }
        void setMouseDragCallback       (PyObject* callback) { m_mouseDragCallback = SanitizeCallback(callback); }
        void setKeyDownCallback         (PyObject* callback) { m_keyDownCallback = SanitizeCallback(callback); }
        void setKeyPressCallback        (PyObject* callback) { m_keyPressCallback = SanitizeCallback(callback); }
        void setKeyReleaseCallback      (PyObject* callback) { m_keyReleaseCallback = SanitizeCallback(callback); }

        [[nodiscard]] PyObject* getResizeCallback          (){ return m_resizeCallback; }
        [[nodiscard]] PyObject* getMouseReleaseCallback    (){ return m_mouseReleaseCallback; }
        [[nodiscard]] PyObject* getMouseClickCallback      (){ return m_mouseClickCallback; }
        [[nodiscard]] PyObject* getMouseDownCallback       (){ return m_mouseDownCallback; }
        [[nodiscard]] PyObject* getMouseDoubleClickCallback(){ return m_mouseDoubleClickCallback; }
        [[nodiscard]] PyObject* getMouseDragCallback       (){ return m_mouseDragCallback; }
        [[nodiscard]] PyObject* getKeyDownCallback         (){ return m_keyDownCallback; }
        [[nodiscard]] PyObject* getKeyPressCallback        (){ return m_keyPressCallback; }
        [[nodiscard]] PyObject* getKeyReleaseCallback      (){ return m_keyReleaseCallback; }
        [[nodiscard]] PyObject* getMouseWheelCallback      (){ return m_mouseWheelCallback; }
        [[nodiscard]] PyObject* getMouseMoveCallback       (){ return m_mouseMoveCallback; }
        [[nodiscard]] PyObject* getOnCloseCallback         (){ return m_onCloseCallback; }
        [[nodiscard]] PyObject* getOnStartCallback         (){ return m_onStartCallback; }
        [[nodiscard]] PyObject* getAcceleratorCallback     (){ return m_acceleratorCallback; }
	
	private:

		// new callback system
		mvQueue<mvFunctionWrapper> m_tasks;
		mvQueue<mvFunctionWrapper> m_calls;
		std::atomic<bool> m_running;
		std::atomic<int> m_callCount = 0;

		// input callbacks
		PyObject* m_mouseDownCallback = nullptr;
		PyObject* m_mouseClickCallback = nullptr;
		PyObject* m_mouseReleaseCallback = nullptr;
		PyObject* m_mouseDoubleClickCallback = nullptr;
		PyObject* m_mouseWheelCallback = nullptr;
		PyObject* m_mouseDragCallback = nullptr;
		PyObject* m_keyDownCallback = nullptr;
		PyObject* m_keyPressCallback = nullptr;
		PyObject* m_keyReleaseCallback = nullptr;
		PyObject* m_resizeCallback = nullptr;
		PyObject* m_mouseMoveCallback = nullptr;
		PyObject* m_onCloseCallback = nullptr;
		PyObject* m_onStartCallback = nullptr;
		PyObject* m_acceleratorCallback = nullptr; // basically the same as the key press callback

	};

}