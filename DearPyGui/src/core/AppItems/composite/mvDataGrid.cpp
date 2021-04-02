#include "mvDataGrid.h"
#include "mvApp.h"
#include "mvAppLog.h"
#include "mvItemRegistry.h"
#include "mvImGuiThemeScope.h"
#include "mvFontScope.h"

namespace Marvel {

	void mvDataGrid::InsertParser(std::map<std::string, mvPythonParser>* parsers)
	{
		parsers->insert({ s_command, mvPythonParser({
			{mvPythonDataType::Optional},
			{mvPythonDataType::String, "name"},
			{mvPythonDataType::StringList, "headers"},
			{mvPythonDataType::KeywordOnly},
			{mvPythonDataType::Callable, "callback", "Registers a callback", "None"},
			{mvPythonDataType::Object, "callback_data", "Callback data", "None"},
			{mvPythonDataType::String, "parent", "Parent this item will be added to. (runtime adding)", "''"},
			{mvPythonDataType::String, "before","This item will be displayed before the specified item in the parent. (runtime adding)", "''"},
			{mvPythonDataType::Integer, "width","", "0"},
			{mvPythonDataType::Integer, "height","", "200"},
			{mvPythonDataType::Bool, "hide_headers", "Hide headers of the table", "False"},
			{mvPythonDataType::Bool, "show","Attempt to render", "True"}
		}, "Adds data grid.", "None", "Tables") });

		parsers->insert({ "set_grid_data", mvPythonParser({
			{mvPythonDataType::String, "data_grid"},
			{mvPythonDataType::ListStrList, "data"}
		}, "Overwrites data grid data.", "None", "Tables") });

		parsers->insert({ "get_grid_data", mvPythonParser({
			{mvPythonDataType::String, "data_grid"},
		}, "Gets data grid data.", "List[List[str]]", "Tables") });

		parsers->insert({ "set_grid_headers", mvPythonParser({
			{mvPythonDataType::String, "data_grid"},
			{mvPythonDataType::StringList, "headers"},
		}, "Sets a data grid's headers.", "None", "Tables") });

		parsers->insert({ "clear_data_grid", mvPythonParser({
			{mvPythonDataType::String, "data_grid"}
		}, "Clears data in a data grid", "None", "Tables") });

		parsers->insert({ "add_grid_column", mvPythonParser({
			{mvPythonDataType::String, "data_grid"},
			{mvPythonDataType::String, "name"},
			{mvPythonDataType::StringList, "column"},
		}, "Adds a column to the end of a data grid.", "None", "Tables") });

		parsers->insert({ "insert_grid_column", mvPythonParser({
			{mvPythonDataType::String, "data_grid"},
			{mvPythonDataType::Integer, "column_index"},
			{mvPythonDataType::String, "name"},
			{mvPythonDataType::StringList, "column"},
		}, "Inserts a column into a data grid.", "None", "Tables") });

		parsers->insert({ "delete_grid_column", mvPythonParser({
			{mvPythonDataType::String, "data_grid"},
			{mvPythonDataType::Integer, "column"}
		}, "Delete a column in a data grid.", "None", "Tables") });

		parsers->insert({ "add_grid_row", mvPythonParser({
			{mvPythonDataType::String, "data_grid"},
			{mvPythonDataType::StringList, "row"},
		}, "Adds a row to the end of a data grid.", "None", "Tables") });

		parsers->insert({ "insert_grid_row", mvPythonParser({
			{mvPythonDataType::String, "data_grid"},
			{mvPythonDataType::Integer, "row_index"},
			{mvPythonDataType::StringList, "row"},
		}, "Inserts a row into a data grid.", "None", "Tables") });

		parsers->insert({ "delete_grid_row", mvPythonParser({
			{mvPythonDataType::String, "data_grid"},
			{mvPythonDataType::Integer, "row"}
		}, "Delete a row in a data grid.", "None", "Tables") });

		parsers->insert({ "get_grid_item", mvPythonParser({
			{mvPythonDataType::String, "data_grid"},
			{mvPythonDataType::Integer, "row"},
			{mvPythonDataType::Integer, "column"}
		}, "Gets a data grid's cell value.", "str", "Tables") });

		parsers->insert({ "set_grid_item", mvPythonParser({
			{mvPythonDataType::String, "data_grid"},
			{mvPythonDataType::Integer, "row"},
			{mvPythonDataType::Integer, "column"},
			{mvPythonDataType::String, "value"},
		}, "Sets a data grid's cell value.", "None", "Tables") });

		parsers->insert({ "get_grid_selections", mvPythonParser({
			{mvPythonDataType::String, "data_grid"}
		}, "Retrieves data from storage.", "List[List[int]]", "Tables") });

		parsers->insert({ "set_grid_selection", mvPythonParser({
			{mvPythonDataType::String, "data_grid"},
			{mvPythonDataType::Integer, "row"},
			{mvPythonDataType::Integer, "column"},
			{mvPythonDataType::Bool, "value"},
		}, "Sets a data grid's cell selection value.", "None", "Tables") });
	}

