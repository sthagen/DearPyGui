#pragma once

#include <implot.h>
#include <implot_internal.h>
#include <array>
#include "mvItemRegistry.h"
#include "cpp.hint"

//-----------------------------------------------------------------------------
// mvTypeBases
//
//     - This file contains abstract classes for concrete mvAppItem 
//       implementations which share common underlying data types.
//     
//-----------------------------------------------------------------------------

namespace Marvel {

	//-----------------------------------------------------------------------------
	// mvIntPtrBase
	//-----------------------------------------------------------------------------
	class mvIntPtrBase : public mvAppItem
	{

	public:

		mvIntPtrBase(mvUUID uuid);
		void setDataSource(mvUUID dataSource) override;
		mvValueVariant getValue() override { return m_value; }
		PyObject*      getPyValue() override;
		void           setPyValue(PyObject* value) override;

	protected:

		mvRef<int> m_value = CreateRef<int>(0);
		int  m_disabled_value = 0;
	};

	//-----------------------------------------------------------------------------
	// mvInt4PtrBase
	//-----------------------------------------------------------------------------
	class mvInt4PtrBase : public mvAppItem
	{

	public:

		mvInt4PtrBase(mvUUID uuid);
		void setDataSource(mvUUID dataSource) override;
		mvValueVariant getValue() override { return m_value; }
		PyObject* getPyValue() override;
		void           setPyValue(PyObject* value) override;

	protected:

		mvRef<std::array<int, 4>> m_value = CreateRef<std::array<int, 4>>(std::array<int, 4>{0, 0, 0, 0});
		int  m_disabled_value[4] {};
	};

	//-----------------------------------------------------------------------------
	// mvFloatPtrBase
	//-----------------------------------------------------------------------------
	class mvFloatPtrBase : public mvAppItem
	{

	public:

		mvFloatPtrBase(mvUUID uuid);
		void setDataSource(mvUUID dataSource) override;
		mvValueVariant getValue() override { return m_value; }
		PyObject* getPyValue() override;
		void           setPyValue(PyObject* value) override;

	protected:

		mvRef<float> m_value = CreateRef<float>(0.0f);
		float  m_disabled_value = 0.0f;
	};

	//-----------------------------------------------------------------------------
	// mvDoublePtrBase
	//-----------------------------------------------------------------------------
	class mvDoublePtrBase : public mvAppItem
	{

	public:

		mvDoublePtrBase(mvUUID uuid);
		void setDataSource(mvUUID dataSource) override;
		mvValueVariant getValue() override { return m_value; }
		PyObject* getPyValue() override;
		void           setPyValue(PyObject* value) override;

	protected:

		mvRef<double> m_value = CreateRef<double>(0.0);
		float  m_disabled_value = 0.0;
	};

	//-----------------------------------------------------------------------------
	// mvFloat4PtrBase
	//-----------------------------------------------------------------------------
	class mvFloat4PtrBase : public mvAppItem
	{

	public:

		mvFloat4PtrBase(mvUUID uuid);
		void setDataSource(mvUUID dataSource) override;
		mvValueVariant getValue() override { return m_value; }
		PyObject* getPyValue() override;
		void           setPyValue(PyObject* value) override;

	protected:

		mvRef<std::array<float, 4>> m_value = CreateRef<std::array<float, 4>>(std::array<float, 4>{0.0f, 0.0f, 0.0f, 0.0f});
		float  m_disabled_value[4] {};
	};

	//-----------------------------------------------------------------------------
	// mvDouble4PtrBase
	//-----------------------------------------------------------------------------
	class mvDouble4PtrBase : public mvAppItem
	{

	public:

		mvDouble4PtrBase(mvUUID uuid);
		void setDataSource(mvUUID dataSource) override;
		mvValueVariant getValue() override { return m_value; }
		PyObject* getPyValue() override;
		void           setPyValue(PyObject* value) override;

	protected:

		mvRef<std::array<double, 4>> m_value = CreateRef<std::array<double, 4>>(std::array<double, 4>{0.0, 0.0, 0.0, 0.0});
		double  m_disabled_value[4]{};
	};

	//-----------------------------------------------------------------------------
	// mvColorPtrBase
	//-----------------------------------------------------------------------------
	class mvColorPtrBase : public mvAppItem
	{

	public:

