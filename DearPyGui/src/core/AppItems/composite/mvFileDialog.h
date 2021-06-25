#pragma once

#include "mvTypeBases.h"
#include "mvApp.h"
#include "mvItemRegistry.h"

#pragma warning(push, 0) 
#include <ImGuiFileDialog.h>
#pragma warning(pop)

namespace Marvel {

	MV_REGISTER_WIDGET(mvFileDialog, MV_ITEM_DESC_ROOT | MV_ITEM_DESC_CONTAINER, StorageValueTypes::Bool, 1);
	class mvFileDialog : public mvBoolPtrBase
	{
	public:

		static void InsertParser(std::map<std::string, mvPythonParser>* parsers);

		MV_APPLY_WIDGET_REGISTRATION(mvAppItemType::mvFileDialog, add_file_dialog)

		MV_CREATE_COMMAND(get_file_dialog_info);

		MV_START_COMMANDS
			MV_ADD_COMMAND(get_file_dialog_info);
		MV_END_COMMANDS

		MV_START_CONSTANTS
		MV_END_CONSTANTS

	public:

		mvFileDialog(mvUUID uuid);

		void draw(ImDrawList* drawlist, float x, float y) override;
		void drawPanel();

		void setLabel(const std::string& value) override;
		void handleSpecificKeywordArgs(PyObject* dict) override;
		void getSpecificConfiguration(PyObject* dict) override;

		ImGuiFileDialog& getDialog();
		void             markDirty() { m_dirtySettings = true; }
		PyObject* getInfoDict();
		bool      getContinueValue() const { return *m_value; }

	private:

		ImGuiFileDialog m_instance;
		bool            m_dirtySettings = true;

		std::string m_filters;
		std::string m_defaultPath;
		std::string m_defaultFilename = ".";
		int         m_fileCount = 0;
		bool        m_modal = false;
		bool        m_directory = false;
	};

}