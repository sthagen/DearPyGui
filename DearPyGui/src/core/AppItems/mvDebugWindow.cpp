#include "mvDebugWindow.h"
#include "core/mvEvents.h"
#include <misc/cpp/imgui_stdlib.h>
#include "mvApp.h"
#include "mvInput.h"
#include "Registries/mvDataStorage.h"
#include "Registries/mvTextureStorage.h"
#include "Registries/mvValueStorage.h"
#include "PythonUtilities/mvPythonTranslator.h"

namespace Marvel {

	static void DebugItem(const char* label, const char* item)
	{
		ImGui::Text("%s", label);
		ImGui::SameLine();
		ImGui::TextColored(ImVec4(1.0f, 0.0f, 1.0f, 1.0f), "%s", item);
	}

	static void DebugItem(const char* label, float x)
	{
		ImGui::Text("%s", label);
		ImGui::SameLine();
		ImGui::TextColored(ImVec4(1.0f, 0.0f, 1.0f, 1.0f), "%s", std::to_string(x).c_str());
	}

	static void DebugItem(const char* label, float x, float y)
	{
		ImGui::Text("%s", label);
		ImGui::SameLine();
		ImGui::TextColored(ImVec4(1.0f, 0.0f, 1.0f, 1.0f), "%s", (std::to_string(x) + ", " + std::to_string(y)).c_str());
	}

	void mvDebugWindow::renderItem(mvAppItem* item)
	{
		

		if (item->getDescription().container)
		{
			std::string container = item->getName() + "*";

			ImGui::PushID(item);
			if (ImGui::TreeNodeEx(container.c_str()))
			{
				
				auto stringPos = item->getName().find_first_not_of("##");
				if (stringPos != std::string::npos && stringPos > 0)
				{
					ImGui::PushID(item);
					if (ImGui::Selectable(item->getName().substr().erase(0, 2).c_str(), 
						item->getName() == m_selectedItem && ImGui::GetID(item->getName().substr().erase(0, 2).c_str()) == m_selectedID))
					{
						m_selectedItem = item->getName();
						m_selectedID = ImGui::GetID(item->getName().substr().erase(0, 2).c_str());
					}
					ImGui::PopID();
				}
				else
				{
					ImGui::PushID(item);
					if (ImGui::Selectable(item->getName().c_str(),
						item->getName() == m_selectedItem && ImGui::GetID(item->getName().c_str()) == m_selectedID))
					{
						m_selectedItem = item->getName();
						m_selectedID = ImGui::GetID(item->getName().c_str());
					}
					ImGui::PopID();
				}			

				for (mvAppItem* child : item->getChildren())
					renderItem(child);

				ImGui::TreePop();
			}
			ImGui::PopID();
		}
		else
		{
			auto stringPos = item->getName().find_first_not_of("##");
			if (stringPos != std::string::npos && stringPos > 0)
			{
				ImGui::PushID(item);
				if (ImGui::Selectable(item->getName().substr().erase(0, 2).c_str(),
					item->getName() == m_selectedItem && ImGui::GetID(item->getName().substr().erase(0, 2).c_str()) == m_selectedID))
				{
					m_selectedItem = item->getName();
					m_selectedID = ImGui::GetID(item->getName().substr().erase(0, 2).c_str());
				}
				ImGui::PopID();
			}
			else
			{
				ImGui::PushID(item);
				if (ImGui::Selectable(item->getName().c_str(),
					item->getName() == m_selectedItem && ImGui::GetID(item->getName().c_str()) == m_selectedID))
				{
					m_selectedItem = item->getName();
					m_selectedID = ImGui::GetID(item->getName().c_str());
				}
				ImGui::PopID();
			}
			
		}

		
	}

