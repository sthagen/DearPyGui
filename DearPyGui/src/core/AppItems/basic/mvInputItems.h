#pragma once

#include "mvTypeBases.h"
#include "mvPythonTranslator.h"
#include <utility>
#include "mvValueStorage.h"
#include "mvGlobalIntepreterLock.h"

//-----------------------------------------------------------------------------
// Widget Index
//
//     * mvInputInt
//     * mvInputInt2
//     * mvInputInt3
//     * mvInputInt4
//     * mvInputFloat
//     * mvInputFloat2
//     * mvInputFloat3
//     * mvInputFloat4
//
//-----------------------------------------------------------------------------

namespace Marvel {

	//-----------------------------------------------------------------------------
	// mvInputInt
	//-----------------------------------------------------------------------------
	class mvInputInt : public mvIntPtrBase
	{

	public:

		MV_APPITEM_TYPE(mvAppItemType::InputInt, "add_input_int")

		mvInputInt(const std::string& name, int default_value, const std::string& dataSource)
			: mvIntPtrBase(name, default_value, dataSource)
		{
			m_description.disableAllowed = true;
		}

		void setEnabled(bool value) override
		{
			if (value)
				m_flags = m_stor_flags;

			else
			{
				m_stor_flags = m_flags;
				m_flags |= ImGuiInputTextFlags_ReadOnly;
				m_flags &= ~ImGuiInputTextFlags_EnterReturnsTrue;
			}

			m_enabled = value;
		}

		void draw() override
		{
			auto styleManager = m_styleManager.getScopedStyleManager();
			ScopedID id;

			if (!m_enabled)
			{
				ImVec4 disabled_color = ImVec4(ImGui::GetStyleColorVec4(ImGuiCol_TextDisabled));
				disabled_color.w = 0.392f;
				styleManager.addColorStyle(ImGuiCol_FrameBg, disabled_color);
				styleManager.addColorStyle(ImGuiCol_FrameBgHovered, disabled_color);
				styleManager.addColorStyle(ImGuiCol_FrameBgActive, disabled_color);
				styleManager.addColorStyle(ImGuiCol_Button, disabled_color);
				styleManager.addColorStyle(ImGuiCol_Text, ImVec4(ImGui::GetStyleColorVec4(ImGuiCol_TextDisabled)));
			}

			if (ImGui::InputInt(m_label.c_str(), m_value, m_step, m_step_fast, m_flags))
				mvCallbackRegistry::GetCallbackRegistry()->addCallback(m_callback, m_name, m_callbackData);

		}

		void setExtraConfigDict(PyObject* dict) override
		{
			if (dict == nullptr)
				return;
			mvGlobalIntepreterLock gil;
			if (PyObject* item = PyDict_GetItemString(dict, "on_enter")) ToBool(item) ? m_flags |= ImGuiInputTextFlags_EnterReturnsTrue : m_flags &= ~ImGuiInputTextFlags_EnterReturnsTrue;
			if (PyObject* item = PyDict_GetItemString(dict, "readonly")) ToBool(item) ? m_flags |= ImGuiInputTextFlags_ReadOnly : m_flags &= ~ImGuiInputTextFlags_ReadOnly;
			if (PyObject* item = PyDict_GetItemString(dict, "step")) m_step = ToInt(item);
			if (PyObject* item = PyDict_GetItemString(dict, "step_fast")) m_step_fast = ToInt(item);
		}

		void getExtraConfigDict(PyObject* dict) override
		{
			if (dict == nullptr)
				return;
			mvGlobalIntepreterLock gil;
			PyDict_SetItemString(dict, "on_enter", ToPyBool(m_flags & ImGuiInputTextFlags_EnterReturnsTrue));
			PyDict_SetItemString(dict, "readonly", ToPyBool(m_flags & ImGuiInputTextFlags_ReadOnly));
			PyDict_SetItemString(dict, "step", ToPyInt(m_step));
			PyDict_SetItemString(dict, "step_fast", ToPyInt(m_step_fast));
		}