		mvColorPtrBase(mvUUID uuid);
		void setDataSource(mvUUID dataSource) override;
		mvValueVariant getValue() override { return m_value; }
		PyObject* getPyValue() override;
		void           setPyValue(PyObject* value) override;

	protected:

		mvRef<std::array<float, 4>> m_value = CreateRef<std::array<float, 4>>(std::array<float, 4>{0.0f, 0.0f, 0.0f, 1.0f});
		float  m_disabled_value[4]{};
	};

	//-----------------------------------------------------------------------------
	// mvBoolPtrBase
	//-----------------------------------------------------------------------------
	class mvBoolPtrBase : public mvAppItem
	{

	public:

		mvBoolPtrBase(mvUUID uuid);
		void setDataSource(mvUUID dataSource) override;
		mvValueVariant getValue() override { return m_value; }
		PyObject* getPyValue() override;
		void           setPyValue(PyObject* value) override;

	protected:

		mvRef<bool> m_value = CreateRef<bool>(false);
		bool  m_disabled_value = false;
	};

	//-----------------------------------------------------------------------------
	// mvStringPtrBase
	//-----------------------------------------------------------------------------
	class mvStringPtrBase : public mvAppItem
	{

	public:

		mvStringPtrBase(mvUUID uuid);
		void setDataSource(mvUUID dataSource) override;
		mvValueVariant getValue() override { return m_value; }
		PyObject* getPyValue() override;
		void      setPyValue(PyObject* value) override;

	protected:

		mvRef<std::string> m_value = CreateRef<std::string>("");
		std::string  m_disabled_value = "";
	};

	//-----------------------------------------------------------------------------
	// mvUUIDPtrBase
	//-----------------------------------------------------------------------------
	class mvUUIDPtrBase : public mvAppItem
	{

	public:

		mvUUIDPtrBase(mvUUID uuid);
		void setDataSource(mvUUID dataSource) override;
		mvValueVariant getValue() override { return m_value; }
		PyObject* getPyValue() override;
		void      setPyValue(PyObject* value) override;

	protected:

		mvRef<mvUUID> m_value = CreateRef<mvUUID>(0);
		mvUUID  m_disabled_value = 0;
	};

	//-----------------------------------------------------------------------------
	// mvTimePtrBase
	//-----------------------------------------------------------------------------
	class mvTimePtrBase : public mvAppItem
	{

	public:

		mvTimePtrBase(mvUUID uuid);
		mvValueVariant getValue() override { return m_value; }
		PyObject* getPyValue() override;
		void           setPyValue(PyObject* value) override;

	protected:

		mvRef<tm>         m_value = CreateRef<tm>();
		mvRef<ImPlotTime> m_imvalue = CreateRef<ImPlotTime>();
	};

	//-----------------------------------------------------------------------------
	// mvFloatVectPtrBase
	//-----------------------------------------------------------------------------
	class mvFloatVectPtrBase : public mvAppItem
	{

	public:

		mvFloatVectPtrBase(mvUUID uuid);
		void setDataSource(mvUUID dataSource) override;
		mvValueVariant getValue() override { return m_value; }
		PyObject* getPyValue() override;
		void           setPyValue(PyObject* value) override;

	protected:

		mvRef<std::vector<float>> m_value = CreateRef<std::vector<float>>(std::vector<float>{0.0f});
	};

	//-----------------------------------------------------------------------------
	// mvSeriesBase
	//-----------------------------------------------------------------------------
	class mvSeriesBase : public mvAppItem
	{

	public:

		mvSeriesBase(mvUUID uuid);
		void setDataSource(mvUUID dataSource) override;
		mvValueVariant getValue() override { return m_value; }
		PyObject* getPyValue() override;
		void setPyValue(PyObject* value) override;

		const std::pair<double, double>& getMaxMin(int i) const;
		bool doesSeriesContributeToBounds() const { return m_contributeToBounds; }

	protected:

		void calculateMaxMins();
		void resetMaxMins();

	protected:

		mvRef<std::vector<std::vector<double>>> m_value = CreateRef<std::vector<std::vector<double>>>(
			std::vector<std::vector<double>>{ std::vector<double>{},
			std::vector<double>{},
			std::vector<double>{},
			std::vector<double>{},
			std::vector<double>{} });
		std::vector<std::pair<double, double>>   m_maxMins;
		bool                                   m_contributeToBounds = false;
	};

}