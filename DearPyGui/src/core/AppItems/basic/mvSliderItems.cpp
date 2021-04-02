#include "mvSliderItems.h"
#include "mvTypeBases.h"
#include <utility>
#include "mvAppItem.h"
#include "mvModule_Core.h"
#include "mvApp.h"
#include <string>
#include "mvItemRegistry.h"
#include "mvImGuiThemeScope.h"
#include "mvFontScope.h"

namespace Marvel {

    void mvSliderFloat::InsertParser(std::map<std::string, mvPythonParser>* parsers)
    {
        parsers->insert({ s_command, mvPythonParser({
            {mvPythonDataType::Optional},
            {mvPythonDataType::String, "name"},
            {mvPythonDataType::KeywordOnly},
            {mvPythonDataType::Float, "default_value", "", "0.0"},
            {mvPythonDataType::Float, "min_value", "", "0.0"},
            {mvPythonDataType::Float, "max_value", "", "100.0"},
            {mvPythonDataType::String, "format", "", "'%.3f'"},
            {mvPythonDataType::Bool, "vertical", "sets orientation to vertical", "False"},
            {mvPythonDataType::Callable, "callback", "Registers a callback", "None"},
            {mvPythonDataType::Object, "callback_data", "Callback data", "None"},
            {mvPythonDataType::String, "parent", "Parent this item will be added to. (runtime adding)", "''"},
            {mvPythonDataType::String, "before", "This item will be displayed before the specified item in the parent. (runtime adding)", "''"},
            {mvPythonDataType::String, "source", "", "''"},
            {mvPythonDataType::Bool, "enabled", "Display grayed out text so selectable cannot be selected", "True"},
            {mvPythonDataType::Integer, "width","", "0"},
            {mvPythonDataType::Integer, "height","Height of a vertical slider", "0"},
            {mvPythonDataType::Bool, "no_input", "Disable CTRL+Click or Enter key allowing to input text directly into the widget", "False"},
            {mvPythonDataType::Bool, "clamped", "Clamp value to min/max bounds when input manually with CTRL+Click. By default CTRL+Click allows going out of bounds.", "False"},
            {mvPythonDataType::String, "label", "", "''"},
            {mvPythonDataType::Bool, "show", "Attempt to render", "True"},
        }, "Adds slider for a single float value. CTRL+Click to directly modify the value.", "None", "Adding Widgets") });

    }

    void mvSliderFloat2::InsertParser(std::map<std::string, mvPythonParser>* parsers)
    {
        parsers->insert({ "add_slider_float2", mvPythonParser({
            {mvPythonDataType::String, "name"},
            {mvPythonDataType::KeywordOnly},
            {mvPythonDataType::FloatList, "default_value", "", "(0.0, 0.0)"},
            {mvPythonDataType::Float, "min_value", "", "0.0"},
            {mvPythonDataType::Float, "max_value", "", "100.0"},
            {mvPythonDataType::String, "format", "", "'%.3f'"},
            {mvPythonDataType::Callable, "callback", "Registers a callback", "None"},
            {mvPythonDataType::Object, "callback_data", "Callback data", "None"},
            {mvPythonDataType::String, "parent", "Parent this item will be added to. (runtime adding)", "''"},
            {mvPythonDataType::String, "before", "This item will be displayed before the specified item in the parent. (runtime adding)", "''"},
            {mvPythonDataType::String, "source", "", "''"},
            {mvPythonDataType::Bool, "enabled", "Display grayed out text so selectable cannot be selected", "True"},
            {mvPythonDataType::Integer, "width","", "0"},
            {mvPythonDataType::Bool, "no_input", "Disable CTRL+Click or Enter key allowing to input text directly into the widget", "False"},
            {mvPythonDataType::Bool, "clamped", "Clamp value to min/max bounds when input manually with CTRL+Click. By default CTRL+Click allows going out of bounds.", "False"},
            {mvPythonDataType::String, "label", "", "''"},
            {mvPythonDataType::Bool, "show", "Attempt to render", "True"},
        }, "Adds slider for a 2 float values. CTRL+Click to directly modify the value.", "None", "Adding Widgets") });

    }

    void mvSliderFloat3::InsertParser(std::map<std::string, mvPythonParser>* parsers)
    {
        parsers->insert({ "add_slider_float3", mvPythonParser({
            {mvPythonDataType::String, "name"},
            {mvPythonDataType::KeywordOnly},
            {mvPythonDataType::FloatList, "default_value", "", "(0.0, 0.0, 0.0)"},
            {mvPythonDataType::Float, "min_value", "", "0.0"},
            {mvPythonDataType::Float, "max_value", "", "100.0"},
            {mvPythonDataType::String, "format", "", "'%.3f'"},
            {mvPythonDataType::Callable, "callback", "Registers a callback", "None"},
            {mvPythonDataType::Object, "callback_data", "Callback data", "None"},
            {mvPythonDataType::String, "parent", "Parent this item will be added to. (runtime adding)", "''"},
            {mvPythonDataType::String, "before", "This item will be displayed before the specified item in the parent. (runtime adding)", "''"},
            {mvPythonDataType::String, "source", "", "''"},
            {mvPythonDataType::Bool, "enabled", "Display grayed out text so selectable cannot be selected", "True"},
            {mvPythonDataType::Integer, "width","", "0"},
            {mvPythonDataType::Bool, "no_input", "Disable CTRL+Click or Enter key allowing to input text directly into the widget", "False"},
            {mvPythonDataType::Bool, "clamped", "Clamp value to min/max bounds when input manually with CTRL+Click. By default CTRL+Click allows going out of bounds.", "False"},
            {mvPythonDataType::String, "label", "", "''"},
            {mvPythonDataType::Bool, "show", "Attempt to render", "True"},
        }, "Adds slider for a 3 float values. CTRL+Click to directly modify the value.", "None", "Adding Widgets") });

    }

