#include "mvAreaSeries.h"
#include "mvCore.h"
#include "mvApp.h"
#include "mvItemRegistry.h"
#include "mvPythonExceptions.h"

namespace Marvel {

	void mvAreaSeries::drawPolygon()
	{

		static const std::vector<double>* xptr;
		static const std::vector<double>* yptr;

		xptr = &(*m_value.get())[0];
		yptr = &(*m_value.get())[1];

		std::vector<ImVec2> points;
		for (unsigned i = 0; i < xptr->size(); i++)
		{
			auto p = ImPlot::PlotToPixels({ (*xptr)[i], (*yptr)[i] });
			points.push_back(p);
		}

		if (m_fill.r > 0.0f)
		{
			size_t i;
			double y;
			double miny, maxy;
			double x1, y1;
			double x2, y2;
			int ind1, ind2;
			size_t ints;
			size_t n = points.size();
			int* polyints = new int[n];


			/* Get plot Y range in pixels */
			ImPlotLimits limits = ImPlot::GetPlotLimits();
			auto upperLimitsPix = ImPlot::PlotToPixels({ limits.X.Max, limits.Y.Max });
			auto lowerLimitsPix = ImPlot::PlotToPixels({ limits.X.Min, limits.Y.Min });

			/* Determine Y range of data*/
			miny = (int)points[0].y;
			maxy = (int)points[0].y;
			for (i = 1; i < n; i++)
			{
				miny = std::min((int)miny, (int)points[i].y);
				maxy = std::max((int)maxy, (int)points[i].y);
			}

			/* Determine to clip scans based on plot bounds y or data bounds y
			when the plot data is converted the min and max y invert (due to plot to graphics coord) 
			so we comapre min with max and max with min*/
			miny = std::max((int)miny, (int)upperLimitsPix.y);
			maxy = std::min((int)maxy, (int)lowerLimitsPix.y);

			/* Draw, scanning y */
			for (y = miny; y <= maxy; y++) {
				ints = 0;
				for (i = 0; (i < n); i++) {
					if (!i)
					{
						ind1 = (int)n - 1;
						ind2 = 0;
					}
					else
					{
						ind1 = (int)i - 1;
						ind2 = (int)i;
					}
					y1 = (int)points[ind1].y;
					y2 = (int)points[ind2].y;
					if (y1 < y2)
					{
						x1 = (int)points[ind1].x;
						x2 = (int)points[ind2].x;
					}
					else if (y1 > y2)
					{
						y2 = (int)points[ind1].y;
						y1 = (int)points[ind2].y;
						x2 = (int)points[ind1].x;
						x1 = (int)points[ind2].x;
					}
					else
						continue;

					if (((y >= y1) && (y < y2)) || ((y == maxy) && (y > y1) && (y <= y2)))
						polyints[ints++] = (y - y1) * (x2 - x1) / (y2 - y1) + x1;

				}

				auto compare_int = [](const void* a, const void* b)
				{
					return (*(const int*)a) - (*(const int*)b);
				};

				qsort(polyints, ints, sizeof(int), compare_int);

				for (i = 0; i < ints; i += 2)
					ImGui::GetWindowDrawList()->AddLine({ (float)polyints[i], (float)y }, { (float)polyints[i + 1], (float)y }, m_fill, 1.0f);
			}
			delete[] polyints;
		}

	}

	void mvAreaSeries::InsertParser(std::map<std::string, mvPythonParser>* parsers)
	{

		mvPythonParser parser(mvPyDataType::UUID, "Adds an area series to a plot.", { "Plotting", "Containers", "Widgets" });
		mvAppItem::AddCommonArgs(parser, (CommonParserArgs)(
			MV_PARSER_ARG_ID |
			MV_PARSER_ARG_PARENT |
			MV_PARSER_ARG_BEFORE |
			MV_PARSER_ARG_SOURCE |
			MV_PARSER_ARG_SHOW)
		);

		parser.addArg<mvPyDataType::DoubleList>("x");
		parser.addArg<mvPyDataType::DoubleList>("y");

		parser.addArg<mvPyDataType::IntList>("fill", mvArgType::KEYWORD_ARG, "(0, 0, 0, -255)");

		parser.addArg<mvPyDataType::Bool>("contribute_to_bounds", mvArgType::KEYWORD_ARG, "True");

		parser.finalize();

		parsers->insert({ s_command, parser });
	}

