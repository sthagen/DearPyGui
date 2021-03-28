#include "mvItemRegistry.h"
#include "mvProfiler.h"
#include "mvApp.h"
#include "mvItemRegistry.h"
#include "mvAppItems.h"
#include "mvLog.h"

namespace Marvel {

	mvItemRegistry::mvItemRegistry()
	{
		mvEventBus::Subscribe(this, 0, mvEVT_CATEGORY_ITEM);
		mvEventBus::Subscribe(this, mvEVT_PRE_RENDER_RESET);
		mvEventBus::Subscribe(this, mvEVT_RENDER);
		mvEventBus::Subscribe(this, mvEVT_ACTIVE_WINDOW);

		auto add_hidden_window = [&](mvRef<mvAppItem> item, const std::string& label) {
			m_backWindows.push_back(item);
			m_backWindows.back()->setLabel(label);
			m_backWindows.back()->hide();
		};

#ifndef MV_CPP
		add_hidden_window(CreateRef<mvDocWindow>("documentation##standard"), "Core Documentation");
		add_hidden_window(CreateRef<mvDebugWindow>("debug##standard"), "Dear PyGui Debug");
#endif // !MV_CPP

		add_hidden_window(CreateRef<mvAboutWindow>("about##standard"), "About Dear PyGui");
		add_hidden_window(CreateRef<mvMetricsWindow>("metrics##standard"), "Metrics");
		add_hidden_window(CreateRef<mvStyleWindow>("style##standard"), "Dear PyGui Style Editor");
		add_hidden_window(CreateRef<mvFileDialog>(), "FileDialog");
		
	}

	mvValueVariant mvItemRegistry::getValue(const std::string& name)
	{
		mvRef<mvAppItem> item = getItem(name);
		if (item)
			return item->getValue();
		return nullptr;
	}

	bool mvItemRegistry::deleteItem(const std::string& name, bool childrenOnly)
	{

		MV_ITEM_REGISTRY_TRACE("Attempting to delete: " + name);

		// delete item's children only
		if(childrenOnly)
		{
			auto item = getItem(name);
			if (item)
			{
				item->deleteChildren();
				MV_ITEM_REGISTRY_INFO("Item found and it's children deleted.");
				return true;
			}
		}

		bool deletedItem = false;

		// try to delete build-in item
		for (auto window : m_frontWindows)
		{
			deletedItem = window->deleteChild(name);
			if (deletedItem)
				break;
		}

		// try to delete user added item
		if (!deletedItem)
		{
			for (auto window : m_backWindows)
			{
				deletedItem = window->deleteChild(name);
				if (deletedItem)
					break;
			}
		}

		bool frontWindowDeleting = false;
		bool backWindowDeleting = false;

		// check if attempting to delete a window
		for (auto window : m_frontWindows)
		{
			if (window->m_core_config.name == name)
			{
				frontWindowDeleting = true;
				break;
			}
		}

		for (auto window : m_backWindows)
		{
			if (window->m_core_config.name == name)
			{
				backWindowDeleting = true;
				break;
			}
		}

		// delete window and update window vector
		// this should be changed to a different data
		// structure
		if (frontWindowDeleting)
		{
			std::vector<mvRef<mvAppItem>> oldwindows = m_frontWindows;

			m_frontWindows.clear();

			for (auto window : oldwindows)
			{
				if (window->m_core_config.name == name)
				{
					deletedItem = true;
					continue;
				}
				m_frontWindows.push_back(window);
			}
		}

		if (backWindowDeleting)
		{
			std::vector<mvRef<mvAppItem>> oldwindows = m_backWindows;

			m_backWindows.clear();

			for (auto window : oldwindows)
			{
				if (window->m_core_config.name == name)
				{
					deletedItem = true;
					continue;
				}
				m_backWindows.push_back(window);
			}
		}

		if (deletedItem)
		{
			MV_ITEM_REGISTRY_INFO(name + " found and deleted.");
		}
		else
			mvThrowPythonError(1001, name + " not deleted because it was not found");

		assert(deletedItem && "Item to delete not found");
		return deletedItem;
	}

