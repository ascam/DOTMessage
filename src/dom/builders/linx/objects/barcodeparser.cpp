#include "barcodeparser.hpp"
#include "fontparser.hpp"
#include "datasources/dataparser.hpp"
#include "utils/macsalogger.hpp"
#include "utils/stringutils.hpp"

using tinyxml2::XMLElement;
using tinyxml2::XMLAttribute;
using macsa::linx::BarcodeParser;
using macsa::dot::Barcode;
using macsa::dot::Object;
using macsa::utils::MacsaLogger;
using namespace macsa::utils::stringutils;

static constexpr const char* kBarcode = "Barcode";
static constexpr const char* kMag = "Mag";
static constexpr const char* kBcH = "BcH";
static constexpr const char* kHR = "HR";
static constexpr const char* kHRDisplayed = "HRDisplayed";
static constexpr const char* kHRFont = "HRFont";
static constexpr const char* kCheckDigit = "CheckDigit";
static constexpr const char* kQuietMargin = "QuietMargin";
static constexpr const char* kBearerBox = "BearerBox";
static constexpr const char* kBearerBars = "BearerBars";
static constexpr const char* kThickThinRatio = "ThickThinRatio";
static constexpr float  kDefaultRatio = 2.5;
static constexpr uint8_t kPrecision = 100;
static constexpr bool  kDefaultShowHRT = true;

// EAN13
static constexpr const char* kEAN13 = "EAN13";
// QR
static constexpr const char* kQR = "QR";
// CODE128 / EAN128
static constexpr const char* kEAN128 = "EAN128";
static constexpr const char* kCode128 = "Code128";
static constexpr const char* kGS1128 = "IntelligentEan128";
static constexpr const char* kHGauge = "HGauge";
// ITF14
static constexpr const char* kITF14 = "ITF";
static constexpr const char* kHRStyle = "HRStyle";
// UPC-A
static constexpr const char* kUPCA = "UPCA";
// CODE 39
static constexpr const char* kCode39 = "Code39";
// EAN 8
static constexpr const char* kEAN8 = "EAN8";
// UPC-E
static constexpr const char* kUPCE = "UPCE";
// DataMatrix
static constexpr const char* kDataMatrix = "DataMatrix";
// PDF417
static constexpr const char* kMicroPDF417 = "MicroPDF417";
static constexpr const char* kPDF417= "PDF417";
// RSS
static constexpr const char* kRSSExpanded = "RSSExpanded";

BarcodeParser::BarcodeParser(Object* barcode, LinxParserContext& context):
	ObjectParser(),
	_barcode{dynamic_cast<Barcode*>(barcode)},
	_context{context}
{
	if (!_barcode) {
		std::stringstream message;
		message << "Unable to parse text field to a ";
		if (!barcode) {
			message << "nullptr object";
		}
		else {
			message << _barcode->GetType().toString() << " object";
		}
		throw (std::invalid_argument(message.str()));
	}
	else{
		_barcode->SetBackgroundColor(_context.GetColorsPalette().at(kTransparent));
		_barcode->SetForegroundColor(_context.GetColorsPalette().at(kBlack));
		_barcode->SetRatio(kDefaultRatio);
	}
}

bool BarcodeParser::VisitEnter(const tinyxml2::XMLElement& element, const tinyxml2::XMLAttribute* attribute)
{
	std::string eName {ToString(element.Name())};

	if (eName == kField) {
		return true;
	}
	else if (eName == kDisplayed) {
		_barcode->SetPrintable(element.BoolText());
		return false;
	}
	else if (parseCommonElements(element)) {
		return false;
	}
	else if (parseGeometry(element, _geometry)) {
		return false;
	}
	else if (eName == kCalcData) {
		_barcode->SetCode(ToString(element.GetText()));
		return false;
	}
	else if (eName == kData) {
		DataParser dataParser(_barcode, _context);
		element.Accept(&dataParser);
		return false;
	}
	else if (eName == kBarcode) {
		BarcodeInfoParser barcodeInfo(_barcode);
		element.Accept(&barcodeInfo);
		return false;
	}
	else{
		std::stringstream trace;
		trace << "Unknown element (line " << element.GetLineNum() << "): " << element.Name();
		if (attribute) {
			trace << "\n\tattribute: " << attribute->Name();
		}
		WLog() << trace.str();
	}

	return (eName == kField);
}