	private:

		ImGuiInputTextFlags m_flags = 0;
		ImGuiInputTextFlags m_stor_flags = 0;
		int                 m_step = 1;
		int                 m_step_fast = 100;
	};

	//-----------------------------------------------------------------------------
	// mvInputInt2
	//-----------------------------------------------------------------------------
	class mvInputInt2 : public mvInt2PtrBase
	{

	public:

		MV_APPITEM_TYPE(mvAppItemType::InputInt2, "add_input_int")

		mvInputInt2(const std::string& name, int* default_value, const std::string& dataSource)
			: mvInt2PtrBase(name, default_value, dataSource)
		{
			m_description.disableAllowed = true;
		}

		void setEnabled(bool value) override
		{
			if (value)
				m_flags = m_stor_flags;

			else
			{
				m_stor_flags = m_flags;
				m_flags |= ImGuiInputTextFlags_ReadOnly;
				m_flags &= ~ImGuiInputTextFlags_EnterReturnsTrue;
			}

			m_enabled = value;
		}

		void draw() override
		{
			auto styleManager = m_styleManager.getScopedStyleManager();
			ScopedID id;

			if (!m_enabled)
			{
				ImVec4 disabled_color = ImVec4(ImGui::GetStyleColorVec4(ImGuiCol_TextDisabled));
				disabled_color.w = 0.392f;
				styleManager.addColorStyle(ImGuiCol_FrameBg, disabled_color);
				styleManager.addColorStyle(ImGuiCol_FrameBgHovered, disabled_color);
				styleManager.addColorStyle(ImGuiCol_FrameBgActive, disabled_color);
				styleManager.addColorStyle(ImGuiCol_Button, disabled_color);
				styleManager.addColorStyle(ImGuiCol_Text, ImVec4(ImGui::GetStyleColorVec4(ImGuiCol_TextDisabled)));
			}

			if (ImGui::InputInt2(m_label.c_str(), m_value, m_flags))
				mvCallbackRegistry::GetCallbackRegistry()->addCallback(m_callback, m_name, m_callbackData);

		}

		void setExtraConfigDict(PyObject* dict) override
		{
			if (dict == nullptr)
				return;
			mvGlobalIntepreterLock gil;
			if (PyObject* item = PyDict_GetItemString(dict, "on_enter")) ToBool(item) ? m_flags |= ImGuiInputTextFlags_EnterReturnsTrue : m_flags &= ~ImGuiInputTextFlags_EnterReturnsTrue;
			if (PyObject* item = PyDict_GetItemString(dict, "readonly")) ToBool(item) ? m_flags |= ImGuiInputTextFlags_ReadOnly : m_flags &= ~ImGuiInputTextFlags_ReadOnly;
		}

		void getExtraConfigDict(PyObject* dict) override
		{
			if (dict == nullptr)
				return;
			mvGlobalIntepreterLock gil;
			PyDict_SetItemString(dict, "on_enter", ToPyBool(m_flags & ImGuiInputTextFlags_EnterReturnsTrue));
			PyDict_SetItemString(dict, "readonly", ToPyBool(m_flags & ImGuiInputTextFlags_ReadOnly));
		}

	private:

		ImGuiInputTextFlags m_flags = 0;
		ImGuiInputTextFlags m_stor_flags = 0;
	};

	//-----------------------------------------------------------------------------
	// mvInputInt3
	//-----------------------------------------------------------------------------
	class mvInputInt3 : public mvInt3PtrBase
	{

	public:

		MV_APPITEM_TYPE(mvAppItemType::InputInt3, "add_input_int3")

		mvInputInt3(const std::string& name, int* default_value, const std::string& dataSource)
			: mvInt3PtrBase(name, default_value, dataSource)
		{
			m_description.disableAllowed = true;
		}

