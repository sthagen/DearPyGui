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
#include "mvAppLog.h"
#include "mvEvents.h"
#include "mvDrawList.h"

namespace Marvel {

	//-----------------------------------------------------------------------------
	// mvWindow
	//-----------------------------------------------------------------------------
	class mvWindow : public mvEventHandler
	{

	public:

		static mvWindow* CreatemvWindow(unsigned width, unsigned height, bool error = false);

		mvWindow(unsigned width, unsigned height, bool error = false);
		virtual ~mvWindow() = default;

		bool onEvent (mvEvent& event) override;
		bool onRender(mvEvent& event);

		mvDrawList& getFrontDrawList() { return m_frontDrawList; }
		mvDrawList& getBackDrawList() { return m_backDrawList; }

		virtual void show       () {}
		virtual void run        () {}
		virtual void setup      () {}
		virtual void prerender  () {}
		virtual void render     () {}
		virtual void renderFrame() {}
		virtual void postrender () {}
		virtual void cleanup    () {}
		virtual void setWindowText(const std::string& name) {}
		
		void stop      () { m_running = false; }
		void setupFonts();

	protected:

		bool              m_running = true;
		mvApp*            m_app     = nullptr;
		bool              m_error   = false;
		unsigned          m_width;
		unsigned          m_height;
		mvDrawList        m_frontDrawList;
		mvDrawList        m_backDrawList;

	};

}