    void mvSliderFloat4::InsertParser(std::map<std::string, mvPythonParser>* parsers)
    {
        parsers->insert({ "add_slider_float4", mvPythonParser({
            {mvPythonDataType::String, "name"},
            {mvPythonDataType::KeywordOnly},
            {mvPythonDataType::FloatList, "default_value", "", "(0.0, 0.0, 0.0, 0.0)"},
            {mvPythonDataType::Float, "min_value", "", "0.0"},
            {mvPythonDataType::Float, "max_value", "", "100.0"},
            {mvPythonDataType::String, "format", "", "'%.3f'"},
            {mvPythonDataType::Callable, "callback", "Registers a callback", "None"},
            {mvPythonDataType::Object, "callback_data", "Callback data", "None"},
            {mvPythonDataType::String, "parent", "Parent this item will be added to. (runtime adding)", "''"},
            {mvPythonDataType::String, "before", "This item will be displayed before the specified item in the parent. (runtime adding)", "''"},
            {mvPythonDataType::String, "source", "", "''"},
            {mvPythonDataType::Bool, "enabled", "Display grayed out text so selectable cannot be selected", "True"},
            {mvPythonDataType::Integer, "width","", "0"},
            {mvPythonDataType::Bool, "no_input", "Disable CTRL+Click or Enter key allowing to input text directly into the widget", "False"},
            {mvPythonDataType::Bool, "clamped", "Clamp value to min/max bounds when input manually with CTRL+Click. By default CTRL+Click allows going out of bounds.", "False"},
            {mvPythonDataType::String, "label", "", "''"},
            {mvPythonDataType::Bool, "show", "Attempt to render", "True"},
        }, "Adds slider for a 4 float values. CTRL+Click to directly modify the value.", "None", "Adding Widgets") });

    }

    void mvSliderInt::InsertParser(std::map<std::string, mvPythonParser>* parsers)
    {
        parsers->insert({ "add_slider_int", mvPythonParser({
            {mvPythonDataType::String, "name"},
            {mvPythonDataType::KeywordOnly},
            {mvPythonDataType::Integer, "default_value", "", "0"},
            {mvPythonDataType::Integer, "min_value", "", "0"},
            {mvPythonDataType::Integer, "max_value", "", "100"},
            {mvPythonDataType::String, "format", "", "'%d'"},
            {mvPythonDataType::Bool, "vertical", "sets orientation to vertical", "False"},
            {mvPythonDataType::Callable, "callback", "Registers a callback", "None"},
            {mvPythonDataType::Object, "callback_data", "Callback data", "None"},
            {mvPythonDataType::String, "parent", "Parent this item will be added to. (runtime adding)", "''"},
            {mvPythonDataType::String, "before", "This item will be displayed before the specified item in the parent. (runtime adding)", "''"},
            {mvPythonDataType::String, "source", "", "''"},
            {mvPythonDataType::Bool, "enabled", "Display grayed out text so selectable cannot be selected", "True"},
            {mvPythonDataType::Integer, "width","", "0"},
            {mvPythonDataType::Integer, "height","Height of a vertical slider", "0"},
            {mvPythonDataType::Bool, "no_input", "Disable CTRL+Click or Enter key allowing to input text directly into the widget", "False"},
            {mvPythonDataType::Bool, "clamped", "Clamp value to min/max bounds when input manually with CTRL+Click. By default CTRL+Click allows going out of bounds.", "False"},
            {mvPythonDataType::String, "label", "", "''"},
            {mvPythonDataType::Bool, "show", "Attempt to render", "True"},
        }, "Adds slider for a single int value. CTRL+Click to directly modify the value.", "None", "Adding Widgets") });

    }

    void mvSliderInt2::InsertParser(std::map<std::string, mvPythonParser>* parsers)
    {
        parsers->insert({ "add_slider_int2", mvPythonParser({
            {mvPythonDataType::String, "name"},
            {mvPythonDataType::KeywordOnly},
            {mvPythonDataType::IntList, "default_value", "", "(0, 0)"},
            {mvPythonDataType::Integer, "min_value", "", "0"},
            {mvPythonDataType::Integer, "max_value", "", "100"},
            {mvPythonDataType::String, "format", "", "'%d'"},
            {mvPythonDataType::Callable, "callback", "Registers a callback", "None"},
            {mvPythonDataType::Object, "callback_data", "Callback data", "None"},
            {mvPythonDataType::String, "parent", "Parent this item will be added to. (runtime adding)", "''"},
            {mvPythonDataType::String, "before", "This item will be displayed before the specified item in the parent. (runtime adding)", "''"},
            {mvPythonDataType::String, "source", "", "''"},
            {mvPythonDataType::Bool, "enabled", "Display grayed out text so selectable cannot be selected", "True"},
            {mvPythonDataType::Integer, "width","", "0"},
            {mvPythonDataType::Bool, "no_input", "Disable CTRL+Click or Enter key allowing to input text directly into the widget", "False"},
            {mvPythonDataType::Bool, "clamped", "Clamp value to min/max bounds when input manually with CTRL+Click. By default CTRL+Click allows going out of bounds.", "False"},
            {mvPythonDataType::String, "label", "", "''"},
            {mvPythonDataType::Bool, "show", "Attempt to render", "True"},
        }, "Adds slider for a 2 int values. CTRL+Click to directly modify the value.", "None", "Adding Widgets") });

    }

    void mvSliderInt3::InsertParser(std::map<std::string, mvPythonParser>* parsers)
    {
        parsers->insert({ "add_slider_int3", mvPythonParser({
            {mvPythonDataType::String, "name"},
            {mvPythonDataType::KeywordOnly},
            {mvPythonDataType::IntList, "default_value", "", "(0, 0, 0)"},
            {mvPythonDataType::Integer, "min_value", "", "0"},
            {mvPythonDataType::Integer, "max_value", "", "100"},
            {mvPythonDataType::String, "format", "", "'%d'"},
            {mvPythonDataType::Callable, "callback", "Registers a callback", "None"},
            {mvPythonDataType::Object, "callback_data", "Callback data", "None"},
            {mvPythonDataType::String, "parent", "Parent this item will be added to. (runtime adding)", "''"},
            {mvPythonDataType::String, "before", "This item will be displayed before the specified item in the parent. (runtime adding)", "''"},
            {mvPythonDataType::String, "source", "", "''"},
            {mvPythonDataType::Bool, "enabled", "Display grayed out text so selectable cannot be selected", "True"},
            {mvPythonDataType::Integer, "width","", "0"},
            {mvPythonDataType::Bool, "no_input", "Disable CTRL+Click or Enter key allowing to input text directly into the widget", "False"},
            {mvPythonDataType::Bool, "clamped", "Clamp value to min/max bounds when input manually with CTRL+Click. By default CTRL+Click allows going out of bounds.", "False"},
            {mvPythonDataType::String, "label", "", "''"},
            {mvPythonDataType::Bool, "show", "Attempt to render", "True"},
        }, "Adds slider for a 3 int values. CTRL+Click to directly modify the value.", "None", "Adding Widgets") });

    }

