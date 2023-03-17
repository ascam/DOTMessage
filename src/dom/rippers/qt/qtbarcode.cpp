#include "qtbarcode.hpp"

#include "backend_qt/qzint.h"
#include "backend/qr.h"
#include "utils/macsalogger.hpp"

using macsa::dot::QtBarcode;
using Zint::QZint;
using macsa::dot::Barcode;
using macsa::dot::BarcodeSymbol;
using macsa::dot::NBarcodeSymbol;
using macsa::utils::MacsaLogger;

QtBarcode::QtBarcode(const Barcode *barcode, QPainter &painter,
					 int vres, int hres, const ColorsPalette& palette) :
	QtObject(barcode, painter, vres, hres, palette),
	_barcode(barcode)
{}

void QtBarcode::Render()
{
	Render(_barcode->GetCode());
}

void QtBarcode::Render(const std::string& text)
{
	if (text.empty()) {
		WLog() << "No text to render";
		return;
	}

	_painter.save();

	QRectF rect = GetRect();
	changePainterCoords(_painter, _barcode->GetGeometry().rotation, rect);

	auto symbol = _barcode->GetSymbology();
	int zintSymbol = getZintSymbology(symbol());

	QZint zintCode;
	zintCode.setBgColor(Qt::transparent);
	zintCode.setText(text.c_str());
	zintCode.setSymbol(zintSymbol);
	zintCode.setInputMode(getZintSymbologyMode(symbol()));

	if (zintSymbol == BARCODE_QRCODE) {
		int level = -1;
		switch (_barcode->GetQrCorrectionLevel()()) {
			case NQRCorrectionLevel::kM: // Level M, approx 15%
				level = LEVEL_M;
				break;
			case NQRCorrectionLevel::kQ: // Level Q, approx 25%
				level = LEVEL_Q;
				break;
			case NQRCorrectionLevel::kH: // Level H, approx 30%
				level = LEVEL_H;
				break;
			case NQRCorrectionLevel::kL: // Level M, approx 7%
			default:
				level = LEVEL_L;
				break;
		}
		zintCode.setSecurityLevel(level);
	}
	else {
		zintCode.setSecurityLevel(_barcode->GetSecurityLevel());
	}

	zintCode.setHideText(!_barcode->GetShowHumanReadableCode());

	int whitespace = 0;
	switch (_barcode->GetBearerBarStyle()()) {
		case NBearerBarStyle::kFrame: // Frame around the barcode
			zintCode.setOutputOptions(BARCODE_BOX);
			whitespace = 12;
			zintCode.setBorderWidth(6);
			break;
		case NBearerBarStyle::kHorizontalRules: // Frame lines on top and bottom
			zintCode.setOutputOptions(BARCODE_BIND);
			whitespace = 12;
			zintCode.setBorderWidth(6); // TODO(iserra): Hardcoded ?
			break;
		case NBearerBarStyle::kNone: // No Frame
		default:
			zintCode.setOutputOptions(0);
			zintCode.setBorderWidth(0); // TODO(iserra): Hardcoded ?
			break;
	}



	if (isBarcodeWithTextOutside(symbol)) {
		whitespace += 10;
	}
	zintCode.setWhitespace(whitespace);

	if (_barcode->HasShavingMode()){
		zintCode.setOutputOptions(BARCODE_DOTTY_MODE);
		zintCode.setShaving(static_cast<float>(_barcode->GetShavingValue()));
	}

	if (!isBarcodeWithoutText(symbol)){
		zintCode.setFont(_barcode->GetFont().family.c_str());
		zintCode.setFontSize(_barcode->GetFont().size);
	}

	if (!_barcode->GetPrintable())	{
		_painter.setOpacity(0.5);
	}

	if (_barcode->GetKeepAspectRatio()) {
		zintCode.render(_painter, rect, Zint::QZint::KeepAspectRatio, _vres, _hres);
	}
	else {
		zintCode.render(_painter, rect, Zint::QZint::IgnoreAspectRatio);
	}

	_painter.restore();

#if defined(EDITOR_MODE)
	QtObject::Render();
#endif
}

