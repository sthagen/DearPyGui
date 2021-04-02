#pragma once

#include "mvTypeBases.h"
#include <vector>

namespace Marvel {

	MV_REGISTER_WIDGET(mvTableNextColumn);
	class mvTableNextColumn : public mvAppItem
	{

	public:

		static void InsertParser(std::map<std::string, mvPythonParser>* parsers);

	public:

		MV_APPITEM_TYPE(mvAppItemType::mvTableNextColumn, add_table_next_column)

		MV_START_EXTRA_COMMANDS
		MV_END_EXTRA_COMMANDS

		MV_START_GENERAL_CONSTANTS
		MV_END_GENERAL_CONSTANTS

		MV_START_COLOR_CONSTANTS
		MV_END_COLOR_CONSTANTS

		MV_START_STYLE_CONSTANTS
		MV_END_STYLE_CONSTANTS

			mvTableNextColumn(const std::string& name);

		bool isParentCompatible(mvAppItemType type) override;

		void draw(ImDrawList* drawlist, float x, float y) override;

	};

}
