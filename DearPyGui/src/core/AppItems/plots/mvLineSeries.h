#pragma once

#include "mvPlot.h"

namespace Marvel {

	MV_REGISTER_WIDGET(mvLineSeries, MV_ITEM_DESC_DEFAULT, StorageValueTypes::Series, 1);
	class mvLineSeries : public mvSeriesBase
	{
	public:

		static void InsertParser(std::map<std::string, mvPythonParser>* parsers);

		MV_APPLY_WIDGET_REGISTRATION(mvAppItemType::mvLineSeries, add_line_series)

		MV_CREATE_CONSTANT(mvThemeCol_Plot_Line, ImPlotCol_Line, 0L);
		MV_CREATE_CONSTANT(mvThemeCol_Plot_Line_MarkerOutline, ImPlotCol_MarkerOutline, 0L);
		MV_CREATE_CONSTANT(mvThemeCol_Plot_Line_MarkerFill, ImPlotCol_MarkerFill, 0L);

		MV_CREATE_CONSTANT(mvThemeStyle_Plot_Line_Weight, ImPlotStyleVar_LineWeight, 0L);
		MV_CREATE_CONSTANT(mvThemeStyle_Plot_Line_Marker, ImPlotStyleVar_Marker, 0L);
		MV_CREATE_CONSTANT(mvThemeStyle_Plot_Line_MarkerWeight, ImPlotStyleVar_MarkerWeight, 0L);
		MV_CREATE_CONSTANT(mvThemeStyle_Plot_Line_MarkerSize, ImPlotStyleVar_MarkerSize, 0L);

		MV_START_EXTRA_COMMANDS
		MV_END_EXTRA_COMMANDS

		MV_START_GENERAL_CONSTANTS
		MV_END_GENERAL_CONSTANTS

		MV_START_COLOR_CONSTANTS
		MV_ADD_CONSTANT(mvThemeCol_Plot_Line, mvColor(0, 0, 0, -255), mvColor(0, 0, 0, -255)),
		MV_ADD_CONSTANT(mvThemeCol_Plot_Line_MarkerOutline, mvColor(0, 0, 0, -255), mvColor(0, 0, 0, -255)),
		MV_ADD_CONSTANT(mvThemeCol_Plot_Line_MarkerFill, mvColor(0, 0, 0, -255), mvColor(0, 0, 0, -255)),
		MV_END_COLOR_CONSTANTS

		MV_START_STYLE_CONSTANTS
		MV_ADD_CONSTANT_F(mvThemeStyle_Plot_Line_Weight, 1.0f, 12),
		MV_ADD_CONSTANT_F(mvThemeStyle_Plot_Line_Marker, ImPlotMarker_None, 9),
		MV_ADD_CONSTANT_F(mvThemeStyle_Plot_Line_MarkerWeight, 1.0f, 12),
		MV_ADD_CONSTANT_F(mvThemeStyle_Plot_Line_MarkerSize, 4.0f, 12),
		MV_END_STYLE_CONSTANTS

	public:

		mvLineSeries(const std::string& name);

		void draw(ImDrawList* drawlist, float x, float y) override;

		void handleSpecificRequiredArgs(PyObject* args) override;
		void handleSpecificKeywordArgs(PyObject* dict) override;
		void getSpecificConfiguration(PyObject* dict) override;

	};

}
