#pragma once

#include "mvTypeBases.h"
#include "mvApp.h"

namespace Marvel {

	MV_REGISTER_WIDGET(mvMenuItem);
	class mvMenuItem : public mvBoolPtrBase
	{

		MV_APPITEM_TYPE(mvAppItemType::mvMenuItem, add_menu_item)

		MV_CREATE_CONSTANT(mvThemeCol_MenuItem_Text			,  0L, 0L);
		MV_CREATE_CONSTANT(mvThemeCol_MenuItem_BgHovered		, 25L, 0L);

		MV_CREATE_CONSTANT(ImGuiStyleVar_MenuItem_TextAlignX	, 23L, 0L);
		MV_CREATE_CONSTANT(ImGuiStyleVar_MenuItem_TextAlignY	, 23L, 1L);

		MV_START_EXTRA_COMMANDS
		MV_END_EXTRA_COMMANDS

		MV_START_GENERAL_CONSTANTS
		MV_END_GENERAL_CONSTANTS

		MV_START_COLOR_CONSTANTS
			MV_ADD_CONSTANT(mvThemeCol_MenuItem_Text,		mvColor(255, 255, 255, 255), mvColor(128, 128, 128, 63)),
			MV_ADD_CONSTANT(mvThemeCol_MenuItem_BgHovered,	mvColor( 66, 150, 250, 240), mvColor(128, 128, 128, 0)),
		MV_END_COLOR_CONSTANTS

		MV_START_STYLE_CONSTANTS
			MV_ADD_CONSTANT(ImGuiStyleVar_MenuItem_TextAlignX, 0, 1),
			MV_ADD_CONSTANT(ImGuiStyleVar_MenuItem_TextAlignY, 0, 1),
		MV_END_STYLE_CONSTANTS

	public:

		static void InsertParser(std::map<std::string, mvPythonParser>* parsers);

	public:

		explicit mvMenuItem(const std::string& name);

		void draw(ImDrawList* drawlist, float x, float y) override;

		void setExtraConfigDict(PyObject* dict) override;
		void getExtraConfigDict(PyObject* dict) override;

	private:

		std::string m_shortcut;
		bool        m_check = false;

	};

}