int QtBarcode::getZintSymbology(const BarcodeSymbol& symbology) const
{
	switch(symbology())
	{
		/*
		case NBarcodeSymbology::kAustraliaPost:
			return BARCODE_AUSPOST;
		case NBarcodeSymbology::kAustraliaPostDomesticEParcelBarcode:
			return BARCODE_AUSREDIRECT;
		case NBarcodeSymbology::kAztecCode:
			return BARCODE_AZTEC;
		case NBarcodeSymbology::kCodabar:
			return BARCODE_CODABAR;
		case NBarcodeSymbology::kCode11:
			return BARCODE_CODE11;
		case NBarcodeSymbology::kCode16k:
			return BARCODE_CODE16K;
		case NBarcodeSymbology::kCode32:
			return BARCODE_CODE32;
		*/
		case NBarcodeSymbol::kCode39:
			return BARCODE_CODE39;
		/*
		case NBarcodeSymbology::kCode93:
			return BARCODE_CODE93;
		*/
		case NBarcodeSymbol::kCompactPdf417:
			return BARCODE_PDF417TRUNC;
		// case NBarcodeSymbology::kDanishPostal39: return ; // Not implemented
		case NBarcodeSymbol::kDataMatrix:
			return BARCODE_DATAMATRIX;
		case NBarcodeSymbol::kDotCode:
			return BARCODE_DOTCODE;
		/*
		case NBarcodeSymbology::kDeutschePostIdentcode:
			return BARCODE_DPIDENT;
		case NBarcodeSymbology::kDeutschePostLeitcode:
			return BARCODE_DPLEIT;
		*/
		// case NBarcodeSymbology::kDoteCode: return ; // Not implemented

		//case NBarcodeSymbology::kCode128:                             // Default value
		//case NBarcodeSymbology::kEan128:                              // Default value

		case NBarcodeSymbol::kEan13:
		case NBarcodeSymbol::kEan8:
			return BARCODE_EANX;
		case NBarcodeSymbol::kEan13CCA:
		case NBarcodeSymbol::kEan13CCB:
		case NBarcodeSymbol::kEan8CCA:
		case NBarcodeSymbol::kEan8CCB:
			return BARCODE_EANX_CC;

		// case NBarcodeSymbology::kEan99:                 return ; // Not implemented
		// case NBarcodeSymbology::kEanUpcAddOn2:          return ; // Not implemented
		// case NBarcodeSymbology::kEanUpcAddOn5:          return ; // Not implemented
		// case NBarcodeSymbology::kEanVelocity:           return ; // Not implemented
		// case NBarcodeSymbology::kFedExGround96:         return ; // Not implemented
		// case NBarcodeSymbology::kFrenchPostal39AR:      return ; // Not implemented

		case NBarcodeSymbol::kGS1128:
		//case NBarcodeSymbology::kUccEan128:		return BARCODE_EAN128;

		case NBarcodeSymbol::kEan128CCA:
		case NBarcodeSymbol::kEan128CCB:
		case NBarcodeSymbol::kEan128CCC:
		case NBarcodeSymbol::kGS1128CCA:
		case NBarcodeSymbol::kGS1128CCB:
		case NBarcodeSymbol::kGS1128CCC:
		//case NBarcodeSymbology::kUccEan128CCA:
		//case NBarcodeSymbology::kUccEan128CCB:
		//case NBarcodeSymbology::kUccEan128CCC:
			return BARCODE_EAN128_CC;

		case NBarcodeSymbol::kGS1DataBar14:
		//case NBarcodeSymbology::kGS1DataBar14CCA:
		//case NBarcodeSymbology::kGS1DataBar14CCB:
			return BARCODE_RSS14;
		// case NBarcodeSymbology::kGS1DataBar14Stacked: return ; // Not implemented
		// case NBarcodeSymbology::kGS1DataBar14StackedCCA: return ; // Not implemented
		// case NBarcodeSymbology::kGS1DataBar14StackedCCB: return ; // Not implemented
		// case NBarcodeSymbology::kGS1DataBar14StackedOmnidirectional: return ; // Not implemented
		// case NBarcodeSymbology::kGS1DataBar14StackedOmnidirectionalCCA: return ; // Not implemented
		// case NBarcodeSymbology::kGS1DataBar14StackedOmnidirectionalCCB: return ; // Not implemented
		// case NBarcodeSymbology::kGS1DataBar14Truncated: return ; // Not implemented
		// case NBarcodeSymbology::kGS1DataBar14TruncatedCCA: return ; // Not implemented
		// case NBarcodeSymbology::kGS1DataBar14TruncatedCCB: return ; // Not implemented

		case NBarcodeSymbol::kGS1DataBarExpanded:
		//case NBarcodeSymbology::kGS1DataBarExpandedCCA:
		//case NBarcodeSymbology::kGS1DataBarExpandedCCB:
			return BARCODE_RSS_EXP;

		case NBarcodeSymbol::kGS1DataBarExpandedStacked:
		//case NBarcodeSymbology::kGS1DataBarExpandedStackedCCA:
		//case NBarcodeSymbology::kGS1DataBarExpandedStackedCCB:
			return BARCODE_RSS_EXPSTACK;

		// case NBarcodeSymbology::kGS1DataBarLimited: return ; // Not implemented
		// case NBarcodeSymbology::kGS1DataBarLimitedCCA: return ; // Not implemented
		// case NBarcodeSymbology::kGS1DataBarLimitedCCB: return ; // Not implemented

		//case NBarcodeSymbology::kGS1DataBarOmnidirectional:
		//case NBarcodeSymbology::kGS1DataBarOmnidirectionalCCA:
		//case NBarcodeSymbology::kGS1DataBarOmnidirectionalCCB:
		//	return BARCODE_RSS14STACK_OMNI;

		case NBarcodeSymbol::kGS1DataBarStacked:
		//case NBarcodeSymbology::kGS1DataBarStackedCCA:
		//case NBarcodeSymbology::kGS1DataBarStackedCCB:
			return BARCODE_RSS14STACK;

		// case NBarcodeSymbology::kGS1DataBarStackedOmnidirectional: return ; // Not implemented
		// case NBarcodeSymbology::kGS1DataBarStackedOmnidirectionalCCA: return ; // Not implemented
		// case NBarcodeSymbology::kGS1DataBarStackedOmnidirectionalCCB: return ; // Not implemented
		// case NBarcodeSymbology::kGS1DataBarTruncated: return ; // Not implemented
		// case NBarcodeSymbology::kGS1DataBarTruncatedCCA: return ; // Not implemented
		// case NBarcodeSymbology::kGS1DataBarTruncatedCCB: return ; // Not implemented

		case NBarcodeSymbol::kGS1DataMatrix:
			return BARCODE_DATAMATRIX;

		// case NBarcodeSymbology::kHibcLic128: return ; // Not implemented
		// case NBarcodeSymbology::kHibcLic39: return ; // Not implemented
		// case NBarcodeSymbology::kHibcPas128: return ; // Not implemented
		// case NBarcodeSymbology::kHibcPas39: return ; // Not implemented

		//case NBarcodeSymbology::kIATA2of5:
			//return BARCODE_C25IATA;
		//case NBarcodeSymbology::kIndustrial2of5:
			//return BARCODE_C25IND;
		case NBarcodeSymbol::kInterleaved2of5:
			return BARCODE_C25INTER;

		// case NBarcodeSymbology::kIsbn: return ; // Not implemented
		// case NBarcodeSymbology::kIsbt128: return ; // Not implemented
		// case NBarcodeSymbology::kIsmn: return ; // Not implemented
		// case NBarcodeSymbology::kIssn: return ; // Not implemented
		// case NBarcodeSymbology::kItalianPost25: return ; // Not implemented

		case NBarcodeSymbol::kItf14:
			return BARCODE_ITF14;

		// case NBarcodeSymbology::kJan13: return ; // Not implemented
		// case NBarcodeSymbology::kJan8: return ; // Not implemented
		// case NBarcodeSymbology::kKodakPatchCode: return ; // Not implemented
		// case NBarcodeSymbology::kMacroPdf417: return ; // Not implemented
		//case NBarcodeSymbology::kMatrix2of5: return BARCODE_C25MATRIX;
		// case NBarcodeSymbology::kMaxiCode: return ; // Not implemented
		// case NBarcodeSymbology::kMICRE13B: return ; // Not implemented
		case NBarcodeSymbol::kMicroPdf417:
			return BARCODE_MICROPDF417;
		// case NBarcodeSymbology::kMicroQRCode: return ; // Not implemented
		// case NBarcodeSymbology::kMsi: return ; // Not implemented
		// case NBarcodeSymbology::kNumlyNumber: return ; // Not implemented
		// case NBarcodeSymbology::kOpc: return ; // Not implemented
		case NBarcodeSymbol::kPdf417:
			return BARCODE_PDF417;
		case NBarcodeSymbol::kPharmacode:
			return BARCODE_PHARMA;
		// case NBarcodeSymbology::kPlanet: return ; // Not implemented
		// case NBarcodeSymbology::kPostnet: return ; // Not implemented
		// case NBarcodeSymbology::kPzn: return ; // Not implemented
		case NBarcodeSymbol::kQRCode:
			return BARCODE_QRCODE;
		// case NBarcodeSymbology::kRoyalMail: return ; // Not implemented
		// case NBarcodeSymbology::kRoyalTpgPostKix: return ; // Not implemented
		// case NBarcodeSymbology::kRss14: return ; // Not implemented
		// case NBarcodeSymbology::kRss14CCA: return ; // Not implemented
		// case NBarcodeSymbology::kRss14CCB: return ; // Not implemented
		// case NBarcodeSymbology::kRss14Stacked: return ; // Not implemented
		// case NBarcodeSymbology::kRss14StackedCCA: return ; // Not implemented
		// case NBarcodeSymbology::kRss14StackedCCB: return ; // Not implemented
		// case NBarcodeSymbology::kRss14StackedOmnidirectional: return ; // Not implemented
		// case NBarcodeSymbology::kRss14StackedOmnidirectionalCCA: return ; // Not implemented
		// case NBarcodeSymbology::kRss14StackedOmnidirectionalCCB: return ; // Not implemented
		// case NBarcodeSymbology::kRss14Truncated: return ; // Not implemented
		// case NBarcodeSymbology::kRss14TruncatedCCA: return ; // Not implemented
		// case NBarcodeSymbology::kRss14TruncatedCCB: return ; // Not implemented
		// case NBarcodeSymbology::kRssExpanded: return ; // Not implemented
		// case NBarcodeSymbology::kRssExpandedCCA: return ; // Not implemented
		// case NBarcodeSymbology::kRssExpandedCCB: return ; // Not implemented
		// case NBarcodeSymbology::kRssExpandedStacked: return ; // Not implemented
		// case NBarcodeSymbology::kRssExpandedStackedCCA: return ; // Not implemented
		// case NBarcodeSymbology::kRssExpandedStackedCCB: return ; // Not implemented
		// case NBarcodeSymbology::kRssLimited: return ; // Not implemented
		// case NBarcodeSymbology::kRssLimitedCCA: return ; // Not implemented
		// case NBarcodeSymbology::kRssLimitedCCB: return ; // Not implemented
		// case NBarcodeSymbology::kScc14: return ; // Not implemented
		// case NBarcodeSymbology::kSemacode: return ; // Not implemented
		// case NBarcodeSymbology::kSingaporePost: return ; // Not implemented
		// case NBarcodeSymbology::kSscc18: return ; // Not implemented
		// case NBarcodeSymbology::kSwissPostParcel: return ; // Not implemented
		// case NBarcodeSymbology::kTelepen: return ; // Not implemented
		case NBarcodeSymbol::kUpcA:
			return BARCODE_UPCA;
		// case NBarcodeSymbology::kUpcACCA: return ; // Not implemented
		// case NBarcodeSymbology::kUpcACCB: return ; // Not implemented
		// case NBarcodeSymbology::kUpcE: return ; // Not implemented
		// case NBarcodeSymbology::kUpcECCA: return ; // Not implemented
		// case NBarcodeSymbology::kUpcECCB: return ; // Not implemented
		// case NBarcodeSymbology::kUspsFim: return ; // Not implemented
		// case NBarcodeSymbology::kUspsHorizontalBars: return ; // Not implemented
		// case NBarcodeSymbology::kUspsIntelligentMail: return ; // Not implemented
		// case NBarcodeSymbology::kUspsIntelligentMailContainerBarcode: return ; // Not implemented
		// case NBarcodeSymbology::kUspsOneCode4CB: return ; // Not implemented
		// case NBarcodeSymbology::kUspsPicCode128: return ; // Not implemented
		// case NBarcodeSymbology::kUspsPicUccEan128: return ; // Not implemented
		// case NBarcodeSymbology::kUspsSackLabel: return ; // Not implemented
		// case NBarcodeSymbology::kUspsTrayLabel: return ; // Not implemented
		// case NBarcodeSymbology::kVicsBol: return ; // Not implemented
		// case NBarcodeSymbology::kVicsScacPro: return ; // Not implemented
		default:
			return BARCODE_CODE128;
	}
}

