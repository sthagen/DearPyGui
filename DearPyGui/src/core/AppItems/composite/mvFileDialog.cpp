#include "mvFileDialog.h"
#include "mvItemRegistry.h"

namespace Marvel {

	void mvFileDialog::InsertParser(std::map<std::string, mvPythonParser>* parsers)
	{
		parsers->insert({ "open_file_dialog", mvPythonParser({
			{mvPythonDataType::Optional},
			{mvPythonDataType::Callable, "callback", "function to call on completion", "None"},
			{mvPythonDataType::String, "extensions", "filters items with extensions i.e '.*, .py'", "''"},
		}, "Opens an 'open file' dialog.") });

		parsers->insert({ "select_directory_dialog", mvPythonParser({
			{mvPythonDataType::Optional},
			{mvPythonDataType::Callable, "callback", "function to call on completion", "None"},
		}, "Opens a select directory dialog.") });
	}

	mvFileDialog::mvFileDialog() : mvBaseWindowAppitem("filedialog")
	{
		m_description.deleteAllowed = false;
	}

	bool mvFileDialog::prerender2() 
	{ 
		return true; 
	}

	void mvFileDialog::setCallback(mvCallable callback)
	{ 
		m_callback2 = callback; 
	}

	void mvFileDialog::draw()
	{
		if (!prerender2())
			return;

		// display
		if (igfd::ImGuiFileDialog::Instance()->FileDialog("ChooseFileDlgKey", ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoSavedSettings, ImVec2(500, 600)))
		{

			// action if OK
			if (igfd::ImGuiFileDialog::Instance()->IsOk)
			{
				mvApp::GetApp()->getCallbackRegistry().submitCallback([&]() 
					{
						mvApp::GetApp()->getCallbackRegistry().runCallback(m_callback2, "File Dialog", ToPyList({ igfd::ImGuiFileDialog::Instance()->GetCurrentPath(), igfd::ImGuiFileDialog::Instance()->FileNameBuffer }));

						// action
						if (m_callback2)
							Py_XDECREF(m_callback2);
						m_callback2 = nullptr;
					});

			}
			// close
			igfd::ImGuiFileDialog::Instance()->CloseDialog("ChooseFileDlgKey");
			m_core_config.show = false;
		}
	}

#ifdef MV_CPP
#else
	PyObject* select_directory_dialog(PyObject* self, PyObject* args, PyObject* kwargs)
	{
		PyObject* callback = nullptr;

		if (!(mvApp::GetApp()->getParsers())["select_directory_dialog"].parse(args, kwargs, __FUNCTION__, &callback))
			return GetPyNone();

		if (callback)
			Py_XINCREF(callback);

		mvApp::GetApp()->getCallbackRegistry().submit([=]()
			{
				igfd::ImGuiFileDialog::Instance()->OpenModal("ChooseFileDlgKey", "Choose Directory", 0, ".");
				auto window = mvApp::GetApp()->getItemRegistry().getItem("filedialog");
				auto dialog = static_cast<mvFileDialog*>(window.get());
				dialog->setCallback(callback);
				window->show();
			});

		return GetPyNone();
	}

	PyObject* open_file_dialog(PyObject* self, PyObject* args, PyObject* kwargs)
	{
		PyObject* callback = nullptr;
		const char* extensions = ".*";

		if (!(mvApp::GetApp()->getParsers())["open_file_dialog"].parse(args, kwargs, __FUNCTION__,
			&callback, &extensions))
			return GetPyNone();

		if (callback)
			Py_XINCREF(callback);

		mvApp::GetApp()->getCallbackRegistry().submit([=]()
			{
				igfd::ImGuiFileDialog::Instance()->OpenModal("ChooseFileDlgKey", "Choose File", extensions, ".");
				auto window = mvApp::GetApp()->getItemRegistry().getItem("filedialog");
				auto dialog = static_cast<mvFileDialog*>(window.get());

				dialog->setCallback(callback);
				window->show();
			});

		return GetPyNone();
	}
#endif // 


}