		void setEnabled(bool value) override
		{
			if (value)
				m_flags = m_stor_flags;

			else
			{
				m_stor_flags = m_flags;
				m_flags |= ImGuiInputTextFlags_ReadOnly;
				m_flags &= ~ImGuiInputTextFlags_EnterReturnsTrue;
			}

			m_enabled = value;
		}

		void draw() override
		{
			auto styleManager = m_styleManager.getScopedStyleManager();
			ScopedID id;

			if (!m_enabled)
			{
				ImVec4 disabled_color = ImVec4(ImGui::GetStyleColorVec4(ImGuiCol_TextDisabled));
				disabled_color.w = 0.392f;
				styleManager.addColorStyle(ImGuiCol_FrameBg, disabled_color);
				styleManager.addColorStyle(ImGuiCol_FrameBgHovered, disabled_color);
				styleManager.addColorStyle(ImGuiCol_FrameBgActive, disabled_color);
				styleManager.addColorStyle(ImGuiCol_Button, disabled_color);
				styleManager.addColorStyle(ImGuiCol_Text, ImVec4(ImGui::GetStyleColorVec4(ImGuiCol_TextDisabled)));
			}

			if (ImGui::InputInt3(m_label.c_str(), m_value, m_flags))
				mvCallbackRegistry::GetCallbackRegistry()->addCallback(m_callback, m_name, m_callbackData);
		}

		void setExtraConfigDict(PyObject* dict) override
		{
			if (dict == nullptr)
				return;
			mvGlobalIntepreterLock gil;
			if (PyObject* item = PyDict_GetItemString(dict, "on_enter")) ToBool(item) ? m_flags |= ImGuiInputTextFlags_EnterReturnsTrue : m_flags &= ~ImGuiInputTextFlags_EnterReturnsTrue;
			if (PyObject* item = PyDict_GetItemString(dict, "readonly")) ToBool(item) ? m_flags |= ImGuiInputTextFlags_ReadOnly : m_flags &= ~ImGuiInputTextFlags_ReadOnly;
		}

		void getExtraConfigDict(PyObject* dict) override
		{
			if (dict == nullptr)
				return;
			mvGlobalIntepreterLock gil;
			PyDict_SetItemString(dict, "on_enter", ToPyBool(m_flags & ImGuiInputTextFlags_EnterReturnsTrue));
			PyDict_SetItemString(dict, "readonly", ToPyBool(m_flags & ImGuiInputTextFlags_ReadOnly));
		}

	private:

		ImGuiInputTextFlags m_flags = 0;
		ImGuiInputTextFlags m_stor_flags = 0;
	};

	//-----------------------------------------------------------------------------
	// mvInputInt4
	//-----------------------------------------------------------------------------
	class mvInputInt4 : public mvInt4PtrBase
	{

	public:

		MV_APPITEM_TYPE(mvAppItemType::InputInt4, "add_input_int4")

		mvInputInt4(const std::string& name, int* default_value, const std::string& dataSource)
			: mvInt4PtrBase(name, default_value, dataSource)
		{
			m_description.disableAllowed = true;
		}

		void setEnabled(bool value) override
		{
			if (value)
				m_flags = m_stor_flags;

			else
			{
				m_stor_flags = m_flags;
				m_flags |= ImGuiInputTextFlags_ReadOnly;
				m_flags &= ~ImGuiInputTextFlags_EnterReturnsTrue;
			}

			m_enabled = value;
		}

		void draw() override
		{
			auto styleManager = m_styleManager.getScopedStyleManager();
			ScopedID id;

			if (!m_enabled)
			{
				ImVec4 disabled_color = ImVec4(ImGui::GetStyleColorVec4(ImGuiCol_TextDisabled));
				disabled_color.w = 0.392f;
				styleManager.addColorStyle(ImGuiCol_FrameBg, disabled_color);
				styleManager.addColorStyle(ImGuiCol_FrameBgHovered, disabled_color);
				styleManager.addColorStyle(ImGuiCol_FrameBgActive, disabled_color);
				styleManager.addColorStyle(ImGuiCol_Button, disabled_color);
				styleManager.addColorStyle(ImGuiCol_Text, ImVec4(ImGui::GetStyleColorVec4(ImGuiCol_TextDisabled)));
			}

			if (ImGui::InputInt4(m_label.c_str(), m_value, m_flags))
				mvCallbackRegistry::GetCallbackRegistry()->addCallback(m_callback, m_name, m_callbackData);

		}

