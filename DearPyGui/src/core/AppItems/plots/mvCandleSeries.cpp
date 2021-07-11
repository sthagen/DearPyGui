#include "mvCandleSeries.h"
#include "mvCore.h"
#include "mvApp.h"
#include "mvItemRegistry.h"
#include "mvPythonExceptions.h"
#include "AppItems/fonts/mvFont.h"
#include "AppItems/themes/mvTheme.h"
#include "AppItems/containers/mvDragPayload.h"

namespace Marvel {

    template <typename T>
    int BinarySearch(const T* arr, int l, int r, T x) {
        if (r >= l) {
            int mid = l + (r - l) / 2;
            if (arr[mid] == x)
                return mid;
            if (arr[mid] > x)
                return BinarySearch(arr, l, mid - 1, x);
            return BinarySearch(arr, mid + 1, r, x);
        }
        return -1;
    }

    static void PlotCandlestick(const char* label_id, const double* xs, const double* opens,
        const double* closes, const double* lows, const double* highs, int count,
        bool tooltip, float width_percent, ImVec4 bullCol, ImVec4 bearCol) {

        // get ImGui window DrawList
        ImDrawList* draw_list = ImPlot::GetPlotDrawList();
        // calc real value width
        float half_width = count > 1 ? (xs[1] - xs[0]) * width_percent : width_percent;

        // custom tool
        if (ImPlot::IsPlotHovered() && tooltip) {
            ImPlotPoint mouse = ImPlot::GetPlotMousePos();
            mouse.x = ImPlot::RoundTime(ImPlotTime::FromDouble(mouse.x), ImPlotTimeUnit_Day).ToDouble();
            float  tool_l = ImPlot::PlotToPixels(mouse.x - half_width * 1.5, mouse.y).x;
            float  tool_r = ImPlot::PlotToPixels(mouse.x + half_width * 1.5, mouse.y).x;
            float  tool_t = ImPlot::GetPlotPos().y;
            float  tool_b = tool_t + ImPlot::GetPlotSize().y;
            ImPlot::PushPlotClipRect();
            draw_list->AddRectFilled(ImVec2(tool_l, tool_t), ImVec2(tool_r, tool_b), IM_COL32(128, 128, 128, 64));
            ImPlot::PopPlotClipRect();
            // find mouse location index
            int idx = BinarySearch(xs, 0, count - 1, mouse.x);
            // render tool tip (won't be affected by plot clip rect)
            if (idx != -1) {
                ImGui::BeginTooltip();
                char buff[32];
                ImPlot::FormatDate(ImPlotTime::FromDouble(xs[idx]), buff, 32, ImPlotDateFmt_DayMoYr, ImPlot::GetStyle().UseISO8601);
                ImGui::Text("Day:   %s", buff);
                ImGui::Text("Open:  $%.2f", opens[idx]);
                ImGui::Text("Close: $%.2f", closes[idx]);
                ImGui::Text("Low:   $%.2f", lows[idx]);
                ImGui::Text("High:  $%.2f", highs[idx]);
                ImGui::EndTooltip();
            }
        }

        // begin plot item
        if (ImPlot::BeginItem(label_id)) {
            // override legend icon color
            ImPlot::GetCurrentItem()->Color = ImGui::ColorConvertFloat4ToU32({ 0.25f, 0.25f, 0.25f, 1.0f });
            // fit data if requested
            if (ImPlot::FitThisFrame()) {
                for (int i = 0; i < count; ++i) {
                    ImPlot::FitPoint(ImPlotPoint(xs[i], lows[i]));
                    ImPlot::FitPoint(ImPlotPoint(xs[i], highs[i]));
                }
            }
            // render data
            for (int i = 0; i < count; ++i) {
                ImVec2 open_pos = ImPlot::PlotToPixels(xs[i] - half_width, opens[i]);
                ImVec2 close_pos = ImPlot::PlotToPixels(xs[i] + half_width, closes[i]);
                ImVec2 low_pos = ImPlot::PlotToPixels(xs[i], lows[i]);
                ImVec2 high_pos = ImPlot::PlotToPixels(xs[i], highs[i]);
                ImU32 color = ImGui::GetColorU32(opens[i] > closes[i] ? bearCol : bullCol);
                draw_list->AddLine(low_pos, high_pos, color);
                draw_list->AddRectFilled(open_pos, close_pos, color);
            }

            // end plot item
            ImPlot::EndItem();
        }
    }

	void mvCandleSeries::InsertParser(std::map<std::string, mvPythonParser>* parsers)
	{

		mvPythonParser parser(mvPyDataType::UUID, "Adds a candle series to a plot.", { "Plotting", "Containers", "Widgets" });
		mvAppItem::AddCommonArgs(parser, (CommonParserArgs)(
			MV_PARSER_ARG_ID |
			MV_PARSER_ARG_PARENT |
			MV_PARSER_ARG_BEFORE |
			MV_PARSER_ARG_SOURCE |
			MV_PARSER_ARG_SHOW)
		);

		parser.addArg<mvPyDataType::DoubleList>("dates");
		parser.addArg<mvPyDataType::DoubleList>("opens");
		parser.addArg<mvPyDataType::DoubleList>("closes");
		parser.addArg<mvPyDataType::DoubleList>("lows");
		parser.addArg<mvPyDataType::DoubleList>("highs");

		parser.addArg<mvPyDataType::IntList>("bull_color", mvArgType::KEYWORD_ARG, "(0, 255, 113, 255)");
		parser.addArg<mvPyDataType::IntList>("bear_color", mvArgType::KEYWORD_ARG, "(218, 13, 79, 255)");

		parser.addArg<mvPyDataType::Integer>("weight", mvArgType::KEYWORD_ARG, "0.25");

		parser.addArg<mvPyDataType::Bool>("tooltip", mvArgType::KEYWORD_ARG, "True");

		parser.finalize();

		parsers->insert({ s_command, parser });
	}

