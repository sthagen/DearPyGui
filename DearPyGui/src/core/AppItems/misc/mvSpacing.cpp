#include "mvSpacing.h"
#include "mvItemRegistry.h"

namespace Marvel {

	void mvSpacing::InsertParser(std::map<std::string, mvPythonParser>* parsers)
	{

		mvPythonParser parser(mvPyDataType::String);
		mvAppItem::AddCommonArgs(parser);
		parser.removeArg("source");
		parser.removeArg("width");
		parser.removeArg("height");
		parser.removeArg("label");
		parser.removeArg("callback");
		parser.removeArg("callback_data");
		parser.removeArg("enabled");

		parser.addArg<mvPyDataType::Integer>("count", mvArgType::KEYWORD_ARG, "1", "A cardinal direction");

		parser.finalize();

		parsers->insert({ s_command, parser });
	}


	mvSpacing::mvSpacing(const std::string& name)
		: mvIntPtrBase(name)
	{
	}

	void mvSpacing::draw(ImDrawList* drawlist, float x, float y)
	{
		for (int i = 0; i < *m_value; i++)
			ImGui::Spacing();
	}

}