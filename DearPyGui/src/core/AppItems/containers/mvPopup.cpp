#include "mvPopup.h"
#include "mvItemRegistry.h"
#include "mvImGuiThemeScope.h"
#include "mvFontScope.h"
#include "mvPythonExceptions.h"

namespace Marvel {

	void mvPopup::InsertParser(std::map<std::string, mvPythonParser>* parsers)
	{

		{
			mvPythonParser parser(mvPyDataType::String);
			mvAppItem::AddCommonArgs(parser);
			parser.removeArg("source");
			parser.removeArg("before");
			parser.removeArg("label");
			parser.removeArg("callback");
			parser.removeArg("callback_data");
			parser.removeArg("enabled");

			parser.addArg<mvPyDataType::Integer>("mousebutton", mvArgType::KEYWORD_ARG, "1", "The mouse code that will trigger the popup.");
			parser.addArg<mvPyDataType::Bool>("modal", mvArgType::KEYWORD_ARG, "False");

			parser.finalize();

			parsers->insert({ s_command, parser });
		}

		{
			mvPythonParser parser(mvPyDataType::None);
			parser.addArg<mvPyDataType::String>("item");
			parser.finalize();
			parsers->insert({ "close_popup", parser });
		}
	}

	mvPopup::mvPopup(const std::string& name)
		: mvBoolPtrBase(name)
	{
	}

	void mvPopup::closePopup()
	{
		m_close = true;
	}

	void mvPopup::draw(ImDrawList* drawlist, float x, float y)
	{

		ScopedID id(m_parentAddress);
		mvImGuiThemeScope scope(this);
		mvFontScope fscope(this);

		if (m_modal)
		{
			if (ImGui::IsItemHovered() && ImGui::IsMouseReleased(m_button))
				ImGui::OpenPopup(m_name.c_str());

			if (ImGui::BeginPopupModal(m_name.c_str(), nullptr, ImGuiWindowFlags_AlwaysAutoResize))
			{

				if (m_close)
				{
					ImGui::CloseCurrentPopup();
					m_close = false;
				}

				//we do this so that the children dont get the theme
				scope.cleanup();

				for (mvRef<mvAppItem> item : m_children[1])
				{
					// skip item if it's not shown
					if (!item->m_show)
						continue;

					// set item width
					if (item->m_width != 0)
						ImGui::SetNextItemWidth((float)item->m_width);

					item->draw(drawlist, ImGui::GetCursorPosX(), ImGui::GetCursorPosY());

					item->getState().update();
				}

				ImGui::EndPopup();
			}
		}

		else
		{
			if (ImGui::BeginPopupContextItem(m_name.c_str(), m_button))
			{

				//we do this so that the children dont get the theme
				scope.cleanup();

				for (mvRef<mvAppItem> item : m_children[1])
				{
					// skip item if it's not shown
					if (!item->m_show)
						continue;

					// set item width
					if (item->m_width > 0)
						ImGui::SetNextItemWidth((float)item->m_width);

					item->draw(drawlist, x, y);

					item->getState().update();
				}

				// allows this item to have a render callback
				registerWindowFocusing();

				ImGui::EndPopup();
			}
		}
	}

	void mvPopup::handleSpecificKeywordArgs(PyObject* dict)
	{
		if (dict == nullptr)
			return;

		if (PyObject* item = PyDict_GetItemString(dict, "parent"))
		{
			auto parentName = ToString(item);
			auto parent = mvApp::GetApp()->getItemRegistry().getItem(parentName);
			m_parentAddress = parent.get();
		}
		if (PyObject* item = PyDict_GetItemString(dict, "modal")) m_modal = ToBool(item);
		if (PyObject* item = PyDict_GetItemString(dict, "mousebutton")) m_button = ToInt(item);

	}

	void mvPopup::getSpecificConfiguration(PyObject* dict)
	{
		if (dict == nullptr)
			return;

		PyDict_SetItemString(dict, "modal", ToPyBool(m_modal));
		PyDict_SetItemString(dict, "mousebutton", ToPyInt(m_button));
	}

	PyObject* mvPopup::close_popup(PyObject* self, PyObject* args, PyObject* kwargs)
	{
		const char* popup;

		if (!(mvApp::GetApp()->getParsers())["close_popup"].parse(args, kwargs, __FUNCTION__, &popup))
			return GetPyNone();

		std::lock_guard<std::mutex> lk(mvApp::GetApp()->getMutex());

		auto item = mvApp::GetApp()->getItemRegistry().getItem(popup);

		if (item == nullptr)
		{
			std::string message = popup;
			ThrowPythonException(message + " popup does not exist.");
			return GetPyNone();
		}

		mvPopup* pop;
		if (item->getType() == mvAppItemType::mvPopup)
			pop = static_cast<mvPopup*>(item.get());
		else
		{
			ThrowPythonException(std::string(popup) + " is not a popup.");
			return GetPyNone();
		}

		pop->closePopup();

		return GetPyNone();
	}

}