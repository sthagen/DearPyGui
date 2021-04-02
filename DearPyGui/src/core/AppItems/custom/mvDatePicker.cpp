#include "mvDatePicker.h"
#include "mvApp.h"
#include <implot.h>
#include <implot_internal.h>
#include <misc/cpp/imgui_stdlib.h>
#include "mvItemRegistry.h"
#include "mvImGuiThemeScope.h"
#include "mvFontScope.h"

namespace Marvel {

	void mvDatePicker::InsertParser(std::map<std::string, mvPythonParser>* parsers)
	{
		parsers->insert({ s_command, mvPythonParser({
			{mvPythonDataType::Optional},
			{mvPythonDataType::String, "name"},
			{mvPythonDataType::KeywordOnly},
			{mvPythonDataType::Dict, "default_value", "data dict", "{'month_day': 14, 'year':20, 'month':5}"},
			{mvPythonDataType::Integer, "level", "0-day, 1-month, 2-year", "0"},
			{mvPythonDataType::Callable, "callback", "Registers a callback", "None"},
			{mvPythonDataType::Object, "callback_data", "Callback data", "None"},
			{mvPythonDataType::String, "parent", "Parent this item will be added to. (runtime adding)", "''"},
			{mvPythonDataType::String, "before","This item will be displayed before the specified item in the parent. (runtime adding)", "''"},
			{mvPythonDataType::Bool, "show", "Attempt to render", "True"},
		}, "Adds a data selector widget.", "None", "Adding Widgets") });
	}

	mvDatePicker::mvDatePicker(const std::string& name, tm default_value)
		: mvTimePtrBase(name, default_value)
	{
	}

	void mvDatePicker::draw(ImDrawList* drawlist, float x, float y)
	{
		ScopedID id;
		mvImGuiThemeScope scope(this);
		mvFontScope fscope(this);

		if (ImPlot::ShowDatePicker(m_name.c_str(), &m_level, m_imvalue.get(), m_imvalue.get()))
		{
			ImPlot::GetGmtTime(*m_imvalue, m_value.get());
			mvApp::GetApp()->getCallbackRegistry().addCallback(m_callback, m_name, m_callback_data);
		}

	}

	void mvDatePicker::setExtraConfigDict(PyObject* dict)
	{
		if (dict == nullptr)
			return;
		 
		if (PyObject* item = PyDict_GetItemString(dict, "level")) m_level = ToInt(item);
	}

	void mvDatePicker::getExtraConfigDict(PyObject* dict)
	{
		if (dict == nullptr)
			return;
		 
		PyDict_SetItemString(dict, "level", ToPyInt(m_level));
	}

	PyObject* mvDatePicker::add_date_picker(PyObject* self, PyObject* args, PyObject* kwargs)
	{
		static int i = 0; i++;
		std::string sname = std::string(std::string("$$DPG_") + s_internal_id + std::to_string(i));
		const char* name = sname.c_str();
		PyObject* default_value = nullptr;
		int level = 0;
		PyObject* callback = nullptr;
		PyObject* callback_data = nullptr;
		const char* before = "";
		const char* parent = "";
		int show = true;

		if (!(mvApp::GetApp()->getParsers())["add_date_picker"].parse(args, kwargs, __FUNCTION__,
			&name, &default_value, &level, &callback, &callback_data, &parent, &before, &show))
			return ToPyBool(false);

		auto item = CreateRef<mvDatePicker>(name, ToTime(default_value));
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