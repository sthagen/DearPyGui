#pragma once

#include "mvTypeBases.h"
#include "mvApp.h"
#include "mvModule_Core.h"
#include <string>

//-----------------------------------------------------------------------------
// Widget Index
//
//     * mvDragFloat
//     * mvDragFloat2
//     * mvDragFloat3
//     * mvDragFloat4
//     * mvDragInt
//     * mvDragInt2
//     * mvDragInt3
//     * mvDragInt4
//
//-----------------------------------------------------------------------------

namespace Marvel {

    //-----------------------------------------------------------------------------
    // mvDragFloat
    //-----------------------------------------------------------------------------
    MV_REGISTER_WIDGET(mvDragFloat);
    class mvDragFloat : public mvFloatPtrBase
    {

    public:

        static void InsertParser(std::map<std::string, mvPythonParser>* parsers);

        MV_APPITEM_TYPE(mvAppItemType::mvDragFloat, add_drag_float)

        MV_CREATE_CONSTANT(mvThemeCol_DragFloat_Text            ,  0L, 0L);
        MV_CREATE_CONSTANT(mvThemeCol_DragFloat_Bg              ,  7L, 0L);
        MV_CREATE_CONSTANT(mvThemeCol_DragFloat_BgHovered       ,  8L, 0L);
        MV_CREATE_CONSTANT(mvThemeCol_DragFloat_BgActive        ,  9L, 0L);
        MV_CREATE_CONSTANT(mvThemeCol_DragFloat_Border          ,  5L, 0L);
        MV_CREATE_CONSTANT(mvThemeCol_DragFloat_BorderShadow    ,  6L, 0L);

        MV_CREATE_CONSTANT(mvThemeStyle_DragFloat_Rounding      , 11L, 0L);
        MV_CREATE_CONSTANT(mvThemeStyle_DragFloat_BorderSize    , 12L, 0L);
        MV_CREATE_CONSTANT(mvThemeStyle_DragFloat_PaddingX      , 10L, 0L);
        MV_CREATE_CONSTANT(mvThemeStyle_DragFloat_PaddingY      , 10L, 1L);
        MV_CREATE_CONSTANT(mvThemeStyle_DragFloat_InnerSpacingX , 14L, 0L);
        MV_CREATE_CONSTANT(mvThemeStyle_DragFloat_InnerSpacingY , 14L, 1L);

		MV_START_EXTRA_COMMANDS
		MV_END_EXTRA_COMMANDS

		MV_START_GENERAL_CONSTANTS
		MV_END_GENERAL_CONSTANTS

        MV_START_COLOR_CONSTANTS
            MV_ADD_CONSTANT(mvThemeCol_DragFloat_Text,         mvColor(255, 255, 255, 255), mvColor(128, 128, 128, 63)),
            MV_ADD_CONSTANT(mvThemeCol_DragFloat_Bg,           mvColor( 41,  74, 122, 138), mvColor(128, 128, 128, 63)),
            MV_ADD_CONSTANT(mvThemeCol_DragFloat_BgHovered,    mvColor( 66, 150, 250, 102), mvColor(128, 128, 128, 63)),
            MV_ADD_CONSTANT(mvThemeCol_DragFloat_BgActive,     mvColor( 66, 150, 250, 171), mvColor(128, 128, 128, 63)),
            MV_ADD_CONSTANT(mvThemeCol_DragFloat_Border,       mvColor(110, 110, 128, 128), mvColor(128, 128, 128, 63)),
            MV_ADD_CONSTANT(mvThemeCol_DragFloat_BorderShadow, mvColor(  0,   0,   0,   0), mvColor(128, 128, 128, 63)),
        MV_END_COLOR_CONSTANTS

        MV_START_STYLE_CONSTANTS
            MV_ADD_CONSTANT(mvThemeStyle_DragFloat_Rounding        , 0, 12),
            MV_ADD_CONSTANT(mvThemeStyle_DragFloat_BorderSize      , 0, 1),
            MV_ADD_CONSTANT(mvThemeStyle_DragFloat_PaddingX        , 4, 20),
            MV_ADD_CONSTANT(mvThemeStyle_DragFloat_PaddingY        , 3, 20),
            MV_ADD_CONSTANT(mvThemeStyle_DragFloat_InnerSpacingX   , 4, 20),
            MV_ADD_CONSTANT(mvThemeStyle_DragFloat_InnerSpacingY   , 4, 20),
        MV_END_STYLE_CONSTANTS

    public:

        mvDragFloat(const std::string& name, float default_value, const std::string& dataSource);
        
        void setEnabled(bool value) override;
        
        void draw(ImDrawList* drawlist, float x, float y) override;
        
