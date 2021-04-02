#pragma once

//-----------------------------------------------------------------------------
// mvApp
//
//     - This class acts as the primary manager for a DearPyGui app,
//       with the following responsibilities:
//
//         * Callback routing
//     
//     - This class can eventually just contain all static members & methods
//     
//-----------------------------------------------------------------------------

#include "mvPython.h"
#include <vector>
#include <map>
#include <stack>
#include <string>
#include <queue>
#include <thread>
#include <future>
#include <atomic>
#include "mvEvents.h"
#include <memory>
#include "mvModule_Core.h"
#include "cpp.hint"

namespace Marvel {

    //-----------------------------------------------------------------------------
    // Forward Declarations
    //-----------------------------------------------------------------------------
    class mvWindowAppItem;
    class mvTextEditor;
    class mvWindow;
    class mvThemeManager;
    class mvFontManager;
    class mvItemRegistry;
    class mvTextureStorage;
    class mvCallbackRegistry;
    struct mvColor;
    enum class mvAppItemType;
    
    //-----------------------------------------------------------------------------
    // mvApp
    //-----------------------------------------------------------------------------
    class mvApp : public mvEventHandler
    {

        friend class mvWindow;
        friend class mvWindowsWindow;
        friend class mvLinuxWindow;
        friend class mvAppleWindow;

    public:

        static void InsertParser(std::map<std::string, mvPythonParser>* parsers);

        MV_CREATE_EXTRA_COMMAND(enable_docking);
        MV_CREATE_EXTRA_COMMAND(set_viewport_size);
        MV_CREATE_EXTRA_COMMAND(get_dearpygui_version);
        MV_CREATE_EXTRA_COMMAND(get_viewport_size);
        MV_CREATE_EXTRA_COMMAND(setup_dearpygui);
        MV_CREATE_EXTRA_COMMAND(render_dearpygui_frame);
        MV_CREATE_EXTRA_COMMAND(cleanup_dearpygui);
        MV_CREATE_EXTRA_COMMAND(get_delta_time);
        MV_CREATE_EXTRA_COMMAND(get_total_time);
        MV_CREATE_EXTRA_COMMAND(set_vsync);
        MV_CREATE_EXTRA_COMMAND(stop_dearpygui);
        MV_CREATE_EXTRA_COMMAND(is_dearpygui_running);
        MV_CREATE_EXTRA_COMMAND(set_viewport_title);
        MV_CREATE_EXTRA_COMMAND(set_viewport_pos);
        MV_CREATE_EXTRA_COMMAND(set_viewport_resizable);
        MV_CREATE_EXTRA_COMMAND(end);

        MV_START_EXTRA_COMMANDS
            MV_ADD_EXTRA_COMMAND(enable_docking);
            MV_ADD_EXTRA_COMMAND(set_viewport_size);
            MV_ADD_EXTRA_COMMAND(get_dearpygui_version);
            MV_ADD_EXTRA_COMMAND(get_viewport_size);
            MV_ADD_EXTRA_COMMAND(setup_dearpygui);
            MV_ADD_EXTRA_COMMAND(render_dearpygui_frame);
            MV_ADD_EXTRA_COMMAND(cleanup_dearpygui);
            MV_ADD_EXTRA_COMMAND(get_delta_time);
            MV_ADD_EXTRA_COMMAND(get_total_time);
            MV_ADD_EXTRA_COMMAND(set_vsync);
            MV_ADD_EXTRA_COMMAND(stop_dearpygui);
            MV_ADD_EXTRA_COMMAND(is_dearpygui_running);
            MV_ADD_EXTRA_COMMAND(set_viewport_title);
            MV_ADD_EXTRA_COMMAND(set_viewport_pos);
            MV_ADD_EXTRA_COMMAND(set_viewport_resizable);
            MV_ADD_EXTRA_COMMAND(end);
        MV_END_EXTRA_COMMANDS

    public:

        mvApp          (const mvApp& other) = delete;
        mvApp          (mvApp&& other)      = delete;
        mvApp operator=(const mvApp& other) = delete;
        mvApp operator=(mvApp&& other)      = delete;