	void mvDebugWindow::draw()
	{
		if (!prerender())
			return;

		static char ts[6] = "True";
		static char fs[6] = "False";
		static std::string commandstring = "set_theme(\"Light\")";

		ImGuiIO& io = ImGui::GetIO();

		auto app = mvApp::GetApp();

		if (ImGui::BeginTabBar("Main Tabbar"))
		{
			if (ImGui::BeginTabItem("App State"))
			{

				ImGui::PushItemWidth(200);
				ImGui::BeginGroup();
				ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
				ImGui::Text("%d vertices, %d indices (%d triangles)", io.MetricsRenderVertices, io.MetricsRenderIndices, io.MetricsRenderIndices / 3);
				ImGui::Text("%d active allocations", io.MetricsActiveAllocations);
				DebugItem("DearPyGui Version: ", mvApp::GetVersion());
				DebugItem("ImGui Version: ", IMGUI_VERSION);
				DebugItem("Stored Data: ", std::to_string(mvDataStorage::GetDataCount()).c_str());
				DebugItem("Stored Textures: ", std::to_string(mvTextureStorage::GetTextureCount()).c_str());
				DebugItem("Threads Active: ", std::to_string(app->getThreadCount()).c_str());
				DebugItem("Threadpool Timeout: ", std::to_string(app->getThreadPoolTimeout()).c_str());
				DebugItem("Threadpool Active: ", app->usingThreadPool() ? ts : fs);
				DebugItem("Threadpool High: ", app->usingThreadPoolHighPerformance() ? ts : fs);
				ImGui::Separator();
				DebugItem("Int Values", std::to_string(mvValueStorage::s_ints.size()).c_str());
				DebugItem("Int2 Values", std::to_string(mvValueStorage::s_int2s.size()).c_str());
				DebugItem("Int3 Values", std::to_string(mvValueStorage::s_int3s.size()).c_str());
				DebugItem("Int4 Values", std::to_string(mvValueStorage::s_int4s.size()).c_str());
				ImGui::Separator();
				//auto & yy = mvValueStorage::s_refStorage;
				//auto & xx = mvValueStorage::s_floats;
				DebugItem("Float Values", std::to_string(mvValueStorage::s_floats.size()).c_str());
				DebugItem("Float2 Values", std::to_string(mvValueStorage::s_float2s.size()).c_str());
				DebugItem("Float3 Values", std::to_string(mvValueStorage::s_float3s.size()).c_str());
				DebugItem("Float4 Values", std::to_string(mvValueStorage::s_float4s.size()).c_str());
				ImGui::Separator();
				DebugItem("Bool Values", std::to_string(mvValueStorage::s_bools.size()).c_str());
				DebugItem("String Values", std::to_string(mvValueStorage::s_strings.size()).c_str());
				DebugItem("Times Values", std::to_string(mvValueStorage::s_times.size()).c_str());
				DebugItem("ImTimes Values", std::to_string(mvValueStorage::s_imtimes.size()).c_str());


				ImGui::EndGroup();
				ImGui::PopItemWidth();

				ImGui::EndTabItem();
			}

			if (ImGui::BeginTabItem("Input Polling"))
			{

				ImGui::PushItemWidth(200);
				ImGui::BeginGroup();

				auto mousepos = mvInput::getMousePosition();
				DebugItem("Active Window: ", app->getActiveWindow().c_str());
				DebugItem("Local Mouse Position:", mousepos.x, mousepos.y);
				DebugItem("Global Mouse Position:", io.MousePos.x, io.MousePos.y);
				DebugItem("Plot Mouse Position:", mvInput::getPlotMousePosition().x, mvInput::getPlotMousePosition().y);
				DebugItem("Mouse Drag Delta:", mvInput::getMouseDragDelta().x, mvInput::getMouseDragDelta().y);
				DebugItem("Mouse Drag Threshold:", mvInput::getMouseDragThreshold());

				ImGui::Spacing();
				ImGui::Spacing();
				ImGui::Text("ImGui State Inputs");

				ImGui::Text("Mouse delta: (%g, %g)", io.MouseDelta.x, io.MouseDelta.y);
				ImGui::Text("Mouse down:");     for (int i = 0; i < IM_ARRAYSIZE(io.MouseDown); i++) if (io.MouseDownDuration[i] >= 0.0f) { ImGui::SameLine(); ImGui::Text("b%d (%.02f secs)", i, io.MouseDownDuration[i]); }
				ImGui::Text("Mouse clicked:");  for (int i = 0; i < IM_ARRAYSIZE(io.MouseDown); i++) if (ImGui::IsMouseClicked(i)) { ImGui::SameLine(); ImGui::Text("b%d", i); }
				ImGui::Text("Mouse dblclick:"); for (int i = 0; i < IM_ARRAYSIZE(io.MouseDown); i++) if (ImGui::IsMouseDoubleClicked(i)) { ImGui::SameLine(); ImGui::Text("b%d", i); }
				ImGui::Text("Mouse released:"); for (int i = 0; i < IM_ARRAYSIZE(io.MouseDown); i++) if (ImGui::IsMouseReleased(i)) { ImGui::SameLine(); ImGui::Text("b%d", i); }
				ImGui::Text("Mouse wheel: %.1f", io.MouseWheel);

				ImGui::Text("Keys down:");      for (int i = 0; i < IM_ARRAYSIZE(io.KeysDown); i++) if (io.KeysDownDuration[i] >= 0.0f) { ImGui::SameLine(); ImGui::Text("%d (0x%X) (%.02f secs)", i, i, io.KeysDownDuration[i]); }
				ImGui::Text("Keys pressed:");   for (int i = 0; i < IM_ARRAYSIZE(io.KeysDown); i++) if (ImGui::IsKeyPressed(i)) { ImGui::SameLine(); ImGui::Text("%d (0x%X)", i, i); }
				ImGui::Text("Keys release:");   for (int i = 0; i < IM_ARRAYSIZE(io.KeysDown); i++) if (ImGui::IsKeyReleased(i)) { ImGui::SameLine(); ImGui::Text("%d (0x%X)", i, i); }
				ImGui::Text("Keys mods: %s%s%s%s", io.KeyCtrl ? "CTRL " : "", io.KeyShift ? "SHIFT " : "", io.KeyAlt ? "ALT " : "", io.KeySuper ? "SUPER " : "");
				ImGui::Text("Chars queue:");    for (int i = 0; i < io.InputQueueCharacters.Size; i++) { ImWchar c = io.InputQueueCharacters[i]; ImGui::SameLine();  ImGui::Text("\'%c\' (0x%04X)", (c > ' ' && c <= 255) ? (char)c : '?', c); }

				ImGui::EndGroup();
				ImGui::PopItemWidth();

				ImGui::EndTabItem();
			}

			if (ImGui::BeginTabItem("App Item Layout"))
			{
				auto selectedItem = mvApp::GetApp()->getItemRegistry().getItem(m_selectedItem);
				std::string parentName;

				if (selectedItem == nullptr)
					selectedItem = mvApp::GetApp()->getItemRegistry().getBackWindows()[0];
				
				if (selectedItem->getParent())
					parentName = selectedItem->getParent()->getName();

				std::string width = std::to_string(selectedItem->getWidth());
				std::string height = std::to_string(selectedItem->getHeight());
				std::string awidth = std::to_string(selectedItem->getActualWidth());
				std::string aheight = std::to_string(selectedItem->getActualHeight());
				
				std::string sizex = std::to_string(selectedItem->getState().getItemRectSize().x);
				std::string sizey = std::to_string(selectedItem->getState().getItemRectSize().y);

                ImGui::BeginGroup();

                if (ImGui::ArrowButton("Move Up", ImGuiDir_Up))
					mvEventBus::Publish("APP_ITEM_EVENTS", "MOVE_ITEM_UP",
						{
								CreateEventArgument("ITEM", std::string(m_selectedItem))
						});
                ImGui::SameLine();
                if (ImGui::ArrowButton("Move Down", ImGuiDir_Down))
					mvEventBus::Publish("APP_ITEM_EVENTS", "MOVE_ITEM_DOWN",
						{
								CreateEventArgument("ITEM", std::string(m_selectedItem))
						});
                ImGui::SameLine();
                if (ImGui::Button("Delete"))
                {
					mvEventBus::Publish("APP_ITEM_EVENTS", "DELETE_ITEM",
						{
							{SID("ITEM"), std::string(m_selectedItem)},
							{SID("CHILDREN_ONLY"), false}
						});
                    m_selectedItem = "";
                }
                ImGui::SameLine();
                if (ImGui::Button("Show"))
                    app->getItemRegistry().getItem(m_selectedItem)->show();
                ImGui::SameLine();
                if (ImGui::Button("Hide"))
                    app->getItemRegistry().getItem(m_selectedItem)->hide();

                ImGui::PushItemWidth(200);
                DebugItem("Item Name:", m_selectedItem.c_str());
                DebugItem("Item Type:", selectedItem->getStringType().c_str());
                DebugItem("Container:", selectedItem->getDescription().container ? ts : fs);
                DebugItem("Item Parent:", parentName.c_str());
                DebugItem("Item Width:", width.c_str());
                DebugItem("Item Height:", height.c_str());
				DebugItem("Item Actual Width:", awidth.c_str());
				DebugItem("Item Actual Height:", aheight.c_str());
                DebugItem("Item Size x:", sizex.c_str());
                DebugItem("Item Size y:", sizey.c_str());
                DebugItem("Item Tip:", selectedItem->getTip().c_str());
                DebugItem("Item Popup:", selectedItem->getPopup().c_str());
                DebugItem("Item Show:", selectedItem->isShown() ? ts : fs);
                DebugItem("Item Visible:", selectedItem->getState().isItemVisible() ? ts : fs);
                DebugItem("Item Hovered:", selectedItem->getState().isItemHovered() ? ts : fs);
                DebugItem("Item Active:", selectedItem->getState().isItemActive() ? ts : fs);
                DebugItem("Item Focused:", selectedItem->getState().isItemFocused() ? ts : fs);
                DebugItem("Item Clicked:", selectedItem->getState().isItemClicked() ? ts : fs);
                DebugItem("Item Edited:", selectedItem->getState().isItemEdited() ? ts : fs);
                DebugItem("Item Activated:", selectedItem->getState().isItemActivated() ? ts : fs);
                DebugItem("Item Deactivated:", selectedItem->getState().isItemDeactivated() ? ts : fs);
                DebugItem("Item DeavtivatedAfterEdit:", selectedItem->getState().isItemDeactivatedAfterEdit() ? ts : fs);
                DebugItem("Item ToggledOpen:", selectedItem->getState().isItemToogledOpen() ? ts : fs);
                ImGui::EndGroup();
                ImGui::PopItemWidth();
                ImGui::SameLine();

				ImGui::BeginChild("TreeChild", ImVec2(-1.0f, -1.0f), true);
				for (auto window : mvApp::GetApp()->getItemRegistry().getFrontWindows())
					renderItem(window);
				for (auto window : mvApp::GetApp()->getItemRegistry().getBackWindows())
					renderItem(window);
				ImGui::EndChild();

				ImGui::EndTabItem();
			}

			if (ImGui::BeginTabItem("Commands##debug"))
			{

				static size_t commandselection = 0;
				const char* commanddoc = m_commands[commandselection].second.c_str();
				static ImGuiTextFilter filter;
				filter.Draw();

				ImGui::PushItemWidth(-1);
				ImGui::BeginChild("CommandsChild##debug", ImVec2(400.0f, 400.0f), true);
				ImGui::PushStyleColor(ImGuiCol_Text, { 1.0f, 1.0f, 0.0f, 1.0f });
				for (size_t i = 0; i<m_commands.size(); i++)
				{
					auto& item = m_commands[i];

					if (filter.PassFilter(item.first.c_str()))
					{
						if (ImGui::Selectable(item.first.c_str(), i == commandselection))
							commandselection = i;
					}
				}
				ImGui::PopStyleColor();
				ImGui::EndChild();
				ImGui::SameLine();
				ImGui::BeginChild("CommandsDoc##debug", ImVec2(-1.0f, 400.0f), true);
				ImGui::PushStyleColor(ImGuiCol_Text, { 1.0f, 0.0f, 1.0f, 1.0f });
				ImGui::PushTextWrapPos(500);
				ImGui::Text("%s", commanddoc);
				ImGui::PopStyleColor();
				ImGui::PopTextWrapPos();
				ImGui::EndChild();
				ImGui::InputTextMultiline("Command##debug", &commandstring, ImVec2(-1, -50));
				ImGui::PopItemWidth();
				if (ImGui::Button("Run##debug"))
				{
					std::string command = "from dearpygui.core import *\nfrom dearpygui.simple import *\nfrom dearpygui.demo import *\n" + commandstring;
					PyGILState_STATE gstate = PyGILState_Ensure();
					PyRun_SimpleString(command.c_str());
					PyGILState_Release(gstate);
				}
				ImGui::EndTabItem();
			}

			ImGui::EndTabBar();
		}

		if (ImGui::IsWindowFocused())
		{

			float titleBarHeight = ImGui::GetStyle().FramePadding.y * 2 + ImGui::GetFontSize();

			// update mouse
			mvVec2 oldMousePos = mvInput::getGlobalMousePosition();
			ImVec2 mousePos = ImGui::GetMousePos();
			mvInput::setGlobalMousePosition(mousePos.x, mousePos.y);
			float x = mousePos.x - ImGui::GetWindowPos().x;
			float y = mousePos.y - ImGui::GetWindowPos().y - titleBarHeight;
			mvInput::setMousePosition(x, y);
			mvApp::GetApp()->setActiveWindow("debug##standard");

			// mouse move callback
			if (getMouseMoveCallback() != nullptr)
			{
				if (oldMousePos.x != mousePos.x || oldMousePos.y != mousePos.y)
				{
					mvApp::GetApp()->runCallback(getMouseMoveCallback(), m_name,
						ToPyPair(x, y));
				}
			}

		}
		
		ImGui::End();

	}

}
