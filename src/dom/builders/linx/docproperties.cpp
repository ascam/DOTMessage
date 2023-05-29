#include "docproperties.hpp"
#include "utils/macsalogger.hpp"
#include "utils/stringutils.hpp"

using macsa::linx::DocumentPropertiesParser;
using macsa::dot::Document;
using macsa::utils::MacsaLogger;
using namespace macsa::utils::stringutils;

static constexpr const char* kSubHeader = "SubHeader";
static constexpr const char* kImageWidth = "ImageWidth";
static constexpr const char* kImageHeight= "ImageHeight";
static constexpr const char* kImageRotation= "ImageRotation";
static constexpr const char* kEnabled = "Enabled";
static constexpr const char* kMaxImageWidth = "MaxImageWidth";
static constexpr const char* kMaxImageHeight = "MaxImageHeight";
static constexpr const char* kXRes = "XRes";
static constexpr const char* kCurrentOrientation = "CurrentOrientation";
static constexpr uint8_t kPrecision = 10;

DocumentPropertiesParser::DocumentPropertiesParser(LinxParserContext& context) :
	_context{context},
	_width{},
	_height{},
	_canvasRotated{}
{}

DocumentPropertiesParser::~DocumentPropertiesParser()
{}

bool DocumentPropertiesParser::VisitEnter(const tinyxml2::XMLElement& element, const tinyxml2::XMLAttribute* attribute)
{
	std::string eName {ToString(element.Name())};
	if (eName == kSubHeader) {
		return true;
	}
	else if (eName == kImageWidth) {
		return false;
	}
	else if (eName == kImageHeight) {
		return false;
	}
	else if (eName == kImageRotation) {
		if (attribute && ToString(attribute->Name()) == kEnabled && ToBool(attribute->Value())) {
			_canvasRotated =  element.IntText() / kPrecision;
		}
		return false;
	}
	else if (eName == kMaxImageWidth) {
		_width = element.DoubleText();
		return false;
	}
	else if (eName == kMaxImageHeight) {
		_height = element.DoubleText();
		return false;
	}
	else if (eName == kXRes) {
		_context.SetUnitsRatio(element.DoubleText());
		return false;
	}
	else if (eName == kCurrentOrientation) {
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
	return (eName == kSubHeader);
}

bool DocumentPropertiesParser::VisitExit(const tinyxml2::XMLElement &element)
{
	std::string eName {ToString(element.Name())};
	if (eName == kSubHeader) {
		_context.GetDocument().SetCanvasWidth(_context.ConvertUnits(_width));
		_context.GetDocument().SetCanvasHeight(_context.ConvertUnits(_height));
		_context.GetDocument().SetCanvasRotation(_canvasRotated);
	}
	return true;
}