        void setExtraConfigDict(PyObject* dict) override;
        void getExtraConfigDict(PyObject* dict) override;
       
    private:

        float               m_speed = 1.0f;
        float               m_min = 0.0f;
        float               m_max = 100.0f;
        std::string         m_format = "%.3f";
        ImGuiInputTextFlags m_flags = ImGuiSliderFlags_None;
        ImGuiInputTextFlags m_stor_flags = ImGuiSliderFlags_None;

    };
        
    //-----------------------------------------------------------------------------
    // mvDragFloat2
    //-----------------------------------------------------------------------------
    MV_REGISTER_WIDGET(mvDragFloat2);
    class mvDragFloat2 : public mvFloat2PtrBase
    {

        MV_APPITEM_TYPE(mvAppItemType::mvDragFloat2, add_drag_float2)

        MV_CREATE_CONSTANT(mvThemeCol_DragFloat2_Text              ,  0L, 0L);
        MV_CREATE_CONSTANT(mvThemeCol_DragFloat2_Bg                ,  7L, 0L);
        MV_CREATE_CONSTANT(mvThemeCol_DragFloat2_BgHovered         ,  8L, 0L);
        MV_CREATE_CONSTANT(mvThemeCol_DragFloat2_BgActive          ,  9L, 0L);
        MV_CREATE_CONSTANT(mvThemeCol_DragFloat2_Border            ,  5L, 0L);
        MV_CREATE_CONSTANT(mvThemeCol_DragFloat2_BorderShadow      ,  6L, 0L);

        MV_CREATE_CONSTANT(mvThemeStyle_DragFloat2_Rounding        , 11L, 0L);
        MV_CREATE_CONSTANT(mvThemeStyle_DragFloat2_BorderSize      , 12L, 0L);
        MV_CREATE_CONSTANT(mvThemeStyle_DragFloat2_PaddingX        , 10L, 0L);
        MV_CREATE_CONSTANT(mvThemeStyle_DragFloat2_PaddingY        , 10L, 1L);
        MV_CREATE_CONSTANT(mvThemeStyle_DragFloat2_InnerSpacingX   , 14L, 0L);
        MV_CREATE_CONSTANT(mvThemeStyle_DragFloat2_InnerSpacingY   , 14L, 1L);

		MV_START_EXTRA_COMMANDS
		MV_END_EXTRA_COMMANDS

		MV_START_GENERAL_CONSTANTS
		MV_END_GENERAL_CONSTANTS

        MV_START_COLOR_CONSTANTS
            MV_ADD_CONSTANT(mvThemeCol_DragFloat2_Text,         mvColor(255, 255, 255, 255), mvColor(128, 128, 128, 63)),
            MV_ADD_CONSTANT(mvThemeCol_DragFloat2_Bg,           mvColor( 41,  74, 122, 138), mvColor(128, 128, 128, 63)),
            MV_ADD_CONSTANT(mvThemeCol_DragFloat2_BgHovered,    mvColor( 66, 150, 250, 102), mvColor(128, 128, 128, 63)),
            MV_ADD_CONSTANT(mvThemeCol_DragFloat2_BgActive,     mvColor( 66, 150, 250, 171), mvColor(128, 128, 128, 63)),
            MV_ADD_CONSTANT(mvThemeCol_DragFloat2_Border,       mvColor(110, 110, 128, 128), mvColor(128, 128, 128, 63)),
            MV_ADD_CONSTANT(mvThemeCol_DragFloat2_BorderShadow, mvColor(  0,   0,   0,   0), mvColor(128, 128, 128, 63)),
        MV_END_COLOR_CONSTANTS

        MV_START_STYLE_CONSTANTS
            MV_ADD_CONSTANT(mvThemeStyle_DragFloat2_Rounding       , 0, 12),
            MV_ADD_CONSTANT(mvThemeStyle_DragFloat2_BorderSize     , 0,  1),
            MV_ADD_CONSTANT(mvThemeStyle_DragFloat2_PaddingX       , 4, 20),
            MV_ADD_CONSTANT(mvThemeStyle_DragFloat2_PaddingY       , 3, 20),
            MV_ADD_CONSTANT(mvThemeStyle_DragFloat2_InnerSpacingX  , 4, 20),
            MV_ADD_CONSTANT(mvThemeStyle_DragFloat2_InnerSpacingY  , 4, 20),
        MV_END_STYLE_CONSTANTS

    public:

        static void InsertParser(std::map<std::string, mvPythonParser>* parsers);

    public:

        mvDragFloat2(const std::string& name, float* default_value, const std::string& dataSource);
        
        void setEnabled(bool value) override;
        void draw(ImDrawList* drawlist, float x, float y) override;

