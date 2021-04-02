#pragma once

#include "mvTypeBases.h"

namespace Marvel {

	MV_REGISTER_WIDGET(mvChild);
	class mvChild : public mvBoolPtrBase
	{
		MV_APPITEM_TYPE(mvAppItemType::mvChild, add_child)

		MV_CREATE_CONSTANT(mvThemeCol_Child_Bg					,  3L, 0L);
		MV_CREATE_CONSTANT(mvThemeCol_Child_MenuBar				, 13L, 0L);
		MV_CREATE_CONSTANT(mvThemeCol_Child_Border				,  5L, 0L);
		MV_CREATE_CONSTANT(mvThemeCol_Child_Scrollbar				, 14L, 0L);
		MV_CREATE_CONSTANT(mvThemeCol_Child_ScrollbarGrab			, 15L, 0L);
		MV_CREATE_CONSTANT(mvThemeCol_Child_ScrollbarGrabHovered	, 16L, 0L);
		MV_CREATE_CONSTANT(mvThemeCol_Child_ScrollbarGrabActive	, 17L, 0L);

		MV_CREATE_CONSTANT(mvThemeStyle_Child_BorderSize			,  7L, 0L);
		MV_CREATE_CONSTANT(mvThemeStyle_Child_Rounding			,  6L, 0L);
		MV_CREATE_CONSTANT(mvThemeStyle_Child_PaddingX			,  1L, 0L);
		MV_CREATE_CONSTANT(mvThemeStyle_Child_PaddingY			,  1L, 1L);
		MV_CREATE_CONSTANT(mvThemeStyle_Child_ItemSpacingX		, 13L, 0L);
		MV_CREATE_CONSTANT(mvThemeStyle_Child_ItemSpacingY		, 13L, 1L);
		MV_CREATE_CONSTANT(mvThemeStyle_Child_ScrollbarSize		, 17L, 0L);
		MV_CREATE_CONSTANT(mvThemeStyle_Child_ScrollbarRounding	, 18L, 0L);

		MV_START_EXTRA_COMMANDS
		MV_END_EXTRA_COMMANDS

		MV_START_GENERAL_CONSTANTS
		MV_END_GENERAL_CONSTANTS

		MV_START_COLOR_CONSTANTS
			MV_CREATE_CONSTANT_PAIR(mvThemeCol_Child_Bg,					mvColor(  0,   0,   0,   0)),
			MV_CREATE_CONSTANT_PAIR(mvThemeCol_Child_MenuBar,				mvColor( 36,  36,  36, 255)),
			MV_CREATE_CONSTANT_PAIR(mvThemeCol_Child_Border,				mvColor(110, 110, 128, 128)),
			MV_CREATE_CONSTANT_PAIR(mvThemeCol_Child_Scrollbar,				mvColor(  5,   5,   5, 135)),
			MV_CREATE_CONSTANT_PAIR(mvThemeCol_Child_ScrollbarGrab,			mvColor( 79,  79,  79, 255)),
			MV_CREATE_CONSTANT_PAIR(mvThemeCol_Child_ScrollbarGrabHovered,	mvColor(105, 105, 105, 255)),
			MV_CREATE_CONSTANT_PAIR(mvThemeCol_Child_ScrollbarGrabActive,	mvColor(130, 130, 130, 255)),
		MV_END_COLOR_CONSTANTS

		MV_START_STYLE_CONSTANTS
			MV_ADD_CONSTANT(mvThemeStyle_Child_BorderSize			, 1,  1),
			MV_ADD_CONSTANT(mvThemeStyle_Child_Rounding			, 0, 12),
			MV_ADD_CONSTANT(mvThemeStyle_Child_PaddingX			, 8, 20),
			MV_ADD_CONSTANT(mvThemeStyle_Child_PaddingY			, 8, 20),
			MV_ADD_CONSTANT(mvThemeStyle_Child_ItemSpacingX		, 8, 20),
			MV_ADD_CONSTANT(mvThemeStyle_Child_ItemSpacingY		, 4, 20),
			MV_ADD_CONSTANT(mvThemeStyle_Child_ScrollbarSize		,14, 20),
			MV_ADD_CONSTANT(mvThemeStyle_Child_ScrollbarRounding	, 9, 12),
		MV_END_STYLE_CONSTANTS

	public:

		static void InsertParser(std::map<std::string, mvPythonParser>* parsers);

	public:

		mvChild(const std::string& name);

		void draw(ImDrawList* drawlist, float x, float y)               override;

		void setExtraConfigDict(PyObject* dict) override;
		void getExtraConfigDict(PyObject* dict) override;

		void addFlag           (ImGuiWindowFlags flag);
		void removeFlag        (ImGuiWindowFlags flag);

	private:

		bool             m_border     = true;
		bool             m_autosize_x = false;
		bool             m_autosize_y = false;
		ImGuiWindowFlags m_windowflags = ImGuiWindowFlags_NoSavedSettings;

	};

}