		void setExtraConfigDict(PyObject* dict) override
		{
			if (dict == nullptr)
				return;
			mvGlobalIntepreterLock gil;
			if (PyObject* item = PyDict_GetItemString(dict, "on_enter")) ToBool(item) ? m_flags |= ImGuiInputTextFlags_EnterReturnsTrue : m_flags &= ~ImGuiInputTextFlags_EnterReturnsTrue;
			if (PyObject* item = PyDict_GetItemString(dict, "readonly")) ToBool(item) ? m_flags |= ImGuiInputTextFlags_ReadOnly : m_flags &= ~ImGuiInputTextFlags_ReadOnly;
		}

		void getExtraConfigDict(PyObject* dict) override
		{
			if (dict == nullptr)
				return;
			mvGlobalIntepreterLock gil;
			PyDict_SetItemString(dict, "on_enter", ToPyBool(m_flags & ImGuiInputTextFlags_EnterReturnsTrue));
			PyDict_SetItemString(dict, "readonly", ToPyBool(m_flags & ImGuiInputTextFlags_ReadOnly));
		}

	private:

		ImGuiInputTextFlags m_flags = 0;
		ImGuiInputTextFlags m_stor_flags = 0;
	};

	//-----------------------------------------------------------------------------
	// mvInputFloat
	//-----------------------------------------------------------------------------
	class mvInputFloat : public mvFloatPtrBase
	{

	public:

		MV_APPITEM_TYPE(mvAppItemType::InputFloat, "add_input_float")

		mvInputFloat(const std::string& name, float default_value, const std::string& dataSource)
			: mvFloatPtrBase(name, default_value, dataSource)
		{
			m_description.disableAllowed = true;
		}

		void setEnabled(bool value) override
		{
			if (value)
				m_flags = m_stor_flags;

			else
			{
				m_stor_flags = m_flags;
				m_flags |= ImGuiInputTextFlags_ReadOnly;
				m_flags &= ~ImGuiInputTextFlags_EnterReturnsTrue;
			}

			m_enabled = value;
		}

		void draw() override
		{
			auto styleManager = m_styleManager.getScopedStyleManager();
			ScopedID id;

			if (!m_enabled)
			{
				ImVec4 disabled_color = ImVec4(ImGui::GetStyleColorVec4(ImGuiCol_TextDisabled));
				disabled_color.w = 0.392f;
				styleManager.addColorStyle(ImGuiCol_FrameBg, disabled_color);
				styleManager.addColorStyle(ImGuiCol_FrameBgHovered, disabled_color);
				styleManager.addColorStyle(ImGuiCol_FrameBgActive, disabled_color);
				styleManager.addColorStyle(ImGuiCol_Button, disabled_color);
				styleManager.addColorStyle(ImGuiCol_Text, ImVec4(ImGui::GetStyleColorVec4(ImGuiCol_TextDisabled)));
			}

			if (ImGui::InputFloat(m_label.c_str(), m_value, m_step, m_step_fast, m_format.c_str(), m_flags))
				mvCallbackRegistry::GetCallbackRegistry()->addCallback(m_callback, m_name, m_callbackData);

		}

