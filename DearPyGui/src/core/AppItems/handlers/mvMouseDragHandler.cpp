#include "mvMouseDragHandler.h"
#include "mvLog.h"
#include "mvItemRegistry.h"
#include "mvPythonExceptions.h"
#include "mvUtilities.h"

namespace Marvel {

	void mvMouseDragHandler::InsertParser(std::map<std::string, mvPythonParser>* parsers)
	{

		mvPythonParser parser(mvPyDataType::UUID, "Adds a handler which runs a given callback when the specified mouse button is clicked and dragged a set threshold. Parent must be a handler registry.", { "Events", "Widgets" });
		mvAppItem::AddCommonArgs(parser, (CommonParserArgs)(
			MV_PARSER_ARG_ID |
			MV_PARSER_ARG_CALLBACK |
			MV_PARSER_ARG_SHOW |
			MV_PARSER_ARG_USER_DATA)
		);

		parser.addArg<mvPyDataType::Integer>("button", mvArgType::POSITIONAL_ARG, "-1", "Submits callback for all mouse buttons");
		parser.addArg<mvPyDataType::Float>("threshold", mvArgType::POSITIONAL_ARG, "10.0", "The threshold the mouse must be dragged before the callback is ran");
		parser.addArg<mvPyDataType::UUID>("parent", mvArgType::KEYWORD_ARG, "internal_dpg.mvReservedUUID_1", "Parent to add this item to. (runtime adding)");
		parser.finalize();

		parsers->insert({ s_command, parser });
	}

	mvMouseDragHandler::mvMouseDragHandler(mvUUID uuid)
		:
		mvAppItem(uuid)
	{

	}

	bool mvMouseDragHandler::isParentCompatible(mvAppItemType type)
	{
		if (type == mvAppItemType::mvStagingContainer) return true;
		if (type == mvAppItemType::mvHandlerRegistry) return true;

		mvThrowPythonError(mvErrorCode::mvIncompatibleParent, s_command,
			"Incompatible parent. Acceptable parents include: staging container, handler registry", this);
		MV_ITEM_REGISTRY_ERROR("Drawing item parent must be a drawing.");
		assert(false);
		return false;
	}

	void mvMouseDragHandler::draw(ImDrawList* drawlist, float x, float y)
	{
		if (m_button == -1)
		{
			for (int i = 0; i < IM_ARRAYSIZE(ImGui::GetIO().MouseDown); i++)
			{
				if (ImGui::IsMouseReleased(i))
					ImGui::ResetMouseDragDelta(i);

				if (ImGui::IsMouseDragging(i, m_threshold))
				{
					mvApp::GetApp()->getCallbackRegistry().submitCallback([=]()
						{
							mvApp::GetApp()->getCallbackRegistry().runCallback(getCallback(false), m_uuid,
								ToPyMTrip(i, ImGui::GetMouseDragDelta(i).x, ImGui::GetMouseDragDelta(i).y), m_user_data);
						});
				}
			}
		}

		else if (ImGui::IsMouseDragging(m_button, m_threshold))
		{
			if (ImGui::IsMouseReleased(m_button))
				ImGui::ResetMouseDragDelta(m_button);
			mvApp::GetApp()->getCallbackRegistry().submitCallback([=]()
				{
					mvApp::GetApp()->getCallbackRegistry().runCallback(getCallback(false), m_uuid,
						ToPyMTrip(m_button, ImGui::GetMouseDragDelta(m_button).x, ImGui::GetMouseDragDelta(m_button).y), m_user_data);
				});
		}
	}

	void mvMouseDragHandler::handleSpecificPositionalArgs(PyObject* dict)
	{
		if (!mvApp::GetApp()->getParsers()[s_command].verifyRequiredArguments(dict))
			return;

		for (int i = 0; i < PyTuple_Size(dict); i++)
		{
			PyObject* item = PyTuple_GetItem(dict, i);
			switch (i)
			{
			case 0:
				m_button = ToInt(item);
				break;
			case 1:
				m_threshold = ToFloat(item);
				break;

			default:
				break;
			}
		}
	}

	void mvMouseDragHandler::handleSpecificKeywordArgs(PyObject* dict)
	{
		if (dict == nullptr)
			return;

		if (PyObject* item = PyDict_GetItemString(dict, "button")) m_button = ToInt(item);
		if (PyObject* item = PyDict_GetItemString(dict, "threshold")) m_threshold = ToFloat(item);
	}

	void mvMouseDragHandler::getSpecificConfiguration(PyObject* dict)
	{
		if (dict == nullptr)
			return;

		PyDict_SetItemString(dict, "button", ToPyInt(m_button));
		PyDict_SetItemString(dict, "threshold", ToPyFloat(m_threshold));
	}
}