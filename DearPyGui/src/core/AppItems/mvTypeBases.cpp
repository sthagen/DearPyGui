#include "mvTypeBases.h"
#include <utility>
#include "mvApp.h"
#include "mvUtilities.h"
#include "mvAppLog.h"
#include "mvValueStorage.h"

namespace Marvel {

	mvIntPtrBase::mvIntPtrBase(const std::string& name, int default_value, const std::string& dataSource)
		: 
		mvAppItem(name)
	{
		if (dataSource.empty())
			m_value = mvApp::GetApp()->getValueStorage().AddIntValue(name, default_value);
		else
			m_value = mvApp::GetApp()->getValueStorage().AddIntValue(dataSource, default_value);

		m_core_config.source = dataSource;
	}

	mvIntPtrBase::~mvIntPtrBase()
	{
		if (m_core_config.source.empty())
			mvApp::GetApp()->getValueStorage().DecrementRef(m_core_config.name);
		else
			mvApp::GetApp()->getValueStorage().DecrementRef(m_core_config.source);
	}

	void mvIntPtrBase::setDataSource(const std::string& dataSource)
	{
		if (dataSource == m_core_config.source) return;
		mvApp::GetApp()->getValueStorage().DecrementRef(m_core_config.source);
		m_value = mvApp::GetApp()->getValueStorage().AddIntValue(dataSource);
		m_core_config.source = dataSource;
	}

	mvInt2PtrBase::mvInt2PtrBase(const std::string& name, int* default_value, const std::string& dataSource)
		: 
		mvAppItem(name)
	{
		if (dataSource.empty())
			m_value = mvApp::GetApp()->getValueStorage().AddInt2Value(name, { default_value[0], default_value[1] });
		else
			m_value = mvApp::GetApp()->getValueStorage().AddInt2Value(dataSource, { default_value[0], default_value[1] });

		m_core_config.source = dataSource;
	}

	mvInt2PtrBase::~mvInt2PtrBase()
	{
		if (m_core_config.source.empty())
			mvApp::GetApp()->getValueStorage().DecrementRef(m_core_config.name);
		else
			mvApp::GetApp()->getValueStorage().DecrementRef(m_core_config.source);
	}

	void mvInt2PtrBase::setDataSource(const std::string& dataSource)
	{
		if (dataSource == m_core_config.source) return;
		mvApp::GetApp()->getValueStorage().DecrementRef(m_core_config.source);
		m_value = mvApp::GetApp()->getValueStorage().AddInt2Value(dataSource);
		m_core_config.source = dataSource;
	}

	mvInt3PtrBase::mvInt3PtrBase(const std::string& name, int* default_value, const std::string& dataSource)
		: 
		mvAppItem(name)
	{
		if (dataSource.empty())
			m_value = mvApp::GetApp()->getValueStorage().AddInt3Value(name, { default_value[0], default_value[1], default_value[2] });
		else
			m_value = mvApp::GetApp()->getValueStorage().AddInt3Value(dataSource, { default_value[0], default_value[1], default_value[2] });

		m_core_config.source = dataSource;
	}

	mvInt3PtrBase::~mvInt3PtrBase()
	{
		if (m_core_config.source.empty())
			mvApp::GetApp()->getValueStorage().DecrementRef(m_core_config.name);
		else
			mvApp::GetApp()->getValueStorage().DecrementRef(m_core_config.source);
	}

	void mvInt3PtrBase::setDataSource(const std::string& dataSource)
	{
		if (dataSource == m_core_config.source) return;
		mvApp::GetApp()->getValueStorage().DecrementRef(m_core_config.source);
		m_value = mvApp::GetApp()->getValueStorage().AddInt3Value(dataSource);
		m_core_config.source = dataSource;
	}

	mvInt4PtrBase::mvInt4PtrBase(const std::string& name, int* default_value, const std::string& dataSource)
		: mvAppItem(name)
	{
		if (dataSource.empty())
			m_value = mvApp::GetApp()->getValueStorage().AddInt4Value(name, { default_value[0], default_value[1], default_value[2], default_value[3] });
		else
			m_value = mvApp::GetApp()->getValueStorage().AddInt4Value(dataSource, { default_value[0], default_value[1], default_value[2], default_value[3] });

		m_core_config.source = dataSource;
	}