	mvAreaSeries::mvAreaSeries(mvUUID uuid)
		: mvSeriesBase(uuid)
	{
		m_contributeToBounds = true;
	}

	bool mvAreaSeries::isParentCompatible(mvAppItemType type)
	{
		if (type == mvAppItemType::mvPlotAxis) return true;

		mvThrowPythonError(mvErrorCode::mvIncompatibleParent, s_command,
			"Incompatible parent. Acceptable parents include: plot axis", this);

		assert(false);
		return false;
	}

	void mvAreaSeries::draw(ImDrawList* drawlist, float x, float y)
	{
		ScopedID id(m_uuid);

		static const std::vector<double>* xptr;
		static const std::vector<double>* yptr;

		xptr = &(*m_value.get())[0];
		yptr = &(*m_value.get())[1];

		ImPlot::PlotLine(m_label.c_str(), xptr->data(), yptr->data(), (int)xptr->size());

		ImPlot::PushPlotClipRect();
		auto item = ImPlot::RegisterOrGetItem(m_label.c_str());
		drawPolygon();
		ImPlot::PopPlotClipRect();

		// Begin a popup for a legend entry.
		if (ImPlot::BeginLegendPopup(m_label.c_str(), 1))
		{
			for (auto& childset : m_children)
			{
				for (auto& item : childset)
				{
					// skip item if it's not shown
					if (!item->m_show)
						continue;
					item->draw(drawlist, ImPlot::GetPlotPos().x, ImPlot::GetPlotPos().y);
					item->getState().update();
				}
			}
			ImPlot::EndLegendPopup();
		}

	}

	void mvAreaSeries::handleSpecificRequiredArgs(PyObject* dict)
	{
		if (!mvApp::GetApp()->getParsers()[s_command].verifyRequiredArguments(dict))
			return;

		for (int i = 0; i < PyTuple_Size(dict); i++)
		{
			PyObject* item = PyTuple_GetItem(dict, i);
			switch (i)
			{
			case 0:
				(*m_value)[0] = ToDoubleVect(item);
				break;

			case 1:
				(*m_value)[1] = ToDoubleVect(item);
				break;

			default:
				break;
			}
		}

		resetMaxMins();
		calculateMaxMins();
	}

	void mvAreaSeries::handleSpecificKeywordArgs(PyObject* dict)
	{
		if (dict == nullptr)
			return;

		if (PyObject* item = PyDict_GetItemString(dict, "contribute_to_bounds")) m_contributeToBounds = ToBool(item);
		if (PyObject* item = PyDict_GetItemString(dict, "fill")) m_fill = ToColor(item);

		bool valueChanged = false;
		if (PyObject* item = PyDict_GetItemString(dict, "x")) { valueChanged = true; (*m_value)[0] = ToDoubleVect(item); }
		if (PyObject* item = PyDict_GetItemString(dict, "y")) { valueChanged = true; (*m_value)[1] = ToDoubleVect(item); }

		if (valueChanged)
		{
			resetMaxMins();
			calculateMaxMins();
		}

	}

	void mvAreaSeries::getSpecificConfiguration(PyObject* dict)
	{
		if (dict == nullptr)
			return;

		PyDict_SetItemString(dict, "contribute_to_bounds", ToPyBool(m_contributeToBounds));
		PyDict_SetItemString(dict, "fill", ToPyColor(m_fill));

	}

}