		void setExtraConfigDict(PyObject* dict) override
		{
			if (dict == nullptr)
				return;
			mvGlobalIntepreterLock gil;
			if (PyObject* item = PyDict_GetItemString(dict, "format")) m_format = ToString(item);
			if (PyObject* item = PyDict_GetItemString(dict, "step")) m_step = ToFloat(item);
			if (PyObject* item = PyDict_GetItemString(dict, "step_fast")) m_step_fast = ToFloat(item);

			// helper for bit flipping
			auto flagop = [dict](const char* keyword, int flag, int& flags)
			{
				if (PyObject* item = PyDict_GetItemString(dict, keyword)) ToBool(item) ? flags |= flag : flags &= ~flag;
			};

			// flags
			flagop("on_enter", ImGuiInputTextFlags_EnterReturnsTrue, m_flags);
			flagop("readonly", ImGuiInputTextFlags_ReadOnly, m_flags);

		}

		void getExtraConfigDict(PyObject* dict) override
		{
			if (dict == nullptr)
				return;
			mvGlobalIntepreterLock gil;
			PyDict_SetItemString(dict, "format", ToPyString(m_format));
			PyDict_SetItemString(dict, "step", ToPyFloat(m_step));
			PyDict_SetItemString(dict, "step_fast", ToPyFloat(m_step_fast));

			// helper to check and set bit
			auto checkbitset = [dict](const char* keyword, int flag, const int& flags)
			{
				PyDict_SetItemString(dict, keyword, ToPyBool(flags & flag));
			};

			// window flags
			checkbitset("on_enter", ImGuiInputTextFlags_EnterReturnsTrue, m_flags);
			checkbitset("readonly", ImGuiInputTextFlags_ReadOnly, m_flags);

		}

	private:

		std::string         m_format = "%.3f";
		float               m_step = 0.1f;
		float               m_step_fast = 1.0f;
		ImGuiInputTextFlags m_flags = 0;
		ImGuiInputTextFlags m_stor_flags = 0;

	};

	//-----------------------------------------------------------------------------
	// mvInputFloat2
	//-----------------------------------------------------------------------------
	class mvInputFloat2: public mvFloat2PtrBase
	{

	public:

		MV_APPITEM_TYPE(mvAppItemType::InputFloat2, "add_input_float2")

		mvInputFloat2(const std::string& name, float* default_value, const std::string& dataSource)
			: mvFloat2PtrBase(name, default_value, dataSource)
		{
			m_description.disableAllowed = true;
		}

		void setEnabled(bool value) override
		{
			if (value)
				m_flags = m_stor_flags;

			else
			{
				m_stor_flags = m_flags;
				m_flags |= ImGuiInputTextFlags_ReadOnly;
				m_flags &= ~ImGuiInputTextFlags_EnterReturnsTrue;
			}

			m_enabled = value;
		}

		void draw() override
		{
			auto styleManager = m_styleManager.getScopedStyleManager();
			ScopedID id;

			if (!m_enabled)
			{
				ImVec4 disabled_color = ImVec4(ImGui::GetStyleColorVec4(ImGuiCol_TextDisabled));
				disabled_color.w = 0.392f;
				styleManager.addColorStyle(ImGuiCol_FrameBg, disabled_color);
				styleManager.addColorStyle(ImGuiCol_FrameBgHovered, disabled_color);
				styleManager.addColorStyle(ImGuiCol_FrameBgActive, disabled_color);
				styleManager.addColorStyle(ImGuiCol_Button, disabled_color);
				styleManager.addColorStyle(ImGuiCol_Text, ImVec4(ImGui::GetStyleColorVec4(ImGuiCol_TextDisabled)));
			}

			if (ImGui::InputFloat2(m_label.c_str(), m_value, m_format.c_str(), m_flags))
				mvCallbackRegistry::GetCallbackRegistry()->addCallback(m_callback, m_name, m_callbackData);
		}

		void setExtraConfigDict(PyObject* dict) override
		{
			if (dict == nullptr)
				return;
			mvGlobalIntepreterLock gil;
			if (PyObject* item = PyDict_GetItemString(dict, "format")) m_format = ToString(item);

			// helper for bit flipping
			auto flagop = [dict](const char* keyword, int flag, int& flags)
			{
				if (PyObject* item = PyDict_GetItemString(dict, keyword)) ToBool(item) ? flags |= flag : flags &= ~flag;
			};

			// flags
			flagop("on_enter", ImGuiInputTextFlags_EnterReturnsTrue, m_flags);
			flagop("readonly", ImGuiInputTextFlags_ReadOnly, m_flags);

		}

