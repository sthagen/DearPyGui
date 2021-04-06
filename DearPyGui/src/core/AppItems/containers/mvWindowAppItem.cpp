#include "mvWindowAppItem.h"
#include "mvInput.h"
#include "mvViewport.h"
#include "mvItemRegistry.h"
#include "mvImGuiThemeScope.h"
#include "mvFontScope.h"

namespace Marvel {

	void mvWindowAppItem::InsertParser(std::map<std::string, mvPythonParser>* parsers)
	{
		parsers->insert({ s_command, mvPythonParser({
			{mvPythonDataType::Optional},
			{mvPythonDataType::String, "name"},
			{mvPythonDataType::KeywordOnly},
			{mvPythonDataType::Integer, "width", "", "-1"},
			{mvPythonDataType::Integer, "height", "", "-1"},
			{mvPythonDataType::Integer, "x_pos", "x position the window will start at", "200"},
			{mvPythonDataType::Integer, "y_pos", "y position the window will start at", "200"},
			{mvPythonDataType::Bool, "autosize", "Autosized the window to fit it's items.", "False"},
			{mvPythonDataType::Bool, "no_resize", "Allows for the window size to be changed or fixed", "False"},
			{mvPythonDataType::Bool, "no_title_bar", "Title name for the title bar of the window", "False"},
			{mvPythonDataType::Bool, "no_move", "Allows for the window's position to be changed or fixed", "False"},
			{mvPythonDataType::Bool, "no_scrollbar" ," Disable scrollbars (window can still scroll with mouse or programmatically)", "False"},
			{mvPythonDataType::Bool, "no_collapse" ,"Disable user collapsing window by double-clicking on it", "False"},
			{mvPythonDataType::Bool, "horizontal_scrollbar" ,"Allow horizontal scrollbar to appear (off by default).", "False"},
			{mvPythonDataType::Bool, "no_focus_on_appearing" ,"Disable taking focus when transitioning from hidden to visible state", "False"},
			{mvPythonDataType::Bool, "no_bring_to_front_on_focus" ,"Disable bringing window to front when taking focus (e.g. clicking on it or programmatically giving it focus)", "False"},
			{mvPythonDataType::Bool, "menubar", "", "False"},
			{mvPythonDataType::Bool, "no_close", "", "False"},
			{mvPythonDataType::Bool, "no_background", "", "False"},
			{mvPythonDataType::String, "label", "", "''"},
			{mvPythonDataType::Bool, "show", "Attempt to render", "True"},
			{mvPythonDataType::Bool, "collapsed", "Collapse the window", "False"},
			{mvPythonDataType::Callable, "on_close", "Callback ran when window is closed", "None"},
			{mvPythonDataType::IntList, "min_size", "Minimum window size.", "[32, 32]"},
			{mvPythonDataType::IntList, "max_size", "Maximum window size.", "[30000, 30000]"},
		}, "Creates a new window for following items to be added to.",
			"None", "Containers") });
	}

	mvWindowAppItem::mvWindowAppItem(const std::string& name, bool mainWindow, mvCallable closing_callback)
		: mvAppItem(name), m_mainWindow(mainWindow)
	{
		m_on_close = SanitizeCallback(closing_callback);

		m_width = 500;
		m_height = 500;

		m_oldWindowflags = ImGuiWindowFlags_NoSavedSettings;

		if (mainWindow)
		{
			m_windowflags = ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoSavedSettings
				| ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar;
		}
	}

	mvWindowAppItem::~mvWindowAppItem()
	{
		mvCallable callback = m_on_close;
		mvApp::GetApp()->getCallbackRegistry().submitCallback([callback]() {
			if (callback)
				Py_XDECREF(callback);
			});

	}

	void mvWindowAppItem::setWindowAsMainStatus(bool value)
	{
		m_mainWindow = value;
		if (value)
		{
			m_oldWindowflags = m_windowflags;
			m_windowflags = ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoSavedSettings
				| ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar;

			if (m_hasMenuBar)
				m_windowflags |= ImGuiWindowFlags_MenuBar;
			m_oldxpos = m_xpos;
			m_oldypos = m_ypos;
			m_oldWidth = m_width;
			m_oldHeight = m_height;
		}
		else
		{
			m_focusNextFrame = true;
			m_windowflags = m_oldWindowflags;
			if (m_hasMenuBar)
				m_windowflags |= ImGuiWindowFlags_MenuBar;
			m_xpos = m_oldxpos;
			m_ypos = m_oldypos;
			m_width = m_oldWidth;
			m_height = m_oldHeight;
			m_dirty_pos = true;
			m_dirty_size = true;
		}


	}