    void mvSliderInt4::InsertParser(std::map<std::string, mvPythonParser>* parsers)
    {
        parsers->insert({ "add_slider_int4", mvPythonParser({
            {mvPythonDataType::String, "name"},
            {mvPythonDataType::KeywordOnly},
            {mvPythonDataType::IntList, "default_value", "", "(0, 0, 0, 0)"},
            {mvPythonDataType::Integer, "min_value", "", "0"},
            {mvPythonDataType::Integer, "max_value", "", "100"},
            {mvPythonDataType::String, "format", "", "'%d'"},
            {mvPythonDataType::Callable, "callback", "Registers a callback", "None"},
            {mvPythonDataType::Object, "callback_data", "Callback data", "None"},
            {mvPythonDataType::String, "parent", "Parent this item will be added to. (runtime adding)", "''"},
            {mvPythonDataType::String, "before", "This item will be displayed before the specified item in the parent. (runtime adding)", "''"},
            {mvPythonDataType::String, "source", "", "''"},
            {mvPythonDataType::Bool, "enabled", "Display grayed out text so selectable cannot be selected", "True"},
            {mvPythonDataType::Integer, "width","", "0"},
            {mvPythonDataType::Bool, "no_input", "Disable CTRL+Click or Enter key allowing to input text directly into the widget", "False"},
            {mvPythonDataType::Bool, "clamped", "Clamp value to min/max bounds when input manually with CTRL+Click. By default CTRL+Click allows going out of bounds.", "False"},
            {mvPythonDataType::String, "label", "", "''"},
            {mvPythonDataType::Bool, "show", "Attempt to render", "True"},
        }, "Adds slider for a 4 int values. CTRL+Click to directly modify the value.", "None", "Adding Widgets") });

    }

    mvSliderFloat::mvSliderFloat(const std::string& name, float default_value, const std::string& dataSource)
        : mvFloatPtrBase(name, default_value)
    {
        m_description.disableAllowed = true;
    }

    void mvSliderFloat::setEnabled(bool value)
    {
        if (value == m_enabled)
            return;

        if (value)
            m_flags = m_stor_flags;

        else
        {
            m_stor_flags = m_flags;
            m_flags |= ImGuiSliderFlags_NoInput;
        }

        m_enabled = value;
    }

    void mvSliderFloat::draw(ImDrawList* drawlist, float x, float y)
    {
        ScopedID id;
        mvImGuiThemeScope scope(this);
        mvFontScope fscope(this);

        if (!m_enabled) m_disabled_value = *m_value;

        if (m_vertical)
        {
            if ((float)m_height < 1.0f)
                m_height = 100;
            if ((float)m_width < 1.0f)
                m_width = 20;

            if (ImGui::VSliderFloat(m_label.c_str(), ImVec2((float)m_width, (float)m_height), m_enabled ? m_value.get() : &m_disabled_value, m_min, m_max, m_format.c_str()))
                mvApp::GetApp()->getCallbackRegistry().addCallback(getCallback(false), m_name, m_callback_data);

        }
        else
        {
            if (ImGui::SliderFloat(m_label.c_str(), m_enabled ? m_value.get() : &m_disabled_value, m_min, m_max, m_format.c_str(), m_flags))
                mvApp::GetApp()->getCallbackRegistry().addCallback(getCallback(false), m_name, m_callback_data);

        }
    }

    mvSliderFloat2::mvSliderFloat2(const std::string& name, float* default_value, const std::string& dataSource)
        : mvFloat2PtrBase(name, default_value)
    {
        m_description.disableAllowed = true;
    }

    void mvSliderFloat2::setEnabled(bool value)
    {
        if (value == m_enabled)
            return;

        if (value)
            m_flags = m_stor_flags;

        else
        {
            m_stor_flags = m_flags;
            m_flags |= ImGuiSliderFlags_NoInput;
        }

        m_enabled = value;
    }

    void mvSliderFloat2::draw(ImDrawList* drawlist, float x, float y)
    {
        ScopedID id;
        mvImGuiThemeScope scope(this);
        mvFontScope fscope(this);

        if (!m_enabled) std::copy(m_value->data(), m_value->data() + 2, m_disabled_value);

        if (ImGui::SliderFloat2(m_label.c_str(), m_enabled ? m_value->data() : &m_disabled_value[0], m_min, m_max, m_format.c_str(), m_flags))
            mvApp::GetApp()->getCallbackRegistry().addCallback(getCallback(false), m_name, m_callback_data);
    }

    mvSliderFloat3::mvSliderFloat3(const std::string& name, float* default_value, const std::string& dataSource)
        : mvFloat3PtrBase(name, default_value)
    {
        m_description.disableAllowed = true;
    }

    void mvSliderFloat3::setEnabled(bool value)
    {
        if (value == m_enabled)
            return;

        if (value)
            m_flags = m_stor_flags;

        else
        {
            m_stor_flags = m_flags;
            m_flags |= ImGuiSliderFlags_NoInput;
        }

        m_enabled = value;
    }

    void mvSliderFloat3::draw(ImDrawList* drawlist, float x, float y)
    {
        ScopedID id;
        mvImGuiThemeScope scope(this);
        mvFontScope fscope(this);

        if (!m_enabled) std::copy(m_value->data(), m_value->data() + 3, m_disabled_value);

        if (ImGui::SliderFloat3(m_label.c_str(), m_enabled ? m_value->data() : &m_disabled_value[0], m_min, m_max, m_format.c_str(), m_flags))
            mvApp::GetApp()->getCallbackRegistry().addCallback(getCallback(false), m_name, m_callback_data);
    }

    mvSliderFloat4::mvSliderFloat4(const std::string& name, float* default_value, const std::string& dataSource)
        : mvFloat4PtrBase(name, default_value)
    {
        m_description.disableAllowed = true;
    }

    void mvSliderFloat4::setEnabled(bool value)
    {
        if (value == m_enabled)
            return;

        if (value)
            m_flags = m_stor_flags;

        else
        {
            m_stor_flags = m_flags;
            m_flags |= ImGuiSliderFlags_NoInput;
        }

        m_enabled = value;
    }

    void mvSliderFloat4::draw(ImDrawList* drawlist, float x, float y)
    {
        ScopedID id;
        mvImGuiThemeScope scope(this);
        mvFontScope fscope(this);

        if (!m_enabled) std::copy(m_value->data(), m_value->data() + 4, m_disabled_value);

        if (ImGui::SliderFloat4(m_label.c_str(), m_enabled ? m_value->data() : &m_disabled_value[0], m_min, m_max, m_format.c_str(), m_flags))
            mvApp::GetApp()->getCallbackRegistry().addCallback(getCallback(false), m_name, m_callback_data);
    }

    mvSliderInt::mvSliderInt(const std::string& name, int default_value, const std::string& dataSource)
        : mvIntPtrBase(name, default_value)
    {
        m_description.disableAllowed = true;
    }

    void mvSliderInt::setEnabled(bool value)
    {
        if (value == m_enabled)
            return;

        if (value)
            m_flags = m_stor_flags;

        else
        {
            m_stor_flags = m_flags;
            m_flags |= ImGuiSliderFlags_NoInput;
        }

        m_enabled = value;
    }