		void getExtraConfigDict(PyObject* dict) override
		{
			if (dict == nullptr)
				return;
			mvGlobalIntepreterLock gil;
			PyDict_SetItemString(dict, "format", ToPyString(m_format));

			// helper to check and set bit
			auto checkbitset = [dict](const char* keyword, int flag, const int& flags)
			{
				PyDict_SetItemString(dict, keyword, ToPyBool(flags & flag));
			};

			// window flags
			checkbitset("on_enter", ImGuiInputTextFlags_EnterReturnsTrue, m_flags);
			checkbitset("readonly", ImGuiInputTextFlags_ReadOnly, m_flags);

		}

	private:

		std::string         m_format = "%.3f";
		ImGuiInputTextFlags m_flags = 0;
		ImGuiInputTextFlags m_stor_flags = 0;

	};

	//-----------------------------------------------------------------------------
	// mvInputFloat3
	//-----------------------------------------------------------------------------
	class mvInputFloat3 : public mvFloat3PtrBase
	{

	public:

		MV_APPITEM_TYPE(mvAppItemType::InputFloat3, "add_input_float3")

		mvInputFloat3(const std::string& name, float* default_value, const std::string& dataSource)
			: mvFloat3PtrBase(name, default_value, dataSource)
		{
			m_description.disableAllowed = true;
		}

		void setEnabled(bool value) override
		{
			if (value)
				m_flags = m_stor_flags;

			else
			{
				m_stor_flags = m_flags;
				m_flags |= ImGuiInputTextFlags_ReadOnly;
				m_flags &= ~ImGuiInputTextFlags_EnterReturnsTrue;
			}

			m_enabled = value;
		}

		void draw() override
		{
			auto styleManager = m_styleManager.getScopedStyleManager();
			ScopedID id;

			if (!m_enabled)
			{
				ImVec4 disabled_color = ImVec4(ImGui::GetStyleColorVec4(ImGuiCol_TextDisabled));
				disabled_color.w = 0.392f;
				styleManager.addColorStyle(ImGuiCol_FrameBg, disabled_color);
				styleManager.addColorStyle(ImGuiCol_FrameBgHovered, disabled_color);
				styleManager.addColorStyle(ImGuiCol_FrameBgActive, disabled_color);
				styleManager.addColorStyle(ImGuiCol_Button, disabled_color);
				styleManager.addColorStyle(ImGuiCol_Text, ImVec4(ImGui::GetStyleColorVec4(ImGuiCol_TextDisabled)));
			}

			if (ImGui::InputFloat3(m_label.c_str(), m_value, m_format.c_str(), m_flags))
				mvCallbackRegistry::GetCallbackRegistry()->addCallback(m_callback, m_name, m_callbackData);

		}

		void setExtraConfigDict(PyObject* dict) override
		{
			if (dict == nullptr)
				return;
			mvGlobalIntepreterLock gil;
			if (PyObject* item = PyDict_GetItemString(dict, "format")) m_format = ToString(item);

			// helper for bit flipping
			auto flagop = [dict](const char* keyword, int flag, int& flags)
			{
				if (PyObject* item = PyDict_GetItemString(dict, keyword)) ToBool(item) ? flags |= flag : flags &= ~flag;
			};

			// flags
			flagop("on_enter", ImGuiInputTextFlags_EnterReturnsTrue, m_flags);
			flagop("readonly", ImGuiInputTextFlags_ReadOnly, m_flags);

		}