	mvInt4PtrBase::~mvInt4PtrBase()
	{
		if (m_core_config.source.empty())
			mvApp::GetApp()->getValueStorage().DecrementRef(m_core_config.name);
		else
			mvApp::GetApp()->getValueStorage().DecrementRef(m_core_config.source);
	}

	void mvInt4PtrBase::setDataSource(const std::string& dataSource)
	{
		if (dataSource == m_core_config.source) return;
		mvApp::GetApp()->getValueStorage().DecrementRef(m_core_config.source);
		m_value = mvApp::GetApp()->getValueStorage().AddInt4Value(dataSource);
		m_core_config.source = dataSource;
	}

	mvFloatPtrBase::mvFloatPtrBase(const std::string& name, float default_value, const std::string& dataSource)
		: mvAppItem(name)
	{
		if (dataSource.empty())
			m_value = mvApp::GetApp()->getValueStorage().AddFloatValue(name, default_value);
		else
			m_value = mvApp::GetApp()->getValueStorage().AddFloatValue(dataSource, default_value);

		m_core_config.source = dataSource;
	}

	mvFloatPtrBase::~mvFloatPtrBase()
	{
		if (m_core_config.source.empty())
			mvApp::GetApp()->getValueStorage().DecrementRef(m_core_config.name);
		else
			mvApp::GetApp()->getValueStorage().DecrementRef(m_core_config.source);
	}

	void mvFloatPtrBase::setDataSource(const std::string& dataSource)
	{
		if (dataSource == m_core_config.source) return;
		mvApp::GetApp()->getValueStorage().DecrementRef(m_core_config.source);
		m_value = mvApp::GetApp()->getValueStorage().AddFloatValue(dataSource);
		m_core_config.source = dataSource;
	}

	mvFloat2PtrBase::mvFloat2PtrBase(const std::string& name, float* default_value, const std::string& dataSource)
		: mvAppItem(name)
	{
		if (dataSource.empty())
			m_value = mvApp::GetApp()->getValueStorage().AddFloat2Value(name, { default_value[0], default_value[1] });
		else
			m_value = mvApp::GetApp()->getValueStorage().AddFloat2Value(dataSource, { default_value[0], default_value[1] });

		m_core_config.source = dataSource;
	}

	mvFloat2PtrBase::~mvFloat2PtrBase()
	{
		if (m_core_config.source.empty())
			mvApp::GetApp()->getValueStorage().DecrementRef(m_core_config.name);
		else
			mvApp::GetApp()->getValueStorage().DecrementRef(m_core_config.source);
	}

	void mvFloat2PtrBase::setDataSource(const std::string& dataSource)
	{
		if (dataSource == m_core_config.source) return;
		mvApp::GetApp()->getValueStorage().DecrementRef(m_core_config.source);
		m_value = mvApp::GetApp()->getValueStorage().AddFloat2Value(dataSource);
		m_core_config.source = dataSource;
	}

	mvFloat3PtrBase::mvFloat3PtrBase(const std::string& name, float* default_value, const std::string& dataSource)
		: mvAppItem(name)
	{
		if (dataSource.empty())
			m_value = mvApp::GetApp()->getValueStorage().AddFloat3Value(name, { default_value[0], default_value[1], default_value[2] });
		else
			m_value = mvApp::GetApp()->getValueStorage().AddFloat3Value(dataSource, { default_value[0], default_value[1], default_value[2] });

		m_core_config.source = dataSource;
	}

	mvFloat3PtrBase::~mvFloat3PtrBase()
	{
		if (m_core_config.source.empty())
			mvApp::GetApp()->getValueStorage().DecrementRef(m_core_config.name);
		else
			mvApp::GetApp()->getValueStorage().DecrementRef(m_core_config.source);
	}