bool BarcodeParser::VisitExit(const tinyxml2::XMLElement& element)
{
	std::string eName {ToString(element.Name())};
	if (eName == kField) {
		_barcode->SetGeometry(_context.ConvertGeometry(_geometry));
		if (_barcode->IsVariable()) {
			_barcode->SetLayer(1);
		}
	}
	return true;
}

macsa::linx::BarcodeInfoParser::BarcodeInfoParser(dot::Barcode* barcode):
	_barcode{barcode}
{}

bool macsa::linx::BarcodeInfoParser::VisitEnter(const tinyxml2::XMLElement& element, const tinyxml2::XMLAttribute* attribute)
{
	std::string eName {ToString(element.Name())};

	if (eName == kBarcode) {
		return true;
	}
	else if (eName == kMag) {
		return false;
	}
	else if (eName == kBcH) {
		return false;
	}
	else if (eName == kHR) {
		return true;
	}
	else if (eName == kHRDisplayed) {
		_barcode->SetShowHumanReadableCode(element.BoolText(kDefaultShowHRT));
		return true;
	}
	else if (eName == kHRFont) {
		dot::TextBoxProperties prop;
		FontParser fontParser(_font, prop);
		element.Accept(&fontParser);
		return false;
	}
	else if (eName == kCheckDigit) {
		_barcode->SetDisplayChecksum(element.BoolText());
		return false;
	}
	else if (eName == kQuietMargin) {
		return false;
	}
	else if(eName == kEAN8) {
		_barcode->SetSymbology(dot::NBarcodeSymbol::kEan8);
		return false;
	}
	else if (eName == kEAN13) {
		_barcode->SetSymbology(dot::NBarcodeSymbol::kEan13);
		return false;
	}
	else if (eName == kCode39) {
		_barcode->SetSymbology(dot::NBarcodeSymbol::kCode39);
		return true;
	}
	else if (eName == kEAN128 || eName == kCode128) {
		_barcode->SetSymbology(dot::NBarcodeSymbol::kCode128);
		return true;
	}
	else if(eName == kGS1128) {
		_barcode->SetSymbology(dot::NBarcodeSymbol::kGS1128);
		return true;
	}
	else if(eName == kUPCA) {
		_barcode->SetSymbology(dot::NBarcodeSymbol::kUpcA);
		return false;
	}
	else if(eName == kUPCE) {
		_barcode->SetSymbology(dot::NBarcodeSymbol::kUpcA); // NO HAY UPCE
		return false;
	}
	else if(eName == kITF14) {
		_barcode->SetSymbology(dot::NBarcodeSymbol::kItf14);
		return true;
	}
	else if (eName == kRSSExpanded) {
		_barcode->SetSymbology(dot::NBarcodeSymbol::kGS1DataBarExpanded);
		return false;
	}
	else if (eName == kQR) {
		_barcode->SetSymbology(dot::NBarcodeSymbol::kQRCode);
		return false;
	}
	else if(eName == kDataMatrix) {
		_barcode->SetSymbology(dot::NBarcodeSymbol::kDataMatrix);
		return false;
	}
	else if (eName == kPDF417) {
		_barcode->SetSymbology(dot::NBarcodeSymbol::kPdf417);
		return false;
	}
	else if (eName == kMicroPDF417) {
		_barcode->SetSymbology(dot::NBarcodeSymbol::kMicroPdf417);
		return false;
	}
	else if (eName == kBearerBox) {
		_barcode->SetBearerBarStyle(dot::NBearerBarStyle::kFrame);
		return false;
	}
	else if (eName == kBearerBars) {
		_barcode->SetBearerBarStyle(dot::NBearerBarStyle::kHorizontalRules);
		return false;
	}
	else if (eName == kThickThinRatio) {
		_barcode->SetRatio(ToDouble(element.GetText())/kPrecision);
		return false;
	}
	else if (eName == kHRStyle) {
		return false;
	}
	else if (eName == kHGauge) {
		return false;
	}
	else{
		std::stringstream trace;
		trace << "Unknown element (line " << element.GetLineNum() << "): " << element.Name();
		if (attribute) {
			trace << "\n\tattribute: " << attribute->Name();
		}
		WLog() << trace.str();
	}
	return (eName == kBarcode);
}

bool macsa::linx::BarcodeInfoParser::VisitExit(const tinyxml2::XMLElement& element)
{
	std::string eName {ToString(element.Name())};
	if (eName == kBarcode) {
		_barcode->SetKeepAspectRatio(false);
	}
	else if (eName == kHRFont) {
		_barcode->SetFont(_font);
	}
	return true;
}
