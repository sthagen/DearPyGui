#include "mvColorButton.h"
#include "mvApp.h"
#include <array>
#include "mvItemRegistry.h"

namespace Marvel {

	void mvColorButton::InsertParser(std::map<std::string, mvPythonParser>* parsers)
	{
		mvPythonParser parser(mvPyDataType::UUID, "Adds a color button.", { "Widgets" });
		mvAppItem::AddCommonArgs(parser, (CommonParserArgs)(
			MV_PARSER_ARG_ID |
			MV_PARSER_ARG_WIDTH |
			MV_PARSER_ARG_HEIGHT |
			MV_PARSER_ARG_INDENT |
			MV_PARSER_ARG_PARENT |
			MV_PARSER_ARG_BEFORE |
			MV_PARSER_ARG_CALLBACK |
			MV_PARSER_ARG_USER_DATA |
			MV_PARSER_ARG_SHOW |
			MV_PARSER_ARG_ENABLED |
			MV_PARSER_ARG_FILTER |
			MV_PARSER_ARG_DROP_CALLBACK |
			MV_PARSER_ARG_DRAG_CALLBACK |
			MV_PARSER_ARG_PAYLOAD_TYPE |
			MV_PARSER_ARG_TRACKED |
			MV_PARSER_ARG_POS)
		);

		parser.addArg<mvPyDataType::IntList>("default_value", mvArgType::POSITIONAL_ARG, "(0, 0, 0, 255)");

		parser.addArg<mvPyDataType::Bool>("no_alpha", mvArgType::KEYWORD_ARG, "False", "Ignore Alpha component.");
		parser.addArg<mvPyDataType::Bool>("no_border", mvArgType::KEYWORD_ARG, "False", "Disable border around the image.");
		parser.addArg<mvPyDataType::Bool>("no_drag_drop", mvArgType::KEYWORD_ARG, "False", "Disable display of inline text label.");

		parser.finalize();

		parsers->insert({ s_command, parser });
	}

	mvColorButton::mvColorButton(mvUUID uuid)
		: 
		mvColorPtrBase(uuid)
	{
	}

	void mvColorButton::draw(ImDrawList* drawlist, float x, float y)
	{
		ScopedID id(m_uuid);

		ImVec4 col = { (*m_value)[0], (*m_value)[1], (*m_value)[2], (*m_value)[3] };

		if (ImGui::ColorButton(m_label.c_str(), col, m_flags, ImVec2((float)m_width, (float)m_height)))
			mvApp::GetApp()->getCallbackRegistry().addCallback(getCallback(false), m_uuid, nullptr, m_user_data);

	}

	void mvColorButton::handleSpecificPositionalArgs(PyObject* dict)
	{
		if (!mvApp::GetApp()->getParsers()[s_command].verifyPositionalArguments(dict))
			return;

		for (int i = 0; i < PyTuple_Size(dict); i++)
		{
			PyObject* item = PyTuple_GetItem(dict, i);
			switch (i)
			{
			case 0:
				setPyValue(item);
				break;

			default:
				break;
			}
		}
	}

	void mvColorButton::handleSpecificKeywordArgs(PyObject* dict)
	{
		if (dict == nullptr)
			return;


		// helpers for bit flipping
		auto flagop = [dict](const char* keyword, int flag, int& flags)
		{
			if (PyObject* item = PyDict_GetItemString(dict, keyword)) ToBool(item) ? flags |= flag : flags &= ~flag;
		};
		flagop("no_alpha", ImGuiColorEditFlags_NoAlpha, m_flags);
		flagop("no_border", ImGuiColorEditFlags_NoBorder, m_flags);
		flagop("no_drag_drop", ImGuiColorEditFlags_NoDragDrop, m_flags);
	}

	void mvColorButton::getSpecificConfiguration(PyObject* dict)
	{
		if (dict == nullptr)
			return;

		// helper to check and set bit
		auto checkbitset = [dict](const char* keyword, int flag, const int& flags)
		{
			PyDict_SetItemString(dict, keyword, ToPyBool(flags & flag));
		};

		checkbitset("no_alpha", ImGuiColorEditFlags_NoAlpha, m_flags);
		checkbitset("no_border", ImGuiColorEditFlags_NoBorder, m_flags);
		checkbitset("no_drag_drop", ImGuiColorEditFlags_NoDragDrop, m_flags);
	}

}