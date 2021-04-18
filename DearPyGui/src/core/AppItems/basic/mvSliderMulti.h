#pragma once
#include "mvTypeBases.h"
#include <string>
#include "mvModule_Core.h"

//-----------------------------------------------------------------------------
// Widget Index
//
//     * mvSliderFloatMulti
//     * mvSliderIntMulti
//
//-----------------------------------------------------------------------------

namespace Marvel {
  
    //-----------------------------------------------------------------------------
    // mvSliderFloat4
    //-----------------------------------------------------------------------------
    MV_REGISTER_WIDGET(mvSliderFloatMulti, MV_ITEM_DESC_DEFAULT, StorageValueTypes::Float4, 1);
    class mvSliderFloatMulti : public mvFloat4PtrBase
    {

    public:

        static void InsertParser(std::map<std::string, mvPythonParser>* parsers);

        MV_APPLY_WIDGET_REGISTRATION(mvAppItemType::mvSliderFloatMulti, add_slider_floatx)

        MV_CREATE_CONSTANT(mvThemeCol_SliderFloatx_Text, ImGuiCol_Text, 0L);
        MV_CREATE_CONSTANT(mvThemeCol_SliderFloatx_Bg, ImGuiCol_FrameBg, 0L);
        MV_CREATE_CONSTANT(mvThemeCol_SliderFloatx_BgHovered, ImGuiCol_FrameBgHovered, 0L);
        MV_CREATE_CONSTANT(mvThemeCol_SliderFloatx_BgActive, ImGuiCol_FrameBgActive, 0L);
        MV_CREATE_CONSTANT(mvThemeCol_SliderFloatx_Grab, ImGuiCol_SliderGrab, 0L);
        MV_CREATE_CONSTANT(mvThemeCol_SliderFloatx_GrabActive, ImGuiCol_SliderGrabActive , 0L);
        MV_CREATE_CONSTANT(mvThemeCol_SliderFloatx_Border, ImGuiCol_Border, 0L);
        MV_CREATE_CONSTANT(mvThemeCol_SliderFloatx_BorderShadow, ImGuiCol_BorderShadow, 0L);

        MV_CREATE_CONSTANT(mvThemeStyle_SliderFloatx_Rounding, ImGuiStyleVar_FrameRounding, 0L);
        MV_CREATE_CONSTANT(mvThemeStyle_SliderFloatx_BorderSize, ImGuiStyleVar_FrameBorderSize, 0L);
        MV_CREATE_CONSTANT(mvThemeStyle_SliderFloatx_PaddingX, ImGuiStyleVar_FramePadding, 0L);
        MV_CREATE_CONSTANT(mvThemeStyle_SliderFloatx_PaddingY, ImGuiStyleVar_FramePadding, 1L);
        MV_CREATE_CONSTANT(mvThemeStyle_SliderFloatx_InnerSpacingX, ImGuiStyleVar_ItemInnerSpacing, 0L);
        MV_CREATE_CONSTANT(mvThemeStyle_SliderFloatx_InnerSpacingY, ImGuiStyleVar_ItemInnerSpacing, 1L);
        MV_CREATE_CONSTANT(mvThemeStyle_SliderFloatx_GrabMinSize, ImGuiStyleVar_GrabMinSize, 0L);
        MV_CREATE_CONSTANT(mvThemeStyle_SliderFloatx_GrabRounding , ImGuiStyleVar_GrabRounding, 0L);

		MV_START_EXTRA_COMMANDS
		MV_END_EXTRA_COMMANDS

		MV_START_GENERAL_CONSTANTS
		MV_END_GENERAL_CONSTANTS

        MV_START_COLOR_CONSTANTS
            MV_ADD_CONSTANT(mvThemeCol_SliderFloatx_Text, mvImGuiCol_Text, mvColor(128, 128, 128, 63)),
            MV_ADD_CONSTANT(mvThemeCol_SliderFloatx_Bg, mvImGuiCol_FrameBg, mvColor(128, 128, 128, 63)),
            MV_ADD_CONSTANT(mvThemeCol_SliderFloatx_BgHovered, mvImGuiCol_FrameBgHovered, mvColor(128, 128, 128, 63)),
            MV_ADD_CONSTANT(mvThemeCol_SliderFloatx_BgActive, mvImGuiCol_FrameBgActive, mvColor(128, 128, 128, 63)),
            MV_ADD_CONSTANT(mvThemeCol_SliderFloatx_Grab, mvImGuiCol_SliderGrab, mvColor(128, 128, 128, 63)),
            MV_ADD_CONSTANT(mvThemeCol_SliderFloatx_GrabActive, mvImGuiCol_ButtonHovered, mvColor(128, 128, 128, 63)),
            MV_ADD_CONSTANT(mvThemeCol_SliderFloatx_Border, mvImGuiCol_Border, mvColor(128, 128, 128, 63)),
            MV_ADD_CONSTANT(mvThemeCol_SliderFloatx_BorderShadow, mvImGuiCol_BorderShadow, mvColor(128, 128, 128, 63)),
        MV_END_COLOR_CONSTANTS