	mvDataGrid::mvDataGrid(const std::string& name, const std::vector<std::string>& headers)
		: mvAppItem(name)
	{
		m_height = 200;
		m_headers = headers;
		m_columns = headers.size();
		m_hide_headers = false;
	}

	void mvDataGrid::setExtraConfigDict(PyObject* dict)
	{
		if (dict == nullptr)
			return;

		if (PyObject* item = PyDict_GetItemString(dict, "hide_headers")) m_hide_headers = ToBool(item);
	}

	void mvDataGrid::getExtraConfigDict(PyObject* dict)
	{
		if (dict == nullptr)
			return;

		PyDict_SetItemString(dict, "hide_headers", ToPyBool(m_hide_headers));
	}

	bool mvDataGrid::isIndexValid(int row, int column) const
	{
		if (column < 0 || row < 0)
		{
			ThrowPythonException("Data Grid index must be a positive integer.");
			return false;
		}

		if (static_cast<size_t>(column) > m_columns + 1 || static_cast<size_t>(row) > m_values.size() + 1)
		{
			ThrowPythonException("Data Grid indices out of range.");
			return false;
		}

		return true;
	}

	void mvDataGrid::updateHashValues()
	{
		m_hashValues.clear();

		m_hashValues = m_values;

		for (size_t i = 0; i < m_hashValues.size(); i++)
		{
			for (size_t j = 0; j < m_hashValues[i].size(); j++)
				m_hashValues[i][j] = m_hashValues[i][j] + "##" + m_name + "-" + std::to_string(i) + "-" + std::to_string(j);

			for (size_t j = m_hashValues[i].size(); j < m_columns; j++)
				m_hashValues[i].push_back("##" + m_name + "-" + std::to_string(i) + "-" + std::to_string(j));
		}
	}

	void mvDataGrid::setGridItem(int row, int column, const std::string& value)
	{
		if (!isIndexValid(row, column))
			return;

		m_values[row][column] = value;
		m_hashValues[row][column] = value + "##" + m_name + "-" + std::to_string(row) + "-" + std::to_string(column);

	}

	std::string mvDataGrid::getGridItem(int row, int column) const
	{
		if (!isIndexValid(row, column))
			return "";

		return m_values[row][column];
	}

	void mvDataGrid::setSelection(int row, int column, bool value)
	{
		if (!isIndexValid(row, column))
			return;

		m_selections[{row, column}] = value;
	}

	void mvDataGrid::setPyValue(PyObject* value)
	{
		auto values = ToVectVectString(value, m_name + " requires a list/tuple or list/tuple of strings.");

		m_values = std::move(values);

		if (!m_values.empty()) // just in case value is set to an empty list
		{
			while (m_headers.size() > m_columns)
				m_headers.pop_back();
		}

		updateHashValues();

		m_selections.clear();
	}

	PyObject* mvDataGrid::getPyValue()
	{
		return ToPyList(m_values);
	}

	PyObject* mvDataGrid::getSelections() const
	{
		int selectionCount = 0;

		for (auto& item : m_selections)
			if (item.second) selectionCount++;

		std::vector<std::pair<int, int>> selections;

		for (auto& item : m_selections)
		{
			if (item.second)
				selections.emplace_back(item.first.first, item.first.second);
		}
		
		return ToPyList(selections);
	}

