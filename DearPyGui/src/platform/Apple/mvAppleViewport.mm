#include "mvAppleViewport.h"
#include <implot.h>
#include "imnodes.h"
#include "mvFontManager.h"
#include "mvToolManager.h"

#define GLFW_INCLUDE_NONE
#define GLFW_EXPOSE_NATIVE_COCOA
#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>

#include "imgui.h"
#include "implot.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_metal.h"
#include <stdio.h>

namespace Marvel {

    id <MTLDevice> mvAppleViewport::device;

    mvViewport* mvViewport::CreateViewport(unsigned width, unsigned height)
	{
		return new mvAppleViewport(width, height);
	}

    static void window_close_callback(GLFWwindow* window)
    {
        mvApp::StopApp();
    }

    static void window_size_callback(GLFWwindow* window, int width, int height)
    {
        mvApp::GetApp()->getViewport()->setActualHeight(height);
        mvApp::GetApp()->getViewport()->setClientHeight(height);
        mvApp::GetApp()->getViewport()->setActualWidth(width);
        mvApp::GetApp()->getViewport()->setClientWidth(width);
        mvApp::GetApp()->getViewport()->onResizeEvent();
    }

    static void glfw_error_callback(int error, const char *description)
    {
        fprintf(stderr, "Glfw Error %d: %s\n", error, description);
    }

    mvAppleViewport::mvAppleViewport(unsigned width, unsigned height)
        : mvViewport(width, height)
    {
    }

    mvAppleViewport::~mvAppleViewport()
    {
        // Cleanup
        ImGui_ImplMetal_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        imnodes::DestroyContext();
        ImPlot::DestroyContext();
        ImGui::DestroyContext();

        glfwDestroyWindow(m_window);
        glfwTerminate();

    }

    void mvAppleViewport::show(bool minimized, bool maximized)
    {

        // Setup window
        glfwSetErrorCallback(glfw_error_callback);
        glfwInitHint(GLFW_COCOA_CHDIR_RESOURCES, GLFW_FALSE);
        glfwInit();

        if (!m_resizable)
            glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
        if(m_alwaysOnTop)
            glfwWindowHint(GLFW_FLOATING, GLFW_TRUE);
        if(maximized)
            glfwWindowHint(GLFW_MAXIMIZED, GLFW_TRUE);
        else if(minimized)
            glfwWindowHint(GLFW_AUTO_ICONIFY, GLFW_TRUE);
        if(!m_caption)
            glfwWindowHint(GLFW_DECORATED, GLFW_FALSE);
        glfwWindowHint(GLFW_COCOA_GRAPHICS_SWITCHING, GLFW_FALSE);


        // Create window with graphics context
        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
        glfwWindowHint(GLFW_COCOA_RETINA_FRAMEBUFFER, GLFW_FALSE);
        m_window = glfwCreateWindow((int)m_actualWidth, (int)m_actualHeight, m_title.c_str(), nullptr, nullptr);
        glfwSetWindowPos(m_window, m_xpos, m_ypos);
        glfwSetWindowSizeLimits(m_window, (int)m_minwidth, (int)m_minheight, (int)m_maxwidth, (int)m_maxheight);


        mvEventBus::Publish(mvEVT_CATEGORY_VIEWPORT, mvEVT_VIEWPORT_RESIZE, {
            CreateEventArgument("actual_width", (int)m_actualWidth),
            CreateEventArgument("actual_height", (int)m_actualHeight),
            CreateEventArgument("client_width", (int)m_actualWidth),
            CreateEventArgument("client_height", (int)m_actualHeight)
                    });

        device = MTLCreateSystemDefaultDevice();;
        m_commandQueue = [device newCommandQueue];

        // Setup Dear ImGui binding
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImPlot::CreateContext();
        imnodes::CreateContext();
        ImGuiIO &io = ImGui::GetIO();
        io.ConfigWindowsMoveFromTitleBarOnly = true;
        io.IniFilename = nullptr;
        (void) io;
        //io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;  // Enable Keyboard Controls
        //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;   // Enable Gamepad Controls

        if(mvApp::GetApp()->m_docking)
            io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

        // Setup style
        ImGui::StyleColorsDark();
        mvApp::SetDefaultTheme();

        ImGui_ImplGlfw_InitForOpenGL(m_window, true);
        ImGui_ImplMetal_Init(device);

        NSWindow *nswin = glfwGetCocoaWindow(m_window);
        m_layer = [CAMetalLayer layer];
        m_layer.device = device;
        m_layer.pixelFormat = MTLPixelFormatBGRA8Unorm;
        nswin.contentView.layer = m_layer;
        nswin.contentView.wantsLayer = YES;

        m_renderPassDescriptor = [MTLRenderPassDescriptor new];

        // Setup callbacks
        glfwSetWindowSizeCallback(m_window, window_size_callback);
        //glfwSetFramebufferSizeCallback(m_window, window_size_callback);
        glfwSetWindowCloseCallback(m_window, window_close_callback);
    }