	void mvWindowAppItem::setWindowPos(float x, float y)
	{
		m_xpos = (int)x;
		m_ypos = (int)y;
		m_dirty_pos = true;
	}

	void mvWindowAppItem::setWidth(int width) 
	{ 
		m_width = width;
		m_dirty_size = true; 
	}

	void mvWindowAppItem::setHeight(int height) 
	{ 
		m_height = height;
		m_dirty_size = true; 
	}

	void mvWindowAppItem::setLabel(const std::string& value)
	{
		m_specificedlabel = value;
		m_label = value + "###" + m_name;
		m_dirty_pos = true;
		m_dirty_size = true;
	}

	mvVec2 mvWindowAppItem::getWindowPos() const
	{
		return { (float)m_xpos, (float)m_ypos };
	}

	void mvWindowAppItem::setResizeCallback(mvCallable callback)
	{
		m_resize_callback = callback;
	}

	void mvWindowAppItem::draw(ImDrawList* drawlist, float x, float y)
	{
		// shouldn't have to do this but do. Fix later
		if (!m_show)
		{
			m_state.setHovered(false);
			m_state.setFocused(false);
			m_state.setActivated(false);
			m_state.setVisible(false);
			if (!m_closing)
			{
				m_closing = true;
				mvApp::GetApp()->getCallbackRegistry().addCallback(m_on_close, m_name, nullptr);

			}
			return;
		}
		m_closing = false;

		if (m_mainWindow)
		{
			ImGui::SetNextWindowBgAlpha(1.0f);
			ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f); // to prevent main window corners from showing
			ImGui::SetNextWindowPos(ImVec2(0.0f, 0.0f));
			ImGui::SetNextWindowSize(ImVec2((float)mvApp::GetApp()->getViewport()->getClientWidth(), (float)mvApp::GetApp()->getViewport()->getClientHeight()));
		}

		else if (m_dirty_pos)
		{
			ImGui::SetNextWindowPos(ImVec2((float)m_xpos, (float)m_ypos));
			m_dirty_pos = false;
		}

		else if (m_focusNextFrame)
		{
			ImGui::SetNextWindowFocus();
			m_focusNextFrame = false;
		}

		if (m_dirty_size)
		{
			ImGui::SetNextWindowSize(ImVec2((float)m_width, (float)m_height));
			m_dirty_size = false;
		}

		if (m_collapsedDirty)
		{
			ImGui::SetNextWindowCollapsed(m_collapsed);
			m_collapsedDirty = false;
		}

		ImGui::SetNextWindowSizeConstraints(m_min_size, m_max_size);

		ScopedID id;
		mvImGuiThemeScope scope(this);
		mvFontScope fscope(this);

		if (!ImGui::Begin(m_label.c_str(), m_no_close ? nullptr : &m_show, m_windowflags))
		{
			if (m_mainWindow)
				ImGui::PopStyleVar();

			ImGui::End();
			return;
		}

		ImDrawList* this_drawlist = ImGui::GetWindowDrawList();

		float startx = (float)ImGui::GetCursorScreenPos().x;
		float starty = (float)ImGui::GetCursorScreenPos().y;

		//we do this so that the children dont get the theme
		scope.cleanup();

		if (m_mainWindow)
			ImGui::PopStyleVar();

		for (auto& item : m_children0)
		{
			// skip item if it's not shown
			if (!item->m_show)
				continue;

			item->draw(this_drawlist, startx, starty);

			item->getState().update();

		}

		for (auto& item : m_children1)
		{
			// skip item if it's not shown
			if (!item->m_show)
				continue;

			// set item width
			if (item->m_width != 0)
				ImGui::SetNextItemWidth((float)item->m_width);

			item->draw(this_drawlist, ImGui::GetCursorPosX(), ImGui::GetCursorPosY());

			item->getState().update();

		}




		m_state.setVisible(true);
		m_state.setHovered(ImGui::IsWindowHovered());
		m_state.setFocused(ImGui::IsWindowFocused());
		m_state.setRectSize({ ImGui::GetWindowSize().x, ImGui::GetWindowSize().y });
		m_state.setActivated(ImGui::IsWindowCollapsed());

