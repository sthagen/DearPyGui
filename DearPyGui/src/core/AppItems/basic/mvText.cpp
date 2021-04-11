#include "mvText.h"
#include "mvApp.h"
#include "mvItemRegistry.h"
#include "mvImGuiThemeScope.h"
#include "mvFontScope.h"

namespace Marvel {

	void mvText::InsertParser(std::map<std::string, mvPythonParser>* parsers)
	{
		parsers->insert({ s_command, mvPythonParser({
			{mvPythonDataType::Optional},
			{mvPythonDataType::String, "name"},
			{mvPythonDataType::KeywordOnly},
			{mvPythonDataType::Integer, "wrap", "number of characters until wraping", "-1"},
			{mvPythonDataType::FloatList, "color", "color of the text (rgba)", "(-1, 0, 0, 0)"},
			{mvPythonDataType::Bool, "bullet", "makes the text bulleted", "False"},
			{mvPythonDataType::String, "parent", "Parent this item will be added to. (runtime adding)", "''"},
			{mvPythonDataType::String, "before", "This item will be displayed before the specified item in the parent. (runtime adding)", "''"},
			{mvPythonDataType::String, "source", "", "''"},
			{mvPythonDataType::String, "default_value", "", "''"},
			{mvPythonDataType::Bool, "show", "Attempt to render", "True"},
		}, "Adds text", "None", "Adding Widgets") });
	}

	void mvLabelText::InsertParser(std::map<std::string, mvPythonParser>* parsers)
	{
		parsers->insert({ s_command, mvPythonParser({
			{mvPythonDataType::Optional},
			{mvPythonDataType::String, "name"},
			{mvPythonDataType::KeywordOnly},
			{mvPythonDataType::String, "default_value", "", "''"},
			{mvPythonDataType::FloatList, "color", "", "(-1, 0, 0, 0)"},
			{mvPythonDataType::String, "parent", "Parent this item will be added to. (runtime adding)", "''"},
			{mvPythonDataType::String, "before", "This item will be displayed before the specified item in the parent. (runtime adding)", "''"},
			{mvPythonDataType::String, "source", "data source for shared data", "''"},
			{mvPythonDataType::String, "label", "", "''"},
			{mvPythonDataType::Bool, "show", "Attempt to render", "True"},
		}, "Adds text with a label. Useful for output values.", "None", "Adding Widgets") });
	}

	mvText::mvText(const std::string& name)
		: 
		mvStringPtrBase(name)
	{
		*m_value = name;
	}

	void mvText::draw(ImDrawList* drawlist, float x, float y)
	{
		ScopedID id;
		mvImGuiThemeScope scope(this);
		mvFontScope fscope(this);

		if (m_color.r > 0.0f)
			ImGui::PushStyleColor(ImGuiCol_Text, m_color.toVec4());

		if (m_wrap >= 0)
			ImGui::PushTextWrapPos((float)m_wrap);

		if (m_bullet)
			ImGui::Bullet();

		//ImGui::Text("%s", m_value.c_str());
		ImGui::TextUnformatted(m_value->c_str()); // this doesn't have a buffer size limit

		if (m_wrap >= 0)
			ImGui::PopTextWrapPos();

		if (m_color.r > 0.0f)
			ImGui::PopStyleColor();

	}

	mvLabelText::mvLabelText(const std::string& name)
		: 
		mvStringPtrBase(name)
	{
	}

	void mvLabelText::draw(ImDrawList* drawlist, float x, float y)
	{

		if (m_color.r > 0.0f)
		{
			ImGui::PushStyleColor(ImGuiCol_Text, m_color.toVec4());

			ImGui::TextUnformatted(m_value->c_str());

			ImGui::PopStyleColor();

			ImGui::SameLine();

			mvImGuiThemeScope scope(this);
			ImGui::TextUnformatted(m_specificedlabel.c_str());
		}

		else
		{
			mvImGuiThemeScope scope(this);
			ImGui::LabelText(m_specificedlabel.c_str(), m_value->c_str());
		}

	}

	void mvText::setExtraConfigDict(PyObject* dict)
	{
		if (dict == nullptr)
			return;

		if (PyObject* item = PyDict_GetItemString(dict, "color")) m_color = ToColor(item);
		if (PyObject* item = PyDict_GetItemString(dict, "wrap")) m_wrap = ToInt(item);
		if (PyObject* item = PyDict_GetItemString(dict, "bullet")) m_bullet = ToBool(item);

	}

	void mvText::getExtraConfigDict(PyObject* dict)
	{
		if (dict == nullptr)
			return;

		PyDict_SetItemString(dict, "color", ToPyColor(m_color));
		PyDict_SetItemString(dict, "wrap", ToPyInt(m_wrap));
		PyDict_SetItemString(dict, "bullet", ToPyBool(m_bullet));
	}

	void mvLabelText::setExtraConfigDict(PyObject* dict)
	{
		if (dict == nullptr)
			return;
		 
		if (PyObject* item = PyDict_GetItemString(dict, "color")) m_color = ToColor(item);
	}

	void mvLabelText::getExtraConfigDict(PyObject* dict)
	{
		if (dict == nullptr)
			return;
		 
		PyDict_SetItemString(dict, "color", ToPyColor(m_color));
	}

}