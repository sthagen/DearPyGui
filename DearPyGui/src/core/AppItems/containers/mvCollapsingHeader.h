#pragma once

#include "mvTypeBases.h"

namespace Marvel {

	MV_REGISTER_WIDGET(mvCollapsingHeader, MV_ITEM_DESC_CONTAINER, StorageValueTypes::Bool, 1);
	class mvCollapsingHeader : public mvBoolPtrBase
	{
	public:

		static void InsertParser(std::map<std::string, mvPythonParser>* parsers);

		MV_APPITEM_TYPE(mvAppItemType::mvCollapsingHeader, add_collapsing_header)

		MV_CREATE_CONSTANT(mvThemeCol_CollapsingHeader_Text		    ,  0L, 0L);
		MV_CREATE_CONSTANT(mvThemeCol_CollapsingHeader_Bg			    , 24L, 0L);
		MV_CREATE_CONSTANT(mvThemeCol_CollapsingHeader_BgHovered	    , 25L, 0L);
		MV_CREATE_CONSTANT(mvThemeCol_CollapsingHeader_BgActive	    , 26L, 0L);
		MV_CREATE_CONSTANT(mvThemeCol_CollapsingHeader_Border		    ,  5L, 0L);
		MV_CREATE_CONSTANT(mvThemeCol_CollapsingHeader_BorderShadow	,  6L, 0L);

		MV_CREATE_CONSTANT(mvThemeStyle_CollapsingHeader_BorderSize	, 12L, 0L);
		MV_CREATE_CONSTANT(mvThemeStyle_CollapsingHeader_Rounding	    , 11L, 0L);
		MV_CREATE_CONSTANT(mvThemeStyle_CollapsingHeader_PaddingX	    , 10L, 0L);
		MV_CREATE_CONSTANT(mvThemeStyle_CollapsingHeader_PaddingY	    , 10L, 1L);
		MV_CREATE_CONSTANT(mvThemeStyle_CollapsingHeader_ItemSpacingX,  13L, 0L);
		MV_CREATE_CONSTANT(mvThemeStyle_CollapsingHeader_ItemSpacingY,  13L, 1L);

		MV_START_EXTRA_COMMANDS
		MV_END_EXTRA_COMMANDS

		MV_START_GENERAL_CONSTANTS
		MV_END_GENERAL_CONSTANTS

		MV_START_COLOR_CONSTANTS
			MV_CREATE_CONSTANT_PAIR(mvThemeCol_CollapsingHeader_Text,			mvColor(255, 255, 255, 255)),
			MV_CREATE_CONSTANT_PAIR(mvThemeCol_CollapsingHeader_Bg,				mvColor( 66, 150, 250, 79)),
			MV_CREATE_CONSTANT_PAIR(mvThemeCol_CollapsingHeader_BgHovered,		mvColor( 66, 150, 250, 204)),
			MV_CREATE_CONSTANT_PAIR(mvThemeCol_CollapsingHeader_BgActive,		mvColor( 66, 150, 250, 255)),
			MV_CREATE_CONSTANT_PAIR(mvThemeCol_CollapsingHeader_Border,			mvColor(110, 110, 128, 128)),
			MV_CREATE_CONSTANT_PAIR(mvThemeCol_CollapsingHeader_BorderShadow,	mvColor(  0,   0,   0,   0)),
		MV_END_COLOR_CONSTANTS

		MV_START_STYLE_CONSTANTS
			MV_ADD_CONSTANT(mvThemeStyle_CollapsingHeader_BorderSize	, 0,  1),
			MV_ADD_CONSTANT(mvThemeStyle_CollapsingHeader_Rounding		, 0, 12),
			MV_ADD_CONSTANT(mvThemeStyle_CollapsingHeader_PaddingX		, 4, 20),
			MV_ADD_CONSTANT(mvThemeStyle_CollapsingHeader_PaddingY		, 3, 20),
			MV_ADD_CONSTANT(mvThemeStyle_CollapsingHeader_ItemSpacingX	, 8, 20),
			MV_ADD_CONSTANT(mvThemeStyle_CollapsingHeader_ItemSpacingY	, 4, 20),
		MV_END_STYLE_CONSTANTS

	public:

		mvCollapsingHeader(const std::string& name);

		void draw(ImDrawList* drawlist, float x, float y)               override;

		void setExtraConfigDict(PyObject* dict) override;
		void getExtraConfigDict(PyObject* dict) override;

	private:

		ImGuiTreeNodeFlags m_flags = ImGuiTreeNodeFlags_None;
		bool               m_closable = false;

	};

}