	bool mvItemRegistry::moveItem(const std::string& name, const std::string& parent, const std::string& before)
	{

		MV_ITEM_REGISTRY_TRACE("Attempting to move: " + name);

		mvRef<mvAppItem> child = nullptr;

		bool movedItem = false;

		for (auto window : m_frontWindows)
		{
			child = window->stealChild(name);
			if (child)
				break;
		}

		if (child == nullptr)
		{
			mvThrowPythonError(1002, name + " not moved because it was not found");
			MV_ITEM_REGISTRY_WARN("Could not move item, it was not found");
		}

		if (child)
			addRuntimeItem(parent, before, child);

		assert(movedItem && "Item to move not found");

		return movedItem;
	}

	bool mvItemRegistry::moveItemUp(const std::string& name)
	{

		MV_ITEM_REGISTRY_TRACE("Attempting to move: " + name);

		bool movedItem = false;

		for (auto window : m_frontWindows)
		{
			movedItem = window->moveChildUp(name);
			if (movedItem)
				break;
		}

		if (!movedItem)
		{
			mvThrowPythonError(1002, name + " not moved because it was not found");
			MV_ITEM_REGISTRY_WARN("Could not move item, it was not found");
		}

		assert(movedItem && "Item to move not found");

		return movedItem;
	}

	bool mvItemRegistry::moveItemDown(const std::string& name)
	{

		MV_ITEM_REGISTRY_TRACE("Attempting to move: " + name);

		bool movedItem = false;

		for (auto window : m_frontWindows)
		{
			movedItem = window->moveChildDown(name);
			if (movedItem)
				break;
		}

		if (!movedItem)
		{
			mvThrowPythonError(1002, name + " not moved because it was not found");
			MV_ITEM_REGISTRY_WARN("Could not move item, it was not found");
		}

		assert(movedItem && "Item to move not found");

		return movedItem;
	}

	bool mvItemRegistry::onEvent(mvEvent& event)
	{
		mvEventDispatcher dispatcher(event);

		dispatcher.dispatch(BIND_EVENT_METH(mvItemRegistry::onPreRenderReset), mvEVT_PRE_RENDER_RESET);
		dispatcher.dispatch(BIND_EVENT_METH(mvItemRegistry::onRender), mvEVT_RENDER);
		dispatcher.dispatch(BIND_EVENT_METH(mvItemRegistry::onActiveWindow), mvEVT_ACTIVE_WINDOW);

		return event.handled;
	}

	bool mvItemRegistry::onRender(mvEvent& event)
	{

		MV_PROFILE_FUNCTION();

		// resets app items states (i.e. hovered)
		for (auto window : m_frontWindows)
			window->draw();
		for (auto window : m_backWindows)
			window->draw();

		return false;
	}

	bool mvItemRegistry::onPreRenderReset(mvEvent& event)
	{

		MV_PROFILE_FUNCTION();

		// resets app items states (i.e. hovered)
		for (auto window : m_frontWindows)
			window->resetState();
		for (auto window : m_backWindows)
			window->resetState();

		return false;
	}

	bool mvItemRegistry::onActiveWindow(mvEvent& event)
	{

		m_activeWindow = GetEString(event, "WINDOW");

		MV_ITEM_REGISTRY_INFO("Active window changed to: " + m_activeWindow);

		return false;
	}

	bool mvItemRegistry::addRuntimeItem(const std::string& parent, const std::string& before, mvRef<mvAppItem> item)
	{
		MV_ITEM_REGISTRY_TRACE("Attempting to add new widget: ", item->getCoreConfig().name);

		// add runtime items
		bool addedItem = false;

		for (auto window : m_frontWindows)
		{
			addedItem = window->addRuntimeChild(parent, before, item);
			if (addedItem)
				break;
		}

		assert(addedItem);
		return addedItem;
	}

	bool mvItemRegistry::addItemAfter(const std::string& prev, mvRef<mvAppItem> item)
	{
		MV_ITEM_REGISTRY_TRACE("Attempting to add new widget after: ", item->getCoreConfig().name);

		bool addedItem = false;

		for (auto& window : m_frontWindows)
		{
			addedItem = window->addChildAfter(prev, item);
			if (addedItem)
				break;
		}

		assert(addedItem);
		return addedItem;
	}

	void mvItemRegistry::pushParent(mvRef<mvAppItem> item)
	{
		m_parents.push(item);
	}

	mvRef<mvAppItem> mvItemRegistry::popParent()
	{
		if (m_parents.empty())
		{
			mvThrowPythonError(1005, "No parent to pop.");
			MV_ITEM_REGISTRY_WARN("No parent to pop.");
			assert(false);
			return nullptr;
		}

		auto item = m_parents.top();
		m_parents.pop();
		return item;
	}

