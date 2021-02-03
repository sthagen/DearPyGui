#pragma once

#include "mvTypeBases.h"

namespace Marvel {

	class mvPopup : public mvBoolPtrBase
	{

	public:

		MV_APPITEM_TYPE(mvAppItemType::Popup, "add_popup")

		mvPopup(const std::string& name, mvAppItem* parentAddress)
			: mvBoolPtrBase(name, false, name), m_parentAddress(parentAddress)
		{
			m_description.container = true;
		}

		void closePopup() { m_close = true; }

		void draw() override
		{

			auto styleManager = m_styleManager.getScopedStyleManager();
			ScopedID id(m_parentAddress);
			mvImGuiThemeScope scope(this);

			if (m_modal)
			{
				if (ImGui::IsItemHovered() && ImGui::IsMouseReleased(m_button))
					ImGui::OpenPopup(m_core_config.name.c_str());

				if (ImGui::BeginPopupModal(m_core_config.name.c_str(), nullptr, ImGuiWindowFlags_AlwaysAutoResize))
				{

					if (m_close)
					{
						ImGui::CloseCurrentPopup();
						m_close = false;
					}

					//we do this so that the children dont get the theme
					scope.cleanup();

					for (mvRef<mvAppItem> item : m_children)
					{
						// skip item if it's not shown
						if (!item->m_core_config.show)
							continue;

						// set item width
						if (item->m_core_config.width != 0)
							ImGui::SetNextItemWidth((float)item->m_core_config.width);

						item->draw();

						item->getState().update();
					}

					ImGui::EndPopup();
				}
			}

			else 
			{
				if (ImGui::BeginPopupContextItem(m_core_config.name.c_str(), m_button))
				{

					//we do this so that the children dont get the theme
					scope.cleanup();

					for (mvRef<mvAppItem> item : m_children)
					{
						// skip item if it's not shown
						if (!item->m_core_config.show)
							continue;

						// set item width
						if (item->m_core_config.width > 0)
							ImGui::SetNextItemWidth((float)item->m_core_config.width);

						item->draw();

						item->getState().update();
					}

					// allows this item to have a render callback
					registerWindowFocusing();

					ImGui::EndPopup();
				}
			}
		}

#ifndef MV_CPP

		void setExtraConfigDict(PyObject* dict) override
		{
			if (dict == nullptr)
				return;
			 
			if (PyObject* item = PyDict_GetItemString(dict, "modal")) m_modal = ToBool(item);
			if (PyObject* item = PyDict_GetItemString(dict, "mousebutton")) m_button = ToInt(item);

		}

		void getExtraConfigDict(PyObject* dict) override
		{
			if (dict == nullptr)
				return;
			 
			PyDict_SetItemString(dict, "modal", ToPyBool(m_modal));
			PyDict_SetItemString(dict, "mousebutton", ToPyInt(m_button));
		}

#endif

	private:

		bool m_modal = false;
		int  m_button = 1;
		mvAppItem* m_parentAddress = nullptr;
		bool m_close = false;

	};

}