        void setExtraConfigDict(PyObject* dict) override;
        void getExtraConfigDict(PyObject* dict) override;

    private:

        float               m_speed = 1.0f;
        float               m_min = 0.0f;
        float               m_max = 100.0f;
        std::string         m_format = "%.3f";
        ImGuiInputTextFlags m_flags = ImGuiSliderFlags_None;
        ImGuiInputTextFlags m_stor_flags = ImGuiSliderFlags_None;
    };
        
    //-----------------------------------------------------------------------------
    // mvDragFloat3
    //-----------------------------------------------------------------------------
    MV_REGISTER_WIDGET(mvDragFloat3);
    class mvDragFloat3 : public mvFloat3PtrBase
    {

        MV_APPITEM_TYPE(mvAppItemType::mvDragFloat3, add_drag_float3)

        MV_CREATE_CONSTANT(mvThemeCol_DragFloat3_Text              ,  0L, 0L);
        MV_CREATE_CONSTANT(mvThemeCol_DragFloat3_Bg                ,  7L, 0L);
        MV_CREATE_CONSTANT(mvThemeCol_DragFloat3_BgHovered         ,  8L, 0L);
        MV_CREATE_CONSTANT(mvThemeCol_DragFloat3_BgActive          ,  9L, 0L);
        MV_CREATE_CONSTANT(mvThemeCol_DragFloat3_Border            ,  5L, 0L);
        MV_CREATE_CONSTANT(mvThemeCol_DragFloat3_BorderShadow      ,  6L, 0L);

        MV_CREATE_CONSTANT(mvThemeStyle_DragFloat3_Rounding        , 11L, 0L);
        MV_CREATE_CONSTANT(mvThemeStyle_DragFloat3_BorderSize      , 12L, 0L);
        MV_CREATE_CONSTANT(mvThemeStyle_DragFloat3_PaddingX        , 10L, 0L);
        MV_CREATE_CONSTANT(mvThemeStyle_DragFloat3_PaddingY        , 10L, 1L);
        MV_CREATE_CONSTANT(mvThemeStyle_DragFloat3_InnerSpacingX   , 14L, 0L);
        MV_CREATE_CONSTANT(mvThemeStyle_DragFloat3_InnerSpacingY   , 14L, 1L);

		MV_START_EXTRA_COMMANDS
		MV_END_EXTRA_COMMANDS

		MV_START_GENERAL_CONSTANTS
		MV_END_GENERAL_CONSTANTS

        MV_START_COLOR_CONSTANTS
            MV_ADD_CONSTANT(mvThemeCol_DragFloat3_Text,         mvColor(255, 255, 255, 255), mvColor(128, 128, 128, 63)),
            MV_ADD_CONSTANT(mvThemeCol_DragFloat3_Bg,           mvColor( 41,  74, 122, 138), mvColor(128, 128, 128, 63)),
            MV_ADD_CONSTANT(mvThemeCol_DragFloat3_BgHovered,    mvColor( 66, 150, 250, 102), mvColor(128, 128, 128, 63)),
            MV_ADD_CONSTANT(mvThemeCol_DragFloat3_BgActive,     mvColor( 66, 150, 250, 171), mvColor(128, 128, 128, 63)),
            MV_ADD_CONSTANT(mvThemeCol_DragFloat3_Border,       mvColor(110, 110, 128, 128), mvColor(128, 128, 128, 63)),
            MV_ADD_CONSTANT(mvThemeCol_DragFloat3_BorderShadow, mvColor(  0,   0,   0,   0), mvColor(128, 128, 128, 63)),
        MV_END_COLOR_CONSTANTS

        MV_START_STYLE_CONSTANTS
            MV_ADD_CONSTANT(mvThemeStyle_DragFloat3_Rounding       , 0, 12),
            MV_ADD_CONSTANT(mvThemeStyle_DragFloat3_BorderSize     , 0,  1),
            MV_ADD_CONSTANT(mvThemeStyle_DragFloat3_PaddingX       , 4, 20),
            MV_ADD_CONSTANT(mvThemeStyle_DragFloat3_PaddingY       , 3, 20),
            MV_ADD_CONSTANT(mvThemeStyle_DragFloat3_InnerSpacingX  , 4, 20),
            MV_ADD_CONSTANT(mvThemeStyle_DragFloat3_InnerSpacingY  , 4, 20),
        MV_END_STYLE_CONSTANTS

    public:

        static void InsertParser(std::map<std::string, mvPythonParser>* parsers);

    public:

        mvDragFloat3(const std::string& name, float* default_value, const std::string& dataSource);
        
        void setEnabled(bool value) override;
        void draw(ImDrawList* drawlist, float x, float y) override;