	void mvFloat3PtrBase::setDataSource(const std::string& dataSource)
	{
		if (dataSource == m_core_config.source) return;
		mvApp::GetApp()->getValueStorage().DecrementRef(m_core_config.source);
		m_value = mvApp::GetApp()->getValueStorage().AddFloat3Value(dataSource);
		m_core_config.source = dataSource;
	}

	mvFloat4PtrBase::mvFloat4PtrBase(const std::string& name, float* default_value, const std::string& dataSource)
		: mvAppItem(name)
	{
		if (dataSource.empty())
			m_value = mvApp::GetApp()->getValueStorage().AddFloat4Value(name, { default_value[0], default_value[1], default_value[2], default_value[3] });
		else
			m_value = mvApp::GetApp()->getValueStorage().AddFloat4Value(dataSource, { default_value[0], default_value[1], default_value[2], default_value[3] });

		m_core_config.source = dataSource;
	}

	mvFloat4PtrBase::~mvFloat4PtrBase()
	{
		if (m_core_config.source.empty())
			mvApp::GetApp()->getValueStorage().DecrementRef(m_core_config.name);
		else
			mvApp::GetApp()->getValueStorage().DecrementRef(m_core_config.source);
	}

	void mvFloat4PtrBase::setDataSource(const std::string& dataSource)
	{
		if (dataSource == m_core_config.source) return;
		mvApp::GetApp()->getValueStorage().DecrementRef(m_core_config.source);
		m_value = mvApp::GetApp()->getValueStorage().AddFloat4Value(dataSource);
		m_core_config.source = dataSource;
	}

	mvColorPtrBase::mvColorPtrBase(const std::string& name, float* default_value, const std::string& dataSource)
		: mvAppItem(name)
	{
		if (dataSource.empty())
			m_value = mvApp::GetApp()->getValueStorage().AddColorValue(name, { default_value[0], default_value[1], default_value[2], default_value[3] });
		else
			m_value = mvApp::GetApp()->getValueStorage().AddColorValue(dataSource, { default_value[0], default_value[1], default_value[2], default_value[3] });

		m_core_config.source = dataSource;
	}

	mvColorPtrBase::~mvColorPtrBase()
	{
		if (m_core_config.source.empty())
			mvApp::GetApp()->getValueStorage().DecrementRef(m_core_config.name);
		else
			mvApp::GetApp()->getValueStorage().DecrementRef(m_core_config.source);
	}

	void mvColorPtrBase::setDataSource(const std::string& dataSource)
	{
		if (dataSource == m_core_config.source) return;
		mvApp::GetApp()->getValueStorage().DecrementRef(m_core_config.source);
		m_value = mvApp::GetApp()->getValueStorage().AddFloat4Value(dataSource);
		m_core_config.source = dataSource;
	}

	mvBoolPtrBase::mvBoolPtrBase(const std::string& name, bool default_value, const std::string& dataSource)
		: mvAppItem(name)
	{
		if (dataSource.empty())
			m_value = mvApp::GetApp()->getValueStorage().AddBoolValue(name, default_value);
		else
			m_value = mvApp::GetApp()->getValueStorage().AddBoolValue(dataSource, default_value);

		m_core_config.source = dataSource;

	}

	mvBoolPtrBase::~mvBoolPtrBase()
	{
		if (m_core_config.source.empty())
			mvApp::GetApp()->getValueStorage().DecrementRef(m_core_config.name);
		else
			mvApp::GetApp()->getValueStorage().DecrementRef(m_core_config.source);
	}

	void mvBoolPtrBase::setDataSource(const std::string& dataSource)
	{
		if (dataSource == m_core_config.source) return;
		mvApp::GetApp()->getValueStorage().DecrementRef(m_core_config.source);
		m_value = mvApp::GetApp()->getValueStorage().AddBoolValue(dataSource);
		m_core_config.source = dataSource;
	}

	mvStringPtrBase::mvStringPtrBase(const std::string& name, const std::string& default_value, const std::string& dataSource)
		: mvAppItem(name)
	{
		if (dataSource.empty())
			m_value = mvApp::GetApp()->getValueStorage().AddStringValue(name, default_value);
		else
			m_value = mvApp::GetApp()->getValueStorage().AddStringValue(dataSource, default_value);

		m_core_config.source = dataSource;
	}

