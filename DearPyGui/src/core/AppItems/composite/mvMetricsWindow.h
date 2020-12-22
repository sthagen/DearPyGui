#pragma once
#include "mvTypeBases.h"
#include "mvAppItem.h"
#include "mvInput.h"

namespace Marvel {

	class mvMetricsWindow : public mvBaseWindowAppitem
	{

		MV_APPITEM_TYPE(mvAppItemType::MetricsWindow, "add_metrics_window")

	public:

		mvMetricsWindow(const std::string& name) 
			: mvBaseWindowAppitem(name)
		{
			m_description.deleteAllowed = false;
		}

		void draw() override
		{
			if (!prerender())
				return;

			ImGuiIO& io = ImGui::GetIO();
			ImGui::Text("Dear PyGui %s", mvApp::GetVersion());
			ImGui::Text("Dear ImGui %s", ImGui::GetVersion());
			ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
			ImGui::Text("%d vertices, %d indices (%d triangles)", io.MetricsRenderVertices, io.MetricsRenderIndices, io.MetricsRenderIndices / 3);
			ImGui::Text("%d active windows (%d visible)", io.MetricsActiveWindows, io.MetricsRenderWindows);
			ImGui::Text("%d active allocations", io.MetricsActiveAllocations);

			if (ImGui::IsWindowFocused())
			{

				float titleBarHeight = ImGui::GetStyle().FramePadding.y * 2 + ImGui::GetFontSize();

				// update mouse
				ImVec2 mousePos = ImGui::GetMousePos();
				float x = mousePos.x - ImGui::GetWindowPos().x;
				float y = mousePos.y - ImGui::GetWindowPos().y - titleBarHeight;
				mvInput::setMousePosition(x, y);

				if (mvApp::GetApp()->getItemRegistry().getActiveWindow() != "metrics##standard")
					mvEventBus::Publish(mvEVT_CATEGORY_ITEM, mvEVT_ACTIVE_WINDOW, { CreateEventArgument("WINDOW", std::string("metrics##standard")) });

			}

			ImGui::End();
		}

	};

}