        static mvApp*            GetApp              ();
        static void              DeleteApp           ();
        static const char*       GetVersion          () { return MV_SANDBOX_VERSION; }
        static bool              IsAppStarted        () { return s_started; }
        static void              SetAppStarted       ();
        static void              SetAppStopped       ();
        static void              StopApp             () { s_started = false; } // ugly

        void start(const std::string& primaryWindow);
        void cleanup();

        ~mvApp() override;

        //-----------------------------------------------------------------------------
        // New event handling system
        //-----------------------------------------------------------------------------
        bool onEvent         (mvEvent& event) override;
        bool onViewPortResize(mvEvent& event);

        //-----------------------------------------------------------------------------
        // Rendering
        //-----------------------------------------------------------------------------
        void                     render          (); // actual render loop          

        //-----------------------------------------------------------------------------
        // Managers
        //-----------------------------------------------------------------------------
        mvItemRegistry&          getItemRegistry    ();
        mvTextureStorage&        getTextureStorage  ();
        mvCallbackRegistry&      getCallbackRegistry();
        mvThemeManager&          getThemeManager    ();
        mvFontManager&           getFontManager     ();
        
        //-----------------------------------------------------------------------------
        // App Settings
        //-----------------------------------------------------------------------------
        void                     turnOnDocking     (bool shiftOnly, bool dockSpace);
        void                     setVSync          (bool value) { m_vsync = value; }
        void                     setResizable      (bool value) { m_resizable = value; }			
        void                     setMainPos        (int x, int y);			
        void                     setViewport       (mvWindow* viewport) { m_viewport = viewport; }
        void                     setTitle          (const std::string& title) { m_title = title; }
        
        int                      getActualWidth    () const { return m_actualWidth; }
        int                      getActualHeight   () const { return m_actualHeight; }
        int                      getClientWidth    () const { return m_clientWidth; }
        int                      getClientHeight   () const { return m_clientHeight; }
        mvWindow*                getViewport       ()       { return m_viewport; }
        bool                     getVSync          () const { return m_vsync; }
        bool                     getResizable      () const { return m_resizable; }
       

        //-----------------------------------------------------------------------------
        // Concurrency
        //-----------------------------------------------------------------------------      
        bool                     checkIfMainThread             () const;

        //-----------------------------------------------------------------------------
        // Timing
        //-----------------------------------------------------------------------------
        float                    getDeltaTime() const { return m_deltaTime; }
        double                   getTotalTime() const { return m_time; }

        //-----------------------------------------------------------------------------
        // Other
        //-----------------------------------------------------------------------------
        std::map<std::string, mvPythonParser>& getParsers() { return const_cast<std::map<std::string, mvPythonParser>&>(mvModule_Core::GetModuleParsers()); }
        std::mutex& getMutex() const { return m_mutex; }
            
    private:

        //-----------------------------------------------------------------------------
        // Post Rendering Methods
        //     - actually performs queued operations
        //-----------------------------------------------------------------------------
        void postProfile    ();

        mvApp();
        
    private:

        static mvApp* s_instance;
        static std::atomic_bool s_started;

        // managers
        mvOwnedPtr<mvItemRegistry>                     m_itemRegistry;
        mvOwnedPtr<mvTextureStorage>                   m_textureStorage;
        mvOwnedPtr<mvThemeManager>                     m_themeManager;
        mvOwnedPtr<mvFontManager>                      m_fontManager;
        mvOwnedPtr<mvCallbackRegistry>                 m_callbackRegistry;

                                                     
        // docking                                   
        bool                                         m_docking          = false;
        bool                                         m_dockingShiftOnly = true;
        bool                                         m_dockingViewport  = false;
                                                     
        mvWindow*                                    m_viewport = nullptr;
        int                                          m_actualWidth = 1280;
        int                                          m_actualHeight = 800;
        int                                          m_clientWidth = 1280;
        int                                          m_clientHeight = 800;
        int                                          m_mainXPos = 100;
        int                                          m_mainYPos = 100;
        std::string                                  m_title = "DearPyGui";
        
        // appearance
        bool        m_vsync = true;
        bool        m_resizable = true;

        // timing
        float                        m_deltaTime = 0.0f; // time since last frame
        double                       m_time      = 0.0;  // total time since starting
        
        std::thread::id                  m_mainThreadID;
        mutable std::mutex               m_mutex;
        std::future<bool>                m_future;

    };

}