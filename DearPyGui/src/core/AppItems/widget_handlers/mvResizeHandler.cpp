#include "mvResizeHandler.h"
#include "mvLog.h"
#include "mvItemRegistry.h"
#include "mvPythonExceptions.h"
#include "mvUtilities.h"
#include "containers/mvWindowAppItem.h"

namespace Marvel {

	void mvResizeHandler::InsertParser(std::map<std::string, mvPythonParser>* parsers)
	{

		mvPythonParser parser(mvPyDataType::UUID, "Adds a handler which runs a given callback when the specified item is resized.", { "Events", "Widgets" });
		mvAppItem::AddCommonArgs(parser, (CommonParserArgs)(
			MV_PARSER_ARG_ID |
			MV_PARSER_ARG_USER_DATA |
			MV_PARSER_ARG_CALLBACK)
		);

		parser.addArg<mvPyDataType::UUID>("parent");

		parser.finalize();

		parsers->insert({ s_command, parser });
	}

	mvResizeHandler::mvResizeHandler(mvUUID uuid)
		:
		mvAppItem(uuid)
	{

	}

	bool mvResizeHandler::isParentCompatible(mvAppItemType type)
	{
		if (type == mvAppItemType::mvWindowAppItem) return true;
		MV_ITEM_REGISTRY_ERROR("mvResizeHandler item parent must be a Window.");
		assert(false);
		return false;
	}

	void mvResizeHandler::draw(ImDrawList* drawlist, float x, float y)
	{

		if (m_parentPtr)
		{
			auto parentPtr = static_cast<mvWindowAppItem*>(m_parentPtr);
			if (parentPtr->m_resized && m_callback)
			{
				mvApp::GetApp()->getCallbackRegistry().submitCallback([=]() {
					PyObject* dimensions = PyTuple_New(2);
					PyTuple_SetItem(dimensions, 0, PyLong_FromLong(m_parentPtr->getWidth()));
					PyTuple_SetItem(dimensions, 1, PyLong_FromLong(m_parentPtr->getHeight()));
					mvApp::GetApp()->getCallbackRegistry().addCallback(m_callback, m_uuid, dimensions, m_user_data);
					});
			}

			parentPtr->m_resized = false;
		}
	}

	void mvResizeHandler::handleSpecificRequiredArgs(PyObject* dict)
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