	void mvDataGrid::addHeaders(const std::vector<std::string>& headers)
	{
		m_headers = headers; 
		m_columns = headers.size(); 

		if (m_values.empty())
			return;

		if (m_columns > m_values[0].size())
		{
			for (auto& row : m_values)
				row.emplace_back("");
		}
		else if (m_columns < m_values[0].size())
		{
			m_columns = m_values[0].size();
			while (m_headers.size() < m_columns)
				m_headers.emplace_back("Header");
		}
		updateHashValues();
	}

	void mvDataGrid::addRow(const std::vector<std::string>& row)
	{
		m_values.push_back(row);

		while (m_values.back().size() < m_headers.size())
			m_values.back().emplace_back("");

		while (m_values.back().size() > m_headers.size())
			m_values.back().pop_back();

		updateHashValues();
	}

	void mvDataGrid::addColumn(const std::string& name, const std::vector<std::string>& column)
	{
		m_headers.push_back(name);

		if (column.size() > m_values.size())
		{
			for (unsigned i = 0; i < column.size(); i++)
			{
				// row exists
				if (i < m_values.size())
				{
					m_values[i].emplace_back(column[i]);
					continue;
				}

				// row does not exist
				m_values.push_back({});
				for (unsigned j = 0; j < m_headers.size() - 1; j++)
					m_values[i].emplace_back("");

				m_values[i].emplace_back(column[i]);
			}
		}

		else
		{
			size_t index = 0;
			for (auto& row : m_values)
			{
				if (index >= column.size())
				{
					row.emplace_back("");
					index++;
					continue;

				}

				row.push_back(column[index]);
				index++;
			}
		}

		m_columns++;

		updateHashValues();
	}

	void mvDataGrid::insertColumn(int column_index, const std::string& name, const std::vector<std::string>& column)
	{
		if (!isIndexValid(0, column_index))
			return;

		if (static_cast<size_t>(column_index) == m_headers.size())
		{
			addColumn(name, column);
			return;
		}

		auto oldValues = m_values;
		auto oldHeaders = m_headers;

		m_values.clear();
		m_headers.clear();
		m_columns++;

		for (size_t i = 0; i < m_columns; i++)
		{
			if (i < static_cast<size_t>(column_index))
				m_headers.push_back(oldHeaders[i]);
			else if (i == static_cast<size_t>(column_index))
				m_headers.push_back(name);
			else
				m_headers.push_back(oldHeaders[i - 1]);
		}

		if (column.size() > oldValues.size())
		{
			for (size_t i = 0; i < column.size(); i++)
			{
				if (i < oldValues.size())
				{
					std::vector<std::string> row;
					for (size_t j = 0; j < oldHeaders.size(); j++)
					{
						if (j == static_cast<size_t>(column_index))
						{
							row.push_back(column[i]);
							continue;
						}

						if (j > static_cast<size_t>(column_index))
							row.push_back(oldValues[i][j - 1]);

						else
							row.push_back(oldValues[i][j]);

					}
					row.push_back(oldValues[i].back());

					m_values.push_back(row);
				}

				else
				{
					std::vector<std::string> row;
					for (size_t j = 0; j < oldHeaders.size(); j++)
					{
						if (j == static_cast<size_t>(column_index))
						{
							row.push_back(column[i]);
							continue;
						}
						row.push_back("");
					}
					row.push_back("");

					m_values.push_back(row);
				}
			}
		}

		else
		{
			for (size_t i = 0; i < oldValues.size(); i++)
			{
				std::vector<std::string> row;
				for (size_t j = 0; j < oldHeaders.size(); j++)
				{
					if (j == static_cast<size_t>(column_index))
					{
						if (i >= column.size())
							row.emplace_back("");
						else
							row.push_back(column[i]);
						continue;
					}

					if (j > static_cast<size_t>(column_index))
						row.push_back(oldValues[i][j - 1]);

					else
						row.push_back(oldValues[i][j]);

				}
				row.push_back(oldValues[i].back());

				m_values.push_back(row);
			}
		}

		updateHashValues();

		// update selections
		std::map<std::pair<int, int>, bool> oldSelection = m_selections;
		m_selections.clear();

		for (auto& item : oldSelection)
		{

			if (item.first.second >= column_index)
				m_selections[{item.first.first, item.first.second + 1}] = item.second;

			else
				m_selections[item.first] = item.second;

		}

	}

