#include "mvWindowAppItem.h"
#include "mvInput.h"
#include "mvViewport.h"
#include "mvItemRegistry.h"
#include "mvLog.h"
#include "mvPythonExceptions.h"
#include "mvChild.h"
#include "fonts/mvFont.h"
#include "themes/mvTheme.h"

namespace Marvel {

	void mvWindowAppItem::InsertParser(std::map<std::string, mvPythonParser>* parsers)
	{
		{
			mvPythonParser parser(mvPyDataType::UUID, "Creates a new window for following items to be added to.", { "Containers", "Widgets" }, true);
			mvAppItem::AddCommonArgs(parser, (CommonParserArgs)(
				MV_PARSER_ARG_ID |
				MV_PARSER_ARG_WIDTH |
				MV_PARSER_ARG_HEIGHT |
				MV_PARSER_ARG_INDENT |
				MV_PARSER_ARG_USER_DATA |
				MV_PARSER_ARG_SEARCH_DELAY |
				MV_PARSER_ARG_SHOW)
			);

			parser.addArg<mvPyDataType::IntList>("min_size", mvArgType::KEYWORD_ARG, "[32, 32]", "Minimum window size.");
			parser.addArg<mvPyDataType::IntList>("max_size", mvArgType::KEYWORD_ARG, "[30000, 30000]", "Maximum window size.");

			parser.addArg<mvPyDataType::Bool>("menubar", mvArgType::KEYWORD_ARG, "False");
			parser.addArg<mvPyDataType::Bool>("collapsed", mvArgType::KEYWORD_ARG, "False", "Collapse the window.");
			parser.addArg<mvPyDataType::Bool>("autosize", mvArgType::KEYWORD_ARG, "False", "Autosized the window to fit it's items.");
			parser.addArg<mvPyDataType::Bool>("no_resize", mvArgType::KEYWORD_ARG, "False", "Allows for the window size to be changed or fixed.");
			parser.addArg<mvPyDataType::Bool>("no_title_bar", mvArgType::KEYWORD_ARG, "False", "Title name for the title bar of the window.");
			parser.addArg<mvPyDataType::Bool>("no_move", mvArgType::KEYWORD_ARG, "False", "Allows for the window's position to be changed or fixed.");
			parser.addArg<mvPyDataType::Bool>("no_scrollbar", mvArgType::KEYWORD_ARG, "False", " Disable scrollbars. (window can still scroll with mouse or programmatically)");
			parser.addArg<mvPyDataType::Bool>("no_collapse", mvArgType::KEYWORD_ARG, "False", "Disable user collapsing window by double-clicking on it.");
			parser.addArg<mvPyDataType::Bool>("horizontal_scrollbar", mvArgType::KEYWORD_ARG, "False", "Allow horizontal scrollbar to appear. (off by default)");
			parser.addArg<mvPyDataType::Bool>("no_focus_on_appearing", mvArgType::KEYWORD_ARG, "False", "Disable taking focus when transitioning from hidden to visible state.");
			parser.addArg<mvPyDataType::Bool>("no_bring_to_front_on_focus", mvArgType::KEYWORD_ARG, "False", "Disable bringing window to front when taking focus. (e.g. clicking on it or programmatically giving it focus)");
			parser.addArg<mvPyDataType::Bool>("no_close", mvArgType::KEYWORD_ARG, "False", "Disable user closing the window by removing the close button.");
			parser.addArg<mvPyDataType::Bool>("no_background", mvArgType::KEYWORD_ARG, "False", "Sets Background and border alpha to transparent.");
			parser.addArg<mvPyDataType::Bool>("modal", mvArgType::KEYWORD_ARG, "False", "Fills area behind window according to the theme and disables user ability to interact with anything except the window.");
			parser.addArg<mvPyDataType::Bool>("popup", mvArgType::KEYWORD_ARG, "False", "Fills area behind window according to the theme, removes title bar, collapse and close. Window can be closed by selecting area in the background behind the window.");
			
			parser.addArg<mvPyDataType::Callable>("on_close", mvArgType::KEYWORD_ARG, "None", "Callback ran when window is closed.");

			parser.finalize();

			parsers->insert({ s_command, parser });
		}

		{
			mvPythonParser parser(mvPyDataType::None);
			parser.addArg<mvPyDataType::UUID>("item");
			parser.addArg<mvPyDataType::Float>("value");
			parser.finalize();
			parsers->insert({ "set_x_scroll", parser });
		}

		{
			mvPythonParser parser(mvPyDataType::None);
			parser.addArg<mvPyDataType::UUID>("item");
			parser.addArg<mvPyDataType::Float>("value");
			parser.finalize();
			parsers->insert({ "set_y_scroll", parser });
		}

		{
			mvPythonParser parser(mvPyDataType::Float);
			parser.addArg<mvPyDataType::UUID>("item");
			parser.finalize();
			parsers->insert({ "get_x_scroll", parser });
		}

		{
			mvPythonParser parser(mvPyDataType::Float);
			parser.addArg<mvPyDataType::UUID>("item");
			parser.finalize();
			parsers->insert({ "get_y_scroll", parser });
		}

		{
			mvPythonParser parser(mvPyDataType::Float);
			parser.addArg<mvPyDataType::UUID>("item");
			parser.finalize();
			parsers->insert({ "get_x_scroll_max", parser });
		}

		{
			mvPythonParser parser(mvPyDataType::Float);
			parser.addArg<mvPyDataType::UUID>("item");
			parser.finalize();
			parsers->insert({ "get_y_scroll_max", parser });
		}
	}