	void mvItemRegistry::emptyParents()
	{
		while (!m_parents.empty())
			m_parents.pop();

		MV_ITEM_REGISTRY_INFO("Parent stack emptied.");
	}

	mvRef<mvAppItem> mvItemRegistry::topParent()
	{
		if (!m_parents.empty())
			return m_parents.top();
		return nullptr;
	}

	mvRef<mvAppItem> mvItemRegistry::getItem(const std::string& name)
	{
		mvRef<mvAppItem> item = nullptr;

		for (auto window : m_frontWindows)
		{
			if (window->m_core_config.name == name)
				return window;

			auto child = window->getChild(name);
			if (child)
				return child;
		}

		for (auto window : m_backWindows)
		{
			if (window->m_core_config.name == name)
				return window;

			auto child = window->getChild(name);
			if (child)
				return child;
		}

		//assert(false && "Item not found.");

		return nullptr;
	}

	mvWindowAppItem* mvItemRegistry::getWindow(const std::string& name)
	{

		mvRef<mvAppItem> item = getItem(name);
		if (item == nullptr)
		{
			assert(false && "Window not found.");
			return nullptr;
		}

		if (item->getType() == mvAppItemType::mvWindowAppItem)
			return static_cast<mvWindowAppItem*>(item.get());

		assert(false && "Item is not a window not found.");
		return nullptr;
	}

	bool mvItemRegistry::addItem(mvRef<mvAppItem> item)
	{

		MV_ITEM_REGISTRY_TRACE("Adding item: " + item->getCoreConfig().name);

		mvRef<mvAppItem> parentitem = topParent();
		item->m_parent = parentitem.get();
		parentitem->m_children.emplace_back(item);

		return true;
	}

	bool mvItemRegistry::addWindow(mvRef<mvAppItem> item)
	{
		MV_ITEM_REGISTRY_INFO("Adding window: " + item->getCoreConfig().name);
		m_frontWindows.push_back(item);
		return true;
	}

	void mvItemRegistry::clearRegistry()
	{
		MV_ITEM_REGISTRY_INFO("Clearing item registry.");
		m_frontWindows.clear();
		m_backWindows.clear();
	}

	bool mvItemRegistry::addItemWithRuntimeChecks(mvRef<mvAppItem> item, const char* parent, const char* before)
	{
		MV_ITEM_REGISTRY_TRACE("Adding runtime item: " + item->getCoreConfig().name);

		if (item == nullptr)
			return false;

		//---------------------------------------------------------------------------
		// STEP 0: check if an item with this name exists
		//---------------------------------------------------------------------------
		if (!item->getDescription().duplicatesAllowed)
		{
			if (getItem(item->m_core_config.name))
			{
				mvThrowPythonError(1000, "Item must have a unique name.");
				MV_ITEM_REGISTRY_WARN("Item must have a unique name.");
				assert(false);
				return false;
			}
		}

		enum class AddTechnique
		{
			NONE, BEFORE, PARENT, STACK
		};
		AddTechnique technique = AddTechnique::NONE;

		std::lock_guard<std::mutex> lk(mvApp::GetApp()->getMutex());

		//---------------------------------------------------------------------------
		// STEP 1: empty parent stack if mistakes were made
		//---------------------------------------------------------------------------
		if (item->getDescription().root && topParent() != nullptr)
		{
			mvThrowPythonError(1000, "Parent stack not empty.");
			emptyParents();
			MV_ITEM_REGISTRY_ERROR("Parent stack not empty when adding " + item->getCoreConfig().name);
			assert(false);
		}

		//---------------------------------------------------------------------------
		// STEP 2: handle window case
		//---------------------------------------------------------------------------
		if (item->getDescription().root)
		{
			if (mvApp::IsAppStarted())
			{
				m_frontWindows.push_back(item);
				return true;
			}
			return addWindow(item);
		}
			
		//---------------------------------------------------------------------------
		// STEP 3: attempt to deduce parent
		//---------------------------------------------------------------------------
		mvRef<mvAppItem> parentPtr = nullptr;
		if (!std::string(before).empty())
		{
			parentPtr = getItem(before);
			technique = AddTechnique::BEFORE;
		}

		else if (!std::string(parent).empty())
		{
			parentPtr = getItem(parent);
			technique = AddTechnique::PARENT;
		}

		else
		{
			parentPtr = topParent();
			technique = AddTechnique::STACK;
		}

		//---------------------------------------------------------------------------
		// STEP 4: check if parent was deduced
		//---------------------------------------------------------------------------
		if (parentPtr == nullptr)
		{
			mvThrowPythonError(1000, "Parent could not be deduced.");
			MV_ITEM_REGISTRY_ERROR("Parent could not be deduced.");
			assert(false);
			return false;
		}

		//---------------------------------------------------------------------------
		// STEP 5: check if parent is a compatible type
		//---------------------------------------------------------------------------
		if (!item->isParentCompatible(parentPtr->getType()))
			return false;

		//---------------------------------------------------------------------------
		// STEP 6: check if parent accepts our item (this isn't duplicate STEP 3 ha)
		//---------------------------------------------------------------------------
		if (!parentPtr->canChildBeAdded(item->getType()))
			return false;

		//---------------------------------------------------------------------------
		// STEP 7: add items who require "after" adding (i.e. popup, tooltip)
		//---------------------------------------------------------------------------
		if (item->getDescription().addAfterRequired)
			return addItemAfter(parent, item);

		//---------------------------------------------------------------------------
		// STEP 8: handle "before" and "after" style adding
		//---------------------------------------------------------------------------
		if (technique == AddTechnique::BEFORE || technique == AddTechnique::PARENT)
			return addRuntimeItem(parent, before, item); // same for run/compile time

		//---------------------------------------------------------------------------
		// STEP 9: handle "stack" style adding
		//---------------------------------------------------------------------------
		if(mvApp::IsAppStarted())
			return addRuntimeItem(parentPtr->m_core_config.name, "", item);
		return addItem(item);
	}