	void mvDataGrid::insertRow(int row_index, const std::vector<std::string>& row)
	{
		if (!isIndexValid(row_index, 0))
			return;

		if (static_cast<size_t>(row_index) >= m_values.size())
		{
			addRow(row);
			return;
		}

		auto oldValues = m_values;

		m_values.clear();

		for (size_t i = 0; i < oldValues.size(); i++)
		{
			if (i == static_cast<size_t>(row_index))
			{
				m_values.push_back(row);
				continue;
			}

			if(i > static_cast<size_t>(row_index))
				m_values.push_back(oldValues[i-1]);
			else
				m_values.push_back(oldValues[i]);
		}
		m_values.push_back(oldValues.back());

		while (m_values[row_index].size() < m_headers.size())
			m_values[row_index].emplace_back("");

		while (m_values.back().size() > m_headers.size())
			m_values.back().pop_back();

		updateHashValues();

		// update selections
		std::map<std::pair<int, int>, bool> oldSelection = m_selections;
		m_selections.clear();

		for (auto& item : oldSelection)
		{

			if (item.first.first >= row_index)
				m_selections[{item.first.first + 1, item.first.second}] = item.second;

			else
				m_selections[item.first] = item.second;
			
		}

	}

	void mvDataGrid::deleteRow(int row)
	{
		if (!isIndexValid(row, 0))
			return ;

		auto oldValues = m_values;

		m_values.clear();

		int index = 0;
		for (auto& item : oldValues)
		{
			
			if (index == row)
			{
				index++;
				continue;
			}
			m_values.push_back(item);

			index++;
			
		}

		updateHashValues();

		// update selections
		std::map<std::pair<int, int>, bool> oldSelection = m_selections;
		m_selections.clear();

		for (auto& item : oldSelection)
		{
			if (item.first.first == row)
				continue;

			else if (item.first.first < row)
				m_selections[item.first] = item.second;


			else if (item.first.first > row)
				m_selections[{item.first.first - 1, item.first.second}] = item.second;
		}

	}

	void mvDataGrid::deleteColumn(int column)
	{
		if (!isIndexValid(0, column))
			return;

		if (static_cast<size_t>(column) >= m_headers.size())
		{
			ThrowPythonException("Column to delete does not exist.");
			return;
		}

		auto oldValues = m_values;
		auto oldHeaders = m_headers;

		m_values.clear();
		m_headers.clear();
		m_columns--;

		for (size_t i = 0; i < oldHeaders.size(); i++)
		{
			if (i == static_cast<size_t>(column))
				continue;
			m_headers.push_back(oldHeaders[i]);
		}

		//for (int i = 0; i < oldValues.size(); i++)
		for (auto& oldvalue : oldValues)
		{
			std::vector<std::string> row;
			for (size_t j = 0; j < oldHeaders.size(); j++)
			{
				if (j == static_cast<size_t>(column))
					continue;
				row.push_back(oldvalue[j]);
			}

			m_values.push_back(row);
		}

		updateHashValues();

		// update selections
		std::map<std::pair<int, int>, bool> oldSelection = m_selections;
		m_selections.clear();
		for (auto& item : oldSelection)
		{
			if (item.first.second == column)
				continue;

			else if (item.first.second < column)
				m_selections[item.first] = item.second;


			else if (item.first.second > column)
				m_selections[{item.first.first, item.first.second - 1}] = item.second;
		}

	}

	void mvDataGrid::clearGrid()
	{
		m_selections.clear();
		m_hashValues.clear();
		m_values.clear();
	}