	mvWindowAppItem::mvWindowAppItem(mvUUID uuid, bool mainWindow)
		: mvAppItem(uuid), m_mainWindow(mainWindow)
	{
		m_label = "Window###" + std::to_string(m_uuid);
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
		PyObject* callback = m_on_close;
		mvApp::GetApp()->getCallbackRegistry().submitCallback([callback]() {
			if (callback)
				Py_XDECREF(callback);
			});
	}

	void mvWindowAppItem::onChildAdd(mvRef<mvAppItem> item)
	{
		if(item->getType() == mvAppItemType::mvMenuBar)
			m_windowflags |= ImGuiWindowFlags_MenuBar;
	}

	void mvWindowAppItem::onChildRemoved(mvRef<mvAppItem> item)
	{
		if (item->getType() == mvAppItemType::mvMenuBar)
			m_windowflags &= ~ImGuiWindowFlags_MenuBar;
	}

	bool mvWindowAppItem::preDraw()
	{
		if (!m_show)
		{
			if (!DoesItemHaveFlag(this, MV_ITEM_DESC_ALWAYS_DRAW))
				return false;
		}

		if (m_focusNextFrame)
		{
			ImGui::SetKeyboardFocusHere();
			m_focusNextFrame = false;
		}

		if (m_font)
		{
			ImFont* fontptr = static_cast<mvFont*>(m_font.get())->getFontPtr();
			ImGui::PushFont(fontptr);
		}


		if (m_enabled)
		{
			if (auto classTheme = getClassTheme())
			{
				static_cast<mvTheme*>(classTheme.get())->draw(nullptr, 0.0f, 0.0f);
			}
			if (m_theme)
			{
				static_cast<mvTheme*>(m_theme.get())->draw(nullptr, 0.0f, 0.0f);
			}
		}
		else
		{

			if (auto classTheme = getClassDisabledTheme())
			{
				static_cast<mvTheme*>(classTheme.get())->draw(nullptr, 0.0f, 0.0f);
			}

			if (m_disabledTheme)
			{
				static_cast<mvTheme*>(m_disabledTheme.get())->draw(nullptr, 0.0f, 0.0f);
			}
		}

		return true;
	}