		if (ImGui::GetWindowWidth() != (float)m_width || ImGui::GetWindowHeight() != (float)m_height)
		{
			m_width = (int)ImGui::GetWindowWidth();
			m_height = (int)ImGui::GetWindowHeight();
			mvApp::GetApp()->getCallbackRegistry().addCallback(m_resize_callback, m_name, nullptr);
		}

		m_width = (int)ImGui::GetWindowWidth();
		m_height = (int)ImGui::GetWindowHeight();

		if (m_state.isItemFocused())
		{

			float titleBarHeight = ImGui::GetStyle().FramePadding.y * 2 + ImGui::GetFontSize();

			// update mouse
			ImVec2 mousePos = ImGui::GetMousePos();
			float x = mousePos.x - ImGui::GetWindowPos().x;
			float y = mousePos.y - ImGui::GetWindowPos().y - titleBarHeight;
			mvInput::setMousePosition(x, y);

			if (mvApp::GetApp()->getItemRegistry().getActiveWindow() != m_name)
				mvEventBus::Publish(mvEVT_CATEGORY_ITEM, mvEVT_ACTIVE_WINDOW, { CreateEventArgument("WINDOW", m_name) });

		}

		m_xpos = (int)ImGui::GetWindowPos().x;
		m_ypos = (int)ImGui::GetWindowPos().y;

		ImGui::End();