	void mvDataGrid::draw(ImDrawList* drawlist, float x, float y)
	{
		ScopedID id;
		mvImGuiThemeScope scope(this);
		mvFontScope fscope(this);

		if (ImGui::BeginTable(m_name.c_str(), m_columns,
			ImGuiTableFlags_Hideable | ImGuiTableFlags_Resizable | ImGuiTableFlags_RowBg | ImGuiTableFlags_Borders))
		{
			if (!m_hide_headers)
			{
				for (auto& header : m_headers)
					ImGui::TableSetupColumn(header.c_str());
				ImGui::TableHeadersRow();
				//ImGui::TableNextColumn();
			}

			for (size_t i = 0; i < m_hashValues.size(); i++)
			{
				ImGui::TableNextRow();
				for (size_t j = 0; j < m_hashValues[i].size(); j++)
				{
					ImGui::TableSetColumnIndex(j);
					if (ImGui::Selectable(m_hashValues[i][j].c_str(), m_selections[{i, j}]))
					{
						m_selections[{i, j}] = !m_selections[{i, j}];
						mvApp::GetApp()->getCallbackRegistry().addCallback(m_callback, 
							m_name, m_callback_data);
					}
				}

			}

			ImGui::EndTable();
		}


	}

	PyObject* mvDataGrid::add_data_grid(PyObject* self, PyObject* args, PyObject* kwargs)
	{
		static int i = 0; i++;
		std::string sname = std::string(std::string("$$DPG_") + s_internal_id + std::to_string(i));
		const char* name = sname.c_str();
		PyObject* headers;
		PyObject* callback = nullptr;
		PyObject* callback_data = nullptr;
		const char* parent = "";
		const char* before = "";
		int width = 0;
		int height = 0;
		int show = true;
		bool hide_headers = false;

		if (!(mvApp::GetApp()->getParsers())["add_data_grid"].parse(args, kwargs, __FUNCTION__,
			&name, &headers, &callback, &callback_data, &parent,
			&before, &width, &height, &show, &hide_headers))
			return ToPyBool(false);

		auto item = CreateRef<mvDataGrid>(name, ToStringVect(headers));
		if (callback)
			Py_XINCREF(callback);
		item->setCallback(callback);
		if (callback_data)
			Py_XINCREF(callback_data);
		item->setCallbackData(callback_data);

		item->checkConfigDict(kwargs);
		item->setConfigDict(kwargs);
		item->setExtraConfigDict(kwargs);

		mvApp::GetApp()->getItemRegistry().addItemWithRuntimeChecks(item, parent, before);

		return ToPyString(name);
	}

	PyObject* mvDataGrid::get_grid_data(PyObject* self, PyObject* args, PyObject* kwargs)
	{
		const char* grid;

		if (!(mvApp::GetApp()->getParsers())["get_grid_data"].parse(args, kwargs, __FUNCTION__, &grid))
			return GetPyNone();

		std::lock_guard<std::mutex> lk(mvApp::GetApp()->getMutex());
		auto item = mvApp::GetApp()->getItemRegistry().getItem(std::string(grid));

		if (item == nullptr)
		{
			std::string message = grid;
			ThrowPythonException(message + " table does not exist.");
			return GetPyNone();
		}

		if (item->getType() != mvAppItemType::mvDataGrid)
		{
			std::string message = grid;
			ThrowPythonException(message + " is not a table.");
			return GetPyNone();
		}

		return static_cast<mvDataGrid*>(item.get())->getPyValue();
	}

	PyObject* mvDataGrid::set_grid_data(PyObject* self, PyObject* args, PyObject* kwargs)
	{
		const char* grid;
		PyObject* value;

		if (!(mvApp::GetApp()->getParsers())["set_grid_data"].parse(args, kwargs, __FUNCTION__, &grid, &value))
			return GetPyNone();

		std::lock_guard<std::mutex> lk(mvApp::GetApp()->getMutex());
		auto item = mvApp::GetApp()->getItemRegistry().getItem(std::string(grid));

		if (item == nullptr)
		{
			std::string message = grid;
			ThrowPythonException(message + " grid does not exist.");
			return GetPyNone();
		}

		if (item->getType() != mvAppItemType::mvDataGrid)
		{
			std::string message = grid;
			ThrowPythonException(message + " is not a grid.");
			return GetPyNone();
		}

		static_cast<mvDataGrid*>(item.get())->setPyValue(value);

		return GetPyNone();
	}

