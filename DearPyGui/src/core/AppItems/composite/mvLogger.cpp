#include "mvLogger.h"
#include <chrono>
#include "mvInput.h"
#include "mvCore.h"
#include "mvGlobalIntepreterLock.h"
#include "mvItemRegistry.h"
#include "mvFontScope.h"
#include "mvPythonExceptions.h"

typedef std::chrono::high_resolution_clock clock_;
typedef std::chrono::duration<double, std::ratio<1> > second_;

namespace Marvel {

	void mvLoggerItem::InsertParser(std::map<std::string, mvPythonParser>* parsers)
	{
		{
			mvPythonParser parser(mvPyDataType::String);
			mvAppItem::AddCommonArgs(parser);
			parser.removeArg("source");
			parser.removeArg("label");
			parser.removeArg("callback");
			parser.removeArg("callback_data");
			parser.removeArg("enabled");

			parser.addArg<mvPyDataType::Integer>("log_level", mvArgType::KEYWORD_ARG, "1");

			parser.addArg<mvPyDataType::Bool>("autosize_x", mvArgType::KEYWORD_ARG, "False");
			parser.addArg<mvPyDataType::Bool>("autosize_y", mvArgType::KEYWORD_ARG, "False");
			parser.addArg<mvPyDataType::Bool>("copy_button", mvArgType::KEYWORD_ARG, "True", "show copy button");
			parser.addArg<mvPyDataType::Bool>("clear_button", mvArgType::KEYWORD_ARG, "True", "show clear butter");
			parser.addArg<mvPyDataType::Bool>("filter", mvArgType::KEYWORD_ARG, "True", "show filter");
			parser.addArg<mvPyDataType::Bool>("auto_scroll", mvArgType::KEYWORD_ARG, "True", "auto scroll");
			parser.addArg<mvPyDataType::Bool>("auto_scroll_button", mvArgType::KEYWORD_ARG, "True", "show auto scroll button");

			parser.finalize();

			parsers->insert({ s_command, parser });
		}

		{
			mvPythonParser parser(mvPyDataType::Integer);
			parser.addArg<mvPyDataType::String>("logger", mvArgType::KEYWORD_ARG, "''", "specific logger");
			parser.finalize();
			parsers->insert({ "get_log_level", parser });
		}

		{
			mvPythonParser parser(mvPyDataType::None);
			parser.addArg<mvPyDataType::String>("logger", mvArgType::KEYWORD_ARG, "''", "specific logger");
			parser.finalize();
			parsers->insert({ "clear_log", parser });
		}

		{
			mvPythonParser parser(mvPyDataType::None);
			parser.addArg<mvPyDataType::Integer>("level", mvArgType::REQUIRED_ARG);
			parser.addArg<mvPyDataType::String>("logger", mvArgType::KEYWORD_ARG, "''", "specific logger");
			parser.finalize();
			parsers->insert({ "set_log_level", parser });
		}

		{
			mvPythonParser parser(mvPyDataType::None);
			parser.addArg<mvPyDataType::Object>("message", mvArgType::REQUIRED_ARG);
			parser.addArg<mvPyDataType::Integer>("level", mvArgType::KEYWORD_ARG, "'TRACE'");
			parser.addArg<mvPyDataType::String>("logger", mvArgType::KEYWORD_ARG, "''", "specific logger");
			parser.finalize();
			parsers->insert({ "log", parser });
		}

		{
			mvPythonParser parser(mvPyDataType::None);
			parser.addArg<mvPyDataType::Object>("message", mvArgType::REQUIRED_ARG);
			parser.addArg<mvPyDataType::String>("logger", mvArgType::KEYWORD_ARG, "''", "specific logger");
			parser.finalize();
			parsers->insert({ "log_debug", parser });
		}

		{
			mvPythonParser parser(mvPyDataType::None);
			parser.addArg<mvPyDataType::Object>("message", mvArgType::REQUIRED_ARG);
			parser.addArg<mvPyDataType::String>("logger", mvArgType::KEYWORD_ARG, "''", "specific logger");
			parser.finalize();
			parsers->insert({ "log_info", parser });
		}

		{
			mvPythonParser parser(mvPyDataType::None);
			parser.addArg<mvPyDataType::Object>("message", mvArgType::REQUIRED_ARG);
			parser.addArg<mvPyDataType::String>("logger", mvArgType::KEYWORD_ARG, "''", "specific logger");
			parser.finalize();
			parsers->insert({ "log_warning", parser });
		}

		{
			mvPythonParser parser(mvPyDataType::None);
			parser.addArg<mvPyDataType::Object>("message", mvArgType::REQUIRED_ARG);
			parser.addArg<mvPyDataType::String>("logger", mvArgType::KEYWORD_ARG, "''", "specific logger");
			parser.finalize();
			parsers->insert({ "log_error", parser });
		}

		{
			mvPythonParser parser(mvPyDataType::None);
			parser.finalize();
			parsers->insert({ "show_logger", parser });
		}

		{
			mvPythonParser parser(mvPyDataType::None);
			parser.addArg<mvPyDataType::String>("title", mvArgType::REQUIRED_ARG);
			parser.finalize();
			parsers->insert({ "set_logger_window_title", parser });
		}

	}

#if defined (_WIN32)
	std::chrono::steady_clock::time_point mvLoggerItem::s_start = clock_::now();
#elif defined(__APPLE__)
	std::chrono::steady_clock::time_point mvLoggerItem::s_start = clock_::now();
#else
	std::chrono::system_clock::time_point mvLoggerItem::s_start = clock_::now();
#endif

