#pragma once

#include <utility>
#include <array>
#include "mvAppItem.h"

namespace Marvel {

	MV_REGISTER_WIDGET(mvImageButton);
	class mvImageButton : public mvAppItem, public mvEventHandler
	{

		MV_APPITEM_TYPE(mvAppItemType::mvImageButton, add_image_button)

		MV_CREATE_CONSTANT(mvThemeCol_ImageButton_Bg				, 21L, 0L);
		MV_CREATE_CONSTANT(mvThemeCol_ImageButton_BgHovered		, 22L, 0L);
		MV_CREATE_CONSTANT(mvThemeCol_ImageButton_BgActive		, 23L, 0L);
		MV_CREATE_CONSTANT(mvThemeCol_ImageButton_Border			,  5L, 0L);
		MV_CREATE_CONSTANT(mvThemeCol_ImageButton_BorderShadow	,  6L, 0L);

		MV_CREATE_CONSTANT(mvThemeStyle_ImageButton_BorderSize	, 12L, 0L);
		MV_CREATE_CONSTANT(mvThemeStyle_ImageButton_PaddingX		, 10L, 0L);
		MV_CREATE_CONSTANT(mvThemeStyle_ImageButton_PaddingY		, 10L, 1L);

		MV_START_EXTRA_COMMANDS
		MV_END_EXTRA_COMMANDS

		MV_START_GENERAL_CONSTANTS
		MV_END_GENERAL_CONSTANTS

		MV_START_COLOR_CONSTANTS
			MV_ADD_CONSTANT(mvThemeCol_ImageButton_Bg,           mvColor( 41,  74, 122, 138), mvColor(128, 128, 128, 63)),
			MV_ADD_CONSTANT(mvThemeCol_ImageButton_BgHovered,    mvColor( 66, 150, 250, 102), mvColor(128, 128, 128, 63)),
			MV_ADD_CONSTANT(mvThemeCol_ImageButton_BgActive,     mvColor( 66, 150, 250, 171), mvColor(128, 128, 128, 63)),
			MV_ADD_CONSTANT(mvThemeCol_ImageButton_Border,       mvColor(110, 110, 128, 128), mvColor(128, 128, 128, 63)),
			MV_ADD_CONSTANT(mvThemeCol_ImageButton_BorderShadow, mvColor(  0,   0,   0,   0), mvColor(128, 128, 128, 63)),
		MV_END_COLOR_CONSTANTS

		MV_START_STYLE_CONSTANTS
			MV_ADD_CONSTANT(mvThemeStyle_ImageButton_BorderSize, 0,  1),
			MV_ADD_CONSTANT(mvThemeStyle_ImageButton_PaddingX	, 4, 20),
			MV_ADD_CONSTANT(mvThemeStyle_ImageButton_PaddingY	, 3, 20),
		MV_END_STYLE_CONSTANTS

	public:

		static void InsertParser(std::map<std::string, mvPythonParser>* parsers);

	public:

		mvImageButton(const std::string& name, std::string  default_value);

		~mvImageButton() override;

		bool onEvent(mvEvent& event) override;
		bool onTextureDeleted(mvEvent& event);

		void draw(ImDrawList* drawlist, float x, float y) override;

		void setExtraConfigDict(PyObject* dict) override;
		void getExtraConfigDict(PyObject* dict) override;

	private:

		std::string m_value;
		mvVec2	    m_uv_min = { 0.0f, 0.0f };
		mvVec2	    m_uv_max = { 1.0f, 1.0f };
		mvColor     m_tintColor = { 1.0f, 1.0f, 1.0f, 1.0f };
		mvColor     m_backgroundColor = { 0.0f, 0.0f, 0.0f, 0.0f };
		void*       m_texture = nullptr;
		int         m_framePadding = -1;
		bool        m_dirty = false;

	};

}