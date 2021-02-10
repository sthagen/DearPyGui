#include "mvAppItem.h"
#include "mvApp.h"
#include "mvInput.h"
#include "mvItemRegistry.h"

namespace Marvel{

	mvAppItem::mvAppItem(const std::string& name)
	{
		m_core_config.name = name;
		m_label = name + "###" + name;
		m_core_config.label = name;
		m_state.setParent(this);
	}

	mvAppItem::mvAppItem(const mvAppItemConfig& config)
	{
		m_core_config.name = config.name;
		m_label = config.name + "###" + config.name;
		m_core_config.label = config.name;
		m_state.setParent(this);

		if (m_label != "__DearPyGuiDefault")
		{
			m_label = config.label + "###" + config.label;
			m_core_config.label = config.label;
		}
	}

	void mvAppItem::updateCoreConfig()
	{

		setLabel(m_core_config.label);
		setWidth(m_core_config.width);
		setHeight(m_core_config.height);
		setDataSource(m_core_config.source);
		setEnabled(m_core_config.enabled);
	}

	mvAppItemConfig& mvAppItem::getCoreConfig()
	{
		return m_core_config;
	}

	void mvAppItem::registerWindowFocusing()
	{
		if (ImGui::IsWindowFocused())
		{

			// update mouse
			ImVec2 mousePos = ImGui::GetMousePos();
			float x = mousePos.x - ImGui::GetWindowPos().x;
			float y = mousePos.y - ImGui::GetWindowPos().y;
			mvInput::setMousePosition(x, y);

			if (mvApp::GetApp()->getItemRegistry().getActiveWindow() != m_core_config.name)
				mvEventBus::Publish(mvEVT_CATEGORY_ITEM, mvEVT_ACTIVE_WINDOW, { CreateEventArgument("WINDOW", m_core_config.name) });

		}
	}

	void mvAppItem::setCallback(mvCallable callback)
	{ 
#ifndef MV_CPP
		if (callback == Py_None)
		{
			m_core_config.callback = nullptr;
			return;
		}
#endif // !MV_CPP

		m_core_config.callback = callback;
	}

	void mvAppItem::setCallbackData(mvCallableData data)
	{
		if (data == Py_None)
		{
			m_core_config.callback_data = nullptr;
			return;
		}
		m_core_config.callback_data = data;
	}

	void mvAppItem::resetState()
	{
		m_state.reset();
		for (auto& item : m_children)
			item->resetState();

	}

	bool  mvAppItem::moveChildUp(const std::string& name)
	{
		bool found = false;
		int index = 0;

		// check children
		for (size_t i = 0; i<m_children.size(); i++)
		{

			if (m_children[i]->m_core_config.name == name)
			{
				found = true;
				index = (int)i;
				break;
			}

			if (m_children[i]->getDescription().container)
			{
				found = m_children[i]->moveChildUp(name);
				if (found)
					return true;
			}

		}

		if (found)
		{
			if (index > 0)
			{
				auto upperitem = m_children[index - 1];
				auto loweritem = m_children[index];

				m_children[index] = upperitem;
				m_children[index-1] = loweritem;
			}

			return true;
		}

		return false;

	}

	bool  mvAppItem::moveChildDown(const std::string& name)
	{
		bool found = false;
		size_t index = 0;

		// check children
		for (size_t i = 0; i < m_children.size(); i++)
		{

			if (m_children[i]->m_core_config.name == name)
			{
				found = true;
				index = i;
				break;
			}

			if (m_children[i]->getDescription().container)
			{
				found = m_children[i]->moveChildDown(name);
				if (found)
					return true;
			}

		}

		if (found)
		{
			if (index < m_children.size()-1)
			{
				auto upperitem = m_children[index];
				auto loweritem = m_children[index+1];

				m_children[index] = loweritem;
				m_children[index + 1] = upperitem;
			}

			return true;
		}

		return false;
	}

	bool mvAppItem::addRuntimeChild(const std::string& parent, const std::string& before, mvRef<mvAppItem> item)
	{
		if (before.empty() && parent.empty())
			return false;

		//this is the container, add item to beginning.
		if (before.empty())
		{
			if (parent == m_core_config.name)
			{
				m_children.push_back(item);
				item->m_parent = this;
				return true;
			}

			else
			{
				// check children
				for (auto& child : m_children)
				{
					if (child->getDescription().container)
					{
						// parent found
						if (child->addRuntimeChild(parent, before, item))
							return true;
					}
				}
			}
		}

		else
		{
			bool beforeFound = false;

			// check children
			for (auto& child : m_children)
			{

				if (child->m_core_config.name == before)
				{
					beforeFound = true;
					break;
				}

			}

			// after item is in this container
			if (beforeFound)
			{
				item->m_parent = this;

				std::vector<mvRef<mvAppItem>> oldchildren = m_children;
				m_children.clear();

				for (auto child : oldchildren)
				{
					if (child->m_core_config.name == before)
						m_children.push_back(item);
					m_children.push_back(child);

				}

				return true;
			}
		}

		// check children
		for (auto& child : m_children)
		{
			if (child->getDescription().container)
			{
				// parent found
				if (child->addRuntimeChild(parent, before, item))
					return true;
			}
		}

		return false;
	}

	bool mvAppItem::addChildAfter(const std::string& prev, mvRef<mvAppItem> item)
	{
		if (prev.empty())
			return false;


		bool prevFound = false;

		// check children
		for (auto& child : m_children)
		{

			if (child->m_core_config.name == prev)
			{
				item->m_parent = this;
				prevFound = true;
				break;
			}

		}

		// prev item is in this container
		if (prevFound)
		{
			//item->setParent(this);

			std::vector<mvRef<mvAppItem>> oldchildren = m_children;
			m_children.clear();

			for (auto& child : oldchildren)
			{
				m_children.push_back(child);
				if (child->m_core_config.name == prev)
					m_children.push_back(item);
			}

			return true;
		}
		

		// check children
		for (auto& child : m_children)
		{
			if (child->getDescription().container)
			{
				// parent found
				if (child->addChildAfter(prev, item))
					return true;
			}
		}

		return false;
	}