        void setExtraConfigDict(PyObject* dict) override;
        void getExtraConfigDict(PyObject* dict) override;

    private:

        float               m_speed = 1.0f;
        float               m_min = 0.0f;
        float               m_max = 100.0f;
        std::string         m_format = "%.3f";
        ImGuiInputTextFlags m_flags = ImGuiSliderFlags_None;
        ImGuiInputTextFlags m_stor_flags = ImGuiSliderFlags_None;
    };
        
    //-----------------------------------------------------------------------------
    // mvDragFloat4
    //-----------------------------------------------------------------------------
    MV_REGISTER_WIDGET(mvDragFloat4);
    class mvDragFloat4 : public mvFloat4PtrBase
    {

        MV_APPITEM_TYPE(mvAppItemType::mvDragFloat4, add_drag_float4)

        MV_CREATE_CONSTANT(mvThemeCol_DragFloat4_Text              ,  0L, 0L);
        MV_CREATE_CONSTANT(mvThemeCol_DragFloat4_Bg                ,  7L, 0L);
        MV_CREATE_CONSTANT(mvThemeCol_DragFloat4_BgHovered         ,  8L, 0L);
        MV_CREATE_CONSTANT(mvThemeCol_DragFloat4_BgActive          ,  9L, 0L);
        MV_CREATE_CONSTANT(mvThemeCol_DragFloat4_Border            ,  5L, 0L);
        MV_CREATE_CONSTANT(mvThemeCol_DragFloat4_BorderShadow      ,  6L, 0L);

        MV_CREATE_CONSTANT(mvThemeStyle_DragFloat4_Rounding        , 11L, 0L);
        MV_CREATE_CONSTANT(mvThemeStyle_DragFloat4_BorderSize      , 12L, 0L);
        MV_CREATE_CONSTANT(mvThemeStyle_DragFloat4_PaddingX        , 10L, 0L);
        MV_CREATE_CONSTANT(mvThemeStyle_DragFloat4_PaddingY        , 10L, 1L);
        MV_CREATE_CONSTANT(mvThemeStyle_DragFloat4_InnerSpacingX   , 14L, 0L);
        MV_CREATE_CONSTANT(mvThemeStyle_DragFloat4_InnerSpacingY   , 14L, 1L);

		MV_START_EXTRA_COMMANDS
		MV_END_EXTRA_COMMANDS

		MV_START_GENERAL_CONSTANTS
		MV_END_GENERAL_CONSTANTS

        MV_START_COLOR_CONSTANTS
            MV_ADD_CONSTANT(mvThemeCol_DragFloat4_Text,         mvColor(255, 255, 255, 255), mvColor(128, 128, 128, 63)),
            MV_ADD_CONSTANT(mvThemeCol_DragFloat4_Bg,           mvColor( 41,  74, 122, 138), mvColor(128, 128, 128, 63)),
            MV_ADD_CONSTANT(mvThemeCol_DragFloat4_BgHovered,    mvColor( 66, 150, 250, 102), mvColor(128, 128, 128, 63)),
            MV_ADD_CONSTANT(mvThemeCol_DragFloat4_BgActive,     mvColor( 66, 150, 250, 171), mvColor(128, 128, 128, 63)),
            MV_ADD_CONSTANT(mvThemeCol_DragFloat4_Border,       mvColor(110, 110, 128, 128), mvColor(128, 128, 128, 63)),
            MV_ADD_CONSTANT(mvThemeCol_DragFloat4_BorderShadow, mvColor(  0,   0,   0,   0), mvColor(128, 128, 128, 63)),
        MV_END_COLOR_CONSTANTS

        MV_START_STYLE_CONSTANTS
            MV_ADD_CONSTANT(mvThemeStyle_DragFloat4_Rounding       , 0, 12),
            MV_ADD_CONSTANT(mvThemeStyle_DragFloat4_BorderSize     , 0,  1),
            MV_ADD_CONSTANT(mvThemeStyle_DragFloat4_PaddingX       , 4, 20),
            MV_ADD_CONSTANT(mvThemeStyle_DragFloat4_PaddingY       , 3, 20),
            MV_ADD_CONSTANT(mvThemeStyle_DragFloat4_InnerSpacingX  , 4, 20),
            MV_ADD_CONSTANT(mvThemeStyle_DragFloat4_InnerSpacingY  , 4, 20),
        MV_END_STYLE_CONSTANTS

    public:

        static void InsertParser(std::map<std::string, mvPythonParser>* parsers);

    public:

        mvDragFloat4(const std::string& name, float* default_value, const std::string& dataSource);
        
        void setEnabled(bool value) override;
        void draw(ImDrawList* drawlist, float x, float y) override;

