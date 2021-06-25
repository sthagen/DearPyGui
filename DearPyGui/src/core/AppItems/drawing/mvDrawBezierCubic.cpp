#include "mvDrawBezierCubic.h"
#include "mvLog.h"
#include "mvItemRegistry.h"
#include "mvPythonExceptions.h"

namespace Marvel {

	void mvDrawBezierCubic::InsertParser(std::map<std::string, mvPythonParser>* parsers)
	{

		mvPythonParser parser(mvPyDataType::UUID, "Draws a cubic bezier curve on a drawing.", { "Drawlist", "Widgets" });
		mvAppItem::AddCommonArgs(parser, (CommonParserArgs)(
			MV_PARSER_ARG_ID |
			MV_PARSER_ARG_PARENT |
			MV_PARSER_ARG_BEFORE |
			MV_PARSER_ARG_SHOW)
		);

		parser.addArg<mvPyDataType::FloatList>("p1");
		parser.addArg<mvPyDataType::FloatList>("p2");
		parser.addArg<mvPyDataType::FloatList>("p3");
		parser.addArg<mvPyDataType::FloatList>("p4");

		parser.addArg<mvPyDataType::IntList>("color", mvArgType::KEYWORD_ARG, "(255, 255, 255, 255)");

		parser.addArg<mvPyDataType::Float>("thickness", mvArgType::KEYWORD_ARG, "1.0");

		parser.addArg<mvPyDataType::Integer>("size", mvArgType::KEYWORD_ARG, "4");
		parser.addArg<mvPyDataType::Integer>("segments", mvArgType::KEYWORD_ARG, "0");

		parser.finalize();

		parsers->insert({ s_command, parser });
	}

	mvDrawBezierCubic::mvDrawBezierCubic(mvUUID uuid)
		:
		mvAppItem(uuid)
	{
	}

	bool mvDrawBezierCubic::isParentCompatible(mvAppItemType type)
	{
		if (type == mvAppItemType::mvStagingContainer) return true;
		if (type == mvAppItemType::mvDrawlist) return true;
		if (type == mvAppItemType::mvWindowAppItem) return true;
		if (type == mvAppItemType::mvPlot) return true;
		if (type == mvAppItemType::mvDrawLayer) return true;
		if (type == mvAppItemType::mvViewportDrawlist) return true;

		mvThrowPythonError(mvErrorCode::mvIncompatibleParent, s_command,
			"Incompatible parent. Acceptable parents include: staging container, drawlist, layer, window, plot, viewport drawlist.", this);

		MV_ITEM_REGISTRY_ERROR("Drawing item parent must be a drawing.");
		assert(false);
		return false;
	}

	void mvDrawBezierCubic::draw(ImDrawList* drawlist, float x, float y)
	{
		mvVec2 start = { x, y };
		drawlist->AddBezierCubic(m_p1 + start, m_p2 + start, m_p3 + start, m_p4 + start, m_color, m_thickness, m_segments);
	}

	void mvDrawBezierCubic::handleSpecificRequiredArgs(PyObject* dict)
	{
		if (!mvApp::GetApp()->getParsers()[s_command].verifyRequiredArguments(dict))
			return;

		for (int i = 0; i < PyTuple_Size(dict); i++)
		{
			PyObject* item = PyTuple_GetItem(dict, i);
			switch (i)
			{
			case 0:
				m_p1 = ToVec2(item);
				break;

			case 1:
				m_p2 = ToVec2(item);
				break;

			case 2:
				m_p3 = ToVec2(item);
				break;

			case 3:
				m_p4 = ToVec2(item);
				break;

			default:
				break;
			}
		}
	}

	void mvDrawBezierCubic::handleSpecificKeywordArgs(PyObject* dict)
	{
		if (dict == nullptr)
			return;

		if (PyObject* item = PyDict_GetItemString(dict, "p1")) m_p1 = ToVec2(item);
		if (PyObject* item = PyDict_GetItemString(dict, "p2")) m_p2 = ToVec2(item);
		if (PyObject* item = PyDict_GetItemString(dict, "p3")) m_p3 = ToVec2(item);
		if (PyObject* item = PyDict_GetItemString(dict, "p4")) m_p4 = ToVec2(item);
		if (PyObject* item = PyDict_GetItemString(dict, "color")) m_color = ToColor(item);
		if (PyObject* item = PyDict_GetItemString(dict, "thickness")) m_thickness = ToFloat(item);
		if (PyObject* item = PyDict_GetItemString(dict, "segments")) m_segments = ToInt(item);
	}

	void mvDrawBezierCubic::getSpecificConfiguration(PyObject* dict)
	{
		if (dict == nullptr)
			return;

		PyDict_SetItemString(dict, "p1", ToPyPair(m_p1.x, m_p1.y));
		PyDict_SetItemString(dict, "p2", ToPyPair(m_p2.x, m_p2.y));
		PyDict_SetItemString(dict, "p3", ToPyPair(m_p3.x, m_p3.y));
		PyDict_SetItemString(dict, "p4", ToPyPair(m_p4.x, m_p4.y));
		PyDict_SetItemString(dict, "color", ToPyColor(m_color));
		PyDict_SetItemString(dict, "thickness", ToPyFloat(m_thickness));
		PyDict_SetItemString(dict, "segments", ToPyInt(m_segments));
	}

}