    void mvSliderInt::draw(ImDrawList* drawlist, float x, float y)
    {
        ScopedID id;
        mvImGuiThemeScope scope(this);
        mvFontScope fscope(this);

        if (!m_enabled) m_disabled_value = *m_value;

        if (m_vertical)
        {
            if ((float)m_height < 1.0f)
                m_height = 100;
            if ((float)m_width < 1.0f)
                m_width = 20;

            if (ImGui::VSliderInt(m_label.c_str(), ImVec2((float)m_width, (float)m_height), m_enabled ? m_value.get() : &m_disabled_value, m_min, m_max, m_format.c_str()))
                mvApp::GetApp()->getCallbackRegistry().addCallback(getCallback(false), m_name, m_callback_data);
        }
        else
        {
            if (ImGui::SliderInt(m_label.c_str(), m_enabled ? m_value.get() : &m_disabled_value, m_min, m_max, m_format.c_str(), m_flags))
                mvApp::GetApp()->getCallbackRegistry().addCallback(getCallback(false), m_name, m_callback_data);

        }
    }

    mvSliderInt2::mvSliderInt2(const std::string& name, int* default_value, const std::string& dataSource)
        : mvInt2PtrBase(name, default_value)
    {
        m_description.disableAllowed = true;
    }

    void mvSliderInt2::setEnabled(bool value)
    {
        if (value == m_enabled)
            return;

        if (value)
            m_flags = m_stor_flags;

        else
        {
            m_stor_flags = m_flags;
            m_flags |= ImGuiSliderFlags_NoInput;
        }

        m_enabled = value;
    }

    void mvSliderInt2::draw(ImDrawList* drawlist, float x, float y)
    {
        ScopedID id;
        mvImGuiThemeScope scope(this);
        mvFontScope fscope(this);

        if (!m_enabled) std::copy(m_value->data(), m_value->data() + 2, m_disabled_value);

        if (ImGui::SliderInt2(m_label.c_str(), m_enabled ? m_value->data() : &m_disabled_value[0], m_min, m_max, m_format.c_str(), m_flags))
            mvApp::GetApp()->getCallbackRegistry().addCallback(getCallback(false), m_name, m_callback_data);
    }

    mvSliderInt3::mvSliderInt3(const std::string& name, int* default_value, const std::string& dataSource)
        : mvInt3PtrBase(name, default_value)
    {
        m_description.disableAllowed = true;
    }

    void mvSliderInt3::setEnabled(bool value)
    {
        if (value == m_enabled)
            return;

        if (value)
            m_flags = m_stor_flags;

        else
        {
            m_stor_flags = m_flags;
            m_flags |= ImGuiSliderFlags_NoInput;
        }

        m_enabled = value;
    }

    void mvSliderInt3::draw(ImDrawList* drawlist, float x, float y)
    {
        ScopedID id;
        mvImGuiThemeScope scope(this);
        mvFontScope fscope(this);

        if (!m_enabled) std::copy(m_value->data(), m_value->data() + 3, m_disabled_value);

        if (ImGui::SliderInt3(m_label.c_str(), m_enabled ? m_value->data() : &m_disabled_value[0], m_min, m_max, m_format.c_str(), m_flags))
            mvApp::GetApp()->getCallbackRegistry().addCallback(getCallback(false), m_name, m_callback_data);
    }

    mvSliderInt4::mvSliderInt4(const std::string& name, int* default_value, const std::string& dataSource)
        : mvInt4PtrBase(name, default_value)
    {
        m_description.disableAllowed = true;
    }

    void mvSliderInt4::setEnabled(bool value)
    {
        if (value == m_enabled)
            return;

        if (value)
            m_flags = m_stor_flags;

        else
        {
            m_stor_flags = m_flags;
            m_flags |= ImGuiSliderFlags_NoInput;
        }

        m_enabled = value;
    }

    void mvSliderInt4::draw(ImDrawList* drawlist, float x, float y)
    {
        ScopedID id;
        mvImGuiThemeScope scope(this);
        mvFontScope fscope(this);

        if (!m_enabled) std::copy(m_value->data(), m_value->data() + 4, m_disabled_value);

        if (ImGui::SliderInt4(m_label.c_str(), m_enabled ? m_value->data() : &m_disabled_value[0], m_min, m_max, m_format.c_str(), m_flags))
            mvApp::GetApp()->getCallbackRegistry().addCallback(getCallback(false), m_name, m_callback_data);

    }

    void mvSliderFloat::setExtraConfigDict(PyObject* dict)
    {
        if (dict == nullptr)
            return;

        if (PyObject* item = PyDict_GetItemString(dict, "format")) m_format = ToString(item);
        if (PyObject* item = PyDict_GetItemString(dict, "vertical")) m_vertical = ToBool(item);
        if (PyObject* item = PyDict_GetItemString(dict, "min_value")) m_min = ToFloat(item);
        if (PyObject* item = PyDict_GetItemString(dict, "max_value")) m_max = ToFloat(item);

        // helper for bit flipping
        auto flagop = [dict](const char* keyword, int flag, int& flags)
        {
            if (PyObject* item = PyDict_GetItemString(dict, keyword)) ToBool(item) ? flags |= flag : flags &= ~flag;
        };

        // flags
        flagop("clamped", ImGuiSliderFlags_ClampOnInput, m_flags);
        flagop("clamped", ImGuiSliderFlags_ClampOnInput, m_stor_flags);
        flagop("no_input", ImGuiSliderFlags_NoInput, m_flags);
        flagop("no_input", ImGuiSliderFlags_NoInput, m_stor_flags);

    }

    void mvSliderFloat::getExtraConfigDict(PyObject* dict)
    {
        if (dict == nullptr)
            return;

        PyDict_SetItemString(dict, "format", ToPyString(m_format));
        PyDict_SetItemString(dict, "vertical", ToPyBool(m_vertical));
        PyDict_SetItemString(dict, "min_value", ToPyFloat(m_min));
        PyDict_SetItemString(dict, "max_value", ToPyFloat(m_max));

        // helper to check and set bit
        auto checkbitset = [dict](const char* keyword, int flag, const int& flags)
        {
            PyDict_SetItemString(dict, keyword, ToPyBool(flags & flag));
        };

        // window flags
        checkbitset("clamped", ImGuiSliderFlags_ClampOnInput, m_flags);
        checkbitset("no_input", ImGuiSliderFlags_NoInput, m_flags);

    }