        void setExtraConfigDict(PyObject* dict) override;
        void getExtraConfigDict(PyObject* dict) override;

    private:

        float               m_speed = 1.0f;
        float               m_min = 0.0f;
        float               m_max = 100.0f;
        std::string         m_format = "%.3f";
        ImGuiInputTextFlags m_flags = ImGuiSliderFlags_None;
        ImGuiInputTextFlags m_stor_flags = ImGuiSliderFlags_None;
    };
        
    //-----------------------------------------------------------------------------
    // mvDragInt
    //----------------------------------------------------------------------------- 
    MV_REGISTER_WIDGET(mvDragInt);
    class mvDragInt : public mvIntPtrBase
    {

        MV_APPITEM_TYPE(mvAppItemType::mvDragInt, add_drag_int)

        MV_CREATE_CONSTANT(mvThemeCol_DragInt_Text            ,  0L, 0L);
        MV_CREATE_CONSTANT(mvThemeCol_DragInt_Bg              ,  7L, 0L);
        MV_CREATE_CONSTANT(mvThemeCol_DragInt_BgHovered       ,  8L, 0L);
        MV_CREATE_CONSTANT(mvThemeCol_DragInt_BgActive        ,  9L, 0L);
        MV_CREATE_CONSTANT(mvThemeCol_DragInt_Border          ,  5L, 0L);
        MV_CREATE_CONSTANT(mvThemeCol_DragInt_BorderShadow    ,  6L, 0L);

        MV_CREATE_CONSTANT(mvThemeStyle_DragInt_Rounding      , 11L, 0L);
        MV_CREATE_CONSTANT(mvThemeStyle_DragInt_BorderSize    , 12L, 0L);
        MV_CREATE_CONSTANT(mvThemeStyle_DragInt_PaddingX      , 10L, 0L);
        MV_CREATE_CONSTANT(mvThemeStyle_DragInt_PaddingY      , 10L, 1L);
        MV_CREATE_CONSTANT(mvThemeStyle_DragInt_InnerSpacingX , 14L, 0L);
        MV_CREATE_CONSTANT(mvThemeStyle_DragInt_InnerSpacingY , 14L, 1L);

		MV_START_EXTRA_COMMANDS
		MV_END_EXTRA_COMMANDS

		MV_START_GENERAL_CONSTANTS
		MV_END_GENERAL_CONSTANTS

        MV_START_COLOR_CONSTANTS
            MV_ADD_CONSTANT(mvThemeCol_DragInt_Text,         mvColor(255, 255, 255, 255), mvColor(128, 128, 128, 63)),
            MV_ADD_CONSTANT(mvThemeCol_DragInt_Bg,           mvColor( 41,  74, 122, 138), mvColor(128, 128, 128, 63)),
            MV_ADD_CONSTANT(mvThemeCol_DragInt_BgHovered,    mvColor( 66, 150, 250, 102), mvColor(128, 128, 128, 63)),
            MV_ADD_CONSTANT(mvThemeCol_DragInt_BgActive,     mvColor( 66, 150, 250, 171), mvColor(128, 128, 128, 63)),
            MV_ADD_CONSTANT(mvThemeCol_DragInt_Border,       mvColor(110, 110, 128, 128), mvColor(128, 128, 128, 63)),
            MV_ADD_CONSTANT(mvThemeCol_DragInt_BorderShadow, mvColor(  0,   0,   0,   0), mvColor(128, 128, 128, 63)),
        MV_END_COLOR_CONSTANTS

        MV_START_STYLE_CONSTANTS
            MV_ADD_CONSTANT(mvThemeStyle_DragInt_Rounding     , 0, 12),
            MV_ADD_CONSTANT(mvThemeStyle_DragInt_BorderSize   , 0,  1),
            MV_ADD_CONSTANT(mvThemeStyle_DragInt_PaddingX     , 4, 20),
            MV_ADD_CONSTANT(mvThemeStyle_DragInt_PaddingY     , 3, 20),
            MV_ADD_CONSTANT(mvThemeStyle_DragInt_InnerSpacingX, 4, 20),
            MV_ADD_CONSTANT(mvThemeStyle_DragInt_InnerSpacingY, 4, 20),
        MV_END_STYLE_CONSTANTS

    public:

        static void InsertParser(std::map<std::string, mvPythonParser>* parsers);

    public:

        mvDragInt(const std::string& name, int default_value, const std::string& dataSource);
        
        void setEnabled(bool value) override;
        void draw(ImDrawList* drawlist, float x, float y) override;

        void setExtraConfigDict(PyObject* dict) override;
        void getExtraConfigDict(PyObject* dict) override;
       
    private:

