#include "mvActivatedHandler.h"
#include "mvLog.h"
#include "mvItemRegistry.h"
#include "mvPythonExceptions.h"
#include "mvUtilities.h"

namespace Marvel {

	void mvActivatedHandler::InsertParser(std::map<std::string, mvPythonParser>* parsers)
	{

		mvPythonParser parser(mvPyDataType::UUID, "Adds a handler which runs a given callback when the specified item is activated.", { "Events", "Widgets" });
		mvAppItem::AddCommonArgs(parser, (CommonParserArgs)(
			MV_PARSER_ARG_ID |
			MV_PARSER_ARG_USER_DATA |
			MV_PARSER_ARG_CALLBACK)
		);

		parser.addArg<mvPyDataType::UUID>("parent");

		parser.finalize();

		parsers->insert({ s_command, parser });
	}

	mvActivatedHandler::mvActivatedHandler(mvUUID uuid)
		:
		mvAppItem(uuid)
	{

	}

	bool mvActivatedHandler::isParentCompatible(mvAppItemType type)
	{
		return true;

		//mvThrowPythonError(mvErrorCode::mvN1one, "Drawing item parent must be a drawing.");
		//MV_ITEM_REGISTRY_ERROR("Drawing item parent must be a drawing.");
		//assert(false);
		//return false;
	}

	void mvActivatedHandler::draw(ImDrawList* drawlist, float x, float y)
	{

		if (ImGui::IsItemActivated())
		{
			mvApp::GetApp()->getCallbackRegistry().submitCallback([=]()
				{
					mvApp::GetApp()->getCallbackRegistry().runCallback(getCallback(false), m_uuid, GetPyNone(), m_user_data);
				});
		}
	}

	void mvActivatedHandler::handleSpecificRequiredArgs(PyObject* dict)
	{
		if (!mvApp::GetApp()->getParsers()[s_command].verifyRequiredArguments(dict))
			return;

		for (int i = 0; i < PyTuple_Size(dict); i++)
		{
			PyObject* item = PyTuple_GetItem(dict, i);
			switch (i)
			{
			case 0:
				m_parent = ToUUID(item);
				break;

			default:
				break;
			}
		}
	}
}