	bool mvAppItem::deleteChild(const std::string& name)
	{

		bool childfound = false;
		bool itemDeleted = false;

		for (auto& item : m_children)
		{
			if (item->m_core_config.name == name)
			{
				childfound = true;
				break;
			}

			if (item->getDescription().container)
			{
				itemDeleted = item->deleteChild(name);
				if (itemDeleted)
					break;
			}
		}

		if (childfound)
		{
			std::vector<mvRef<mvAppItem>> oldchildren = m_children;

			m_children.clear();

			for (auto& item : oldchildren)
			{
				if (item->m_core_config.name == name)
				{
					itemDeleted = true;
					continue;
				}

				m_children.push_back(item);
			}
		}

		return itemDeleted;
	}

	void mvAppItem::deleteChildren()
	{
		m_children.clear();
	}

	void mvAppItem::setLabel(const std::string& value)
	{
		m_core_config.label = value;
		m_label = value + "###" + m_core_config.name;
	}

	mvRef<mvAppItem> mvAppItem::stealChild(const std::string& name)
	{
		mvRef<mvAppItem> stolenChild = nullptr;

		bool childfound = false;

		for (auto& item : m_children)
		{
			if (item->m_core_config.name == name)
			{
				childfound = true;
				break;
			}

			if (item->getDescription().container)
			{
				stolenChild = item->stealChild(name);
				if (stolenChild)
					return stolenChild;
			}
		}

		if (childfound)
		{
			std::vector<mvRef<mvAppItem>> oldchildren = m_children;

			m_children.clear();

			for (auto& item : oldchildren)
			{
				if (item->m_core_config.name == name)
				{
					stolenChild = item;
					continue;
				}

				m_children.push_back(item);
			}
		}

		return stolenChild;
	}

	mvRef<mvAppItem> mvAppItem::getChild(const std::string& name)
	{
		for (auto& item : m_children)
		{
			if (item->m_core_config.name == name)
				return item;

			if (item->getDescription().container)
			{
				auto child = item->getChild(name);
				if (child)
					return child;
			}
		}

		return nullptr;
	}

	mvAppItem::~mvAppItem()
	{
		deleteChildren();

#ifndef MV_CPP		 
		mvGlobalIntepreterLock gil;
		if (m_core_config.callback)
			Py_DECREF(m_core_config.callback);
		if (m_core_config.callback_data)
			Py_DECREF(m_core_config.callback_data);
#endif
	}

	mvCallable mvAppItem::getCallback(bool ignore_enabled)
	{
		if (m_core_config.enabled)
			return m_core_config.callback;
#ifdef MV_CPP	
		return m_core_config.callback;
#else
		return ignore_enabled ? m_core_config.callback : nullptr;
#endif
		
	}

#ifndef MV_CPP

	void mvAppItem::checkConfigDict(PyObject* dict)
	{
#ifndef MV_CPP	
		if (dict == nullptr)
			return;

		auto configKeys = ToStringVect(PyDict_Keys(dict));
		auto parserKeywords = (*mvApp::GetApp()->getParsers())[getParserCommand()].getKeywords();
		if (parserKeywords.empty())
		{
			ThrowPythonException("\"" + m_core_config.name + "\" could not find a parser that matched \"" + getParserCommand() + "\".");
			return;
		}
		for (const auto& key : configKeys)
		{
			size_t i = 0;
			while (i < parserKeywords.size() - 1)
			{
				if (key == parserKeywords[i])
				{
					break;
				}
				i++;
			}
			if (i == parserKeywords.size() - 1)
			{
				ThrowPythonException("\"" + key + "\" configuration does not exist in \"" + m_core_config.name + "\".");
			}
		}
#endif
	}

	void mvAppItem::setConfigDict(PyObject* dict)
	{
		if (dict == nullptr)
			return;

#ifndef MV_CPP	
		if (PyObject* item = PyDict_GetItemString(dict, "name")) m_core_config.name = ToString(item);
		if (PyObject* item = PyDict_GetItemString(dict, "label")) setLabel(ToString(item));
		if (PyObject* item = PyDict_GetItemString(dict, "width")) setWidth(ToInt(item));
		if (PyObject* item = PyDict_GetItemString(dict, "height")) setHeight(ToInt(item));
		if (PyObject* item = PyDict_GetItemString(dict, "show")) m_core_config.show = ToBool(item);
		if (PyObject* item = PyDict_GetItemString(dict, "source")) setDataSource(ToString(item));
		if (PyObject* item = PyDict_GetItemString(dict, "enabled")) setEnabled(ToBool(item));
#endif
	}

	void mvAppItem::getConfigDict(PyObject* dict)
	{
		if (dict == nullptr)
			return;
#ifndef MV_CPP	
		PyDict_SetItemString(dict, "name", ToPyString(m_core_config.name));
		PyDict_SetItemString(dict, "label", ToPyString(m_core_config.label));
		PyDict_SetItemString(dict, "source", ToPyString(m_core_config.source));
		PyDict_SetItemString(dict, "show", ToPyBool(m_core_config.show));
		PyDict_SetItemString(dict, "enabled", ToPyBool(m_core_config.enabled));
		PyDict_SetItemString(dict, "width", ToPyInt(m_core_config.width));
		PyDict_SetItemString(dict, "height", ToPyInt(m_core_config.height));
#endif
	}

#endif // !MV_CPP
}
