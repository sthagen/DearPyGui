#pragma once

#include "mvTypeBases.h"

namespace Marvel {

	MV_REGISTER_WIDGET(mvTab);
	class mvTab : public mvBoolPtrBase
	{

		MV_APPITEM_TYPE(mvAppItemType::mvTab, add_tab)

		MV_CREATE_CONSTANT(mvThemeCol_Tab_Text			,  0L, 0L);
		MV_CREATE_CONSTANT(mvThemeCol_Tab_Border			,  5L, 0L);
		MV_CREATE_CONSTANT(mvThemeCol_Tab_Bg				, 33L, 0L);
		MV_CREATE_CONSTANT(mvThemeCol_Tab_BgHovered		, 34L, 0L);
		MV_CREATE_CONSTANT(mvThemeCol_Tab_BgActive		, 35L, 0L);
		MV_CREATE_CONSTANT(mvThemeCol_Tab_PopupBg			,  4L, 0L);

		MV_CREATE_CONSTANT(mvThemeStyle_Tab_Rounding		, 21L, 0L);
		MV_CREATE_CONSTANT(mvThemeStyle_Tab_PaddingX		, 10L, 0L);
		MV_CREATE_CONSTANT(mvThemeStyle_Tab_PaddingY		, 10L, 1L);
		MV_CREATE_CONSTANT(mvThemeStyle_Tab_InnerSpacingX	, 14L, 0L);
		MV_CREATE_CONSTANT(mvThemeStyle_Tab_InnerSpacingY	, 14L, 1L);

		MV_START_EXTRA_COMMANDS
		MV_END_EXTRA_COMMANDS

		MV_START_GENERAL_CONSTANTS
		MV_END_GENERAL_CONSTANTS

		MV_START_COLOR_CONSTANTS
			MV_CREATE_CONSTANT_PAIR(mvThemeCol_Tab_Text,		mvColor(255, 255, 255, 255)),
			MV_CREATE_CONSTANT_PAIR(mvThemeCol_Tab_Bg,			mvColor( 46,  89, 148, 220)),
			MV_CREATE_CONSTANT_PAIR(mvThemeCol_Tab_BgHovered,	mvColor( 66, 150, 250, 204)),
			MV_CREATE_CONSTANT_PAIR(mvThemeCol_Tab_BgActive,	mvColor( 51, 105, 173, 255)),
			MV_CREATE_CONSTANT_PAIR(mvThemeCol_Tab_Border,		mvColor(110, 110, 128, 128)),
			MV_CREATE_CONSTANT_PAIR(mvThemeCol_Tab_PopupBg,		mvColor( 20,  20,  20, 240)),
		MV_END_COLOR_CONSTANTS

		MV_START_STYLE_CONSTANTS
			MV_ADD_CONSTANT(mvThemeStyle_Tab_Rounding		, 4, 12),
			MV_ADD_CONSTANT(mvThemeStyle_Tab_PaddingX		, 4, 20),
			MV_ADD_CONSTANT(mvThemeStyle_Tab_PaddingY		, 3, 20),
			MV_ADD_CONSTANT(mvThemeStyle_Tab_InnerSpacingX	, 4, 20),
			MV_ADD_CONSTANT(mvThemeStyle_Tab_InnerSpacingY	, 4, 20),
		MV_END_STYLE_CONSTANTS

	public:

		static void InsertParser(std::map<std::string, mvPythonParser>* parsers);

	public:

		mvTab(const std::string& name);

		void draw(ImDrawList* drawlist, float x, float y) override;
		void addFlag   (ImGuiTabItemFlags flag);
		void removeFlag(ImGuiTabItemFlags flag);

		void setExtraConfigDict(PyObject* dict) override;
		void getExtraConfigDict(PyObject* dict) override;

	private:

		bool              m_closable = false;
		ImGuiTabItemFlags m_flags = ImGuiTabItemFlags_None;

	};

}