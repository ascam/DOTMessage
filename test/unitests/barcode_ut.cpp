#include "dom/barcode.hpp"
#include "utils/macsalogger.hpp"
#include "gtest/gtest.h"

using macsa::dot::Barcode;
using macsa::dot::NBarcodeSymbol;
using macsa::dot::Geometry;
using macsa::utils::MacsaLogger;
using macsa::utils::NLogLevel;

class BarcodeUt : public ::testing::Test
{
	public:
		BarcodeUt() :
			_barcode("barcode", Geometry())
		{
			// initialization code here
			MacsaLogger::SetCurrentLevel(NLogLevel::kNoLog);
		}

		~BarcodeUt() {
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
		Barcode _barcode;
};

// Test set Barcode symbology
TEST_F(BarcodeUt, SetCode128Symbology_returnCode128Symbology)
{
	_barcode.SetSymbology(NBarcodeSymbol::kCode128);
	EXPECT_EQ(_barcode.GetSymbology(), NBarcodeSymbol::kCode128);
}

// Test set Barcode symbology
TEST_F(BarcodeUt, SetCode39Symbology_returnCode39Symbology)
{
	_barcode.SetSymbology(NBarcodeSymbol::kCode39);
	EXPECT_EQ(_barcode.GetSymbology(), NBarcodeSymbol::kCode39);
}

// Test set Barcode symbology
TEST_F(BarcodeUt, SetCompactSymbology_returnCompactPdf417Symbology)
{
	_barcode.SetSymbology(NBarcodeSymbol::kCompactPdf417);
	EXPECT_EQ(_barcode.GetSymbology(), NBarcodeSymbol::kCompactPdf417);
}

// Test set Barcode symbology
TEST_F(BarcodeUt, SetDataMatSymbology_returnDataMatrixSymbology)
{
	_barcode.SetSymbology(NBarcodeSymbol::kDataMatrix);
	EXPECT_EQ(_barcode.GetSymbology(), NBarcodeSymbol::kDataMatrix);
}

// Test set Barcode symbology
TEST_F(BarcodeUt, SetGS1DataSymbology_returnGS1DataMatrixSymbology)
{
	_barcode.SetSymbology(NBarcodeSymbol::kGS1DataMatrix);
	EXPECT_EQ(_barcode.GetSymbology(), NBarcodeSymbol::kGS1DataMatrix);
}

// Test set Barcode symbology
TEST_F(BarcodeUt, SetGS1QRCoSymbology_returnGS1QRCodeSymbology)
{
	_barcode.SetSymbology(NBarcodeSymbol::kGS1QRCode);
	EXPECT_EQ(_barcode.GetSymbology(), NBarcodeSymbol::kGS1QRCode);
}

// Test set Barcode symbology
TEST_F(BarcodeUt, SetMicroPdSymbology_returnMicroPdf417Symbology)
{
	_barcode.SetSymbology(NBarcodeSymbol::kMicroPdf417);
	EXPECT_EQ(_barcode.GetSymbology(), NBarcodeSymbol::kMicroPdf417);
}

// Test set Barcode symbology
TEST_F(BarcodeUt, SetMicroQRSymbology_returnMicroQRCodeSymbology)
{
	_barcode.SetSymbology(NBarcodeSymbol::kMicroQRCode);
	EXPECT_EQ(_barcode.GetSymbology(), NBarcodeSymbol::kMicroQRCode);
}

// Test set Barcode symbology
TEST_F(BarcodeUt, SetInterleSymbology_returnInterleaved2of5Symbology)
{
	_barcode.SetSymbology(NBarcodeSymbol::kInterleaved2of5);
	EXPECT_EQ(_barcode.GetSymbology(), NBarcodeSymbol::kInterleaved2of5);
}

// Test set Barcode symbology
TEST_F(BarcodeUt, SetItf14Symbology_returnIf14Symbology)
{
	_barcode.SetSymbology(NBarcodeSymbol::kItf14);
	EXPECT_EQ(_barcode.GetSymbology(), NBarcodeSymbol::kItf14);
}

// Test set Barcode symbology
TEST_F(BarcodeUt, SetQRCodeSymbology_returnQRCodeSymbology)
{
	_barcode.SetSymbology(NBarcodeSymbol::kQRCode);
	EXPECT_EQ(_barcode.GetSymbology(), NBarcodeSymbol::kQRCode);
}

// Test set Barcode symbology
TEST_F(BarcodeUt, SetEan13Symbology_returnEan13Symbology)
{
	_barcode.SetSymbology(NBarcodeSymbol::kEan13);
	EXPECT_EQ(_barcode.GetSymbology(), NBarcodeSymbol::kEan13);
}

// Test set Barcode symbology
TEST_F(BarcodeUt, SetEan13CCASymbology_returnEan13CCASymbology)
{
	_barcode.SetSymbology(NBarcodeSymbol::kEan13CCA);
	EXPECT_EQ(_barcode.GetSymbology(), NBarcodeSymbol::kEan13CCA);
}

// Test set Barcode symbology
TEST_F(BarcodeUt, SetEan13CCBSymbology_returnEan13CCBSymbology)
{
	_barcode.SetSymbology(NBarcodeSymbol::kEan13CCB);
	EXPECT_EQ(_barcode.GetSymbology(), NBarcodeSymbol::kEan13CCB);
}

// Test set Barcode symbology
TEST_F(BarcodeUt, SetEan8Symbology_returnEan8Symbology)
{
	_barcode.SetSymbology(NBarcodeSymbol::kEan8);
	EXPECT_EQ(_barcode.GetSymbology(), NBarcodeSymbol::kEan8);
}

// Test set Barcode symbology
TEST_F(BarcodeUt, SetEan8CCASymbology_returnEan8CCASymbology)
{
	_barcode.SetSymbology(NBarcodeSymbol::kEan8CCA);
	EXPECT_EQ(_barcode.GetSymbology(), NBarcodeSymbol::kEan8CCA);
}

// Test set Barcode symbology
TEST_F(BarcodeUt, SetEan8CCBSymbology_returnEan8CCBSymbology)
{
	_barcode.SetSymbology(NBarcodeSymbol::kEan8CCB);
	EXPECT_EQ(_barcode.GetSymbology(), NBarcodeSymbol::kEan8CCB);
}

// Test set Barcode symbology
TEST_F(BarcodeUt, SetPdf417Symbology_returnPdf417Symbology)
{
	_barcode.SetSymbology(NBarcodeSymbol::kPdf417);
	EXPECT_EQ(_barcode.GetSymbology(), NBarcodeSymbol::kPdf417);
}

// Test set Barcode symbology
TEST_F(BarcodeUt, SetPharmacodeSymbology_returnPharmacodeSymbology)
{
	_barcode.SetSymbology(NBarcodeSymbol::kPharmacode);
	EXPECT_EQ(_barcode.GetSymbology(), NBarcodeSymbol::kPharmacode);
}

// Test set Barcode symbology
TEST_F(BarcodeUt, SetEan128Symbology_returnEan128Symbology)
{
	_barcode.SetSymbology(NBarcodeSymbol::kEan128);
	EXPECT_EQ(_barcode.GetSymbology(), NBarcodeSymbol::kEan128);
}

// Test set Barcode symbology
TEST_F(BarcodeUt, SetEan128CCASymbology_returnEan128CCASymbology)
{
	_barcode.SetSymbology(NBarcodeSymbol::kEan128CCA);
	EXPECT_EQ(_barcode.GetSymbology(), NBarcodeSymbol::kEan128CCA);
}

// Test set Barcode symbology
TEST_F(BarcodeUt, SetEan128CCBSymbology_returnEan128CCBSymbology)
{
	_barcode.SetSymbology(NBarcodeSymbol::kEan128CCB);
	EXPECT_EQ(_barcode.GetSymbology(), NBarcodeSymbol::kEan128CCB);
}

// Test set Barcode symbology
TEST_F(BarcodeUt, SetEan128CCCSymbology_returnEan128CCCSymbology)
{
	_barcode.SetSymbology(NBarcodeSymbol::kEan128CCC);
	EXPECT_EQ(_barcode.GetSymbology(), NBarcodeSymbol::kEan128CCC);
}

// Test set Barcode symbology
TEST_F(BarcodeUt, SetGS1128Symbology_returnGS1128Symbology)
{
	_barcode.SetSymbology(NBarcodeSymbol::kGS1128);
	EXPECT_EQ(_barcode.GetSymbology(), NBarcodeSymbol::kGS1128);
}

// Test set Barcode symbology
TEST_F(BarcodeUt, SetGS1128CCASymbology_returnGS1128CCASymbology)
{
	_barcode.SetSymbology(NBarcodeSymbol::kGS1128CCA);
	EXPECT_EQ(_barcode.GetSymbology(), NBarcodeSymbol::kGS1128CCA);
}

// Test set Barcode symbology
TEST_F(BarcodeUt, SetGS1128CCBSymbology_returnGS1128CCBSymbology)
{
	_barcode.SetSymbology(NBarcodeSymbol::kGS1128CCB);
	EXPECT_EQ(_barcode.GetSymbology(), NBarcodeSymbol::kGS1128CCB);
}

// Test set Barcode symbology
TEST_F(BarcodeUt, SetGS1128CCCSymbology_returnGS1128CCCSymbology)
{
	_barcode.SetSymbology(NBarcodeSymbol::kGS1128CCC);
	EXPECT_EQ(_barcode.GetSymbology(), NBarcodeSymbol::kGS1128CCC);
}

// Test set Barcode symbology
TEST_F(BarcodeUt, SetUpcASymbology_returnUpcASymbology)
{
	_barcode.SetSymbology(NBarcodeSymbol::kUpcA);
	EXPECT_EQ(_barcode.GetSymbology(), NBarcodeSymbol::kUpcA);
}

// Test set Barcode symbology
TEST_F(BarcodeUt, SetGS1DataBar14Symbology_returnGS1DataBar14Symbology)
{
	_barcode.SetSymbology(NBarcodeSymbol::kGS1DataBar14);
	EXPECT_EQ(_barcode.GetSymbology(), NBarcodeSymbol::kGS1DataBar14);
}

// Test set Barcode symbology
TEST_F(BarcodeUt, SetGS1DataBarExpandedSymbology_returnGS1DataBarExpandedSymbology)
{
	_barcode.SetSymbology(NBarcodeSymbol::kGS1DataBarExpanded);
	EXPECT_EQ(_barcode.GetSymbology(), NBarcodeSymbol::kGS1DataBarExpanded);
}

// Test set Barcode symbology
TEST_F(BarcodeUt, SetGS1DataBarExpandedStackedSymbology_returnGS1DataBarExpandedStackedSymbology)
{
	_barcode.SetSymbology(NBarcodeSymbol::kGS1DataBarExpandedStacked);
	EXPECT_EQ(_barcode.GetSymbology(), NBarcodeSymbol::kGS1DataBarExpandedStacked);
}

// Test set Barcode symbology
TEST_F(BarcodeUt, SetGS1DataBarStackedSymbology_returnGS1DataBarStackedSymbology)
{
	_barcode.SetSymbology(NBarcodeSymbol::kGS1DataBarStacked);
	EXPECT_EQ(_barcode.GetSymbology(), NBarcodeSymbol::kGS1DataBarStacked);
}

// Test set Barcode symbology
TEST_F(BarcodeUt, SetRss14StackedOmnidirectionalSymbology_returnRss14StackedOmnidirectionalSymbology)
{
	_barcode.SetSymbology(NBarcodeSymbol::kRss14StackedOmnidirectional);
	EXPECT_EQ(_barcode.GetSymbology(), NBarcodeSymbol::kRss14StackedOmnidirectional);
}

// Test set Barcode symbology
TEST_F(BarcodeUt, SetDotDotCodeSymbology_returnDotCodeSymbology)
{
	_barcode.SetSymbology(NBarcodeSymbol::kDotCode);
	EXPECT_EQ(_barcode.GetSymbology(), NBarcodeSymbol::kDotCode);
}


