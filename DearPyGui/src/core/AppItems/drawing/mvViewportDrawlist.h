#pragma once

#include "mvTypeBases.h"

namespace Marvel {

	MV_REGISTER_WIDGET(mvViewportDrawlist, MV_ITEM_DESC_CONTAINER | MV_ITEM_DESC_ROOT, StorageValueTypes::None, 1);
	class mvViewportDrawlist : public mvAppItem
	{

	public:

		static void InsertParser(std::map<std::string, mvPythonParser>* parsers);

		MV_APPLY_WIDGET_REGISTRATION(mvAppItemType::mvViewportDrawlist, add_viewport_drawlist)

		MV_START_COMMANDS
		MV_END_COMMANDS

		MV_START_CONSTANTS
		MV_END_CONSTANTS

		mvViewportDrawlist(mvUUID uuid);

		void draw(ImDrawList* drawlist, float x, float y) override;
		bool canChildBeAdded(mvAppItemType type) override;
		void handleSpecificKeywordArgs(PyObject* dict) override;
		void getSpecificConfiguration(PyObject* dict) override;

	private:

		bool m_front = true;

	};
}