	void mvLoggerItem::draw(ImDrawList* drawlist, float x, float y)
	{
		mvFontScope fscope(this);

		ImGui::BeginGroup();

		ImGui::PushID(this);
		
		// auto scroll button
		if (m_autoScrollButton)
		{
			ImGui::Checkbox(m_autoScrollButtonName.c_str(), &AutoScroll);
			ImGui::SameLine();
		}

		if (m_clearButton)
		{
			if (ImGui::Button(m_clearButtonName.c_str()))
				ClearLog();
			ImGui::SameLine();
		}

		if (m_copyButton)
		{
			if (ImGui::Button(m_copyButtonName.c_str()))
				ImGui::LogToClipboard();
			ImGui::SameLine();
		}

		if (m_filter)
		{
			ImGui::NewLine();
			Filter.Draw("Filter", m_width-100.0f);
		}

		ImGui::BeginChild(m_name.c_str(), ImVec2(m_autosize_x ? 0 : (float)m_width, m_autosize_y ? 0 : (float)m_height), true, ImGuiWindowFlags_AlwaysHorizontalScrollbar);

		ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0, 0));
		const char* buf = Buf.begin();
		const char* buf_end = Buf.end();
		if (Filter.IsActive())
		{
			// In this example we don't use the clipper when Filter is enabled.
			// This is because we don't have a random access on the result on our filter.
			// A real application processing logs with ten of thousands of entries may want to store the result of search/filter.
			// especially if the filtering function is not trivial (e.g. reg-exp).
			for (int line_no = 0; line_no < LineOffsets.Size; line_no++)
			{
				const char* line_start = buf + LineOffsets[line_no];
				const char* line_end = (line_no + 1 < LineOffsets.Size) ? (buf + LineOffsets[line_no + 1] - 1) : buf_end;
				if (Filter.PassFilter(line_start, line_end))
					ImGui::TextUnformatted(line_start, line_end);
			}
		}
		else
		{


			// The simplest and easy way to display the entire buffer:
			//   ImGui::TextUnformatted(buf_begin, buf_end);
			// And it'll just work. TextUnformatted() has specialization for large blob of text and will fast-forward to skip non-visible lines.
			// Here we instead demonstrate using the clipper to only process lines that are within the visible area.
			// If you have tens of thousands of items and their processing cost is non-negligible, coarse clipping them on your side is recommended.
			// Using ImGuiListClipper requires A) random access into your data, and B) items all being the  same height,
			// both of which we can handle since we an array pointing to the beginning of each line of text.
			// When using the filter (in the block of code above) we don't have random access into the data to display anymore, which is why we don't use the clipper.
			// Storing or skimming through the search result would make it possible (and would be recommended if you want to search through tens of thousands of entries)
			ImGuiListClipper clipper;
			clipper.Begin(LineOffsets.Size);
			while (clipper.Step())
			{
				for (int line_no = clipper.DisplayStart; line_no < clipper.DisplayEnd; line_no++)
				{

					const char* line_start = buf + LineOffsets[line_no];
					const char* line_end = (line_no + 1 < LineOffsets.Size) ? (buf + LineOffsets[line_no + 1] - 1) : buf_end;

					std::string mystring = line_start;

					std::string splitstring = mystring.substr(0, 20);

					if (strstr(splitstring.c_str(), "[ERROR]"))
						ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.0f, 0.0f, 0.0f, 1.0f));

					else if (strstr(splitstring.c_str(), "[WARNING]"))
						ImGui::PushStyleColor(ImGuiCol_Text, ImGui::GetStyleColorVec4(ImGuiCol_PlotHistogramHovered));

					else if (strstr(splitstring.c_str(), "[TRACE]"))
						ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.0f, 1.0f, 0.0f, 1.0f));

					else if (strstr(splitstring.c_str(), "[INFO]"))
						ImGui::PushStyleColor(ImGuiCol_Text, ImGui::GetStyleColorVec4(ImGuiCol_Text));

					else if (strstr(splitstring.c_str(), "[DEBUG]"))

						ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.25f, 0.50f, 1.0f, 1.0f));

					else
						ImGui::PushStyleColor(ImGuiCol_Text, ImGui::GetStyleColorVec4(ImGuiCol_Text));

					ImGui::TextUnformatted(line_start, line_end);
					ImGui::PopStyleColor();
				}
			}
			clipper.End();
		}
		ImGui::PopStyleVar();

		if (AutoScroll && ImGui::GetScrollY() >= ImGui::GetScrollMaxY())
			ImGui::SetScrollHereY(0.0f);

		if (ImGui::IsWindowFocused())
		{

			float titleBarHeight = ImGui::GetStyle().FramePadding.y * 2 + ImGui::GetFontSize();

			// update mouse
			ImVec2 mousePos = ImGui::GetMousePos();
			mvInput::setGlobalMousePosition(mousePos.x, mousePos.y);
			float x = mousePos.x - ImGui::GetWindowPos().x;
			float y = mousePos.y - ImGui::GetWindowPos().y - titleBarHeight;
			mvInput::setMousePosition(x, y);

			if (mvApp::GetApp()->getItemRegistry().getActiveWindow() != m_name)
				mvEventBus::Publish(mvEVT_CATEGORY_ITEM, mvEVT_ACTIVE_WINDOW, { CreateEventArgument("WINDOW", m_name) });


		}

		m_width = (int)ImGui::GetWindowWidth();
		m_height = (int)ImGui::GetWindowHeight();

		ImGui::EndChild();
		ImGui::PopID();
		ImGui::EndGroup();

	}

	void mvLoggerItem::AddLog(const char* fmt, ...)
	{
		static std::mutex mutex;

		std::lock_guard<std::mutex> lock(mutex);

		int old_size = Buf.size();
		va_list args;
		va_start(args, fmt);
		Buf.appendfv(fmt, args);
		va_end(args);
		for (int new_size = Buf.size(); old_size < new_size; old_size++)
			if (Buf[old_size] == '\n')
				LineOffsets.push_back(old_size + 1);
	}

	void mvLoggerItem::Log(const std::string& text, const std::string& level)
	{
		if (m_loglevel < 1)
		{
			AddLog("[%0.2f] [%1s]  %2s\n", std::chrono::duration_cast<second_>(clock_::now() - s_start).count(),
				level.c_str(), text.c_str());
		}
	}

	void mvLoggerItem::LogDebug(const std::string& text)
	{
		if (m_loglevel < 2)
			AddLog("[%0.2f] [DEBUG]  %1s\n", std::chrono::duration_cast<second_>(clock_::now() - s_start).count(),
				text.c_str());
	}

	void mvLoggerItem::LogInfo(const std::string& text)
	{
		if (m_loglevel < 3)
			AddLog("[%0.2f] [INFO]  %1s\n", std::chrono::duration_cast<second_>(clock_::now() - s_start).count(),
				text.c_str());
	}

	void mvLoggerItem::LogWarning(const std::string& text)
	{
		if (m_loglevel < 4)
			AddLog("[%0.2f] [WARNING]  %1s\n", std::chrono::duration_cast<second_>(clock_::now() - s_start).count(),
				text.c_str());
	}

	void mvLoggerItem::LogError(const std::string& text)
	{
		if (m_loglevel < 5)
			AddLog("[%0.2f] [ERROR]  %1s\n", std::chrono::duration_cast<second_>(clock_::now() - s_start).count(),
				text.c_str());
	}

	void mvLoggerItem::ClearLog()
	{
		Buf.clear();
		LineOffsets.clear();
		LineOffsets.push_back(0);
	}

	void mvLoggerItem::handleSpecificKeywordArgs(PyObject* dict)
	{
		if (dict == nullptr)
			return;
		 
		if (PyObject* item = PyDict_GetItemString(dict, "auto_scroll")) AutoScroll = ToBool(item);
		if (PyObject* item = PyDict_GetItemString(dict, "auto_scroll_button")) m_autoScrollButton = ToBool(item);
		if (PyObject* item = PyDict_GetItemString(dict, "clear_button")) m_clearButton = ToBool(item);
		if (PyObject* item = PyDict_GetItemString(dict, "copy_button")) m_copyButton = ToBool(item);
		if (PyObject* item = PyDict_GetItemString(dict, "filter")) m_filter = ToBool(item);
		if (PyObject* item = PyDict_GetItemString(dict, "autosize_x")) m_autosize_x = ToBool(item);
		if (PyObject* item = PyDict_GetItemString(dict, "autosize_y")) m_autosize_y = ToBool(item);

		if (PyObject* item = PyDict_GetItemString(dict, "log_level"))
		{
			m_loglevel = ToInt(item);
			DecodelibID(m_loglevel, &m_loglevel);
		}
		

	}

	void mvLoggerItem::getSpecificConfiguration(PyObject* dict)
	{
		if (dict == nullptr)
			return;
		 

		PyDict_SetItemString(dict, "log_level", ToPyInt(MV_ENCODE_CONSTANT(m_loglevel, 0)));
		PyDict_SetItemString(dict, "auto_scroll", ToPyBool(AutoScroll));
		PyDict_SetItemString(dict, "auto_scroll_button", ToPyBool(m_autoScrollButton));
		PyDict_SetItemString(dict, "clear_button", ToPyBool(m_clearButton));
		PyDict_SetItemString(dict, "copy_button", ToPyBool(m_copyButton));
		PyDict_SetItemString(dict, "filter", ToPyBool(m_filter));
		PyDict_SetItemString(dict, "autosize_x", ToPyBool(m_autosize_x));
		PyDict_SetItemString(dict, "autosize_y", ToPyBool(m_autosize_y));
	}

	PyObject* mvLoggerItem::get_log_level(PyObject* self, PyObject* args, PyObject* kwargs)
	{
		const char* logger = "";

		if (!(mvApp::GetApp()->getParsers())["get_log_level"].parse(args, kwargs, __FUNCTION__, &logger))
			return GetPyNone();


		if (!std::string(logger).empty())
		{
			auto loggeritem = mvApp::GetApp()->getItemRegistry().getItem(logger);
			if (loggeritem == nullptr)
			{
				mvThrowPythonError(1000, std::string(logger) + " logger does not exist.");
				return ToPyInt(-1);
			}

			if (loggeritem->getType() != mvAppItemType::mvLoggerItem)
			{
				mvThrowPythonError(1000, std::string(logger) + " is not a logger.");
				return ToPyInt(-1);
			}

			auto loggerwidget = static_cast<mvLoggerItem*>(loggeritem.get());
			return ToPyInt(loggerwidget->getLogLevel());

		}
		else
			return ToPyInt((int)mvAppLog::getLogLevel());

	}

	PyObject* mvLoggerItem::set_log_level(PyObject* self, PyObject* args, PyObject* kwargs)
	{
		int level;
		const char* logger = "";
		if (!(mvApp::GetApp()->getParsers())["set_log_level"].parse(args, kwargs, __FUNCTION__,
			&level, &logger))
			return GetPyNone();


		if (!std::string(logger).empty())
		{
			auto loggeritem = mvApp::GetApp()->getItemRegistry().getItem(logger);
			if (loggeritem == nullptr)
			{
				mvThrowPythonError(1000, std::string(logger) + " logger does not exist.");
				return GetPyNone();
			}

			if (loggeritem->getType() != mvAppItemType::mvLoggerItem)
			{
				mvThrowPythonError(1000, std::string(logger) + " is not a logger.");
				return GetPyNone();
			}

			auto loggerwidget = static_cast<mvLoggerItem*>(loggeritem.get());
			loggerwidget->setLogLevel(level);

		}
		else
			mvAppLog::setLogLevel(level);

		return GetPyNone();
	}

	PyObject* mvLoggerItem::log(PyObject* self, PyObject* args, PyObject* kwargs)
	{
		PyObject* message;
		const char* level = "TRACE";
		const char* logger = "";
		if (!(mvApp::GetApp()->getParsers())["log"].parse(args, kwargs, __FUNCTION__, &message, &level, &logger))
			return GetPyNone();

		std::string cmessage = ToString(message);

		if (!std::string(logger).empty())
		{
			auto loggeritem = mvApp::GetApp()->getItemRegistry().getItem(logger);
			if (loggeritem == nullptr)
			{
				mvThrowPythonError(1000, std::string(logger) + " logger does not exist.");
				return GetPyNone();
			}

			if (loggeritem->getType() != mvAppItemType::mvLoggerItem)
			{
				mvThrowPythonError(1000, std::string(logger) + " is not a logger.");
				return GetPyNone();
			}

			auto loggerwidget = static_cast<mvLoggerItem*>(loggeritem.get());
			loggerwidget->Log(cmessage, std::string(level));

		}
		else
			mvAppLog::Log(cmessage, std::string(level));

		return GetPyNone();
	}

	PyObject* mvLoggerItem::log_debug(PyObject* self, PyObject* args, PyObject* kwargs)
	{
		PyObject* message;
		const char* logger = "";

		if (!(mvApp::GetApp()->getParsers())["log_debug"].parse(args, kwargs, __FUNCTION__, &message, &logger))
			return GetPyNone();

		std::string cmessage = ToString(message);

		if (!std::string(logger).empty())
		{
			auto loggeritem = mvApp::GetApp()->getItemRegistry().getItem(logger);
			if (loggeritem == nullptr)
			{
				mvThrowPythonError(1000, std::string(logger) + " logger does not exist.");
				return GetPyNone();
			}

			if (loggeritem->getType() != mvAppItemType::mvLoggerItem)
			{
				mvThrowPythonError(1000, std::string(logger) + " is not a logger.");
				return GetPyNone();
			}

			auto loggerwidget = static_cast<mvLoggerItem*>(loggeritem.get());
			loggerwidget->LogDebug(cmessage);

		}
		else
			mvAppLog::LogDebug(cmessage);

		return GetPyNone();
	}

	PyObject* mvLoggerItem::log_info(PyObject* self, PyObject* args, PyObject* kwargs)
	{
		PyObject* message;
		const char* logger = "";

		if (!(mvApp::GetApp()->getParsers())["log_info"].parse(args, kwargs, __FUNCTION__, &message, &logger))
			return GetPyNone();

		std::string cmessage = ToString(message);

		if (!std::string(logger).empty())
		{
			auto loggeritem = mvApp::GetApp()->getItemRegistry().getItem(logger);
			if (loggeritem == nullptr)
			{
				mvThrowPythonError(1000, std::string(logger) + " logger does not exist.");
				return GetPyNone();
			}

			if (loggeritem->getType() != mvAppItemType::mvLoggerItem)
			{
				mvThrowPythonError(1000, std::string(logger) + " is not a logger.");
				return GetPyNone();
			}

			auto loggerwidget = static_cast<mvLoggerItem*>(loggeritem.get());
			loggerwidget->LogInfo(cmessage);

		}
		else
			mvAppLog::LogInfo(cmessage);

		return GetPyNone();
	}

	PyObject* mvLoggerItem::log_warning(PyObject* self, PyObject* args, PyObject* kwargs)
	{
		PyObject* message;
		const char* logger = "";

		if (!(mvApp::GetApp()->getParsers())["log_warning"].parse(args, kwargs, __FUNCTION__, &message, &logger))
			return GetPyNone();

		std::string cmessage = ToString(message);

		if (!std::string(logger).empty())
		{
			auto loggeritem = mvApp::GetApp()->getItemRegistry().getItem(logger);
			if (loggeritem == nullptr)
			{
				mvThrowPythonError(1000, std::string(logger) + " logger does not exist.");
				return GetPyNone();
			}

			if (loggeritem->getType() != mvAppItemType::mvLoggerItem)
			{
				mvThrowPythonError(1000, std::string(logger) + " is not a logger.");
				return GetPyNone();
			}

			auto loggerwidget = static_cast<mvLoggerItem*>(loggeritem.get());
			loggerwidget->LogWarning(cmessage);

		}
		else
			mvAppLog::LogWarning(cmessage);
		return GetPyNone();
	}

	PyObject* mvLoggerItem::log_error(PyObject* self, PyObject* args, PyObject* kwargs)
	{
		PyObject* message;
		const char* logger = "";

		if (!(mvApp::GetApp()->getParsers())["log_error"].parse(args, kwargs, __FUNCTION__, &message, &logger))
			return GetPyNone();

		std::string cmessage = ToString(message);
		if (!std::string(logger).empty())
		{
			auto loggeritem = mvApp::GetApp()->getItemRegistry().getItem(logger);
			if (loggeritem == nullptr)
			{
				mvThrowPythonError(1000, std::string(logger) + " logger does not exist.");
				return GetPyNone();
			}

			if (loggeritem->getType() != mvAppItemType::mvLoggerItem)
			{
				mvThrowPythonError(1000, std::string(logger) + " is not a logger.");
				return GetPyNone();
			}

			auto loggerwidget = static_cast<mvLoggerItem*>(loggeritem.get());
			loggerwidget->LogError(cmessage);

		}
		else
			mvAppLog::LogError(cmessage);
		return GetPyNone();
	}

	PyObject* mvLoggerItem::clear_log(PyObject* self, PyObject* args, PyObject* kwargs)
	{
		const char* logger = "";

		if (!(mvApp::GetApp()->getParsers())["clear_log"].parse(args, kwargs, __FUNCTION__, &logger))
			return GetPyNone();

		if (!std::string(logger).empty())
		{
			auto loggeritem = mvApp::GetApp()->getItemRegistry().getItem(logger);
			if (loggeritem == nullptr)
			{
				mvThrowPythonError(1000, std::string(logger) + " logger does not exist.");
				return GetPyNone();
			}

			if (loggeritem->getType() != mvAppItemType::mvLoggerItem)
			{
				mvThrowPythonError(1000, std::string(logger) + " is not a logger.");
				return GetPyNone();
			}

			auto loggerwidget = static_cast<mvLoggerItem*>(loggeritem.get());
			loggerwidget->ClearLog();

		}
		else
			mvAppLog::ClearLog();

		return GetPyNone();
	}

	PyObject* mvLoggerItem::show_logger(PyObject* self, PyObject* args)
	{
		std::lock_guard<std::mutex> lk(mvApp::GetApp()->getMutex());
		mvAppLog::Show();
		return GetPyNone();
	}

	PyObject* mvLoggerItem::set_logger_window_title(PyObject* self, PyObject* args, PyObject* kwargs)
	{
		const char* title;

		if (!(mvApp::GetApp()->getParsers())["set_logger_window_title"].parse(args, kwargs, __FUNCTION__,
			&title))
			return GetPyNone();

		std::lock_guard<std::mutex> lk(mvApp::GetApp()->getMutex());
		mvAppLog::setTitle(title);

		return GetPyNone();
	}

}