		m_collapsed = ImGui::IsWindowCollapsed();

	}

	void mvWindowAppItem::setExtraConfigDict(PyObject* dict)
	{
		if (dict == nullptr)
			return;
		 
		if (PyObject* item = PyDict_GetItemString(dict, "x_pos")) setWindowPos((float)ToInt(item), (float)m_ypos);
		if (PyObject* item = PyDict_GetItemString(dict, "y_pos")) setWindowPos((float)m_xpos, (float)ToInt(item));
		if (PyObject* item = PyDict_GetItemString(dict, "no_close")) m_no_close = ToBool(item);
		if (PyObject* item = PyDict_GetItemString(dict, "collapsed"))
		{
			m_collapsedDirty = true;
			m_collapsed = ToBool(item);
		}

		if (PyObject* item = PyDict_GetItemString(dict, "min_size"))
		{
			auto min_size = ToIntVect(item);
			m_min_size = { (float)min_size[0], (float)min_size[1]};
		}

		if (PyObject* item = PyDict_GetItemString(dict, "max_size"))
		{
			auto max_size = ToIntVect(item);
			m_max_size = { (float)max_size[0], (float)max_size[1] };
		}

		// helper for bit flipping
		auto flagop = [dict](const char* keyword, int flag, int& flags)
		{
			if (PyObject* item = PyDict_GetItemString(dict, keyword)) ToBool(item) ? flags |= flag : flags &= ~flag;
		};

		// window flags
		flagop("autosize", ImGuiWindowFlags_AlwaysAutoResize, m_windowflags);
		flagop("no_move", ImGuiWindowFlags_NoMove, m_windowflags);
		flagop("no_resize", ImGuiWindowFlags_NoResize, m_windowflags);
		flagop("no_title_bar", ImGuiWindowFlags_NoTitleBar, m_windowflags);
		flagop("no_scrollbar", ImGuiWindowFlags_NoScrollbar, m_windowflags);
		flagop("no_collapse", ImGuiWindowFlags_NoCollapse, m_windowflags);
		flagop("horizontal_scrollbar", ImGuiWindowFlags_HorizontalScrollbar, m_windowflags);
		flagop("no_focus_on_appearing", ImGuiWindowFlags_NoFocusOnAppearing, m_windowflags);
		flagop("no_bring_to_front_on_focus", ImGuiWindowFlags_NoBringToFrontOnFocus, m_windowflags);
		flagop("menubar", ImGuiWindowFlags_MenuBar, m_windowflags);
		flagop("no_background", ImGuiWindowFlags_NoBackground, m_windowflags);

		m_oldxpos = m_xpos;
		m_oldypos = m_ypos;
		m_oldWidth = m_width;
		m_oldHeight = m_height;
		m_oldWindowflags = m_windowflags;

	}

	void mvWindowAppItem::getExtraConfigDict(PyObject* dict)
	{
		if (dict == nullptr)
			return;
		 
		PyDict_SetItemString(dict, "x_pos", ToPyInt(m_xpos));
		PyDict_SetItemString(dict, "y_pos", ToPyInt(m_ypos));
		PyDict_SetItemString(dict, "no_close", ToPyBool(m_no_close));
		PyDict_SetItemString(dict, "collapsed", ToPyBool(m_collapsed));
		PyDict_SetItemString(dict, "min_size", ToPyPair(m_min_size.x, m_min_size.y));
		PyDict_SetItemString(dict, "max_size", ToPyPair(m_min_size.x, m_min_size.y));

		// helper to check and set bit
		auto checkbitset = [dict](const char* keyword, int flag, const int& flags)
		{
			PyDict_SetItemString(dict, keyword, ToPyBool(flags & flag));
		};

		// window flags
		checkbitset("autosize", ImGuiWindowFlags_AlwaysAutoResize, m_windowflags);
		checkbitset("no_resize", ImGuiWindowFlags_NoResize, m_windowflags);
		checkbitset("no_title_bar", ImGuiWindowFlags_NoTitleBar, m_windowflags);
		checkbitset("no_move", ImGuiWindowFlags_NoMove, m_windowflags);
		checkbitset("no_scrollbar", ImGuiWindowFlags_NoScrollbar, m_windowflags);
		checkbitset("no_collapse", ImGuiWindowFlags_NoCollapse, m_windowflags);
		checkbitset("horizontal_scrollbar", ImGuiWindowFlags_HorizontalScrollbar, m_windowflags);
		checkbitset("no_focus_on_appearing", ImGuiWindowFlags_NoFocusOnAppearing, m_windowflags);
		checkbitset("no_bring_to_front_on_focus", ImGuiWindowFlags_NoBringToFrontOnFocus, m_windowflags);
		checkbitset("menubar", ImGuiWindowFlags_MenuBar, m_windowflags);
		checkbitset("no_background", ImGuiWindowFlags_NoBackground, m_windowflags);
	}

	PyObject* mvWindowAppItem::add_window(PyObject* self, PyObject* args, PyObject* kwargs)
	{
		static int i = 0; i++;
		std::string sname = std::string(std::string("$$DPG_") + s_internal_id + std::to_string(i));
		const char* name = sname.c_str();
		int width = -1;
		int height = -1;
		int x_pos = 200;
		int y_pos = 200;
		int autosize = false;
		int no_resize = false;
		int no_title_bar = false;
		int no_move = false;
		int no_scrollbar = false;
		int no_collapse = false;
		int horizontal_scrollbar = false;
		int no_focus_on_appearing = false;
		int no_bring_to_front_on_focus = false;
		int menubar = false;
		int noclose = false;
		int no_background = false;

		const char* label = "";
		int show = true;
		int collapsed = false;

		PyObject* closing_callback = nullptr;
		PyObject* min_size = PyList_New(2);
		PyList_SetItem(min_size, 0, PyLong_FromLong(-1));
		PyList_SetItem(min_size, 1, PyLong_FromLong(-1));

		PyObject* max_size = PyList_New(2);
		PyList_SetItem(max_size, 0, PyLong_FromLong(-1));
		PyList_SetItem(max_size, 1, PyLong_FromLong(-1));

		if (!(mvApp::GetApp()->getParsers())["add_window"].parse(args, kwargs, __FUNCTION__, &name, &width,
			&height, &x_pos, &y_pos, &autosize, &no_resize, &no_title_bar, &no_move, &no_scrollbar,
			&no_collapse, &horizontal_scrollbar, &no_focus_on_appearing, &no_bring_to_front_on_focus, &menubar,
			&noclose, &no_background, &label, &show, &collapsed, &closing_callback, &min_size, &max_size))
			return ToPyBool(false);

		if (closing_callback)
			Py_XINCREF(closing_callback);

		auto item = CreateRef<mvWindowAppItem>(name, false, closing_callback);

		item->checkConfigDict(kwargs);
		item->setConfigDict(kwargs);
		item->setExtraConfigDict(kwargs);

		if (mvApp::GetApp()->getItemRegistry().addItemWithRuntimeChecks(item, "", ""))
		{
			mvApp::GetApp()->getItemRegistry().pushParent(item);
			if (!show)
				item->hide();

		}

		return ToPyString(name);
	}

}