    void mvAppleViewport::maximize()
	{
        glfwMaximizeWindow(m_window);
	}

	void mvAppleViewport::minimize()
	{
        glfwIconifyWindow(m_window);
	}

    void mvAppleViewport::restore()
    {
        glfwRestoreWindow(m_window);
    }

    void mvAppleViewport::renderFrame()
    {
        m_running = !glfwWindowShouldClose(m_window);

        if(m_posDirty)
        {
            glfwSetWindowPos(m_window, m_xpos, m_ypos);
            m_posDirty = false;
        }

        if(m_sizeDirty)
        {
            glfwSetWindowSizeLimits(m_window, (int)m_minwidth, (int)m_minheight, (int)m_maxwidth, (int)m_maxheight);
            glfwSetWindowSize(m_window, m_actualWidth, m_actualHeight);
            m_sizeDirty = false;
        }

        if(m_modesDirty)
        {
            glfwSetWindowTitle(m_window, m_title.c_str());
            glfwSetWindowAttrib(m_window, GLFW_RESIZABLE, m_resizable ? GLFW_TRUE : GLFW_FALSE);
            glfwSetWindowAttrib(m_window, GLFW_DECORATED, m_caption ? GLFW_TRUE : GLFW_FALSE);
            glfwSetWindowAttrib(m_window, GLFW_FLOATING, m_alwaysOnTop ? GLFW_TRUE : GLFW_FALSE);
            m_modesDirty = false;
        }

        if(glfwGetWindowAttrib(m_window, GLFW_ICONIFIED))
        {
            glfwWaitEvents();
            return;
        }

        @autoreleasepool {
            // Poll and handle events (inputs, window resize, etc.)
            // You can read the io.WantCaptureMouse, io.WantCaptureKeyboard flags to tell if dear imgui wants to use your inputs.
            // - When io.WantCaptureMouse is true, do not dispatch mouse input data to your main application.
            // - When io.WantCaptureKeyboard is true, do not dispatch keyboard input data to your main application.
            // Generally you may always pass all inputs to dear imgui, and hide them from your application based on those two flags.
            glfwPollEvents();

            if (mvToolManager::GetFontManager().isInvalid())
            {
                mvToolManager::GetFontManager().rebuildAtlas();
                ImGui_ImplMetal_DestroyFontsTexture();
                mvToolManager::GetFontManager().updateAtlas();
                ImGui_ImplMetal_CreateFontsTexture(device);
            }

            NSWindow *nswin = glfwGetCocoaWindow(m_window);
            if(nswin.isVisible && (nswin.occlusionState & NSWindowOcclusionStateVisible) == 0)
                usleep(32000u);

            m_layer.displaySyncEnabled = m_vsync;

            int width;
            int height;
            glfwGetFramebufferSize(m_window, &width, &height);
            m_layer.drawableSize = CGSizeMake(width, height);
            id <CAMetalDrawable> drawable = [m_layer nextDrawable];

            m_width = (unsigned)width;
            m_height = (unsigned)height;

            id <MTLCommandBuffer> commandBuffer = [m_commandQueue commandBuffer];
            m_renderPassDescriptor.colorAttachments[0].clearColor = MTLClearColorMake(m_clearColor.r,
                                                                                      m_clearColor.g,
                                                                                      m_clearColor.b,
                                                                                      m_clearColor.a);
            m_renderPassDescriptor.colorAttachments[0].texture = drawable.texture;
            m_renderPassDescriptor.colorAttachments[0].loadAction = MTLLoadActionClear;
            m_renderPassDescriptor.colorAttachments[0].storeAction = MTLStoreActionStore;
            id <MTLRenderCommandEncoder> m_renderEncoder = [commandBuffer renderCommandEncoderWithDescriptor:m_renderPassDescriptor];
            [m_renderEncoder pushDebugGroup:@"ImGui demo"];

            // Start the Dear ImGui frame
            ImGui_ImplMetal_NewFrame(m_renderPassDescriptor);
            ImGui_ImplGlfw_NewFrame();
            ImGui::NewFrame();

            m_app->render();

            glfwGetWindowPos(m_window, &m_xpos, &m_ypos);

            // Rendering
            ImGui::Render();
            ImGui_ImplMetal_RenderDrawData(ImGui::GetDrawData(), commandBuffer, m_renderEncoder);

            [m_renderEncoder popDebugGroup];
            [m_renderEncoder endEncoding];

            [commandBuffer presentDrawable:drawable];
            [commandBuffer commit];

        }
	}

}