	mvStringPtrBase::~mvStringPtrBase()
	{
		if (m_core_config.source.empty())
			mvApp::GetApp()->getValueStorage().DecrementRef(m_core_config.name);
		else
			mvApp::GetApp()->getValueStorage().DecrementRef(m_core_config.source);
	}

	void mvStringPtrBase::setDataSource(const std::string& dataSource)
	{
		if (dataSource == m_core_config.source) return;
		mvApp::GetApp()->getValueStorage().DecrementRef(m_core_config.source);
		m_value = mvApp::GetApp()->getValueStorage().AddStringValue(dataSource);
		m_core_config.source = dataSource;
	}

	mvTimePtrBase::mvTimePtrBase(const std::string& name, const tm& default_value, const std::string& dataSource)
		: mvAppItem(name)
	{
		if (dataSource.empty())
		{
			m_value = mvApp::GetApp()->getValueStorage().AddTimeValue(name, default_value);
			m_imvalue = mvApp::GetApp()->getValueStorage().GetImTimeValue(name);
		}
		else
		{
			m_value = mvApp::GetApp()->getValueStorage().AddTimeValue(dataSource, default_value);
			m_imvalue = mvApp::GetApp()->getValueStorage().GetImTimeValue(dataSource);
		}

		m_core_config.source = dataSource;
	}

	mvTimePtrBase::~mvTimePtrBase()
	{
		if (m_core_config.source.empty())
			mvApp::GetApp()->getValueStorage().DecrementRef(m_core_config.name);
		else
			mvApp::GetApp()->getValueStorage().DecrementRef(m_core_config.source);
	}

	mvFloatVectPtrBase::mvFloatVectPtrBase(const std::string& name, const std::vector<float>& default_value, const std::string& dataSource)
		: mvAppItem(name)
	{
		if (dataSource.empty())
			m_value = mvApp::GetApp()->getValueStorage().AddFloatVectorValue(name, default_value);
		else
			m_value = mvApp::GetApp()->getValueStorage().AddFloatVectorValue(dataSource, default_value);

		m_core_config.source = dataSource;
	}

	mvFloatVectPtrBase::~mvFloatVectPtrBase()
	{
		if (m_core_config.source.empty())
			mvApp::GetApp()->getValueStorage().DecrementRef(m_core_config.name);
		else
			mvApp::GetApp()->getValueStorage().DecrementRef(m_core_config.source);
	}

	void mvFloatVectPtrBase::setDataSource(const std::string& dataSource)
	{
		if (dataSource == m_core_config.source) return;
		mvApp::GetApp()->getValueStorage().DecrementRef(m_core_config.source);
		m_value = mvApp::GetApp()->getValueStorage().AddFloatVectorValue(dataSource);
		m_core_config.source = dataSource;
	}

	mvBaseWindowAppitem::mvBaseWindowAppitem(const std::string& name)
		: 
		mvAppItem(name)
	{
		m_description.root = true;
	}

	void mvBaseWindowAppitem::addFlag(ImGuiWindowFlags flag) 
	{ 
		m_windowflags |= flag; 
	}

	void mvBaseWindowAppitem::removeFlag(ImGuiWindowFlags flag) 
	{ 
		m_windowflags &= ~flag; 
	}

	void mvBaseWindowAppitem::setWindowPos(float x, float y)
	{
		m_xpos = (int)x;
		m_ypos = (int)y;
		m_dirty_pos = true;
	}

	void mvBaseWindowAppitem::setWidth(int width)
	{ 
		m_core_config.width = width;
		m_dirty_size = true; 
	}

	void mvBaseWindowAppitem::setHeight(int height)
	{
		m_core_config.height = height;
		m_dirty_size = true; 
	}

	mvVec2 mvBaseWindowAppitem::getWindowPos() const
	{
		return { (float)m_xpos, (float)m_ypos };
	}

