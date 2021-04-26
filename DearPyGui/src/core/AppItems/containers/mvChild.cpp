#include "mvChild.h"
#include "mvInput.h"
#include "mvApp.h"
#include "mvItemRegistry.h"
#include "mvImGuiThemeScope.h"
#include "mvFontScope.h"

namespace Marvel {

	void mvChild::InsertParser(std::map<std::string, mvPythonParser>* parsers)
	{
		mvPythonParser parser(mvPyDataType::String);
		mvAppItem::AddCommonArgs(parser);
		parser.removeArg("source");
		parser.removeArg("label");
		parser.removeArg("callback");
		parser.removeArg("callback_data");
		parser.removeArg("enabled");

		parser.addArg<mvPyDataType::Bool>("border", mvArgType::KEYWORD_ARG, "True");
		parser.addArg<mvPyDataType::Bool>("autosize_x", mvArgType::KEYWORD_ARG, "False", "Autosize the window to fit it's items in the x.");
		parser.addArg<mvPyDataType::Bool>("autosize_y", mvArgType::KEYWORD_ARG, "False", "Autosize the window to fit it's items in the y.");
		parser.addArg<mvPyDataType::Bool>("no_scrollbar", mvArgType::KEYWORD_ARG, "False", " Disable scrollbars (window can still scroll with mouse or programmatically)");
		parser.addArg<mvPyDataType::Bool>("horizontal_scrollbar", mvArgType::KEYWORD_ARG, "False", "Allow horizontal scrollbar to appear (off by default).");
		parser.addArg<mvPyDataType::Bool>("menubar", mvArgType::KEYWORD_ARG, "False");

		parser.finalize();

		parsers->insert({ s_command, parser });
	}

	mvChild::mvChild(const std::string& name)
		: mvBoolPtrBase(name)
	{
	}

	void mvChild::addFlag(ImGuiWindowFlags flag)
	{
		m_windowflags |= flag;
	}

	void mvChild::removeFlag(ImGuiWindowFlags flag)
	{
		m_windowflags &= ~flag;
	}

	void mvChild::draw(ImDrawList* drawlist, float x, float y)
	{
		ScopedID id;
		mvImGuiThemeScope scope(this);
		mvFontScope fscope(this);

		ImGui::BeginChild(m_label.c_str(), ImVec2(m_autosize_x ? 0 : (float)m_width, m_autosize_y ? 0 : (float)m_height), m_border, m_windowflags);

		//we do this so that the children dont get the theme
		scope.cleanup();

		for (auto& item : m_children[1])
		{
			// skip item if it's not shown
			if (!item->m_show)
				continue;

			if (item->m_focusNextFrame)
			{
				ImGui::SetKeyboardFocusHere();
				item->m_focusNextFrame = false;
			}

			auto oldCursorPos = ImGui::GetCursorPos();
			if (item->m_dirtyPos)
				ImGui::SetCursorPos(item->getState().getItemPos());

			item->getState().setPos({ ImGui::GetCursorPosX(), ImGui::GetCursorPosY()});

			// set item width
			if (item->m_width != 0)
				ImGui::SetNextItemWidth((float)item->m_width);

			item->draw(drawlist, ImGui::GetCursorPosX(), ImGui::GetCursorPosY());

			if (item->m_dirtyPos)
				ImGui::SetCursorPos(oldCursorPos);

			item->getState().update();
		}

		// allows this item to have a render callback
		registerWindowFocusing();

		m_width = (int)ImGui::GetWindowWidth();
		m_height = (int)ImGui::GetWindowHeight();

		ImGui::EndChild();
	}

	void mvChild::handleSpecificKeywordArgs(PyObject* dict)
	{
		if (dict == nullptr)
			return;
		 
		if (PyObject* item = PyDict_GetItemString(dict, "border")) m_border = ToBool(item);
		if (PyObject* item = PyDict_GetItemString(dict, "autosize_x")) m_autosize_x = ToBool(item);
		if (PyObject* item = PyDict_GetItemString(dict, "autosize_y")) m_autosize_y = ToBool(item);

		// helper for bit flipping
		auto flagop = [dict](const char* keyword, int flag, int& flags)
		{
			if (PyObject* item = PyDict_GetItemString(dict, keyword)) ToBool(item) ? flags |= flag : flags &= ~flag;
		};

		// window flags
		flagop("no_scrollbar", ImGuiWindowFlags_NoScrollbar, m_windowflags);
		flagop("horizontal_scrollbar", ImGuiWindowFlags_HorizontalScrollbar, m_windowflags);
		flagop("menubar", ImGuiWindowFlags_MenuBar, m_windowflags);
	}

	void mvChild::getSpecificConfiguration(PyObject* dict)
	{
		if (dict == nullptr)
			return;
		 
		PyDict_SetItemString(dict, "border", ToPyBool(m_border));
		PyDict_SetItemString(dict, "autosize_x", ToPyBool(m_autosize_x));
		PyDict_SetItemString(dict, "autosize_y", ToPyBool(m_autosize_y));

		// helper for bit flipping
		auto checkbitset = [dict](const char* keyword, int flag, const int& flags)
		{
			PyDict_SetItemString(dict, keyword, ToPyBool(flags & flag));
		};

		// window flags
		checkbitset("no_scrollbar", ImGuiWindowFlags_NoScrollbar, m_windowflags);
		checkbitset("horizontal_scrollbar", ImGuiWindowFlags_HorizontalScrollbar, m_windowflags);
		checkbitset("menubar", ImGuiWindowFlags_MenuBar, m_windowflags);
	}

}