        float               m_speed = 1.0f;
        int                 m_min = 0;
        int                 m_max = 100;
        std::string         m_format = "%d";
        ImGuiInputTextFlags m_flags = ImGuiSliderFlags_None;
        ImGuiInputTextFlags m_stor_flags = ImGuiSliderFlags_None;

    };
        
    //-----------------------------------------------------------------------------
    // mvDragInt2
    //-----------------------------------------------------------------------------
    MV_REGISTER_WIDGET(mvDragInt2);
    class mvDragInt2 : public mvInt2PtrBase
    {

        MV_APPITEM_TYPE(mvAppItemType::mvDragInt2, add_drag_int2)

        MV_CREATE_CONSTANT(mvThemeCol_DragInt2_Text              ,  0L, 0L);
        MV_CREATE_CONSTANT(mvThemeCol_DragInt2_Bg                ,  7L, 0L);
        MV_CREATE_CONSTANT(mvThemeCol_DragInt2_BgHovered         ,  8L, 0L);
        MV_CREATE_CONSTANT(mvThemeCol_DragInt2_BgActive          ,  9L, 0L);
        MV_CREATE_CONSTANT(mvThemeCol_DragInt2_Border            ,  5L, 0L);
        MV_CREATE_CONSTANT(mvThemeCol_DragInt2_BorderShadow      ,  6L, 0L);

        MV_CREATE_CONSTANT(mvThemeStyle_DragInt2_Rounding        , 11L, 0L);
        MV_CREATE_CONSTANT(mvThemeStyle_DragInt2_BorderSize      , 12L, 0L);
        MV_CREATE_CONSTANT(mvThemeStyle_DragInt2_PaddingX        , 10L, 0L);
        MV_CREATE_CONSTANT(mvThemeStyle_DragInt2_PaddingY        , 10L, 1L);
        MV_CREATE_CONSTANT(mvThemeStyle_DragInt2_InnerSpacingX   , 14L, 0L);
        MV_CREATE_CONSTANT(mvThemeStyle_DragInt2_InnerSpacingY   , 14L, 1L);

		MV_START_EXTRA_COMMANDS
		MV_END_EXTRA_COMMANDS

		MV_START_GENERAL_CONSTANTS
		MV_END_GENERAL_CONSTANTS

        MV_START_COLOR_CONSTANTS
            MV_ADD_CONSTANT(mvThemeCol_DragInt2_Text,         mvColor(255, 255, 255, 255), mvColor(128, 128, 128, 63)),
            MV_ADD_CONSTANT(mvThemeCol_DragInt2_Bg,           mvColor( 41,  74, 122, 138), mvColor(128, 128, 128, 63)),
            MV_ADD_CONSTANT(mvThemeCol_DragInt2_BgHovered,    mvColor( 66, 150, 250, 102), mvColor(128, 128, 128, 63)),
            MV_ADD_CONSTANT(mvThemeCol_DragInt2_BgActive,     mvColor( 66, 150, 250, 171), mvColor(128, 128, 128, 63)),
            MV_ADD_CONSTANT(mvThemeCol_DragInt2_Border,       mvColor(110, 110, 128, 128), mvColor(128, 128, 128, 63)),
            MV_ADD_CONSTANT(mvThemeCol_DragInt2_BorderShadow, mvColor(  0,   0,   0,   0), mvColor(128, 128, 128, 63)),
        MV_END_COLOR_CONSTANTS

        MV_START_STYLE_CONSTANTS
            MV_ADD_CONSTANT(mvThemeStyle_DragInt2_Rounding     , 0, 12),
            MV_ADD_CONSTANT(mvThemeStyle_DragInt2_BorderSize   , 0,  1),
            MV_ADD_CONSTANT(mvThemeStyle_DragInt2_PaddingX     , 4, 20),
            MV_ADD_CONSTANT(mvThemeStyle_DragInt2_PaddingY     , 3, 20),
            MV_ADD_CONSTANT(mvThemeStyle_DragInt2_InnerSpacingX, 4, 20),
            MV_ADD_CONSTANT(mvThemeStyle_DragInt2_InnerSpacingY, 4, 20),
        MV_END_STYLE_CONSTANTS

    public:

        static void InsertParser(std::map<std::string, mvPythonParser>* parsers);

    public:

        mvDragInt2(const std::string& name, int* default_value, const std::string& dataSource);
        
        void setEnabled(bool value) override;
        void draw(ImDrawList* drawlist, float x, float y) override;

        void setExtraConfigDict(PyObject* dict) override;
        void getExtraConfigDict(PyObject* dict) override;

    private:

        float               m_speed = 1.0f;
        int                 m_min = 0;
        int                 m_max = 100;
        std::string         m_format = "%d";
        ImGuiInputTextFlags m_flags = ImGuiSliderFlags_None;
        ImGuiInputTextFlags m_stor_flags = ImGuiSliderFlags_None;

    };
        
    //-----------------------------------------------------------------------------
    // mvDragInt3
    //-----------------------------------------------------------------------------
    MV_REGISTER_WIDGET(mvDragInt3);
    class mvDragInt3 : public mvInt3PtrBase
    {

        MV_APPITEM_TYPE(mvAppItemType::mvDragInt3, add_drag_int3)

        MV_CREATE_CONSTANT(mvThemeCol_DragInt3_Text              ,  0L, 0L);
        MV_CREATE_CONSTANT(mvThemeCol_DragInt3_Bg                ,  7L, 0L);
        MV_CREATE_CONSTANT(mvThemeCol_DragInt3_BgHovered         ,  8L, 0L);
        MV_CREATE_CONSTANT(mvThemeCol_DragInt3_BgActive          ,  9L, 0L);
        MV_CREATE_CONSTANT(mvThemeCol_DragInt3_Border            ,  5L, 0L);
        MV_CREATE_CONSTANT(mvThemeCol_DragInt3_BorderShadow      ,  6L, 0L);

        MV_CREATE_CONSTANT(mvThemeStyle_DragInt3_Rounding        , 11L, 0L);
        MV_CREATE_CONSTANT(mvThemeStyle_DragInt3_BorderSize      , 12L, 0L);
        MV_CREATE_CONSTANT(mvThemeStyle_DragInt3_PaddingX        , 10L, 0L);
        MV_CREATE_CONSTANT(mvThemeStyle_DragInt3_PaddingY        , 10L, 1L);
        MV_CREATE_CONSTANT(mvThemeStyle_DragInt3_InnerSpacingX   , 14L, 0L);
        MV_CREATE_CONSTANT(mvThemeStyle_DragInt3_InnerSpacingY   , 14L, 1L);

		MV_START_EXTRA_COMMANDS
		MV_END_EXTRA_COMMANDS

		MV_START_GENERAL_CONSTANTS
		MV_END_GENERAL_CONSTANTS

        MV_START_COLOR_CONSTANTS
            MV_ADD_CONSTANT(mvThemeCol_DragInt3_Text,         mvColor(255, 255, 255, 255), mvColor(128, 128, 128, 63)),
            MV_ADD_CONSTANT(mvThemeCol_DragInt3_Bg,           mvColor( 41,  74, 122, 138), mvColor(128, 128, 128, 63)),
            MV_ADD_CONSTANT(mvThemeCol_DragInt3_BgHovered,    mvColor( 66, 150, 250, 102), mvColor(128, 128, 128, 63)),
            MV_ADD_CONSTANT(mvThemeCol_DragInt3_BgActive,     mvColor( 66, 150, 250, 171), mvColor(128, 128, 128, 63)),
            MV_ADD_CONSTANT(mvThemeCol_DragInt3_Border,       mvColor(110, 110, 128, 128), mvColor(128, 128, 128, 63)),
            MV_ADD_CONSTANT(mvThemeCol_DragInt3_BorderShadow, mvColor(  0,   0,   0,   0), mvColor(128, 128, 128, 63)),
        MV_END_COLOR_CONSTANTS

        MV_START_STYLE_CONSTANTS
            MV_ADD_CONSTANT(mvThemeStyle_DragInt3_Rounding     , 0, 12),
            MV_ADD_CONSTANT(mvThemeStyle_DragInt3_BorderSize   , 0,  1),
            MV_ADD_CONSTANT(mvThemeStyle_DragInt3_PaddingX     , 4, 20),
            MV_ADD_CONSTANT(mvThemeStyle_DragInt3_PaddingY     , 3, 20),
            MV_ADD_CONSTANT(mvThemeStyle_DragInt3_InnerSpacingX, 4, 20),
            MV_ADD_CONSTANT(mvThemeStyle_DragInt3_InnerSpacingY, 4, 20),
        MV_END_STYLE_CONSTANTS

    public:

        static void InsertParser(std::map<std::string, mvPythonParser>* parsers);

    public:

        mvDragInt3(const std::string& name, int* default_value, const std::string& dataSource);
        
        void setEnabled(bool value) override;
        void draw(ImDrawList* drawlist, float x, float y) override;

        void setExtraConfigDict(PyObject* dict) override;
        void getExtraConfigDict(PyObject* dict) override;

    private:

        float               m_speed = 1.0f;
        int                 m_min = 0;
        int                 m_max = 100;
        std::string         m_format = "%d";
        ImGuiInputTextFlags m_flags = ImGuiSliderFlags_None;
        ImGuiInputTextFlags m_stor_flags = ImGuiSliderFlags_None;
    };
        