	mvCandleSeries::mvCandleSeries(mvUUID uuid)
		: mvSeriesBase(uuid)
	{
	}

	bool mvCandleSeries::isParentCompatible(mvAppItemType type)
	{
		if (type == mvAppItemType::mvPlotAxis) return true;

		mvThrowPythonError(mvErrorCode::mvIncompatibleParent, s_command,
			"Incompatible parent. Acceptable parents include: plot axis", this);

		assert(false);
		return false;
	}

	void mvCandleSeries::draw(ImDrawList* drawlist, float x, float y)
	{
		//-----------------------------------------------------------------------------
		// pre draw
		//-----------------------------------------------------------------------------
		if (!m_show)
			return;

		// push font if a font object is attached
		if (m_font)
		{
			ImFont* fontptr = static_cast<mvFont*>(m_font.get())->getFontPtr();
			ImGui::PushFont(fontptr);
		}

		// handle enabled theming
		if (m_enabled)
		{
			// push class theme (if it exists)
			if (auto classTheme = getClassTheme())
				static_cast<mvTheme*>(classTheme.get())->draw(nullptr, 0.0f, 0.0f);

			// push item theme (if it exists)
			if (m_theme)
				static_cast<mvTheme*>(m_theme.get())->draw(nullptr, 0.0f, 0.0f);
		}

		//-----------------------------------------------------------------------------
		// draw
		//-----------------------------------------------------------------------------
		{

			static const std::vector<double>* datesptr;
			static const std::vector<double>* openptr;
			static const std::vector<double>* closeptr;
			static const std::vector<double>* lowptr;
			static const std::vector<double>* highptr;

			datesptr = &(*m_value.get())[0];
			openptr = &(*m_value.get())[1];
			closeptr = &(*m_value.get())[2];
			lowptr = &(*m_value.get())[3];
			highptr = &(*m_value.get())[4];

			PlotCandlestick(m_label.c_str(), datesptr->data(), openptr->data(), closeptr->data(),
				lowptr->data(), highptr->data(), (int)datesptr->size(), m_tooltip, m_weight, m_bullColor,
				m_bearColor);

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


		//-----------------------------------------------------------------------------
		// update state
		//   * only update if applicable
		//-----------------------------------------------------------------------------


		//-----------------------------------------------------------------------------
		// post draw
		//-----------------------------------------------------------------------------

		// pop font off stack
		if (m_font)
			ImGui::PopFont();

		// handle popping styles
		if (m_enabled)
		{
			if (auto classTheme = getClassTheme())
				static_cast<mvTheme*>(classTheme.get())->customAction();

			if (m_theme)
				static_cast<mvTheme*>(m_theme.get())->customAction();
		}

	}

	void mvCandleSeries::handleSpecificRequiredArgs(PyObject* dict)
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

			case 2:
				(*m_value)[2] = ToDoubleVect(item);
				break;

			case 3:
				(*m_value)[3] = ToDoubleVect(item);
				break;

			case 4:
				(*m_value)[4] = ToDoubleVect(item);
				break;

			default:
				break;
			}
		}
	}

	void mvCandleSeries::handleSpecificKeywordArgs(PyObject* dict)
	{
		if (dict == nullptr)
			return;

		if (PyObject* item = PyDict_GetItemString(dict, "bull_color")) m_bullColor = ToColor(item);
		if (PyObject* item = PyDict_GetItemString(dict, "bear_color")) m_bearColor = ToColor(item);
		if (PyObject* item = PyDict_GetItemString(dict, "weight")) m_weight = ToFloat(item);
		if (PyObject* item = PyDict_GetItemString(dict, "tooltip")) m_tooltip = ToBool(item);

		if (PyObject* item = PyDict_GetItemString(dict, "dates")) { (*m_value)[0] = ToDoubleVect(item); }
		if (PyObject* item = PyDict_GetItemString(dict, "opens")) { (*m_value)[1] = ToDoubleVect(item); }
		if (PyObject* item = PyDict_GetItemString(dict, "closes")) { (*m_value)[2] = ToDoubleVect(item); }
		if (PyObject* item = PyDict_GetItemString(dict, "lows")) { (*m_value)[3] = ToDoubleVect(item); }
		if (PyObject* item = PyDict_GetItemString(dict, "highs")) { (*m_value)[4] = ToDoubleVect(item); }

	}

	void mvCandleSeries::getSpecificConfiguration(PyObject* dict)
	{
		if (dict == nullptr)
			return;

		PyDict_SetItemString(dict, "bull_color", ToPyColor(m_bullColor));
		PyDict_SetItemString(dict, "bear_color", ToPyColor(m_bearColor));
		PyDict_SetItemString(dict, "weight", ToPyFloat(m_weight));
		PyDict_SetItemString(dict, "tooltip", ToPyBool(m_tooltip));
	}

}