	void mvWindowAppItem::postDraw()
	{

		m_state.update();

		if (m_font)
		{
			ImGui::PopFont();
		}

		if (m_enabled)
		{
			if (auto classTheme = getClassTheme())
			{
				static_cast<mvTheme*>(classTheme.get())->customAction();
			}

			if (m_theme)
			{
				static_cast<mvTheme*>(m_theme.get())->customAction();
			}
		}
		else
		{
			if (auto classTheme = getClassDisabledTheme())
			{
				static_cast<mvTheme*>(classTheme.get())->customAction();
			}
			if (m_disabledTheme)
			{
				static_cast<mvTheme*>(m_disabledTheme.get())->customAction();
			}
		}

		// event handlers
		for (auto& item : m_children[3])
		{
			if (!item->preDraw())
				continue;

			item->draw(nullptr, ImGui::GetCursorPosX(), ImGui::GetCursorPosY());
		}

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
			m_oldxpos = m_state.getItemPos().x;
			m_oldypos = m_state.getItemPos().y;
			m_oldWidth = m_width;
			m_oldHeight = m_height;
		}
		else
		{
			m_focusNextFrame = true;
			m_windowflags = m_oldWindowflags;
			if (m_hasMenuBar)
				m_windowflags |= ImGuiWindowFlags_MenuBar;
			m_state.setPos({ m_oldxpos , m_oldypos });
			m_width = m_oldWidth;
			m_height = m_oldHeight;
			m_dirtyPos = true;
			m_dirty_size = true;
		}


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
		m_label = value + "###" + std::to_string(m_uuid);
		m_dirtyPos = true;
		m_dirty_size = true;
	}

	void mvWindowAppItem::draw(ImDrawList* drawlist, float x, float y)
	{
		ScopedID id(m_uuid);

		if (m_mainWindow)
		{
			ImGui::SetNextWindowBgAlpha(1.0f);
			ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f); // to prevent main window corners from showing
			ImGui::SetNextWindowPos(ImVec2(0.0f, 0.0f));
			ImGui::SetNextWindowSize(ImVec2((float)mvApp::GetApp()->getViewport()->getClientWidth(), (float)mvApp::GetApp()->getViewport()->getClientHeight()));
		}

		else if (m_dirtyPos)
		{
			ImGui::SetNextWindowPos(m_state.getItemPos());
			m_dirtyPos = false;
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

		if (m_focusNextFrame)
		{
			ImGui::SetNextWindowFocus();
			m_focusNextFrame = false;
		}

		if (m_modal)
		{
			if (m_popupInit)
			{
				ImGui::OpenPopup(m_label.c_str());
				m_popupInit = false;
			}
			
			if (!ImGui::BeginPopupModal(m_label.c_str(), m_no_close ? nullptr : &m_show, m_windowflags))
			{
				if (m_mainWindow)
					ImGui::PopStyleVar();
				return;
			}
		}

		else if (m_popup)
		{
			if (m_popupInit)
			{
				ImGui::OpenPopup(m_label.c_str());
				m_popupInit = false;
			}

			if (!ImGui::BeginPopup(m_label.c_str(), m_windowflags))
			{
				if (m_mainWindow)
					ImGui::PopStyleVar();
				return;
			}
		}

		else
		{
			if (!ImGui::Begin(m_label.c_str(), m_no_close ? nullptr : &m_show, m_windowflags))
			{
				if (m_mainWindow)
					ImGui::PopStyleVar();

				ImGui::End();
				return;
			}
		}

		ImDrawList* this_drawlist = ImGui::GetWindowDrawList();

		float startx = (float)ImGui::GetCursorScreenPos().x;
		float starty = (float)ImGui::GetCursorScreenPos().y;

		if (m_mainWindow)
			ImGui::PopStyleVar();

		for (auto& item : m_children[0])
		{
			// skip item if it's not shown
			if (!item->m_show)
				continue;

			item->draw(this_drawlist, startx, starty);

			item->getState().update();

		}

		for (auto& item : m_children[1])
		{
			if (!item->preDraw())
				continue;

			item->draw(drawlist, ImGui::GetCursorPosX(), ImGui::GetCursorPosY());
			if(item->m_tracked)
				ImGui::SetScrollHereY(item->m_trackOffset);

			item->postDraw();
		}

		for (auto& item : m_children[2])
		{
			// skip item if it's not shown
			if (!item->m_show)
				continue;

			item->draw(this_drawlist, startx, starty);

			item->getState().update();

		}

		if (m_scrollXSet)
		{
			if (m_scrollX < 0.0f)
				ImGui::SetScrollHereX(1.0f);
			else
				ImGui::SetScrollX(m_scrollX);
			m_scrollXSet = false;
		}

		if (m_scrollYSet)
		{
			if (m_scrollY < 0.0f)
				ImGui::SetScrollHereY(1.0f);
			else
				ImGui::SetScrollY(m_scrollY);
			m_scrollYSet = false;
		}

		m_scrollX = ImGui::GetScrollX();
		m_scrollY = ImGui::GetScrollY();
		m_scrollMaxX = ImGui::GetScrollMaxX();
		m_scrollMaxY = ImGui::GetScrollMaxY();

		m_state.setVisible(true);
		m_state.setHovered(ImGui::IsWindowHovered());
		m_state.setFocused(ImGui::IsWindowFocused());
		m_state.setRectSize({ ImGui::GetWindowSize().x, ImGui::GetWindowSize().y });
		m_state.setActivated(ImGui::IsWindowCollapsed());

		if (ImGui::GetWindowWidth() != (float)m_width || ImGui::GetWindowHeight() != (float)m_height)
		{
			m_width = (int)ImGui::GetWindowWidth();
			m_height = (int)ImGui::GetWindowHeight();
			m_resized = true;
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

			if (mvApp::GetApp()->getItemRegistry().getActiveWindow() != m_uuid)
				mvEventBus::Publish(mvEVT_CATEGORY_ITEM, mvEVT_ACTIVE_WINDOW, { CreateEventArgument("WINDOW", m_uuid) });

		}

		m_state.setPos({ ImGui::GetWindowPos().x , ImGui::GetWindowPos().y });

		if (m_popup || m_modal)
			ImGui::EndPopup();
		else
			ImGui::End();

		m_collapsed = ImGui::IsWindowCollapsed();

		if (!m_show)
			hide();
	}

	void mvWindowAppItem::show()
	{
		m_show = true;
		m_popupInit = true;
	}

	void mvWindowAppItem::hide()
	{
		// shouldn't have to do this but do. Fix later
		m_show = false;
		m_state.setHovered(false);
		m_state.setFocused(false);
		m_state.setActivated(false);
		m_state.setVisible(false);

		mvApp::GetApp()->getCallbackRegistry().addCallback(m_on_close, m_uuid, nullptr, m_user_data);

	}

	void mvWindowAppItem::handleSpecificKeywordArgs(PyObject* dict)
	{
		if (dict == nullptr)
			return;

		if (PyObject* item = PyDict_GetItemString(dict, "modal"))
		{
			m_modal = ToBool(item);
			m_popupInit = true;
		}

		if (PyObject* item = PyDict_GetItemString(dict, "popup"))
		{
			m_popup = ToBool(item);
			m_popupInit = true;
		}

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

		if (PyObject* item = PyDict_GetItemString(dict, "on_close"))
		{
			if (m_on_close)
				Py_XDECREF(m_on_close);
			item = SanitizeCallback(item);
			if (item)
				Py_XINCREF(item);
			m_on_close = item;
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

		m_oldxpos = m_state.getItemPos().x;
		m_oldypos = m_state.getItemPos().y;
		m_oldWidth = m_width;
		m_oldHeight = m_height;
		m_oldWindowflags = m_windowflags;

	}

	void mvWindowAppItem::getSpecificConfiguration(PyObject* dict)
	{
		if (dict == nullptr)
			return;
		 
		PyDict_SetItemString(dict, "modal", ToPyBool(m_modal));
		PyDict_SetItemString(dict, "popup", ToPyBool(m_popup));
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

	PyObject* mvWindowAppItem::set_x_scroll(PyObject* self, PyObject* args, PyObject* kwargs)
	{

		mvUUID item;
		float value;

		if (!(mvApp::GetApp()->getParsers())["set_x_scroll"].parse(args, kwargs, __FUNCTION__,
			&item, &value))
			return GetPyNone();

		if (!mvApp::s_manualMutexControl) std::lock_guard<std::mutex> lk(mvApp::s_mutex);

		auto window = mvApp::GetApp()->getItemRegistry().getItem(item);
		if (window == nullptr)
		{
			mvThrowPythonError(mvErrorCode::mvItemNotFound, "set_x_scroll",
				"Item not found: " + std::to_string(item), nullptr);
			return GetPyNone();
		}

		if (window->getType() == mvAppItemType::mvWindowAppItem)
		{

			auto pWindow = static_cast<mvWindowAppItem*>(window);

			pWindow->m_scrollX = value;
			pWindow->m_scrollXSet = true;
		}
		else if (window->getType() == mvAppItemType::mvChild)
		{
			auto pChild = static_cast<mvChild*>(window);

			pChild->setScrollX(value);
		}
		else
		{
			mvThrowPythonError(mvErrorCode::mvIncompatibleType, "set_x_scroll",
				"Incompatible type. Expected types include: mvWindowAppItem, mvChild", window);
		}
		
		return GetPyNone();
	}

	PyObject* mvWindowAppItem::set_y_scroll(PyObject* self, PyObject* args, PyObject* kwargs)
	{

		mvUUID item;
		float value;

		if (!(mvApp::GetApp()->getParsers())["set_y_scroll"].parse(args, kwargs, __FUNCTION__,
			&item, &value))
			return GetPyNone();

		if (!mvApp::s_manualMutexControl) std::lock_guard<std::mutex> lk(mvApp::s_mutex);

		auto window = mvApp::GetApp()->getItemRegistry().getItem(item);
		if (window == nullptr)
		{
			mvThrowPythonError(mvErrorCode::mvItemNotFound, "set_y_scroll",
				"Item not found: " + std::to_string(item), nullptr);
			return GetPyNone();
		}

		if (window->getType() == mvAppItemType::mvWindowAppItem)
		{

			auto pWindow = static_cast<mvWindowAppItem*>(window);

			pWindow->m_scrollY = value;
			pWindow->m_scrollYSet = true;
		}
		else if (window->getType() == mvAppItemType::mvChild)
		{
			auto pChild = static_cast<mvChild*>(window);

			pChild->setScrollY(value);
		}
		else
		{
			mvThrowPythonError(mvErrorCode::mvIncompatibleType, "set_y_scroll",
				"Incompatible type. Expected types include: mvWindowAppItem, mvChild", window);
		}

		return GetPyNone();
	}

	PyObject* mvWindowAppItem::get_x_scroll(PyObject* self, PyObject* args, PyObject* kwargs)
	{

		mvUUID item;

		if (!(mvApp::GetApp()->getParsers())["get_x_scroll"].parse(args, kwargs, __FUNCTION__,
			&item))
			return GetPyNone();

		if (!mvApp::s_manualMutexControl) std::lock_guard<std::mutex> lk(mvApp::s_mutex);

		auto window = mvApp::GetApp()->getItemRegistry().getItem(item);
		if (window == nullptr)
		{
			mvThrowPythonError(mvErrorCode::mvItemNotFound, "get_x_scroll",
				"Item not found: " + std::to_string(item), nullptr);
			return GetPyNone();
		}

		if (window->getType() == mvAppItemType::mvWindowAppItem)
		{

			auto pWindow = static_cast<mvWindowAppItem*>(window);

			return ToPyFloat(pWindow->m_scrollX);
		}
		else if (window->getType() == mvAppItemType::mvChild)
		{
			auto pChild = static_cast<mvChild*>(window);

			return ToPyFloat(pChild->getScrollX());
		}
		else
		{
			mvThrowPythonError(mvErrorCode::mvIncompatibleType, "get_x_scroll",
				"Incompatible type. Expected types include: mvWindowAppItem, mvChild", window);
		}

		return GetPyNone();
	}

	PyObject* mvWindowAppItem::get_y_scroll(PyObject* self, PyObject* args, PyObject* kwargs)
	{

		mvUUID item;

		if (!(mvApp::GetApp()->getParsers())["get_y_scroll"].parse(args, kwargs, __FUNCTION__,
			&item))
			return GetPyNone();

		if (!mvApp::s_manualMutexControl) std::lock_guard<std::mutex> lk(mvApp::s_mutex);

		auto window = mvApp::GetApp()->getItemRegistry().getItem(item);
		if (window == nullptr)
		{
			mvThrowPythonError(mvErrorCode::mvItemNotFound, s_command,
				"Item not found: " + std::to_string(item), nullptr);
			return GetPyNone();
		}

		if (window->getType() == mvAppItemType::mvWindowAppItem)
		{

			auto pWindow = static_cast<mvWindowAppItem*>(window);

			return ToPyFloat(pWindow->m_scrollY);
		}
		else if (window->getType() == mvAppItemType::mvChild)
		{
			auto pChild = static_cast<mvChild*>(window);

			return ToPyFloat(pChild->getScrollY());
		}
		else
		{
			mvThrowPythonError(mvErrorCode::mvIncompatibleType, "get_y_scroll",
				"Incompatible type. Expected types include: mvWindowAppItem, mvChild", window);
		}

		return GetPyNone();
	}

	PyObject* mvWindowAppItem::get_x_scroll_max(PyObject* self, PyObject* args, PyObject* kwargs)
	{

		mvUUID item;

		if (!(mvApp::GetApp()->getParsers())["get_x_scroll_max"].parse(args, kwargs, __FUNCTION__,
			&item))
			return GetPyNone();

		if (!mvApp::s_manualMutexControl) std::lock_guard<std::mutex> lk(mvApp::s_mutex);

		auto window = mvApp::GetApp()->getItemRegistry().getItem(item);
		if (window == nullptr)
		{
			mvThrowPythonError(mvErrorCode::mvItemNotFound, s_command,
				"Item not found: " + std::to_string(item), nullptr);
			return GetPyNone();
		}

		if (window->getType() == mvAppItemType::mvWindowAppItem)
		{

			auto pWindow = static_cast<mvWindowAppItem*>(window);

			return ToPyFloat(pWindow->m_scrollMaxX);
		}
		else if (window->getType() == mvAppItemType::mvChild)
		{
			auto pChild = static_cast<mvChild*>(window);

			return ToPyFloat(pChild->getScrollXMax());
		}
		else
		{
			mvThrowPythonError(mvErrorCode::mvIncompatibleType, "get_x_scroll_max",
				"Incompatible type. Expected types include: mvWindowAppItem, mvChild", window);
		}

		return GetPyNone();
	}

	PyObject* mvWindowAppItem::get_y_scroll_max(PyObject* self, PyObject* args, PyObject* kwargs)
	{

		mvUUID item;

		if (!(mvApp::GetApp()->getParsers())["get_y_scroll_max"].parse(args, kwargs, __FUNCTION__,
			&item))
			return GetPyNone();

		if (!mvApp::s_manualMutexControl) std::lock_guard<std::mutex> lk(mvApp::s_mutex);

		auto window = mvApp::GetApp()->getItemRegistry().getItem(item);
		if (window == nullptr)
		{
			mvThrowPythonError(mvErrorCode::mvItemNotFound, s_command,
				"Item not found: " + std::to_string(item), nullptr);
			return GetPyNone();
		}

		if (window->getType() == mvAppItemType::mvWindowAppItem)
		{

			auto pWindow = static_cast<mvWindowAppItem*>(window);

			return ToPyFloat(pWindow->m_scrollMaxY);
		}
		else if (window->getType() == mvAppItemType::mvChild)
		{
			auto pChild = static_cast<mvChild*>(window);

			return ToPyFloat(pChild->getScrollYMax());
		}
		else
		{
			mvThrowPythonError(mvErrorCode::mvIncompatibleType, "set_y_scroll_max",
				"Incompatible type. Expected types include: mvWindowAppItem, mvChild", window);
		}

		return GetPyNone();
	}

}