#pragma once
#include "mvTypeBases.h"
#include "mvMarvel.h"


namespace Marvel {
	struct mvDebugWindowConfig : public mvAppItemConfig
	{
		
		int x_pos = 200;
		int y_pos = 200;
		bool autosize = false;
		bool no_resize = false;
		bool no_title_bar = false;
		bool no_move = false;
		bool no_scrollbar = false;
		bool no_collapse = false;
		bool horizontal_scrollbar = false;
		bool no_focus_on_appearing = false;
		bool no_bring_to_front_on_focus = false;
		bool no_close = false;
		bool no_background = false;

		mvDebugWindowConfig()
		{
			width = 700;
			height = 500;
		}
	};

	PyObject* add_debug_window(PyObject* self, PyObject* args, PyObject* kwargs);

	class mvDebugWindow : public mvBaseWindowAppitem
	{

	public:

		static void InsertParser(std::map<std::string, mvPythonParser>* parsers);

		MV_APPITEM_TYPE_OLD_SYSTEM(mvAppItemType::DebugWindow, "add_debug_window")

	public:

		mvDebugWindow(const std::string& name);

		void draw() override;

		void renderItem(mvAppItem* item);

	private:

		std::string m_selectedItem;
		ImGuiID     m_selectedID = 0u;
		std::vector<std::pair<std::string, std::string>> m_commands;
	};

}