	PyObject* mvDataGrid::set_grid_headers(PyObject* self, PyObject* args, PyObject* kwargs)
	{
		const char* grid;
		PyObject* headers;

		if (!(mvApp::GetApp()->getParsers())["set_grid_headers"].parse(args, kwargs, __FUNCTION__, &grid, &headers))
			return GetPyNone();

		std::lock_guard<std::mutex> lk(mvApp::GetApp()->getMutex());
		auto item = mvApp::GetApp()->getItemRegistry().getItem(grid);
		if (item == nullptr)
		{
			std::string message = grid;
			ThrowPythonException(message + " grid does not exist.");
			return GetPyNone();
		}

		auto prow = ToStringVect(headers);
		mvDataGrid* atable = static_cast<mvDataGrid*>(item.get());

		atable->addHeaders(prow);

		return GetPyNone();
	}

	PyObject* mvDataGrid::clear_data_grid(PyObject* self, PyObject* args, PyObject* kwargs)
	{
		const char* grid;

		if (!(mvApp::GetApp()->getParsers())["clear_data_grid"].parse(args, kwargs, __FUNCTION__, &grid))
			return GetPyNone();

		std::lock_guard<std::mutex> lk(mvApp::GetApp()->getMutex());
		auto item = mvApp::GetApp()->getItemRegistry().getItem(grid);
		if (item == nullptr)
		{
			std::string message = grid;
			ThrowPythonException(message + " grid does not exist.");
			return GetPyNone();
		}

		if (item->getType() != mvAppItemType::mvDataGrid)
		{
			std::string message = grid;
			ThrowPythonException(message + " is not a grid.");
			return GetPyNone();
		}

		mvDataGrid* atable = static_cast<mvDataGrid*>(item.get());
		atable->clearGrid();
		Py_RETURN_NONE;
	}

	PyObject* mvDataGrid::get_grid_item(PyObject* self, PyObject* args, PyObject* kwargs)
	{
		const char* grid;
		int row;
		int column;

		if (!(mvApp::GetApp()->getParsers())["get_grid_item"].parse(args, kwargs, __FUNCTION__, &grid, &row,
			&column))
			return GetPyNone();

		std::lock_guard<std::mutex> lk(mvApp::GetApp()->getMutex());
		auto item = mvApp::GetApp()->getItemRegistry().getItem(grid);
		if (item == nullptr)
		{
			std::string message = grid;
			ThrowPythonException(message + " grid does not exist.");
			return GetPyNone();
		}

		if (item->getType() != mvAppItemType::mvDataGrid)
		{
			std::string message = grid;
			ThrowPythonException(message + " is not a grid.");
			return GetPyNone();
		}

		mvDataGrid* atable = static_cast<mvDataGrid*>(item.get());
		return Py_BuildValue("s", atable->getGridItem(row, column).c_str());

	}

	PyObject* mvDataGrid::set_grid_item(PyObject* self, PyObject* args, PyObject* kwargs)
	{
		const char* grid;
		int row;
		int column;
		const char* value;

		if (!(mvApp::GetApp()->getParsers())["set_grid_item"].parse(args, kwargs, __FUNCTION__, &grid, &row,
			&column, &value))
			return GetPyNone();

		std::lock_guard<std::mutex> lk(mvApp::GetApp()->getMutex());
		auto item = mvApp::GetApp()->getItemRegistry().getItem(grid);
		if (item == nullptr)
		{
			std::string message = grid;
			ThrowPythonException(message + " grid does not exist.");
			return GetPyNone();
		}

		if (item->getType() != mvAppItemType::mvDataGrid)
		{
			std::string message = grid;
			ThrowPythonException(message + " is not a grid.");
			return GetPyNone();
		}

		mvDataGrid* atable = static_cast<mvDataGrid*>(item.get());
		atable->setGridItem(row, column, value);

		return GetPyNone();
	}

