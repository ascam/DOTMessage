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

DocumentPropertiesParser::DocumentPropertiesParser(LinxParserContext& context) :
	_context{context},
	_width{0},
	_height{0},
	_canvasRotated{false}
{}

DocumentPropertiesParser::~DocumentPropertiesParser()
{}

bool DocumentPropertiesParser::VisitEnter(const tinyxml2::XMLElement& element, const tinyxml2::XMLAttribute* attribute)
{
	std::string eName {ToString(element.Name())};
	std::string eValue {ToString(element.GetText())};
	DLog() << eName << " : " << eValue;

	if (eName == kSubHeader){
		return true;
	}
	else if (eName == kImageWidth) {
		return false;
	}
	else if (eName == kImageHeight) {
		return false;
	}
	else if (eName == kImageRotation) {
		if (attribute && ToString(attribute->Name()) == kEnabled){
			_canvasRotated = ToBool(attribute->Value()) && ToInt(eValue) > 0;
		}
		return false;
	}
	else if (eName == kMaxImageWidth) {
		_width = ToDouble(eValue);
		return false;
	}
	else if (eName == kMaxImageHeight) {
		_height = ToDouble(eValue);
		return false;
	}
	else if (eName == kXRes) {
		_context.SetUnitsRatio(ToDouble(eValue));
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
	if (eName == kSubHeader){
		if (_canvasRotated){
			std::swap(_width, _height);
		}
		_context.GetDocument().SetCanvasWidth(_context.ConvertUnits(_width));
		_context.GetDocument().SetCanvasHeight(_context.ConvertUnits(_height));
	}
	return true;
}