	std::string mvItemRegistry::getItemParentName(const std::string& name)
	{
		mvRef<mvAppItem> item = getItem(name);
		if (item)
			return item->m_parent->m_core_config.name;
		
		mvThrowPythonError(1009, name + ": item not found");
		assert(false && "Item not found.");

		return "";
	}

	std::vector<std::string> mvItemRegistry::getItemChildren(const std::string& name)
	{

		mvRef<mvAppItem> item = getItem(name);

		std::vector<std::string> childList;

		if (item)
		{
			auto children = item->m_children;
			for (auto child : children)
				childList.emplace_back(child->m_core_config.name);
		}
		else
		{
			mvThrowPythonError(1010, name + ": item not found");
			assert(false && "Item not found.");
		}

		return childList;
	}

	std::vector<std::string> mvItemRegistry::getAllItems()
	{

		std::vector<std::string> childList;

		// to help recursively retrieve children
		std::function<void(mvRef<mvAppItem>)> ChildRetriever;
		ChildRetriever = [&childList, &ChildRetriever](mvRef<mvAppItem> item) {
			auto children = item->m_children;
			for (auto child : children)
			{
				childList.emplace_back(child->m_core_config.name);
				if (child->getDescription().container)
					ChildRetriever(child);
			}

		};

		for (auto window : m_frontWindows)
		{
			childList.emplace_back(window->getCoreConfig().name);
			ChildRetriever(window);
		}
		for (auto window : m_backWindows)
		{
			childList.emplace_back(window->getCoreConfig().name);
			ChildRetriever(window);
		}

		return childList;
	}

	std::vector<std::string> mvItemRegistry::getWindows()
	{

		std::vector<std::string> childList;
		for (auto window : m_frontWindows)
			childList.emplace_back(window->m_core_config.name);

		for (auto window : m_backWindows)
			childList.emplace_back(window->m_core_config.name);

		return childList;
	}

	void mvItemRegistry::setPrimaryWindow(const std::string& name, bool value)
	{

		mvWindowAppItem* window = getWindow(name);

		if (window)
		{
			if (window->getWindowAsMainStatus() == value)
				return;
			else
				window->setWindowAsMainStatus(value);
		}
		else
		{
			mvThrowPythonError(1011, "Window does not exists.");
			assert(false);
		}

		// reset other windows
		for (auto window : m_frontWindows)
		{
			if (window->m_core_config.name != name)
				static_cast<mvWindowAppItem*>(window.get())->setWindowAsMainStatus(false);
		}

		mvAppLog::Focus();
	}
}