	PyObject* mvDataGrid::get_grid_selections(PyObject* self, PyObject* args, PyObject* kwargs)
	{
		const char* grid;

		if (!(mvApp::GetApp()->getParsers())["get_grid_selections"].parse(args, kwargs, __FUNCTION__, &grid))
			return GetPyNone();

		std::lock_guard<std::mutex> lk(mvApp::GetApp()->getMutex());
		auto item = mvApp::GetApp()->getItemRegistry().getItem(grid);
		if (item == nullptr)
		{
			std::string message = grid;
			ThrowPythonException(message + " grid does not exist.");
			return GetPyNone();
		}

		if (item->getType() != mvAppItemType::mvDataGrid)
		{
			std::string message = grid;
			ThrowPythonException(message + " is not a grid.");
			return GetPyNone();
		}

		mvDataGrid* atable = static_cast<mvDataGrid*>(item.get());
		return atable->getSelections();
	}

	PyObject* mvDataGrid::set_grid_selection(PyObject* self, PyObject* args, PyObject* kwargs)
	{
		const char* grid;
		int row;
		int column;
		int value;

		if (!(mvApp::GetApp()->getParsers())["set_grid_selection"].parse(args, kwargs, __FUNCTION__, &grid, &row,
			&column, &value))
			return GetPyNone();

		std::lock_guard<std::mutex> lk(mvApp::GetApp()->getMutex());
		auto item = mvApp::GetApp()->getItemRegistry().getItem(grid);
		if (item == nullptr)
		{
			std::string message = grid;
			ThrowPythonException(message + " grid does not exist.");
			return GetPyNone();
		}

		if (item->getType() != mvAppItemType::mvDataGrid)
		{
			std::string message = grid;
			ThrowPythonException(message + " is not a grid.");
			return GetPyNone();
		}

		mvDataGrid* atable = static_cast<mvDataGrid*>(item.get());
		atable->setSelection(row, column, value);

		return GetPyNone();
	}

	PyObject* mvDataGrid::add_grid_column(PyObject* self, PyObject* args, PyObject* kwargs)
	{
		const char* grid;
		const char* name;
		PyObject* column;

		if (!(mvApp::GetApp()->getParsers())["add_grid_column"].parse(args, kwargs, __FUNCTION__, &grid, &name, &column))
			return GetPyNone();

		std::lock_guard<std::mutex> lk(mvApp::GetApp()->getMutex());
		auto item = mvApp::GetApp()->getItemRegistry().getItem(grid);
		if (item == nullptr)
		{
			std::string message = grid;
			ThrowPythonException(message + " table does not exist.");
			return GetPyNone();
		}

		if (item->getType() != mvAppItemType::mvDataGrid)
		{
			std::string message = grid;
			ThrowPythonException(message + " is not a table.");
			return GetPyNone();
		}

		auto pcolumn = ToStringVect(column);

		mvDataGrid* atable = static_cast<mvDataGrid*>(item.get());
		atable->addColumn(name, pcolumn);

		return GetPyNone();
	}

	PyObject* mvDataGrid::insert_grid_column(PyObject* self, PyObject* args, PyObject* kwargs)
	{
		const char* grid;
		int column_index;
		const char* name;
		PyObject* column;

		if (!(mvApp::GetApp()->getParsers())["insert_grid_column"].parse(args, kwargs, __FUNCTION__, &grid, &column_index, &name, &column))
			return GetPyNone();

		std::lock_guard<std::mutex> lk(mvApp::GetApp()->getMutex());
		auto item = mvApp::GetApp()->getItemRegistry().getItem(grid);
		if (item == nullptr)
		{
			std::string message = grid;
			ThrowPythonException(message + " grid does not exist.");
			return GetPyNone();
		}

		if (item->getType() != mvAppItemType::mvDataGrid)
		{
			std::string message = grid;
			ThrowPythonException(message + " is not a grid.");
			return GetPyNone();
		}

		auto prow = ToStringVect(column);

		mvDataGrid* atable = static_cast<mvDataGrid*>(item.get());
		atable->insertColumn(column_index, name, prow);

		return GetPyNone();
	}

