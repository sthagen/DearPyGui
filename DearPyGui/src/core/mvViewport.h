#pragma once

//-----------------------------------------------------------------------------
// mvWindow
//
//     - This abstract class is just a light wrapper for a platform specific
//       window. It's quite lacking so may need to be extended later.
//
//     - This class may need to be renamed to remove confusion between this
//       window and the mvWindowAppItem class (maybe to viewport?)
//     
//-----------------------------------------------------------------------------

#include "mvApp.h"
#include "mvEvents.h"
#include "cpp.hint"

namespace Marvel {

	class mvViewport
	{

	public:


        static void InsertParser(std::map<std::string, mvPythonParser>* parsers);

        MV_CREATE_COMMAND(show_viewport);
        MV_CREATE_COMMAND(create_viewport);
        MV_CREATE_COMMAND(configure_viewport);
        MV_CREATE_COMMAND(get_viewport_configuration);
        MV_CREATE_COMMAND(is_viewport_created);
        
		// viewport operations
        MV_CREATE_COMMAND(maximize_viewport);
        MV_CREATE_COMMAND(minimize_viewport);

		MV_START_COMMANDS
			MV_ADD_COMMAND(show_viewport)
			MV_ADD_COMMAND(create_viewport)
			MV_ADD_COMMAND(configure_viewport)
			MV_ADD_COMMAND(maximize_viewport)
			MV_ADD_COMMAND(minimize_viewport)
			MV_ADD_COMMAND(get_viewport_configuration)
			MV_ADD_COMMAND(is_viewport_created)
		MV_END_COMMANDS

		static mvViewport* CreateViewport(unsigned width, unsigned height);

		mvViewport(unsigned width, unsigned height);
		virtual ~mvViewport() = default;

		void getConfigDict(PyObject* dict);
		void setConfigDict(PyObject* dict);

		virtual void invalidateObjects() {}

		virtual void show       (bool minimized, bool maximized) {}
		virtual void run        () {}
		virtual void setup      () {}
		virtual void renderFrame() {}

		virtual void maximize() {}
		virtual void minimize() {}
		virtual void restore() {}
		
		void stop() { m_running = false; }
		bool running() const { return m_running; }

		// for use by primary window
		void setActualWidth(int width) { m_actualWidth = width; }
		void setActualHeight(int height) { m_actualHeight = height; }
		void setClientWidth(int width) { m_clientWidth = width; }
		void setClientHeight(int height) { m_clientHeight = height; }
		int getClientWidth() const { return (int)m_clientWidth; }
		int getClientHeight() const { return (int)m_clientHeight; }
		void onResizeEvent();

	protected:

		bool        m_running = true;
		mvApp*      m_app     = nullptr;
		std::string m_title = "DearPyGui";
		std::string m_small_icon;
		std::string m_large_icon;
		mvColor     m_clearColor = mvColor(0, 0, 0, 255);


		// window modes
		bool m_modesDirty = false;
		bool m_vsync = true;
		bool m_resizable = true;
		bool m_alwaysOnTop = false;
		bool m_maximizeBox = true;
		bool m_minimizeBox = true;
		bool m_border = true;
		bool m_caption = true;
		bool m_overlapped = true;

		// position/size
		bool     m_sizeDirty = false;
		bool     m_posDirty = false;
		unsigned m_width;
		unsigned m_minwidth = 250;
		unsigned m_maxwidth = 10000;
		unsigned m_height;
		unsigned m_minheight = 250;
		unsigned m_maxheight = 10000;
		int      m_actualWidth = 1280;
		int      m_actualHeight = 800;
		int      m_clientWidth = 1280;
		int      m_clientHeight = 800;
		int      m_xpos = 100;
		int      m_ypos = 100;
		

	};

}
