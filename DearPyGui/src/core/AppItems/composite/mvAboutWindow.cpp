#include "mvAboutWindow.h"
#include "mvTypeBases.h"
#include "mvAppItem.h"
#include "mvInput.h"
#include "mvModule_Core.h"
#include "mvApp.h"
#include <string>
#include "mvItemRegistry.h"

namespace Marvel {

    void mvAboutWindow::InsertParser(std::map<std::string, mvPythonParser>* parsers)
    {
        parsers->insert({ "add_about_window", mvPythonParser({
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
            {mvPythonDataType::Bool, "no_close", "", "False"},
            {mvPythonDataType::Bool, "no_background", "", "False"},
            {mvPythonDataType::String, "label", "", "''"},
            {mvPythonDataType::Bool, "show", "Attempt to render", "True"},
        }, "Creates an about window.",
            "None", "Containers") });
    }

    mvAboutWindow::mvAboutWindow(const std::string& name)
        : mvBaseWindowAppitem(name)
    {
        m_windowflags = ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoSavedSettings;
        m_description.deleteAllowed = false;
    }

    void mvAboutWindow::draw()
    {
        if (!prerender())
            return;

        ImGui::Text("Dear PyGui %s", mvApp::GetVersion());
        ImGui::Text("Dear ImGui %s", ImGui::GetVersion());
        ImGui::Separator();
        ImGui::TextColored(ImGui::GetStyleColorVec4(ImGuiCol_PlotHistogramHovered), "Authors");
        ImGui::BulletText("Jonathan Hoffstadt");
        ImGui::BulletText("Preston Cothren");
        ImGui::Text("Dear PyGui is licensed under the MIT License, see LICENSE for more information.");
        ImGui::Separator();
        ImGui::TextColored(ImGui::GetStyleColorVec4(ImGuiCol_PlotHistogramHovered), "Partners");
        ImGui::BulletText("Tkachenko Igor");
        ImGui::BulletText("Dean Keinan");
        ImGui::BulletText("He Lingfeng");
        ImGui::BulletText("Nikki Luzader");
        ImGui::BulletText("Ray Heasman");
        ImGui::BulletText("Marco Studer");
        ImGui::Separator();
        ImGui::TextColored(ImGui::GetStyleColorVec4(ImGuiCol_PlotHistogramHovered), "ImPlot");
        ImGui::Text("ImPlot Author Evan Pezent.");
        ImGui::Separator();
        ImGui::TextColored(ImGui::GetStyleColorVec4(ImGuiCol_PlotHistogramHovered), "imnodes");
        ImGui::Text("imnodes Author Johann Muszynski.");
        ImGui::Separator();
        ImGui::TextColored(ImGui::GetStyleColorVec4(ImGuiCol_PlotHistogramHovered), "Dear ImGui");
        ImGui::Text("Dear ImGui Author Omar Cornut and all Dear ImGui contributors.");
        ImGui::Text("Dear ImGui is licensed under the MIT License, see LICENSE for more information.");

        static bool show_config_info = false;
        ImGui::Checkbox("Config/Build Information", &show_config_info);
        if (show_config_info)
        {
            ImGuiIO& io = ImGui::GetIO();
            ImGuiStyle& style = ImGui::GetStyle();

            bool copy_to_clipboard = ImGui::Button("Copy to clipboard");
            ImGui::BeginChildFrame(ImGui::GetID("cfginfos"), ImVec2(0, ImGui::GetTextLineHeightWithSpacing() * 18), ImGuiWindowFlags_NoMove);
            if (copy_to_clipboard)
            {
                ImGui::LogToClipboard();
                ImGui::LogText("```\n"); // Back quotes will make the text appears without formatting when pasting to GitHub
            }

            ImGui::Text("Dear ImGui %s (%d)", IMGUI_VERSION, IMGUI_VERSION_NUM);
            ImGui::Separator();
            ImGui::Text("sizeof(size_t): %d, sizeof(ImDrawIdx): %d, sizeof(ImDrawVert): %d", (int)sizeof(size_t), (int)sizeof(ImDrawIdx), (int)sizeof(ImDrawVert));
            ImGui::Text("define: __cplusplus=%d", (int)__cplusplus);
            ImGui::Text("define: _WIN32");
            ImGui::Text("define: _WIN64");
    #if defined (_WIN32)
            ImGui::Text("define: _MSC_VER=%d", _MSC_VER);
    #endif
            ImGui::Separator();
            ImGui::Text("io.BackendPlatformName: %s", io.BackendPlatformName ? io.BackendPlatformName : "NULL");
            ImGui::Text("io.BackendRendererName: %s", io.BackendRendererName ? io.BackendRendererName : "NULL");
            ImGui::Text("io.ConfigFlags: 0x%08X", io.ConfigFlags);
            if (io.ConfigFlags & ImGuiConfigFlags_NavEnableKeyboard)        ImGui::Text(" NavEnableKeyboard");
            if (io.ConfigFlags & ImGuiConfigFlags_NavEnableGamepad)         ImGui::Text(" NavEnableGamepad");
            if (io.ConfigFlags & ImGuiConfigFlags_NavEnableSetMousePos)     ImGui::Text(" NavEnableSetMousePos");
            if (io.ConfigFlags & ImGuiConfigFlags_NavNoCaptureKeyboard)     ImGui::Text(" NavNoCaptureKeyboard");
            if (io.ConfigFlags & ImGuiConfigFlags_NoMouse)                  ImGui::Text(" NoMouse");
            if (io.ConfigFlags & ImGuiConfigFlags_NoMouseCursorChange)      ImGui::Text(" NoMouseCursorChange");
            if (io.MouseDrawCursor)                                         ImGui::Text("io.MouseDrawCursor");
            if (io.ConfigMacOSXBehaviors)                                   ImGui::Text("io.ConfigMacOSXBehaviors");
            if (io.ConfigInputTextCursorBlink)                              ImGui::Text("io.ConfigInputTextCursorBlink");
            if (io.ConfigWindowsResizeFromEdges)                            ImGui::Text("io.ConfigWindowsResizeFromEdges");
            if (io.ConfigWindowsMoveFromTitleBarOnly)                       ImGui::Text("io.ConfigWindowsMoveFromTitleBarOnly");
            ImGui::Text("io.BackendFlags: 0x%08X", io.BackendFlags);
            if (io.BackendFlags & ImGuiBackendFlags_HasGamepad)             ImGui::Text(" HasGamepad");
            if (io.BackendFlags & ImGuiBackendFlags_HasMouseCursors)        ImGui::Text(" HasMouseCursors");
            if (io.BackendFlags & ImGuiBackendFlags_HasSetMousePos)         ImGui::Text(" HasSetMousePos");
            if (io.BackendFlags & ImGuiBackendFlags_RendererHasVtxOffset)   ImGui::Text(" RendererHasVtxOffset");
            ImGui::Separator();
            ImGui::Text("io.Fonts: %d fonts, Flags: 0x%08X, TexSize: %d,%d", io.Fonts->Fonts.Size, io.Fonts->Flags, io.Fonts->TexWidth, io.Fonts->TexHeight);
            ImGui::Text("io.DisplaySize: %.2f,%.2f", io.DisplaySize.x, io.DisplaySize.y);
            ImGui::Text("io.DisplayFramebufferScale: %.2f,%.2f", io.DisplayFramebufferScale.x, io.DisplayFramebufferScale.y);
            ImGui::Separator();
            ImGui::Text("style.WindowPadding: %.2f,%.2f", style.WindowPadding.x, style.WindowPadding.y);
            ImGui::Text("style.WindowBorderSize: %.2f", style.WindowBorderSize);
            ImGui::Text("style.FramePadding: %.2f,%.2f", style.FramePadding.x, style.FramePadding.y);
            ImGui::Text("style.FrameRounding: %.2f", style.FrameRounding);
            ImGui::Text("style.FrameBorderSize: %.2f", style.FrameBorderSize);
            ImGui::Text("style.ItemSpacing: %.2f,%.2f", style.ItemSpacing.x, style.ItemSpacing.y);
            ImGui::Text("style.ItemInnerSpacing: %.2f,%.2f", style.ItemInnerSpacing.x, style.ItemInnerSpacing.y);

            if (copy_to_clipboard)
            {
                ImGui::LogText("\n```\n");
                ImGui::LogFinish();
            }
            ImGui::EndChildFrame();
        }

        if (ImGui::IsWindowFocused())
        {

            float titleBarHeight = ImGui::GetStyle().FramePadding.y * 2 + ImGui::GetFontSize();

            // update mouse
            ImVec2 mousePos = ImGui::GetMousePos();
            float x = mousePos.x - ImGui::GetWindowPos().x;
            float y = mousePos.y - ImGui::GetWindowPos().y - titleBarHeight;
            mvInput::setMousePosition(x, y);

            if (mvApp::GetApp()->getItemRegistry().getActiveWindow() != m_core_config.name)
                mvEventBus::Publish(mvEVT_CATEGORY_ITEM, mvEVT_ACTIVE_WINDOW, { CreateEventArgument("WINDOW", m_core_config.name) });
        }

        ImGui::End();
        
    }


#ifdef MV_CPP
#else
    PyObject* add_about_window(PyObject* self, PyObject* args, PyObject* kwargs)
    {
        const char* name;
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
        int noclose = false;
        int no_background = false;

        const char* label = "";
        int show = true;

        if (!(mvApp::GetApp()->getParsers())["add_about_window"].parse(args, kwargs, __FUNCTION__, &name, &width,
            &height, &x_pos, &y_pos, &autosize, &no_resize, &no_title_bar, &no_move, &no_scrollbar,
            &no_collapse, &horizontal_scrollbar, &no_focus_on_appearing, &no_bring_to_front_on_focus,
            &noclose, &no_background, &label, &show))
            return ToPyBool(false);

        auto item = CreateRef<mvAboutWindow>(name);

        item->checkConfigDict(kwargs);
        item->setConfigDict(kwargs);
        item->setExtraConfigDict(kwargs);

        if (mvApp::GetApp()->getItemRegistry().addItemWithRuntimeChecks(item, "", ""))
        {
            mvApp::GetApp()->getItemRegistry().pushParent(item);
            if (!show)
                item->hide();

        }

        return GetPyNone();
    }
#endif // 

}