    //-----------------------------------------------------------------------------
    // mvDragInt4
    //-----------------------------------------------------------------------------
    MV_REGISTER_WIDGET(mvDragInt4);
    class mvDragInt4 : public mvInt4PtrBase
    {
  
        MV_APPITEM_TYPE(mvAppItemType::mvDragInt4, add_drag_int4)

        MV_CREATE_CONSTANT(mvThemeCol_DragInt4_Text              ,  0L, 0L);
        MV_CREATE_CONSTANT(mvThemeCol_DragInt4_Bg                ,  7L, 0L);
        MV_CREATE_CONSTANT(mvThemeCol_DragInt4_BgHovered         ,  8L, 0L);
        MV_CREATE_CONSTANT(mvThemeCol_DragInt4_BgActive          ,  9L, 0L);
        MV_CREATE_CONSTANT(mvThemeCol_DragInt4_Border            ,  5L, 0L);
        MV_CREATE_CONSTANT(mvThemeCol_DragInt4_BorderShadow      ,  6L, 0L);

        MV_CREATE_CONSTANT(mvThemeStyle_DragInt4_Rounding        , 11L, 0L);
        MV_CREATE_CONSTANT(mvThemeStyle_DragInt4_BorderSize      , 12L, 0L);
        MV_CREATE_CONSTANT(mvThemeStyle_DragInt4_PaddingX        , 10L, 0L);
        MV_CREATE_CONSTANT(mvThemeStyle_DragInt4_PaddingY        , 10L, 1L);
        MV_CREATE_CONSTANT(mvThemeStyle_DragInt4_InnerSpacingX   , 14L, 0L);
        MV_CREATE_CONSTANT(mvThemeStyle_DragInt4_InnerSpacingY   , 14L, 1L);

		MV_START_EXTRA_COMMANDS
		MV_END_EXTRA_COMMANDS

		MV_START_GENERAL_CONSTANTS
		MV_END_GENERAL_CONSTANTS

        MV_START_COLOR_CONSTANTS
            MV_ADD_CONSTANT(mvThemeCol_DragInt4_Text,         mvColor(255, 255, 255, 255), mvColor(128, 128, 128, 63)),
            MV_ADD_CONSTANT(mvThemeCol_DragInt4_Bg,           mvColor( 41,  74, 122, 138), mvColor(128, 128, 128, 63)),
            MV_ADD_CONSTANT(mvThemeCol_DragInt4_BgHovered,    mvColor( 66, 150, 250, 102), mvColor(128, 128, 128, 63)),
            MV_ADD_CONSTANT(mvThemeCol_DragInt4_BgActive,     mvColor( 66, 150, 250, 171), mvColor(128, 128, 128, 63)),
            MV_ADD_CONSTANT(mvThemeCol_DragInt4_Border,       mvColor(110, 110, 128, 128), mvColor(128, 128, 128, 63)),
            MV_ADD_CONSTANT(mvThemeCol_DragInt4_BorderShadow, mvColor(  0,   0,   0,   0), mvColor(128, 128, 128, 63)),
        MV_END_COLOR_CONSTANTS

        MV_START_STYLE_CONSTANTS
            MV_ADD_CONSTANT(mvThemeStyle_DragInt4_Rounding     , 0, 12),
            MV_ADD_CONSTANT(mvThemeStyle_DragInt4_BorderSize   , 0,  1),
            MV_ADD_CONSTANT(mvThemeStyle_DragInt4_PaddingX     , 4, 20),
            MV_ADD_CONSTANT(mvThemeStyle_DragInt4_PaddingY     , 3, 20),
            MV_ADD_CONSTANT(mvThemeStyle_DragInt4_InnerSpacingX, 4, 20),
            MV_ADD_CONSTANT(mvThemeStyle_DragInt4_InnerSpacingY, 4, 20),
        MV_END_STYLE_CONSTANTS

    public:

        static void InsertParser(std::map<std::string, mvPythonParser>* parsers);

    public:

        mvDragInt4(const std::string& name, int* default_value, const std::string& dataSource);
        
        void setEnabled(bool value) override;
        void draw(ImDrawList* drawlist, float x, float y) override;

        void setExtraConfigDict(PyObject* dict) override;
        void getExtraConfigDict(PyObject* dict) override;
        
    private:

        float               m_speed = 1.0f;
        int                 m_min = 0;
        int                 m_max = 100;
        std::string         m_format = "%d";
        ImGuiInputTextFlags m_flags = ImGuiSliderFlags_None;
        ImGuiInputTextFlags m_stor_flags = ImGuiSliderFlags_None;

    };

}