	PyObject* mvDataGrid::delete_grid_column(PyObject* self, PyObject* args, PyObject* kwargs)
	{
		const char* grid;
		int column;

		if (!(mvApp::GetApp()->getParsers())["delete_grid_column"].parse(args, kwargs, __FUNCTION__, &grid, &column))
			return GetPyNone();

		std::lock_guard<std::mutex> lk(mvApp::GetApp()->getMutex());
		auto item = mvApp::GetApp()->getItemRegistry().getItem(grid);
		if (item == nullptr)
		{
			std::string message = grid;
			ThrowPythonException(message + " grid does not exist.");
			return GetPyNone();
		}

		if (item->getType() != mvAppItemType::mvDataGrid)
		{
			std::string message = grid;
			ThrowPythonException(message + " is not a grid.");
			return GetPyNone();
		}

		mvDataGrid* atable = static_cast<mvDataGrid*>(item.get());
		atable->deleteColumn(column);

		return GetPyNone();
	}

	PyObject* mvDataGrid::add_grid_row(PyObject* self, PyObject* args, PyObject* kwargs)
	{
		const char* grid;
		PyObject* row;

		if (!(mvApp::GetApp()->getParsers())["add_grid_row"].parse(args, kwargs, __FUNCTION__, &grid, &row))
			return GetPyNone();

		std::lock_guard<std::mutex> lk(mvApp::GetApp()->getMutex());
		auto item = mvApp::GetApp()->getItemRegistry().getItem(grid);
		if (item == nullptr)
		{
			std::string message = grid;
			ThrowPythonException(message + " grid does not exist.");
			return GetPyNone();
		}

		if (item->getType() != mvAppItemType::mvDataGrid)
		{
			std::string message = grid;
			ThrowPythonException(message + " is not a grid.");
			return GetPyNone();
		}

		auto prow = ToStringVect(row);
		mvDataGrid* atable = static_cast<mvDataGrid*>(item.get());
		if (atable->getColumnCount() == 0)
		{
			std::vector<std::string> headers;
			for (size_t i = 0; i < prow.size(); i++)
				headers.emplace_back("Header" + std::to_string(i));
			atable->addHeaders(headers);
		}
		atable->addRow(prow);

		return GetPyNone();
	}

	PyObject* mvDataGrid::insert_grid_row(PyObject* self, PyObject* args, PyObject* kwargs)
	{
		const char* grid;
		int row_index;
		PyObject* row;

		if (!(mvApp::GetApp()->getParsers())["insert_grid_row"].parse(args, kwargs, __FUNCTION__, &grid, &row_index, &row))
			return GetPyNone();

		std::lock_guard<std::mutex> lk(mvApp::GetApp()->getMutex());
		auto item = mvApp::GetApp()->getItemRegistry().getItem(grid);
		if (item == nullptr)
		{
			std::string message = grid;
			ThrowPythonException(message + " grid does not exist.");
			return GetPyNone();
		}

		if (item->getType() != mvAppItemType::mvDataGrid)
		{
			std::string message = grid;
			ThrowPythonException(message + " is not a grid.");
			return GetPyNone();
		}

		auto prow = ToStringVect(row);
		mvDataGrid* atable = static_cast<mvDataGrid*>(item.get());
		if (atable->getColumnCount() == 0)
		{
			std::vector<std::string> headers;
			for (size_t i = 0; i < prow.size(); i++)
				headers.emplace_back("Header" + std::to_string(i));
			atable->addHeaders(headers);
		}
		atable->insertRow(row_index, prow);

		return GetPyNone();
	}

	PyObject* mvDataGrid::delete_grid_row(PyObject* self, PyObject* args, PyObject* kwargs)
	{
		const char* grid;
		int row;

		if (!(mvApp::GetApp()->getParsers())["delete_grid_row"].parse(args, kwargs, __FUNCTION__, &grid, &row))
			return GetPyNone();

		std::lock_guard<std::mutex> lk(mvApp::GetApp()->getMutex());
		auto item = mvApp::GetApp()->getItemRegistry().getItem(grid);
		if (item == nullptr)
		{
			std::string message = grid;
			ThrowPythonException(message + " grid does not exist.");
			return GetPyNone();
		}

		if (item->getType() != mvAppItemType::mvDataGrid)
		{
			std::string message = grid;
			ThrowPythonException(message + " is not a grid.");
			return GetPyNone();
		}

		mvDataGrid* atable = static_cast<mvDataGrid*>(item.get());
		atable->deleteRow(row);

		return GetPyNone();
	}

}