    void mvSliderFloat2::setExtraConfigDict(PyObject* dict)
    {
        if (dict == nullptr)
            return;

        if (PyObject* item = PyDict_GetItemString(dict, "format")) m_format = ToString(item);
        if (PyObject* item = PyDict_GetItemString(dict, "min_value")) m_min = ToFloat(item);
        if (PyObject* item = PyDict_GetItemString(dict, "max_value")) m_max = ToFloat(item);

        // helper for bit flipping
        auto flagop = [dict](const char* keyword, int flag, int& flags)
        {
            if (PyObject* item = PyDict_GetItemString(dict, keyword)) ToBool(item) ? flags |= flag : flags &= ~flag;
        };

        // flags
        flagop("clamped", ImGuiSliderFlags_ClampOnInput, m_flags);
        flagop("clamped", ImGuiSliderFlags_ClampOnInput, m_stor_flags);
        flagop("no_input", ImGuiSliderFlags_NoInput, m_flags);
        flagop("no_input", ImGuiSliderFlags_NoInput, m_stor_flags);

    }

    void mvSliderFloat2::getExtraConfigDict(PyObject* dict)
    {
        if (dict == nullptr)
            return;

        PyDict_SetItemString(dict, "format", ToPyString(m_format));
        PyDict_SetItemString(dict, "min_value", ToPyFloat(m_min));
        PyDict_SetItemString(dict, "max_value", ToPyFloat(m_max));

        // helper to check and set bit
        auto checkbitset = [dict](const char* keyword, int flag, const int& flags)
        {
            PyDict_SetItemString(dict, keyword, ToPyBool(flags & flag));
        };

        // window flags
        checkbitset("clamped", ImGuiSliderFlags_ClampOnInput, m_flags);
        checkbitset("no_input", ImGuiSliderFlags_NoInput, m_flags);

    }

    void mvSliderFloat3::setExtraConfigDict(PyObject* dict)
    {
        if (dict == nullptr)
            return;

        if (PyObject* item = PyDict_GetItemString(dict, "format")) m_format = ToString(item);
        if (PyObject* item = PyDict_GetItemString(dict, "min_value")) m_min = ToFloat(item);
        if (PyObject* item = PyDict_GetItemString(dict, "max_value")) m_max = ToFloat(item);

        // helper for bit flipping
        auto flagop = [dict](const char* keyword, int flag, int& flags)
        {
            if (PyObject* item = PyDict_GetItemString(dict, keyword)) ToBool(item) ? flags |= flag : flags &= ~flag;
        };

        // flags
        flagop("clamped", ImGuiSliderFlags_ClampOnInput, m_flags);
        flagop("clamped", ImGuiSliderFlags_ClampOnInput, m_stor_flags);
        flagop("no_input", ImGuiSliderFlags_NoInput, m_flags);
        flagop("no_input", ImGuiSliderFlags_NoInput, m_stor_flags);

    }

    void mvSliderFloat3::getExtraConfigDict(PyObject* dict)
    {
        if (dict == nullptr)
            return;

        PyDict_SetItemString(dict, "format", ToPyString(m_format));
        PyDict_SetItemString(dict, "min_value", ToPyFloat(m_min));
        PyDict_SetItemString(dict, "max_value", ToPyFloat(m_max));

        // helper to check and set bit
        auto checkbitset = [dict](const char* keyword, int flag, const int& flags)
        {
            PyDict_SetItemString(dict, keyword, ToPyBool(flags & flag));
        };

        // window flags
        checkbitset("clamped", ImGuiSliderFlags_ClampOnInput, m_flags);
        checkbitset("no_input", ImGuiSliderFlags_NoInput, m_flags);

    }

    void mvSliderFloat4::setExtraConfigDict(PyObject* dict)
    {
        if (dict == nullptr)
            return;

        if (PyObject* item = PyDict_GetItemString(dict, "format")) m_format = ToString(item);
        if (PyObject* item = PyDict_GetItemString(dict, "min_value")) m_min = ToFloat(item);
        if (PyObject* item = PyDict_GetItemString(dict, "max_value")) m_max = ToFloat(item);

        // helper for bit flipping
        auto flagop = [dict](const char* keyword, int flag, int& flags)
        {
            if (PyObject* item = PyDict_GetItemString(dict, keyword)) ToBool(item) ? flags |= flag : flags &= ~flag;
        };

        // flags
        flagop("clamped", ImGuiSliderFlags_ClampOnInput, m_flags);
        flagop("clamped", ImGuiSliderFlags_ClampOnInput, m_stor_flags);
        flagop("no_input", ImGuiSliderFlags_NoInput, m_flags);
        flagop("no_input", ImGuiSliderFlags_NoInput, m_stor_flags);

    }

    void mvSliderFloat4::getExtraConfigDict(PyObject* dict)
    {
        if (dict == nullptr)
            return;

        PyDict_SetItemString(dict, "format", ToPyString(m_format));
        PyDict_SetItemString(dict, "min_value", ToPyFloat(m_min));
        PyDict_SetItemString(dict, "max_value", ToPyFloat(m_max));

        // helper to check and set bit
        auto checkbitset = [dict](const char* keyword, int flag, const int& flags)
        {
            PyDict_SetItemString(dict, keyword, ToPyBool(flags & flag));
        };

        // window flags
        checkbitset("clamped", ImGuiSliderFlags_ClampOnInput, m_flags);
        checkbitset("no_input", ImGuiSliderFlags_NoInput, m_flags);

    }

    void mvSliderInt::setExtraConfigDict(PyObject* dict)
    {
        if (dict == nullptr)
            return;

        if (PyObject* item = PyDict_GetItemString(dict, "format")) m_format = ToString(item);
        if (PyObject* item = PyDict_GetItemString(dict, "vertical")) m_vertical = ToBool(item);
        if (PyObject* item = PyDict_GetItemString(dict, "min_value")) m_min = ToInt(item);
        if (PyObject* item = PyDict_GetItemString(dict, "max_value")) m_max = ToInt(item);

        // helper for bit flipping
        auto flagop = [dict](const char* keyword, int flag, int& flags)
        {
            if (PyObject* item = PyDict_GetItemString(dict, keyword)) ToBool(item) ? flags |= flag : flags &= ~flag;
        };

        // flags
        flagop("clamped", ImGuiSliderFlags_ClampOnInput, m_flags);
        flagop("clamped", ImGuiSliderFlags_ClampOnInput, m_stor_flags);
        flagop("no_input", ImGuiSliderFlags_NoInput, m_flags);
        flagop("no_input", ImGuiSliderFlags_NoInput, m_stor_flags);

    }

    void mvSliderInt::getExtraConfigDict(PyObject* dict)
    {
        if (dict == nullptr)
            return;

        PyDict_SetItemString(dict, "format", ToPyString(m_format));
        PyDict_SetItemString(dict, "vertical", ToPyBool(m_vertical));
        PyDict_SetItemString(dict, "min_value", ToPyInt(m_min));
        PyDict_SetItemString(dict, "max_value", ToPyInt(m_max));

        // helper to check and set bit
        auto checkbitset = [dict](const char* keyword, int flag, const int& flags)
        {
            PyDict_SetItemString(dict, keyword, ToPyBool(flags & flag));
        };

        // window flags
        checkbitset("clamped", ImGuiSliderFlags_ClampOnInput, m_flags);
        checkbitset("no_input", ImGuiSliderFlags_NoInput, m_flags);

    }

