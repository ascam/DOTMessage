#include <memory>

#include "mockvariableobject.hpp"
#include "utils/macsalogger.hpp"
#include "gtest/gtest.h"

using macsa::dot::VariableObject;
using macsa::dot::VariableObjectMock;
using macsa::dot::NObjectType;
using macsa::dot::NDataSourceType;
using macsa::utils::MacsaLogger;
using macsa::utils::NLogLevel;

class VariableObjectUt : public ::testing::Test
{
	public:
		VariableObjectUt() :
			_obj("TestText", NObjectType::kText)
		{
			// initialization code here
			MacsaLogger::SetCurrentLevel(NLogLevel::kNoLog);
		}

		~VariableObjectUt() {
			// cleanup any pending stuff, but no exceptions allowed
		}

		void SetUp( ) {
			// code here will execute just before the test ensues
		}

		void TearDown( ) {
			// code here will be called just after the test completes
			// ok to through exceptions from here if need be
		}

	protected:
		VariableObjectMock _obj;
};

// Test variable object initialization
TEST_F(VariableObjectUt, InitTextObject_returnNotVariable)
{
	EXPECT_FALSE(_obj.IsVariable());
}

// Test variable object set datasource
TEST_F(VariableObjectUt, SetDataSource_returnIsVariable)
{
	_obj.SetDatasource(NDataSourceType::kUserInput);
	EXPECT_TRUE(_obj.IsVariable());
}

// Test variable object set datasource
TEST_F(VariableObjectUt, SetUserFieldDataSource_returnUserFieldDataSource)
{
	_obj.SetDatasource(NDataSourceType::kUserInput);
	EXPECT_EQ(_obj.GetDatasource()->GetType(), NDataSourceType::kUserInput);
}

// Test variable object set datasource
TEST_F(VariableObjectUt, SetDateTimeDataSource_returnDateTimeDataSource)
{
	_obj.SetDatasource(NDataSourceType::kDateTime);
	EXPECT_EQ(_obj.GetDatasource()->GetType(), NDataSourceType::kDateTime);
}

// Test variable object set datasource
TEST_F(VariableObjectUt, SetCounterDataSource_returnCounterDataSource)
{
	_obj.SetDatasource(NDataSourceType::kCounter);
	EXPECT_EQ(_obj.GetDatasource()->GetType(), NDataSourceType::kCounter);
}

// Test variable object set datasource
TEST_F(VariableObjectUt, SetCompositeDataSource_returnCompositeDataSource)
{
	_obj.SetDatasource(NDataSourceType::kComposite);
	EXPECT_EQ(_obj.GetDatasource()->GetType(), NDataSourceType::kComposite);
}

// Test variable object set datasource
TEST_F(VariableObjectUt, SetDataBaseDataSource_returnDataBaseDataSource)
{
	_obj.SetDatasource(NDataSourceType::kDataBase);
	EXPECT_EQ(_obj.GetDatasource()->GetType(), NDataSourceType::kDataBase);
}

// Test variable object clear datasource
TEST_F(VariableObjectUt, ClearDataSource_returnIsNotVariable)
{
	_obj.SetDatasource(NDataSourceType::kDataBase);
	ASSERT_TRUE(_obj.IsVariable());
	_obj.ClearDataSource();
	EXPECT_FALSE(_obj.IsVariable());
}
