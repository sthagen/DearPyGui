#pragma once

#include "mvTypeBases.h"
#include "mvApp.h"
#include "mvModule_Core.h"
#include <string>

//-----------------------------------------------------------------------------
// Widget Index
//
//     * mvInputInt
//     * mvInputFloat
//
//-----------------------------------------------------------------------------

namespace Marvel {

    //-----------------------------------------------------------------------------
    // mvInputInt
    //-----------------------------------------------------------------------------
    MV_REGISTER_WIDGET(mvInputInt, MV_ITEM_DESC_DEFAULT, StorageValueTypes::Int, 1);
    class mvInputInt : public mvIntPtrBase
    {

    public:

        static void InsertParser(std::map<std::string, mvPythonParser>* parsers);

        MV_APPLY_WIDGET_REGISTRATION(mvAppItemType::mvInputInt, add_input_int)

        MV_CREATE_CONSTANT(mvThemeCol_InputInt_Text, ImGuiCol_Text, 0L);
        MV_CREATE_CONSTANT(mvThemeCol_InputInt_TextHighlight, ImGuiCol_TextSelectedBg  , 0L);
        MV_CREATE_CONSTANT(mvThemeCol_InputInt_Bg, ImGuiCol_FrameBg, 0L);
        MV_CREATE_CONSTANT(mvThemeCol_InputInt_ButtonBg, ImGuiCol_Button, 0L);
        MV_CREATE_CONSTANT(mvThemeCol_InputInt_ButtonBgHovered, ImGuiCol_ButtonHovered, 0L);
        MV_CREATE_CONSTANT(mvThemeCol_InputInt_ButtonBgActive, ImGuiCol_ButtonActive, 0L);
        MV_CREATE_CONSTANT(mvThemeCol_InputInt_Border, ImGuiCol_Border, 0L);
        MV_CREATE_CONSTANT(mvThemeCol_InputInt_BorderShadow, ImGuiCol_BorderShadow, 0L);

        MV_CREATE_CONSTANT(mvThemeStyle_InputInt_Rounding, ImGuiStyleVar_FrameRounding, 0L);
        MV_CREATE_CONSTANT(mvThemeStyle_InputInt_BorderSize, ImGuiStyleVar_FrameBorderSize, 0L);
        MV_CREATE_CONSTANT(mvThemeStyle_InputInt_PaddingX, ImGuiStyleVar_FramePadding, 0L);
        MV_CREATE_CONSTANT(mvThemeStyle_InputInt_PaddingY, ImGuiStyleVar_FramePadding, 1L);
        MV_CREATE_CONSTANT(mvThemeStyle_InputInt_InnerSpacingX, ImGuiStyleVar_ItemInnerSpacing, 0L);
        MV_CREATE_CONSTANT(mvThemeStyle_InputInt_InnerSpacingY, ImGuiStyleVar_ItemInnerSpacing, 1L);
        MV_CREATE_CONSTANT(mvThemeStyle_InputInt_ButtonTextAlignX, ImGuiStyleVar_ButtonTextAlign, 0L);
        MV_CREATE_CONSTANT(mvThemeStyle_InputInt_ButtonTextAlignY, ImGuiStyleVar_ButtonTextAlign, 1L);

		MV_START_EXTRA_COMMANDS
		MV_END_EXTRA_COMMANDS

		MV_START_GENERAL_CONSTANTS
		MV_END_GENERAL_CONSTANTS

        MV_START_COLOR_CONSTANTS
            MV_ADD_CONSTANT(mvThemeCol_InputInt_Text, mvImGuiCol_Text, mvColor(128, 128, 128, 63)),
            MV_ADD_CONSTANT(mvThemeCol_InputInt_TextHighlight, mvImGuiCol_TextSelectedBg, mvColor(128, 128, 128, 63)),
            MV_ADD_CONSTANT(mvThemeCol_InputInt_Bg, mvImGuiCol_FrameBg, mvColor(128, 128, 128, 63)),
            MV_ADD_CONSTANT(mvThemeCol_InputInt_ButtonBg, mvImGuiCol_FrameBgHovered, mvColor(128, 128, 128, 63)),
            MV_ADD_CONSTANT(mvThemeCol_InputInt_ButtonBgHovered, mvImGuiCol_ButtonHovered, mvColor(128, 128, 128, 63)),
            MV_ADD_CONSTANT(mvThemeCol_InputInt_ButtonBgActive, mvImGuiCol_ButtonActive, mvColor(128, 128, 128, 63)),
            MV_ADD_CONSTANT(mvThemeCol_InputInt_Border, mvImGuiCol_Border, mvColor(128, 128, 128, 63)),
            MV_ADD_CONSTANT(mvThemeCol_InputInt_BorderShadow, mvImGuiCol_TextSelectedBg, mvColor(128, 128, 128, 63)),
        MV_END_COLOR_CONSTANTS

