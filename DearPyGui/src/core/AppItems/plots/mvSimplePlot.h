#pragma once

#include <utility>
#include "mvTypeBases.h"

namespace Marvel{

	class mvSimplePlot : public mvFloatVectPtrBase
	{
		MV_APPITEM_TYPE(mvAppItemType::SimplePlot, mvSimplePlot, "add_simple_plot")

		MV_CREATE_THEME_CONSTANT(mvAppItemType::SimplePlot, mvThemeCol_SimplePlot_Text					,  0L, 0L);
		MV_CREATE_THEME_CONSTANT(mvAppItemType::SimplePlot, mvThemeCol_SimplePlot_Border				,  5L, 0L);
		MV_CREATE_THEME_CONSTANT(mvAppItemType::SimplePlot, mvThemeCol_SimplePlot_BorderShadow			,  6L, 0L);
		MV_CREATE_THEME_CONSTANT(mvAppItemType::SimplePlot, mvThemeCol_SimplePlot_Bg					,  7L, 0L);
		MV_CREATE_THEME_CONSTANT(mvAppItemType::SimplePlot, mvThemeCol_SimplePlot_PopupBg				,  4L, 0L);
		MV_CREATE_THEME_CONSTANT(mvAppItemType::SimplePlot, mvThemeCol_SimplePlot_Lines					, 40L, 0L);
		MV_CREATE_THEME_CONSTANT(mvAppItemType::SimplePlot, mvThemeCol_SimplePlot_LinesHovered			, 41L, 0L);
		MV_CREATE_THEME_CONSTANT(mvAppItemType::SimplePlot, mvThemeCol_SimplePlot_Histogram				, 42L, 0L);
		MV_CREATE_THEME_CONSTANT(mvAppItemType::SimplePlot, mvThemeCol_SimplePlot_HistogramHovered		, 43L, 0L);
		MV_CREATE_THEME_CONSTANT(mvAppItemType::SimplePlot, mvThemeStyle_SimplePlot_Rounding			, 11L, 0L);
		MV_CREATE_THEME_CONSTANT(mvAppItemType::SimplePlot, mvThemeStyle_SimplePlot_BorderSize			, 12L, 0L);
		MV_CREATE_THEME_CONSTANT(mvAppItemType::SimplePlot, mvThemeStyle_SimplePlot_PaddingX			, 10L, 0L);
		MV_CREATE_THEME_CONSTANT(mvAppItemType::SimplePlot, mvThemeStyle_SimplePlot_PaddingY			, 10L, 1L);
		MV_CREATE_THEME_CONSTANT(mvAppItemType::SimplePlot, mvThemeStyle_SimplePlot_InnerItemSpacingX	, 14L, 0L);
		MV_CREATE_THEME_CONSTANT(mvAppItemType::SimplePlot, mvThemeStyle_SimplePlot_InnerItemSpacingY	, 14L, 1L);

		MV_START_COLOR_CONSTANTS
			MV_CREATE_CONSTANT_PAIR(mvThemeCol_SimplePlot_Text, mvColor(255, 255, 255, 255)),
			MV_CREATE_CONSTANT_PAIR(mvThemeCol_SimplePlot_Border, mvColor(255, 255, 255, 255)),
			MV_CREATE_CONSTANT_PAIR(mvThemeCol_SimplePlot_BorderShadow, mvColor(255, 255, 255, 255)),
			MV_CREATE_CONSTANT_PAIR(mvThemeCol_SimplePlot_Bg, mvColor(255, 255, 255, 255)),
			MV_CREATE_CONSTANT_PAIR(mvThemeCol_SimplePlot_PopupBg, mvColor(255, 255, 255, 255)),
			MV_CREATE_CONSTANT_PAIR(mvThemeCol_SimplePlot_Lines, mvColor(255, 255, 255, 255)),
			MV_CREATE_CONSTANT_PAIR(mvThemeCol_SimplePlot_LinesHovered, mvColor(255, 255, 255, 255)),
			MV_CREATE_CONSTANT_PAIR(mvThemeCol_SimplePlot_Histogram, mvColor(255, 255, 255, 255)),
			MV_CREATE_CONSTANT_PAIR(mvThemeCol_SimplePlot_HistogramHovered, mvColor(255, 255, 255, 255)),
		MV_END_COLOR_CONSTANTS