        MV_START_STYLE_CONSTANTS
            MV_ADD_CONSTANT_F(mvThemeStyle_SliderFloatx_Rounding, 0, 12),
            MV_ADD_CONSTANT_F(mvThemeStyle_SliderFloatx_BorderSize, 0,  1),
            MV_ADD_CONSTANT_F(mvThemeStyle_SliderFloatx_PaddingX, 4, 20),
            MV_ADD_CONSTANT_F(mvThemeStyle_SliderFloatx_PaddingY, 3, 20),
            MV_ADD_CONSTANT_F(mvThemeStyle_SliderFloatx_InnerSpacingX, 4, 20),
            MV_ADD_CONSTANT_F(mvThemeStyle_SliderFloatx_InnerSpacingY, 4, 20),
            MV_ADD_CONSTANT_F(mvThemeStyle_SliderFloatx_GrabMinSize,10, 20),
            MV_ADD_CONSTANT_F(mvThemeStyle_SliderFloatx_GrabRounding, 0, 12),
        MV_END_STYLE_CONSTANTS

    public:

        mvSliderFloatMulti(const std::string& name);
        
        void setEnabled(bool value) override;
        void draw(ImDrawList* drawlist, float x, float y) override;

        void handleSpecificKeywordArgs(PyObject* dict) override;
        void getSpecificConfiguration(PyObject* dict) override;
        
    private:

        float                   m_min = 0.0f;
        float                   m_max = 100.0f;
        std::string             m_format = "%.3f";
        ImGuiInputTextFlags     m_flags = ImGuiSliderFlags_None;
        ImGuiInputTextFlags     m_stor_flags = ImGuiSliderFlags_None;
        int                     m_size = 4;
    };
        
    //-----------------------------------------------------------------------------
    // mvSliderIntMulti
    //-----------------------------------------------------------------------------
    MV_REGISTER_WIDGET(mvSliderIntMulti, MV_ITEM_DESC_DEFAULT, StorageValueTypes::Int4, 1);
    class mvSliderIntMulti : public mvInt4PtrBase
    {

    public:

        static void InsertParser(std::map<std::string, mvPythonParser>* parsers);

        MV_APPLY_WIDGET_REGISTRATION(mvAppItemType::mvSliderIntMulti, add_slider_intx)

        MV_CREATE_CONSTANT(mvThemeCol_SliderIntx_Text              , ImGuiCol_Text              , 0L);
        MV_CREATE_CONSTANT(mvThemeCol_SliderIntx_Bg                , ImGuiCol_FrameBg           , 0L);
        MV_CREATE_CONSTANT(mvThemeCol_SliderIntx_BgHovered         , ImGuiCol_FrameBgHovered    , 0L);
        MV_CREATE_CONSTANT(mvThemeCol_SliderIntx_BgActive          , ImGuiCol_FrameBgActive     , 0L);
        MV_CREATE_CONSTANT(mvThemeCol_SliderIntx_Grab              , ImGuiCol_SliderGrab        , 0L);
        MV_CREATE_CONSTANT(mvThemeCol_SliderIntx_GrabActive        , ImGuiCol_SliderGrabActive  , 0L);
        MV_CREATE_CONSTANT(mvThemeCol_SliderIntx_Border            , ImGuiCol_Border            , 0L);
        MV_CREATE_CONSTANT(mvThemeCol_SliderIntx_BorderShadow      , ImGuiCol_BorderShadow      , 0L);

