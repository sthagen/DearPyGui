#pragma once

#include "mvDrawCmd.h"

namespace Marvel {

	PyObject* draw_triangle(PyObject* self, PyObject* args, PyObject* kwargs);

	class mvDrawTriangleCmd : public mvDrawCmd
	{

	public:

		MV_DRAWCMD_TYPE(mvDrawCmdType::DrawTriangle)

		mvDrawTriangleCmd(const mvVec2& p1, const mvVec2& p2, const mvVec2& p3,
			const mvColor& color, float thickness, const mvColor& fill);

		void draw         (ImDrawList* drawlist, float x, float y) override;
		void setConfigDict(PyObject* dict)                         override;
		void getConfigDict(PyObject* dict)                         override;

	private:

		mvVec2  m_p1;
		mvVec2  m_p2;
		mvVec2  m_p3;
		mvColor m_color;
		mvColor m_fill;
		float   m_thickness;

	};

}