		void getExtraConfigDict(PyObject* dict) override
		{
			if (dict == nullptr)
				return;
			mvGlobalIntepreterLock gil;
			PyDict_SetItemString(dict, "format", ToPyString(m_format));

			// helper to check and set bit
			auto checkbitset = [dict](const char* keyword, int flag, const int& flags)
			{
				PyDict_SetItemString(dict, keyword, ToPyBool(flags & flag));
			};

			// window flags
			checkbitset("on_enter", ImGuiInputTextFlags_EnterReturnsTrue, m_flags);
			checkbitset("readonly", ImGuiInputTextFlags_ReadOnly, m_flags);

		}

	private:

		std::string         m_format = "%.3f";
		ImGuiInputTextFlags m_flags = 0;
		ImGuiInputTextFlags m_stor_flags = 0;

	};

	//-----------------------------------------------------------------------------
	// mvInputFloat4
	//-----------------------------------------------------------------------------
	class mvInputFloat4 : public mvFloat4PtrBase
	{

	public:

		MV_APPITEM_TYPE(mvAppItemType::InputFloat4, "add_input_float4")

		mvInputFloat4(const std::string& name, float* default_value, const std::string& dataSource)
			: mvFloat4PtrBase(name, default_value, dataSource)
		{
			m_description.disableAllowed = true;
		}

		void setEnabled(bool value) override
		{
			if (value)
				m_flags = m_stor_flags;

			else
			{
				m_stor_flags = m_flags;
				m_flags |= ImGuiInputTextFlags_ReadOnly;
				m_flags &= ~ImGuiInputTextFlags_EnterReturnsTrue;
			}

			m_enabled = value;
		}

		void draw() override
		{
			auto styleManager = m_styleManager.getScopedStyleManager();
			ScopedID id;

			if (!m_enabled)
			{
				ImVec4 disabled_color = ImVec4(ImGui::GetStyleColorVec4(ImGuiCol_TextDisabled));
				disabled_color.w = 0.392f;
				styleManager.addColorStyle(ImGuiCol_FrameBg, disabled_color);
				styleManager.addColorStyle(ImGuiCol_FrameBgHovered, disabled_color);
				styleManager.addColorStyle(ImGuiCol_FrameBgActive, disabled_color);
				styleManager.addColorStyle(ImGuiCol_Button, disabled_color);
				styleManager.addColorStyle(ImGuiCol_Text, ImVec4(ImGui::GetStyleColorVec4(ImGuiCol_TextDisabled)));
			}

			if (ImGui::InputFloat4(m_label.c_str(), m_value, m_format.c_str(), m_flags))
				mvCallbackRegistry::GetCallbackRegistry()->addCallback(m_callback, m_name, m_callbackData);
		}

		void setExtraConfigDict(PyObject* dict) override
		{
			if (dict == nullptr)
				return;
			mvGlobalIntepreterLock gil;
			if (PyObject* item = PyDict_GetItemString(dict, "format")) m_format = ToString(item);

			// helper for bit flipping
			auto flagop = [dict](const char* keyword, int flag, int& flags)
			{
				if (PyObject* item = PyDict_GetItemString(dict, keyword)) ToBool(item) ? flags |= flag : flags &= ~flag;
			};

			// flags
			flagop("on_enter", ImGuiInputTextFlags_EnterReturnsTrue, m_flags);
			flagop("readonly", ImGuiInputTextFlags_ReadOnly, m_flags);

		}

		void getExtraConfigDict(PyObject* dict) override
		{
			if (dict == nullptr)
				return;
			mvGlobalIntepreterLock gil;
			PyDict_SetItemString(dict, "format", ToPyString(m_format));

			// helper to check and set bit
			auto checkbitset = [dict](const char* keyword, int flag, const int& flags)
			{
				PyDict_SetItemString(dict, keyword, ToPyBool(flags & flag));
			};

			// window flags
			checkbitset("on_enter", ImGuiInputTextFlags_EnterReturnsTrue, m_flags);
			checkbitset("readonly", ImGuiInputTextFlags_ReadOnly, m_flags);
		}

	private:

		std::string         m_format = "%.3f";
		ImGuiInputTextFlags m_flags = 0;
		ImGuiInputTextFlags m_stor_flags = 0;

	};

}