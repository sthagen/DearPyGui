#include "mvDrawTextCmd.h"
#include "mvApp.h"

namespace Marvel {

	mvDrawTextCmd::mvDrawTextCmd(const mvVec2& pos, std::string  text, const mvColor& color, int size)
		:
		m_pos(pos),
		m_text(std::move(text)),
		m_color(color),
		m_size(size)
	{
	}

	void mvDrawTextCmd::draw(ImDrawList* drawlist, float x, float y)
	{
		mvVec2 start = {x, y};
		drawlist->AddText(ImGui::GetFont(), (float)m_size, m_pos + start, m_color, m_text.c_str());
	}

	void mvDrawTextCmd::setConfigDict(PyObject* dict)
	{
		if (dict == nullptr)
			return;
		 

		if (PyObject* item = PyDict_GetItemString(dict, "text")) m_text = ToString(item);
		if (PyObject* item = PyDict_GetItemString(dict, "pos")) m_pos = ToVec2(item);
		if (PyObject* item = PyDict_GetItemString(dict, "color")) m_color = ToColor(item);
		if (PyObject* item = PyDict_GetItemString(dict, "size")) m_size = ToInt(item);

	}

	void mvDrawTextCmd::getConfigDict(PyObject* dict)
	{
		if (dict == nullptr)
			return;
		 
		PyDict_SetItemString(dict, "text", ToPyString(m_text));
		PyDict_SetItemString(dict, "pos", ToPyPair(m_pos.x, m_pos.y));
		PyDict_SetItemString(dict, "color", ToPyColor(m_color));
		PyDict_SetItemString(dict, "size", ToPyInt(m_size));
	}

	PyObject* draw_text(PyObject* self, PyObject* args, PyObject* kwargs)
	{
		const char* drawing;
		const char* text;
		PyObject* pos;
		int size = 10;
		PyObject* color = nullptr;
		const char* tag = "";

		if (!(*mvApp::GetApp()->getParsers())["draw_text"].parse(args, kwargs, __FUNCTION__, &drawing, &pos, &text, &color, &size, &tag))
			return GetPyNone();

		mvVec2 mpos = ToVec2(pos);
		mvColor mcolor = ToColor(color);

		auto cmd = CreateRef<mvDrawTextCmd>(mpos, text, mcolor, size);
		cmd->tag = tag;

		std::lock_guard<std::mutex> lk(mvApp::GetApp()->GetApp()->getMutex());
		mvRef<mvDrawList> drawlist = GetDrawListFromTarget(drawing);
		if (drawlist)
			drawlist->addCommand(cmd);

		return GetPyNone();
	}
}