int QtBarcode::getZintSymbologyMode(const BarcodeSymbol& symbology) const
{
	switch(symbology())
	{
		case NBarcodeSymbol::kGS1128:
		case NBarcodeSymbol::kGS1128CCA:
		case NBarcodeSymbol::kGS1128CCB:
		case NBarcodeSymbol::kGS1128CCC:
		//case NBarcodeSymbology::kGS1DataBar14: //GS1 Mode not accepted

		/*
		case NBarcodeSymbology::kGS1DataBar14CCA:
		case NBarcodeSymbology::kGS1DataBar14CCB:
		case NBarcodeSymbology::kGS1DataBar14Stacked:
		case NBarcodeSymbology::kGS1DataBar14StackedCCA:
		case NBarcodeSymbology::kGS1DataBar14StackedCCB:
		case NBarcodeSymbology::kGS1DataBar14StackedOmnidirectional:
		case NBarcodeSymbology::kGS1DataBar14StackedOmnidirectionalCCA:
		case NBarcodeSymbology::kGS1DataBar14StackedOmnidirectionalCCB:
		case NBarcodeSymbology::kGS1DataBar14Truncated:
		case NBarcodeSymbology::kGS1DataBar14TruncatedCCA:
		case NBarcodeSymbology::kGS1DataBar14TruncatedCCB:
		*/
		//case NBarcodeSymbology::kGS1DataBarExpanded: //GS1 Mode not accepted
		//case NBarcodeSymbology::kGS1DataBarExpandedCCA:
		//case NBarcodeSymbology::kGS1DataBarExpandedCCB:
		//case NBarcodeSymbology::kGS1DataBarExpandedStacked: //GS1 Mode not accepted
		//case NBarcodeSymbology::kGS1DataBarExpandedStackedCCA:
		//case NBarcodeSymbology::kGS1DataBarExpandedStackedCCB:
		//case NBarcodeSymbology::kGS1DataBarLimited:
		//case NBarcodeSymbology::kGS1DataBarLimitedCCA:
		//case NBarcodeSymbology::kGS1DataBarLimitedCCB:
		//case NBarcodeSymbology::kGS1DataBarOmnidirectional: //GS1 Mode not accepted
		//case NBarcodeSymbology::kGS1DataBarOmnidirectionalCCA:
		//case NBarcodeSymbology::kGS1DataBarOmnidirectionalCCB:
		//case NBarcodeSymbology::kGS1DataBarStacked: //GS1 Mode not accepted
		//case NBarcodeSymbology::kGS1DataBarStackedCCA:
		//case NBarcodeSymbology::kGS1DataBarStackedCCB:
		//case NBarcodeSymbology::kGS1DataBarStackedOmnidirectional://GS1 Mode not accepted
		//case NBarcodeSymbology::kGS1DataBarStackedOmnidirectionalCCA:
		//case NBarcodeSymbology::kGS1DataBarStackedOmnidirectionalCCB:
		//case NBarcodeSymbology::kGS1DataBarTruncated:
		//case NBarcodeSymbology::kGS1DataBarTruncatedCCA:
		//case NBarcodeSymbology::kGS1DataBarTruncatedCCB:
		case NBarcodeSymbol::kGS1DataMatrix:
			return GS1_MODE;
		default:
			return UNICODE_MODE;

	}
}

bool QtBarcode::isBarcodeWithTextOutside(const BarcodeSymbol& symbology) const
{
	switch (symbology()){
		case NBarcodeSymbol::kEan13:
		case NBarcodeSymbol::kEan8:
		case NBarcodeSymbol::kUpcA:
			return true;
		default:
			return false;
	}
}

bool QtBarcode::isBarcodeWithoutText(const BarcodeSymbol& symbology) const
{
	switch (symbology()){
		case NBarcodeSymbol::kQRCode:
		case NBarcodeSymbol::kMicroQRCode:
		case NBarcodeSymbol::kGS1DataMatrix:
		case NBarcodeSymbol::kDataMatrix:
		case NBarcodeSymbol::kPdf417:
		case NBarcodeSymbol::kMicroPdf417:
		case NBarcodeSymbol::kGS1DataBarStacked:
		//case NBarcodeSymbology::kGS1DataBarStackedOmnidirectional:
		case NBarcodeSymbol::kGS1DataBarExpandedStacked:
			return true;
		default:
			return false;
	}
}
