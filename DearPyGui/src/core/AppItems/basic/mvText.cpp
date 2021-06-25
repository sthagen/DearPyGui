#include "mvText.h"
#include "mvApp.h"
#include "mvItemRegistry.h"

namespace Marvel {

	void mvText::InsertParser(std::map<std::string, mvPythonParser>* parsers)
	{
		mvPythonParser parser(mvPyDataType::UUID, "Adds text. Text can have an optional label that will display to the right of the text.", { "Widgets" });
		mvAppItem::AddCommonArgs(parser, (CommonParserArgs)(
			MV_PARSER_ARG_ID |
			MV_PARSER_ARG_INDENT |
			MV_PARSER_ARG_PARENT |
			MV_PARSER_ARG_BEFORE |
			MV_PARSER_ARG_SOURCE |
			MV_PARSER_ARG_SHOW |
			MV_PARSER_ARG_FILTER |
			MV_PARSER_ARG_TRACKED |
			MV_PARSER_ARG_POS)
		);

		parser.addArg<mvPyDataType::String>("default_value", mvArgType::POSITIONAL_ARG, "''");

		parser.addArg<mvPyDataType::Integer>("wrap", mvArgType::KEYWORD_ARG, "-1", "Number of pixels until wrapping starts.");

		parser.addArg<mvPyDataType::Bool>("bullet", mvArgType::KEYWORD_ARG, "False", "Makes the text bulleted.");

		parser.addArg<mvPyDataType::FloatList>("color", mvArgType::KEYWORD_ARG, "(-1, -1, -1, -1)", "Color of the text (rgba).");

		parser.addArg<mvPyDataType::Bool>("show_label", mvArgType::KEYWORD_ARG, "False", "Displays the label.");

		parser.finalize();

		parsers->insert({ s_command, parser });
	}

	mvText::mvText(mvUUID uuid)
		: 
		mvStringPtrBase(uuid)
	{
		*m_value = "Not Specified";
	}

	void mvText::draw(ImDrawList* drawlist, float x, float y)
	{
		// this fixes the vertical text alignment issue according it DearImGui issue #2317
		ImGui::AlignTextToFramePadding();

		const ImGuiStyle& style = ImGui::GetStyle();
		const float w = ImGui::CalcItemWidth();
		const float textVertCenter = ImGui::GetCursorPosY();
		const float valueEndX = ImGui::GetCursorPosX() + w;

		if (m_color.r >= 0.0f)
			ImGui::PushStyleColor(ImGuiCol_Text, m_color.toVec4());

		if (m_wrap >= 0)
			ImGui::PushTextWrapPos((float)m_wrap);

		if (m_bullet)
			ImGui::Bullet();

		//ImGui::Text("%s", m_value.c_str());
		ImGui::TextUnformatted(m_value->c_str()); // this doesn't have a buffer size limit

		if (m_wrap >= 0)
			ImGui::PopTextWrapPos();

		if (m_color.r >= 0.0f)
			ImGui::PopStyleColor();

		if (m_show_label)
		{
			ImGui::SameLine();
			ImGui::SetCursorPos({ valueEndX + style.ItemInnerSpacing.x, textVertCenter });
			ImGui::TextUnformatted(m_specificedlabel.c_str());
		}

	}

	void mvText::handleSpecificPositionalArgs(PyObject* dict)
	{
		if (!mvApp::GetApp()->getParsers()[s_command].verifyPositionalArguments(dict))
			return;

		for (int i = 0; i < PyTuple_Size(dict); i++)
		{
			PyObject* item = PyTuple_GetItem(dict, i);
			switch (i)
			{
			case 0:
				*m_value = ToString(item);
				break;

			default:
				break;
			}
		}
	}

	void mvText::handleSpecificKeywordArgs(PyObject* dict)
	{
		if (dict == nullptr)
			return;

		if (PyObject* item = PyDict_GetItemString(dict, "color")) m_color = ToColor(item);
		if (PyObject* item = PyDict_GetItemString(dict, "wrap")) m_wrap = ToInt(item);
		if (PyObject* item = PyDict_GetItemString(dict, "bullet")) m_bullet = ToBool(item);
		if (PyObject* item = PyDict_GetItemString(dict, "show_label")) m_show_label = ToBool(item);

	}

	void mvText::getSpecificConfiguration(PyObject* dict)
	{
		if (dict == nullptr)
			return;

		PyDict_SetItemString(dict, "color", ToPyColor(m_color));
		PyDict_SetItemString(dict, "wrap", ToPyInt(m_wrap));
		PyDict_SetItemString(dict, "bullet", ToPyBool(m_bullet));
		PyDict_SetItemString(dict, "show_label", ToPyBool(m_show_label));
	}
}