    void mvSliderInt2::setExtraConfigDict(PyObject* dict)
    {
        if (dict == nullptr)
            return;

        if (PyObject* item = PyDict_GetItemString(dict, "format")) m_format = ToString(item);
        if (PyObject* item = PyDict_GetItemString(dict, "min_value")) m_min = ToInt(item);
        if (PyObject* item = PyDict_GetItemString(dict, "max_value")) m_max = ToInt(item);

        // helper for bit flipping
        auto flagop = [dict](const char* keyword, int flag, int& flags)
        {
            if (PyObject* item = PyDict_GetItemString(dict, keyword)) ToBool(item) ? flags |= flag : flags &= ~flag;
        };

        // flags
        flagop("clamped", ImGuiSliderFlags_ClampOnInput, m_flags);
        flagop("clamped", ImGuiSliderFlags_ClampOnInput, m_stor_flags);
        flagop("no_input", ImGuiSliderFlags_NoInput, m_flags);
        flagop("no_input", ImGuiSliderFlags_NoInput, m_stor_flags);

    }

    void mvSliderInt2::getExtraConfigDict(PyObject* dict)
    {
        if (dict == nullptr)
            return;

        PyDict_SetItemString(dict, "format", ToPyString(m_format));
        PyDict_SetItemString(dict, "min_value", ToPyInt(m_min));
        PyDict_SetItemString(dict, "max_value", ToPyInt(m_max));

        // helper to check and set bit
        auto checkbitset = [dict](const char* keyword, int flag, const int& flags)
        {
            PyDict_SetItemString(dict, keyword, ToPyBool(flags & flag));
        };

        // window flags
        checkbitset("clamped", ImGuiSliderFlags_ClampOnInput, m_flags);
        checkbitset("no_input", ImGuiSliderFlags_NoInput, m_flags);

    }

    void mvSliderInt3::setExtraConfigDict(PyObject* dict)
    {
        if (dict == nullptr)
            return;

        if (PyObject* item = PyDict_GetItemString(dict, "format")) m_format = ToString(item);
        if (PyObject* item = PyDict_GetItemString(dict, "min_value")) m_min = ToInt(item);
        if (PyObject* item = PyDict_GetItemString(dict, "max_value")) m_max = ToInt(item);

        // helper for bit flipping
        auto flagop = [dict](const char* keyword, int flag, int& flags)
        {
            if (PyObject* item = PyDict_GetItemString(dict, keyword)) ToBool(item) ? flags |= flag : flags &= ~flag;
        };

        // flags
        flagop("clamped", ImGuiSliderFlags_ClampOnInput, m_flags);
        flagop("clamped", ImGuiSliderFlags_ClampOnInput, m_stor_flags);
        flagop("no_input", ImGuiSliderFlags_NoInput, m_flags);
        flagop("no_input", ImGuiSliderFlags_NoInput, m_stor_flags);

    }

    void mvSliderInt3::getExtraConfigDict(PyObject* dict)
    {
        if (dict == nullptr)
            return;

        PyDict_SetItemString(dict, "format", ToPyString(m_format));
        PyDict_SetItemString(dict, "min_value", ToPyInt(m_min));
        PyDict_SetItemString(dict, "max_value", ToPyInt(m_max));

        // helper to check and set bit
        auto checkbitset = [dict](const char* keyword, int flag, const int& flags)
        {
            PyDict_SetItemString(dict, keyword, ToPyBool(flags & flag));
        };

        // window flags
        checkbitset("clamped", ImGuiSliderFlags_ClampOnInput, m_flags);
        checkbitset("no_input", ImGuiSliderFlags_NoInput, m_flags);

    }

    void mvSliderInt4::setExtraConfigDict(PyObject* dict)
    {
        if (dict == nullptr)
            return;
         
        if (PyObject* item = PyDict_GetItemString(dict, "format")) m_format = ToString(item);
        if (PyObject* item = PyDict_GetItemString(dict, "min_value")) m_min = ToInt(item);
        if (PyObject* item = PyDict_GetItemString(dict, "max_value")) m_max = ToInt(item);

        // helper for bit flipping
        auto flagop = [dict](const char* keyword, int flag, int& flags)
        {
            if (PyObject* item = PyDict_GetItemString(dict, keyword)) ToBool(item) ? flags |= flag : flags &= ~flag;
        };

        // flags
        flagop("clamped", ImGuiSliderFlags_ClampOnInput, m_flags);
        flagop("clamped", ImGuiSliderFlags_ClampOnInput, m_stor_flags);
        flagop("no_input", ImGuiSliderFlags_NoInput, m_flags);
        flagop("no_input", ImGuiSliderFlags_NoInput, m_stor_flags);

    }

    void mvSliderInt4::getExtraConfigDict(PyObject* dict)
    {
        if (dict == nullptr)
            return;
         
        PyDict_SetItemString(dict, "format", ToPyString(m_format));
        PyDict_SetItemString(dict, "min_value", ToPyInt(m_min));
        PyDict_SetItemString(dict, "max_value", ToPyInt(m_max));

        // helper to check and set bit
        auto checkbitset = [dict](const char* keyword, int flag, const int& flags)
        {
            PyDict_SetItemString(dict, keyword, ToPyBool(flags & flag));
        };

        // window flags
        checkbitset("clamped", ImGuiSliderFlags_ClampOnInput, m_flags);
        checkbitset("no_input", ImGuiSliderFlags_NoInput, m_flags);

    }

    PyObject* mvSliderFloat::add_slider_float(PyObject* self, PyObject* args, PyObject* kwargs)
    {
        static int i = 0; i++;
        std::string sname = std::string(std::string("$$DPG_") + s_internal_id + std::to_string(i));
        const char* name = sname.c_str();
        float default_value = 0.0f;
        float min_value = 0.0f;
        float max_value = 100.0f;
        const char* format = "%.3f";
        int vertical = false;
        PyObject* callback = nullptr;
        PyObject* callback_data = nullptr;
        const char* parent = "";
        const char* before = "";
        const char* source = "";
        int enabled = true;
        int width = 0;
        int height = 0;
        int no_input = false;
        int clamped = false;
        const char* label = "";
        int show = true;

        if (!(mvApp::GetApp()->getParsers())["add_slider_float"].parse(args, kwargs, __FUNCTION__, &name, &default_value,
            &min_value, &max_value, &format, &vertical, &callback, &callback_data, &parent, &before,
            &source, &enabled, &width, &height, &no_input, &clamped, &label, &show))
            return ToPyBool(false);

        auto item = CreateRef<mvSliderFloat>(name, default_value, source);
        if (callback)
            Py_XINCREF(callback);
        item->setCallback(callback);
        if (callback_data)
            Py_XINCREF(callback_data);
        item->setCallbackData(callback_data);

        item->checkConfigDict(kwargs);
        item->setConfigDict(kwargs);
        item->setExtraConfigDict(kwargs);

        mvApp::GetApp()->getItemRegistry().addItemWithRuntimeChecks(item, parent, before);

        return ToPyString(name);
    }