        MV_CREATE_CONSTANT(mvThemeStyle_SliderIntx_Rounding        , ImGuiStyleVar_FrameRounding    , 0L);
        MV_CREATE_CONSTANT(mvThemeStyle_SliderIntx_BorderSize      , ImGuiStyleVar_FrameBorderSize  , 0L);
        MV_CREATE_CONSTANT(mvThemeStyle_SliderIntx_PaddingX        , ImGuiStyleVar_FramePadding     , 0L);
        MV_CREATE_CONSTANT(mvThemeStyle_SliderIntx_PaddingY        , ImGuiStyleVar_FramePadding     , 1L);
        MV_CREATE_CONSTANT(mvThemeStyle_SliderIntx_InnerSpacingX   , ImGuiStyleVar_ItemInnerSpacing , 0L);
        MV_CREATE_CONSTANT(mvThemeStyle_SliderIntx_InnerSpacingY   , ImGuiStyleVar_ItemInnerSpacing , 1L);
        MV_CREATE_CONSTANT(mvThemeStyle_SliderIntx_GrabMinSize     , ImGuiStyleVar_GrabMinSize      , 0L);
        MV_CREATE_CONSTANT(mvThemeStyle_SliderIntx_GrabRounding    , ImGuiStyleVar_GrabRounding     , 0L);

		MV_START_EXTRA_COMMANDS
		MV_END_EXTRA_COMMANDS

		MV_START_GENERAL_CONSTANTS
		MV_END_GENERAL_CONSTANTS

        MV_START_COLOR_CONSTANTS
            MV_ADD_CONSTANT(mvThemeCol_SliderIntx_Text,         mvImGuiCol_Text, mvColor(128, 128, 128, 63)),
            MV_ADD_CONSTANT(mvThemeCol_SliderIntx_Bg,           mvImGuiCol_FrameBg, mvColor(128, 128, 128, 63)),
            MV_ADD_CONSTANT(mvThemeCol_SliderIntx_BgHovered,    mvImGuiCol_FrameBgHovered, mvColor(128, 128, 128, 63)),
            MV_ADD_CONSTANT(mvThemeCol_SliderIntx_BgActive,     mvImGuiCol_FrameBgActive, mvColor(128, 128, 128, 63)),
            MV_ADD_CONSTANT(mvThemeCol_SliderIntx_Grab,         mvColor( 61, 133, 224, 255), mvColor(128, 128, 128, 63)),
            MV_ADD_CONSTANT(mvThemeCol_SliderIntx_GrabActive,   mvImGuiCol_ButtonHovered, mvColor(128, 128, 128, 63)),
            MV_ADD_CONSTANT(mvThemeCol_SliderIntx_Border,       mvImGuiCol_Border, mvColor(128, 128, 128, 63)),
            MV_ADD_CONSTANT(mvThemeCol_SliderIntx_BorderShadow, mvImGuiCol_BorderShadow, mvColor(128, 128, 128, 63)),
        MV_END_COLOR_CONSTANTS

        MV_START_STYLE_CONSTANTS
            MV_ADD_CONSTANT_F(mvThemeStyle_SliderIntx_Rounding       , 0, 12),
            MV_ADD_CONSTANT_F(mvThemeStyle_SliderIntx_BorderSize     , 0,  1),
            MV_ADD_CONSTANT_F(mvThemeStyle_SliderIntx_PaddingX       , 4, 20),
            MV_ADD_CONSTANT_F(mvThemeStyle_SliderIntx_PaddingY       , 3, 20),
            MV_ADD_CONSTANT_F(mvThemeStyle_SliderIntx_InnerSpacingX  , 4, 20),
            MV_ADD_CONSTANT_F(mvThemeStyle_SliderIntx_InnerSpacingY  , 4, 20),
            MV_ADD_CONSTANT_F(mvThemeStyle_SliderIntx_GrabMinSize    ,10, 20),
            MV_ADD_CONSTANT_F(mvThemeStyle_SliderIntx_GrabRounding   , 0, 12),
        MV_END_STYLE_CONSTANTS

    public:

        mvSliderIntMulti(const std::string& name);
        
        void setEnabled(bool value) override;
        void draw(ImDrawList* drawlist, float x, float y) override;

        void handleSpecificKeywordArgs(PyObject* dict) override;
        void getSpecificConfiguration(PyObject* dict) override;
        
    private:

        int                 m_min = 0;
        int                 m_max = 100;
        std::string         m_format = "%d";
        ImGuiInputTextFlags m_flags = ImGuiSliderFlags_None;
        ImGuiInputTextFlags m_stor_flags = ImGuiSliderFlags_None;
        int                 m_size = 4;
    };

}
