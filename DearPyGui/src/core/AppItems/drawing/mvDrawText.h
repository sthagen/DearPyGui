#pragma once

#include "mvAppItem.h"
#include "mvItemRegistry.h"

namespace Marvel {

	MV_REGISTER_WIDGET(mvDrawText, MV_ITEM_DESC_DEFAULT, StorageValueTypes::None, 2);
	class mvDrawText : public mvAppItem
	{

	public:

		static void InsertParser(std::map<std::string, mvPythonParser>* parsers);

		MV_APPLY_WIDGET_REGISTRATION(mvAppItemType::mvDrawText, draw_text)

		MV_START_COMMANDS
		MV_END_COMMANDS

		MV_START_CONSTANTS
		MV_END_CONSTANTS

	public:

		mvDrawText(mvUUID uuid);

		void draw(ImDrawList* drawlist, float x, float y) override;
		bool isParentCompatible(mvAppItemType type) override;

		void handleSpecificRequiredArgs(PyObject* args) override;
		void handleSpecificKeywordArgs(PyObject* dict) override;
		void getSpecificConfiguration(PyObject* dict) override;


	private:

		mvVec2      m_pos = { 0.0f, 0.0f };
		std::string m_text;
		mvColor     m_color;
		int         m_size = 10;

	};

}