    PyObject* mvSliderFloat2::add_slider_float2(PyObject* self, PyObject* args, PyObject* kwargs)
    {
        static int i = 0; i++;
        std::string sname = std::string(std::string("$$DPG_") + s_internal_id + std::to_string(i));
        const char* name = sname.c_str();
        PyObject* default_value = PyTuple_New(2);
        PyTuple_SetItem(default_value, 0, PyFloat_FromDouble(0.0));
        PyTuple_SetItem(default_value, 1, PyFloat_FromDouble(0.0));
        float min_value = 0.0f;
        float max_value = 100.0f;
        const char* format = "%.3f";
        PyObject* callback = nullptr;
        PyObject* callback_data = nullptr;
        const char* parent = "";
        const char* before = "";
        const char* source = "";
        int enabled = true;
        int width = 0;
        int no_input = false;
        int clamped = false;
        const char* label = "";
        int show = true;

        if (!(mvApp::GetApp()->getParsers())["add_slider_float2"].parse(args, kwargs, __FUNCTION__, &name, &default_value,
            &min_value, &max_value, &format, &callback, &callback_data, &parent, &before, &source, &enabled, &width,
            &no_input, &clamped, &label, &show))
            return ToPyBool(false);


        auto vec = ToFloatVect(default_value);

        auto item = CreateRef<mvSliderFloat2>(name, vec.data(), source);
        if (callback)
            Py_XINCREF(callback);
        item->setCallback(callback);
        if (callback_data)
            Py_XINCREF(callback_data);
        item->setCallbackData(callback_data);

        item->checkConfigDict(kwargs);
        item->setConfigDict(kwargs);
        item->setExtraConfigDict(kwargs);

        mvApp::GetApp()->getItemRegistry().addItemWithRuntimeChecks(item, parent, before);

        return ToPyString(name);
    }

    PyObject* mvSliderFloat3::add_slider_float3(PyObject* self, PyObject* args, PyObject* kwargs)
    {
        static int i = 0; i++;
        std::string sname = std::string(std::string("$$DPG_") + s_internal_id + std::to_string(i));
        const char* name = sname.c_str();
        PyObject* default_value = PyTuple_New(3);
        PyTuple_SetItem(default_value, 0, PyFloat_FromDouble(0.0));
        PyTuple_SetItem(default_value, 1, PyFloat_FromDouble(0.0));
        PyTuple_SetItem(default_value, 2, PyFloat_FromDouble(0.0));
        float min_value = 0.0f;
        float max_value = 100.0f;
        const char* format = "%.3f";
        PyObject* callback = nullptr;
        PyObject* callback_data = nullptr;
        const char* parent = "";
        const char* before = "";
        const char* source = "";
        int enabled = true;
        int width = 0;
        int no_input = false;
        int clamped = false;
        const char* label = "";
        int show = true;

        if (!(mvApp::GetApp()->getParsers())["add_slider_float3"].parse(args, kwargs, __FUNCTION__, &name, &default_value,
            &min_value, &max_value, &format, &callback, &callback_data, &parent, &before, &source, &enabled, &width,
            &no_input, &clamped, &label, &show))
            return ToPyBool(false);

        auto vec = ToFloatVect(default_value);

        auto item = CreateRef<mvSliderFloat3>(name, vec.data(), source);
        if (callback)
            Py_XINCREF(callback);
        item->setCallback(callback);
        if (callback_data)
            Py_XINCREF(callback_data);
        item->setCallbackData(callback_data);

        item->checkConfigDict(kwargs);
        item->setConfigDict(kwargs);
        item->setExtraConfigDict(kwargs);

        mvApp::GetApp()->getItemRegistry().addItemWithRuntimeChecks(item, parent, before);

        return ToPyString(name);
    }

    PyObject* mvSliderFloat4::add_slider_float4(PyObject* self, PyObject* args, PyObject* kwargs)
    {
        static int i = 0; i++;
        std::string sname = std::string(std::string("$$DPG_") + s_internal_id + std::to_string(i));
        const char* name = sname.c_str();
        PyObject* default_value = PyTuple_New(4);
        PyTuple_SetItem(default_value, 0, PyFloat_FromDouble(0.0));
        PyTuple_SetItem(default_value, 1, PyFloat_FromDouble(0.0));
        PyTuple_SetItem(default_value, 2, PyFloat_FromDouble(0.0));
        PyTuple_SetItem(default_value, 3, PyFloat_FromDouble(0.0));
        float min_value = 0.0f;
        float max_value = 100.0f;
        const char* format = "%.3f";
        PyObject* callback = nullptr;
        PyObject* callback_data = nullptr;
        const char* parent = "";
        const char* before = "";
        const char* source = "";
        int enabled = true;
        int width = 0;
        int no_input = false;
        int clamped = false;
        const char* label = "";
        int show = true;

        if (!(mvApp::GetApp()->getParsers())["add_slider_float4"].parse(args, kwargs, __FUNCTION__, &name, &default_value,
            &min_value, &max_value, &format, &callback, &callback_data, &parent, &before, &source, &enabled,
            &width, &no_input, &clamped, &label, &show))
            return ToPyBool(false);

        auto vec = ToFloatVect(default_value);
        auto item = CreateRef<mvSliderFloat4>(name, vec.data(), source);
        if (callback)
            Py_XINCREF(callback);
        item->setCallback(callback);
        if (callback_data)
            Py_XINCREF(callback_data);
        item->setCallbackData(callback_data);

        item->checkConfigDict(kwargs);
        item->setConfigDict(kwargs);
        item->setExtraConfigDict(kwargs);

        mvApp::GetApp()->getItemRegistry().addItemWithRuntimeChecks(item, parent, before);

        return ToPyString(name);
    }

