#include <utility>
#include "mvSelectable.h"
#include "mvApp.h"
#include "mvValueStorage.h"
#include "mvPythonTranslator.h"
#include "mvGlobalIntepreterLock.h"

namespace Marvel {
	void mvSelectable::InsertParser(std::map<std::string, mvPythonParser>* parsers)
	{
		parsers->insert({ "add_selectable", mvPythonParser({
			{mvPythonDataType::String, "name"},
			{mvPythonDataType::KeywordOnly},
			{mvPythonDataType::Bool, "default_value", "", "False"},
			{mvPythonDataType::Callable, "callback", "Registers a callback", "None"},
			{mvPythonDataType::Object, "callback_data", "Callback data", "None"},
			{mvPythonDataType::String, "tip", "Adds a simple tooltip", "''"},
			{mvPythonDataType::String, "parent", "Parent this item will be added to. (runtime adding)", "''"},
			{mvPythonDataType::String, "before", "This item will be displayed before the specified item in the parent. (runtime adding)", "''"},
			{mvPythonDataType::String, "source", "", "''"},
			{mvPythonDataType::Bool, "enabled", "Display grayed out text so selectable cannot be selected", "True"},
			{mvPythonDataType::String, "label", "", "''"},
			{mvPythonDataType::Bool, "show", "Attempt to render", "True"},
			{mvPythonDataType::Bool, "span_columns", "span all columns", "False"},
		}, "Adds a selectable.", "None", "Adding Widgets") });
	}

	mvSelectable::mvSelectable(const std::string& name, bool default_value, const std::string& dataSource)
		: mvBoolPtrBase(name, default_value, dataSource)
	{
		m_description.disableAllowed = true;
	}

	void mvSelectable::setEnabled(bool value)
	{
		if (value)
			m_flags &= ~ImGuiSelectableFlags_Disabled;

		else
			m_flags |= ImGuiSelectableFlags_Disabled;

		m_enabled = value;
	}

	void mvSelectable::draw()
	{
		auto styleManager = m_styleManager.getScopedStyleManager();
		ScopedID id;

		if (ImGui::Selectable(m_label.c_str(), m_value, m_flags))
			mvApp::GetApp()->getCallbackRegistry().addCallback(m_callback, m_name, m_callbackData);

	}

	void mvSelectable::setExtraConfigDict(PyObject* dict)
	{
		if (dict == nullptr)
			return;
		mvGlobalIntepreterLock gil;

		// helper for bit flipping
		auto flagop = [dict](const char* keyword, int flag, int& flags, bool flip)
		{
			if (PyObject* item = PyDict_GetItemString(dict, keyword)) ToBool(item) ? flags |= flag : flags &= ~flag;
		};

		// window flags
		flagop("span_columns", ImGuiSelectableFlags_SpanAllColumns, m_flags, false);

	}

	void mvSelectable::getExtraConfigDict(PyObject* dict)
	{
		if (dict == nullptr)
			return;
		mvGlobalIntepreterLock gil;

		// helper to check and set bit
		auto checkbitset = [dict](const char* keyword, int flag, const int& flags, bool flip)
		{
			PyDict_SetItemString(dict, keyword, ToPyBool(flags & flag));
		};

		// window flags
		checkbitset("span_columns", ImGuiSelectableFlags_SpanAllColumns, m_flags, false);
	}

	PyObject* add_selectable(PyObject* self, PyObject* args, PyObject* kwargs)
	{
		const char* name;
		int default_value = false;
		PyObject* callback = nullptr;
		PyObject* callback_data = nullptr;
		const char* tip = "";
		const char* before = "";
		const char* parent = "";
		const char* source = "";
		int enabled = true;
		const char* label = "";
		int show = true;
		int span_columns = false;

		//ImGuiSelectableFlags flags = ImGuiSelectableFlags_None;

		if (!(*mvApp::GetApp()->getParsers())["add_selectable"].parse(args, kwargs, __FUNCTION__, &name,
			&default_value, &callback, &callback_data, &tip, &parent, &before, &source, &enabled,
			&label, &show, &span_columns))
			return ToPyBool(false);

		auto item = CreateRef<mvSelectable>(name, default_value, source);
		if (callback)
			Py_XINCREF(callback);
		item->setCallback(callback);
		if (callback_data)
			Py_XINCREF(callback_data);
		item->setCallbackData(callback_data);

		item->checkConfigDict(kwargs);
		item->setConfigDict(kwargs);
		item->setExtraConfigDict(kwargs);

		return ToPyBool(mvApp::GetApp()->getItemRegistry().addItemWithRuntimeChecks(item, parent, before));
	}

}