        MV_START_STYLE_CONSTANTS
            MV_ADD_CONSTANT_F(mvThemeStyle_InputInt_Rounding, 0, 12),
            MV_ADD_CONSTANT_F(mvThemeStyle_InputInt_BorderSize, 0, 1),
            MV_ADD_CONSTANT_F(mvThemeStyle_InputInt_PaddingX, 4, 20),
            MV_ADD_CONSTANT_F(mvThemeStyle_InputInt_PaddingY, 3, 20),
            MV_ADD_CONSTANT_F(mvThemeStyle_InputInt_InnerSpacingX, 4, 20),
            MV_ADD_CONSTANT_F(mvThemeStyle_InputInt_InnerSpacingY, 4, 20),
            MV_ADD_CONSTANT_F(mvThemeStyle_InputInt_ButtonTextAlignX, 0.5, 1),
            MV_ADD_CONSTANT_F(mvThemeStyle_InputInt_ButtonTextAlignY, 0.5, 1),
        MV_END_STYLE_CONSTANTS

    public:

        mvInputInt(const std::string& name);
        
        void setEnabled(bool value) override;
        void draw(ImDrawList* drawlist, float x, float y) override;

        void handleSpecificKeywordArgs(PyObject* dict) override;
        void getSpecificConfiguration(PyObject* dict) override;
        
    private:

        int                 m_step = 1;
        int                 m_step_fast = 100;
        int                 m_min = 0;
        int                 m_max = 100;
        bool                m_min_clamped = false;
        bool                m_max_clamped = false;
        ImGuiInputTextFlags m_flags = 0;
        ImGuiInputTextFlags m_stor_flags = 0;
        int                 m_last_value = 0;
        
    };
        
    //-----------------------------------------------------------------------------
    // mvInputFloat
    //-----------------------------------------------------------------------------
    MV_REGISTER_WIDGET(mvInputFloat, MV_ITEM_DESC_DEFAULT, StorageValueTypes::Float, 1);
    class mvInputFloat : public mvFloatPtrBase
    {

    public:

        static void InsertParser(std::map<std::string, mvPythonParser>* parsers);

        MV_APPLY_WIDGET_REGISTRATION(mvAppItemType::mvInputFloat, add_input_float)

        MV_CREATE_CONSTANT(mvThemeCol_InputFloat_Text, ImGuiCol_Text          , 0L);
        MV_CREATE_CONSTANT(mvThemeCol_InputFloat_TextHighlight, ImGuiCol_TextSelectedBg, 0L);
        MV_CREATE_CONSTANT(mvThemeCol_InputFloat_Bg, ImGuiCol_FrameBg       , 0L);
        MV_CREATE_CONSTANT(mvThemeCol_InputFloat_ButtonBg, ImGuiCol_Button        , 0L);
        MV_CREATE_CONSTANT(mvThemeCol_InputFloat_ButtonBgHovered, ImGuiCol_ButtonHovered , 0L);
        MV_CREATE_CONSTANT(mvThemeCol_InputFloat_ButtonBgActive, ImGuiCol_ButtonActive  , 0L);
        MV_CREATE_CONSTANT(mvThemeCol_InputFloat_Border, ImGuiCol_Border        , 0L);
        MV_CREATE_CONSTANT(mvThemeCol_InputFloat_BorderShadow, ImGuiCol_BorderShadow  , 0L);

