#include "dom/document.hpp"
#include "utils/macsalogger.hpp"
#include "gtest/gtest.h"

using macsa::dot::Document;
using macsa::utils::MacsaLogger;
using macsa::utils::NLogLevel;

class DocumentUt : public ::testing::Test
{
	public:
		DocumentUt()
		{
			// initialization code here
			MacsaLogger::SetCurrentLevel(NLogLevel::kNoLog);
		}

		~DocumentUt() {
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
		Document _doc;
};

// Test generic printhead initialization
TEST_F(DocumentUt, AddTextObject_returnValidObject)
{
	EXPECT_NE(_doc.AddObject("TestObject", macsa::dot::NObjectType::kText), nullptr);
}

// Test generic printhead initialization
TEST_F(DocumentUt, AddBarcodeObject_returnValidObject)
{
	EXPECT_NE(_doc.AddObject("TestObject", macsa::dot::NObjectType::kBarcode), nullptr);
}

// Test generic printhead initialization
TEST_F(DocumentUt, AddImageObject_returnValidObject)
{
	EXPECT_NE(_doc.AddObject("TestObject", macsa::dot::NObjectType::kImage), nullptr);
}

// Test generic printhead initialization
TEST_F(DocumentUt, AddRectangleObject_returnValidObject)
{
	EXPECT_NE(_doc.AddObject("TestObject", macsa::dot::NObjectType::kRectangle), nullptr);
}

// Test generic printhead initialization
TEST_F(DocumentUt, AddEllipseObject_returnValidObject)
{
	EXPECT_NE(_doc.AddObject("TestObject", macsa::dot::NObjectType::kEllipse), nullptr);
}

// Test generic printhead initialization
TEST_F(DocumentUt, AddDiamondObject_returnValidObject)
{
	EXPECT_NE(_doc.AddObject("TestObject", macsa::dot::NObjectType::kDiamond), nullptr);
}

// Test generic printhead initialization
TEST_F(DocumentUt, AddLineObject_returnValidObject)
{
	EXPECT_NE(_doc.AddObject("TestObject", macsa::dot::NObjectType::kLine), nullptr);
}
