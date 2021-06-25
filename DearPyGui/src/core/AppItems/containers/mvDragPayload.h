#pragma once

#include "mvTypeBases.h"
#include "cpp.hint"

namespace Marvel {

	MV_REGISTER_WIDGET(mvDragPayload, MV_ITEM_DESC_CONTAINER | MV_ITEM_DESC_HANDLER, StorageValueTypes::None, 4);
	class mvDragPayload : public mvAppItem
	{

	public:

		static void InsertParser(std::map<std::string, mvPythonParser>* parsers);

		MV_APPLY_WIDGET_REGISTRATION(mvAppItemType::mvDragPayload, add_drag_payload)

		MV_START_COMMANDS
		MV_END_COMMANDS

		MV_START_CONSTANTS
		MV_END_CONSTANTS

	public:

		mvDragPayload(mvUUID uuid);

		void draw(ImDrawList* drawlist, float x, float y) override;
		void handleSpecificKeywordArgs(PyObject* dict) override;
		void getSpecificConfiguration(PyObject* dict) override;
		PyObject* getDragData() const { return m_dragData; }

	private:

		std::string m_payloadType = "$$DPG_PAYLOAD";
		PyObject*   m_dragData = nullptr;

	};

}