    PyObject* mvSliderInt::add_slider_int(PyObject* self, PyObject* args, PyObject* kwargs)
    {
        static int i = 0; i++;
        std::string sname = std::string(std::string("$$DPG_") + s_internal_id + std::to_string(i));
        const char* name = sname.c_str();
        int default_value = 0;
        int min_value = 0;
        int max_value = 100;
        const char* format = "%d";
        int vertical = false;
        PyObject* callback = nullptr;
        PyObject* callback_data = nullptr;
        const char* parent = "";
        const char* before = "";
        const char* source = "";
        int enabled = true;
        int width = 0;
        int height = 0;
        int no_input = false;
        int clamped = false;
        const char* label = "";
        int show = true;

        if (!(mvApp::GetApp()->getParsers())["add_slider_int"].parse(args, kwargs, __FUNCTION__, &name, &default_value,
            &min_value, &max_value, &format, &vertical, &callback, &callback_data, &parent, &before, &source, &enabled,
            &width, &height, &no_input, &clamped, &label, &show))
            return ToPyBool(false);

        auto item = CreateRef<mvSliderInt>(name, default_value, source);
        if (callback)
            Py_XINCREF(callback);
        item->setCallback(callback);
        if (callback_data)
            Py_XINCREF(callback_data);
        item->setCallbackData(callback_data);

        item->checkConfigDict(kwargs);
        item->setConfigDict(kwargs);
        item->setExtraConfigDict(kwargs);

        mvApp::GetApp()->getItemRegistry().addItemWithRuntimeChecks(item, parent, before);

        return ToPyString(name);
    }

    PyObject* mvSliderInt2::add_slider_int2(PyObject* self, PyObject* args, PyObject* kwargs)
    {
        static int i = 0; i++;
        std::string sname = std::string(std::string("$$DPG_") + s_internal_id + std::to_string(i));
        const char* name = sname.c_str();
        PyObject* default_value = PyTuple_New(2);
        PyTuple_SetItem(default_value, 0, PyLong_FromLong(0));
        PyTuple_SetItem(default_value, 1, PyLong_FromLong(0));
        int min_value = 0;
        int max_value = 100;
        const char* format = "%d";
        PyObject* callback = nullptr;
        PyObject* callback_data = nullptr;
        const char* parent = "";
        const char* before = "";
        const char* source = "";
        int enabled = true;
        int width = 0;
        int no_input = false;
        int clamped = false;
        const char* label = "";
        int show = true;

        if (!(mvApp::GetApp()->getParsers())["add_slider_int2"].parse(args, kwargs, __FUNCTION__, &name, &default_value,
            &min_value, &max_value, &format, &callback, &callback_data, &parent, &before, &source, &enabled,
            &width, &no_input, &clamped, &label, &show))
            return ToPyBool(false);

        auto vec = ToIntVect(default_value);
        auto item = CreateRef<mvSliderInt2>(name, vec.data(), source);
        if (callback)
            Py_XINCREF(callback);
        item->setCallback(callback);
        if (callback_data)
            Py_XINCREF(callback_data);
        item->setCallbackData(callback_data);

        item->checkConfigDict(kwargs);
        item->setConfigDict(kwargs);
        item->setExtraConfigDict(kwargs);

        mvApp::GetApp()->getItemRegistry().addItemWithRuntimeChecks(item, parent, before);

        return ToPyString(name);
    }

    PyObject* mvSliderInt3::add_slider_int3(PyObject* self, PyObject* args, PyObject* kwargs)
    {
        static int i = 0; i++;
        std::string sname = std::string(std::string("$$DPG_") + s_internal_id + std::to_string(i));
        const char* name = sname.c_str();
        PyObject* default_value = PyTuple_New(3);
        PyTuple_SetItem(default_value, 0, PyLong_FromLong(0));
        PyTuple_SetItem(default_value, 1, PyLong_FromLong(0));
        PyTuple_SetItem(default_value, 2, PyLong_FromLong(0));
        int min_value = 0;
        int max_value = 100;
        const char* format = "%d";
        PyObject* callback = nullptr;
        PyObject* callback_data = nullptr;
        const char* parent = "";
        const char* before = "";
        const char* source = "";
        int enabled = true;
        int width = 0;
        int no_input = false;
        int clamped = false;
        const char* label = "";
        int show = true;

        if (!(mvApp::GetApp()->getParsers())["add_slider_int3"].parse(args, kwargs, __FUNCTION__, &name, &default_value,
            &min_value, &max_value, &format, &callback, &callback_data, &parent, &before, &source, &enabled,
            &width, &no_input, &clamped, &label, &show))
            return ToPyBool(false);

        auto vec = ToIntVect(default_value);
        auto item = CreateRef<mvSliderInt3>(name, vec.data(), source);
        if (callback)
            Py_XINCREF(callback);
        item->setCallback(callback);
        if (callback_data)
            Py_XINCREF(callback_data);
        item->setCallbackData(callback_data);

        item->checkConfigDict(kwargs);
        item->setConfigDict(kwargs);
        item->setExtraConfigDict(kwargs);

        mvApp::GetApp()->getItemRegistry().addItemWithRuntimeChecks(item, parent, before);

        return ToPyString(name);
    }

    PyObject* mvSliderInt4::add_slider_int4(PyObject* self, PyObject* args, PyObject* kwargs)
    {
        static int i = 0; i++;
        std::string sname = std::string(std::string("$$DPG_") + s_internal_id + std::to_string(i));
        const char* name = sname.c_str();
        PyObject* default_value = PyTuple_New(4);
        PyTuple_SetItem(default_value, 0, PyLong_FromLong(0));
        PyTuple_SetItem(default_value, 1, PyLong_FromLong(0));
        PyTuple_SetItem(default_value, 2, PyLong_FromLong(0));
        PyTuple_SetItem(default_value, 3, PyLong_FromLong(0));
        int min_value = 0;
        int max_value = 100;
        const char* format = "%d";
        PyObject* callback = nullptr;
        PyObject* callback_data = nullptr;
        const char* parent = "";
        const char* before = "";
        const char* source = "";
        int enabled = true;
        int width = 0;
        int no_input = false;
        int clamped = false;
        const char* label = "";
        int show = true;

        if (!(mvApp::GetApp()->getParsers())["add_slider_int4"].parse(args, kwargs, __FUNCTION__, &name, &default_value,
            &min_value, &max_value, &format, &callback, &callback_data, &parent, &before, &source, &enabled,
            &width, &no_input, &clamped, &label, &show))
            return ToPyBool(false);

        auto vec = ToIntVect(default_value);
        auto item = CreateRef<mvSliderInt4>(name, vec.data(), source);
        if (callback)
            Py_XINCREF(callback);
        item->setCallback(callback);
        if (callback_data)
            Py_XINCREF(callback_data);
        item->setCallbackData(callback_data);

        item->checkConfigDict(kwargs);
        item->setConfigDict(kwargs);
        item->setExtraConfigDict(kwargs);

        mvApp::GetApp()->getItemRegistry().addItemWithRuntimeChecks(item, parent, before);

        return ToPyString(name);
    }

}