	bool mvBaseWindowAppitem::prerender()
	{

		if (m_dirty_size)
		{
			ImGui::SetNextWindowSize(ImVec2((float)m_core_config.width, (float)m_core_config.height));
			m_dirty_size = false;
		}

		if (m_dirty_pos)
		{
			ImGui::SetNextWindowPos(ImVec2((float)m_xpos, (float)m_ypos));
			m_dirty_pos = false;
		}

		if (!m_core_config.show)
			return false;

		if (!ImGui::Begin(m_label.c_str(), &m_core_config.show, m_windowflags))
		{
			ImGui::End();
			return false;
		}

		return true;
	}

	void mvBaseWindowAppitem::setExtraConfigDict(PyObject* dict)
	{
		if (dict == nullptr)
			return;
		 
		if (PyObject* item = PyDict_GetItemString(dict, "x_pos")) setWindowPos((float)ToInt(item), (float)m_ypos);
		if (PyObject* item = PyDict_GetItemString(dict, "y_pos")) setWindowPos((float)m_xpos, (float)ToInt(item));

		// helper for bit flipping
		auto flagop = [dict](const char* keyword, int flag, int& flags)
		{
			if (PyObject* item = PyDict_GetItemString(dict, keyword)) ToBool(item) ? flags |= flag : flags &= ~flag;
		};

		// window flags
		flagop("autosize", ImGuiWindowFlags_AlwaysAutoResize, m_windowflags);
		flagop("no_move", ImGuiWindowFlags_NoMove, m_windowflags);
		flagop("no_resize", ImGuiWindowFlags_NoResize, m_windowflags);
		flagop("no_title_bar", ImGuiWindowFlags_NoTitleBar, m_windowflags);
		flagop("no_scrollbar", ImGuiWindowFlags_NoScrollbar, m_windowflags);
		flagop("no_collapse", ImGuiWindowFlags_NoCollapse, m_windowflags);
		flagop("horizontal_scrollbar", ImGuiWindowFlags_HorizontalScrollbar, m_windowflags);
		flagop("no_focus_on_appearing", ImGuiWindowFlags_NoFocusOnAppearing, m_windowflags);
		flagop("no_bring_to_front_on_focus", ImGuiWindowFlags_NoBringToFrontOnFocus, m_windowflags);
		flagop("menubar", ImGuiWindowFlags_MenuBar, m_windowflags);
		flagop("no_background", ImGuiWindowFlags_NoBackground, m_windowflags);

	}

	void mvBaseWindowAppitem::getExtraConfigDict(PyObject* dict)
	{
		if (dict == nullptr)
			return;
		 
		PyDict_SetItemString(dict, "x_pos", ToPyInt(m_xpos));
		PyDict_SetItemString(dict, "y_pos", ToPyInt(m_ypos));

		// helper to check and set bit
		auto checkbitset = [dict](const char* keyword, int flag, const int& flags)
		{
			PyDict_SetItemString(dict, keyword, ToPyBool(flags & flag));
		};

		// window flags
		checkbitset("autosize", ImGuiWindowFlags_AlwaysAutoResize, m_windowflags);
		checkbitset("no_resize", ImGuiWindowFlags_NoResize, m_windowflags);
		checkbitset("no_title_bar", ImGuiWindowFlags_NoTitleBar, m_windowflags);
		checkbitset("no_move", ImGuiWindowFlags_NoMove, m_windowflags);
		checkbitset("no_scrollbar", ImGuiWindowFlags_NoScrollbar, m_windowflags);
		checkbitset("no_collapse", ImGuiWindowFlags_NoCollapse, m_windowflags);
		checkbitset("horizontal_scrollbar", ImGuiWindowFlags_HorizontalScrollbar, m_windowflags);
		checkbitset("no_focus_on_appearing", ImGuiWindowFlags_NoFocusOnAppearing, m_windowflags);
		checkbitset("no_bring_to_front_on_focus", ImGuiWindowFlags_NoBringToFrontOnFocus, m_windowflags);
		checkbitset("menubar", ImGuiWindowFlags_MenuBar, m_windowflags);
		checkbitset("no_background", ImGuiWindowFlags_NoBackground, m_windowflags);
	}

}