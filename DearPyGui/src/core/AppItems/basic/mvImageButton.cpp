#include "mvImageButton.h"
#include "mvTextureStorage.h"
#include "mvPythonExceptions.h"
#include "mvApp.h"
#include "mvGlobalIntepreterLock.h"

namespace Marvel {

	mvImageButton::mvImageButton(const std::string& name, std::string  default_value)
		: mvAppItem(name), m_value(std::move(default_value))
	{
		m_description.ignoreSizeUpdate = true;
		mvEventBus::Subscribe(this, mvEVT_DELETE_TEXTURE);
	}

	mvImageButton::~mvImageButton()
	{
		mvEventBus::Publish(mvEVT_CATEGORY_TEXTURE, mvEVT_DEC_TEXTURE, { CreateEventArgument("NAME", m_value) });
		mvEventBus::UnSubscribe(this);
	}

	bool mvImageButton::onEvent(mvEvent& event)
	{
		mvEventDispatcher dispatcher(event);
		dispatcher.dispatch(BIND_EVENT_METH(mvImageButton::onTextureDeleted), mvEVT_DELETE_TEXTURE);

		return event.handled;
	}

	bool mvImageButton::onTextureDeleted(mvEvent& event)
	{
		std::string name = GetEString(event, "NAME");
		
		if (name == m_value)
		{
			m_texture = nullptr;
			return true;
		}

		return false;
	}

	void mvImageButton::draw()
	{
		if (m_texture == nullptr && !m_value.empty())
		{
			mvApp::GetApp()->getTextureStorage().addTexture(m_value);
			mvTexture* texture = mvApp::GetApp()->getTextureStorage().getTexture(m_value);
			if (texture == nullptr)
			{
				PyErr_Format(PyExc_Exception,
					"Image %s could not be found for add_image. Check the path to the image "
					"you provided.", m_value.c_str());
				PyErr_Print();
				m_value = "";
				return;
			}
			if (m_width == 0) m_width = (int)((float)texture->width * (m_uv_max.x - m_uv_min.x));
			if (m_height == 0) m_height = (int)((float)texture->height * (m_uv_max.y - m_uv_min.y));

			m_texture = texture->texture;

		}

		if (m_dirty)
		{
			mvTexture* texture = mvApp::GetApp()->getTextureStorage().getTexture(m_value);
			if (texture)
			{
				m_width = (int)((float)texture->width * (m_uv_max.x - m_uv_min.x));
				m_height = (int)((float)texture->height * (m_uv_max.y - m_uv_min.y));
			}
			m_dirty = false;
		}

		if (m_texture)
		{
			if (ImGui::ImageButton(m_texture, ImVec2((float)m_width, (float)m_height),
				ImVec2(m_uv_min.x, m_uv_min.y), ImVec2(m_uv_max.x, m_uv_max.y), m_framePadding,
				m_backgroundColor.toVec4(), m_tintColor.toVec4()))
				mvCallbackRegistry::GetCallbackRegistry()->addCallback(m_callback, m_name, m_callbackData);

		}

	}

	void mvImageButton::setExtraConfigDict(PyObject* dict)
	{
		if (dict == nullptr)
			return;
		mvGlobalIntepreterLock gil;
		if (PyObject* item = PyDict_GetItemString(dict, "uv_min"))
		{
			m_uv_min = ToVec2(item);
			m_dirty = true;
		}
		if (PyObject* item = PyDict_GetItemString(dict, "uv_max"))
		{
			m_uv_max = ToVec2(item);
			m_dirty = true;
		}
		if (PyObject* item = PyDict_GetItemString(dict, "tint_color")) m_tintColor = ToColor(item);
		if (PyObject* item = PyDict_GetItemString(dict, "background_color")) m_backgroundColor = ToColor(item);
		if (PyObject* item = PyDict_GetItemString(dict, "frame_padding")) m_framePadding = ToInt(item);
	}

	void mvImageButton::getExtraConfigDict(PyObject* dict)
	{
		if (dict == nullptr)
			return;
		mvGlobalIntepreterLock gil;
		PyDict_SetItemString(dict, "uv_min", ToPyPair(m_uv_min.x, m_uv_min.y));
		PyDict_SetItemString(dict, "uv_max", ToPyPair(m_uv_max.x, m_uv_max.y));
		PyDict_SetItemString(dict, "tint_color", ToPyColor(m_tintColor));
		PyDict_SetItemString(dict, "background_color", ToPyColor(m_backgroundColor));
		PyDict_SetItemString(dict, "frame_padding", ToPyInt(m_framePadding));
	}
}