        MV_CREATE_CONSTANT(mvThemeStyle_InputFloat_Rounding, ImGuiStyleVar_FrameRounding    , 0L);
        MV_CREATE_CONSTANT(mvThemeStyle_InputFloat_BorderSize, ImGuiStyleVar_FrameBorderSize  , 0L);
        MV_CREATE_CONSTANT(mvThemeStyle_InputFloat_PaddingX, ImGuiStyleVar_FramePadding     , 0L);
        MV_CREATE_CONSTANT(mvThemeStyle_InputFloat_PaddingY, ImGuiStyleVar_FramePadding     , 1L);
        MV_CREATE_CONSTANT(mvThemeStyle_InputFloat_InnerSpacingX, ImGuiStyleVar_ItemInnerSpacing , 0L);
        MV_CREATE_CONSTANT(mvThemeStyle_InputFloat_InnerSpacingY, ImGuiStyleVar_ItemInnerSpacing , 1L);
        MV_CREATE_CONSTANT(mvThemeStyle_InputFloat_ButtonTextAlignX, ImGuiStyleVar_ButtonTextAlign  , 0L);
        MV_CREATE_CONSTANT(mvThemeStyle_InputFloat_ButtonTextAlignY, ImGuiStyleVar_ButtonTextAlign  , 1L);

		MV_START_EXTRA_COMMANDS
		MV_END_EXTRA_COMMANDS

		MV_START_GENERAL_CONSTANTS
		MV_END_GENERAL_CONSTANTS

        MV_START_COLOR_CONSTANTS
            MV_ADD_CONSTANT(mvThemeCol_InputFloat_Text, mvImGuiCol_Text, mvColor(128, 128, 128, 63)),
            MV_ADD_CONSTANT(mvThemeCol_InputFloat_TextHighlight, mvImGuiCol_TextSelectedBg, mvColor(128, 128, 128, 63)),
            MV_ADD_CONSTANT(mvThemeCol_InputFloat_Bg, mvImGuiCol_FrameBg, mvColor(128, 128, 128, 63)),
            MV_ADD_CONSTANT(mvThemeCol_InputFloat_ButtonBg, mvImGuiCol_FrameBgHovered, mvColor(128, 128, 128, 63)),
            MV_ADD_CONSTANT(mvThemeCol_InputFloat_ButtonBgHovered, mvImGuiCol_ButtonHovered, mvColor(128, 128, 128, 63)),
            MV_ADD_CONSTANT(mvThemeCol_InputFloat_ButtonBgActive, mvImGuiCol_ButtonActive, mvColor(128, 128, 128, 63)),
            MV_ADD_CONSTANT(mvThemeCol_InputFloat_Border, mvImGuiCol_Border, mvColor(128, 128, 128, 63)),
            MV_ADD_CONSTANT(mvThemeCol_InputFloat_BorderShadow, mvImGuiCol_BorderShadow, mvColor(128, 128, 128, 63)),
        MV_END_COLOR_CONSTANTS

        MV_START_STYLE_CONSTANTS
            MV_ADD_CONSTANT_F(mvThemeStyle_InputFloat_Rounding, 0, 12),
            MV_ADD_CONSTANT_F(mvThemeStyle_InputFloat_BorderSize, 0, 1),
            MV_ADD_CONSTANT_F(mvThemeStyle_InputFloat_PaddingX, 4, 20),
            MV_ADD_CONSTANT_F(mvThemeStyle_InputFloat_PaddingY, 3, 20),
            MV_ADD_CONSTANT_F(mvThemeStyle_InputFloat_InnerSpacingX, 4, 20),
            MV_ADD_CONSTANT_F(mvThemeStyle_InputFloat_InnerSpacingY, 4, 20),
            MV_ADD_CONSTANT_F(mvThemeStyle_InputFloat_ButtonTextAlignX, 0.5, 1),
            MV_ADD_CONSTANT_F(mvThemeStyle_InputFloat_ButtonTextAlignY, 0.5, 1),
        MV_END_STYLE_CONSTANTS

    public:

        mvInputFloat(const std::string& name);
        
        void setEnabled(bool value) override;
        void draw(ImDrawList* drawlist, float x, float y) override;

        void handleSpecificKeywordArgs(PyObject* dict) override;
        void getSpecificConfiguration(PyObject* dict) override;

    private:

        float               m_min = 0.0f;
        float               m_max = 100.0f;
        bool                m_min_clamped = false;
        bool                m_max_clamped = false;
        std::string         m_format = "%.3f";
        float               m_step = 0.1f;
        float               m_step_fast = 1.0f;
        ImGuiInputTextFlags m_flags = 0;
        ImGuiInputTextFlags m_stor_flags = 0;
        float               m_last_value = 0.0f;
        
    };
 
}