		MV_START_STYLE_CONSTANTS
			MV_CREATE_CONSTANT_TUPLE(mvThemeStyle_SimplePlot_BorderSize			, 0,  1),
			MV_CREATE_CONSTANT_TUPLE(mvThemeStyle_SimplePlot_Rounding			, 0, 12),
			MV_CREATE_CONSTANT_TUPLE(mvThemeStyle_SimplePlot_PaddingX			, 0, 20),
			MV_CREATE_CONSTANT_TUPLE(mvThemeStyle_SimplePlot_PaddingY			, 0, 20),
			MV_CREATE_CONSTANT_TUPLE(mvThemeStyle_SimplePlot_InnerItemSpacingX	, 0, 20),
			MV_CREATE_CONSTANT_TUPLE(mvThemeStyle_SimplePlot_InnerItemSpacingY	, 0, 20),
		MV_END_STYLE_CONSTANTS

	public:
		mvSimplePlot(const std::string& name, const std::vector<float>& value)
			: mvFloatVectPtrBase(name, value) 
		{

			m_description.ignoreSizeUpdate = true;

			if (!value.empty())
			{
				m_max = m_value->data()[0];
				m_min = m_value->data()[0];

				for (auto& item : *m_value)
				{
					if (item > m_max)
						m_max = item;
					if (item < m_min)
						m_min = item;
				}
			}
		}

		void draw() override
		{
			auto styleManager = m_styleManager.getScopedStyleManager();
			ImGui::PushID(this);
			mvImGuiThemeScope scope(this);

			if(m_histogram)
				ImGui::PlotHistogram(m_label.c_str(), m_value->data(), (int)m_value->size(), 0, m_overlay.c_str(), 
					m_min, m_max, ImVec2((float)m_core_config.width, (float)m_core_config.height));
			else
			ImGui::PlotLines(m_label.c_str(), m_value->data(), (int)m_value->size(), 0, m_overlay.c_str(),
				m_min, m_max, ImVec2((float)m_core_config.width, (float)m_core_config.height));

			ImGui::PopID();
		}

		void setValue(const std::vector<float>& value)
		{ 
			*m_value = value;
		}
		[[nodiscard]] const std::vector<float>& getValue() const { return *m_value; }

#ifndef MV_CPP

		void setExtraConfigDict(PyObject* dict) override
		{
			if (dict == nullptr)
				return;
			 
			if (PyObject* item = PyDict_GetItemString(dict, "overlay")) m_overlay = ToString(item);
			if (PyObject* item = PyDict_GetItemString(dict, "minscale")) m_min = ToFloat(item);
			if (PyObject* item = PyDict_GetItemString(dict, "maxscale")) m_max = ToFloat(item);
			if (PyObject* item = PyDict_GetItemString(dict, "histogram")) m_histogram = ToBool(item);
		}

		void getExtraConfigDict(PyObject* dict) override
		{
			if (dict == nullptr)
				return;
			 
			PyDict_SetItemString(dict, "overlay", ToPyString(m_overlay));
			PyDict_SetItemString(dict, "minscale", ToPyFloat(m_min));
			PyDict_SetItemString(dict, "maxscale", ToPyFloat(m_max));
			PyDict_SetItemString(dict, "histogram", ToPyBool(m_histogram));
		}

#endif

	private:

		//std::vector<float> m_value;
		std::string        m_overlay;
		float              m_min = 0.0f;
		float              m_max = 0.0f;
		bool               m_histogram = false;

	};

}