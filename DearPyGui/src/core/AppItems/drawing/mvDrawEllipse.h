#pragma once

#include "mvAppItem.h"
#include "mvItemRegistry.h"

namespace Marvel {

	MV_REGISTER_WIDGET(mvDrawEllipse, MV_ITEM_DESC_DEFAULT, StorageValueTypes::None, 2);
	class mvDrawEllipse : public mvAppItem
	{
	public:

		static void InsertParser(std::map<std::string, mvPythonParser>* parsers);

		MV_APPLY_WIDGET_REGISTRATION(mvAppItemType::mvDrawEllipse, draw_ellipse)

		MV_START_COMMANDS
		MV_END_COMMANDS

		MV_START_CONSTANTS
		MV_END_CONSTANTS

	public:

		mvDrawEllipse(mvUUID uuid);

		void draw(ImDrawList* drawlist, float x, float y) override;
		bool isParentCompatible(mvAppItemType type) override;

		void handleSpecificRequiredArgs(PyObject* args) override;
		void handleSpecificKeywordArgs(PyObject* dict) override;
		void getSpecificConfiguration(PyObject* dict) override;


	private:

		mvVec2  m_pmin = { 0.0f, 0.0f };
		mvVec2  m_pmax = { 1.0f, 1.0f };
		int     m_segments = 0;
		mvColor m_color;
		mvColor m_fill;
		float   m_thickness = 1.0f;
		std::vector<mvVec2> m_points;
		bool m_dirty = true;

	};

}
