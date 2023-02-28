#include "docproperties.hpp"
#include "nisxcommonnames.hpp"
#include "utils/macsalogger.hpp"
#include "utils/stringutils.hpp"

using macsa::nisx::DocumentPropertiesParser;
using macsa::dot::Document;
using macsa::utils::MacsaLogger;
using namespace macsa::utils::stringutils;

static constexpr const char* kElementName = "PROPERTIES";
static constexpr const char* kMeasureUnits = "MEASURE_UNITS";
static constexpr const char* kResolution = "RESOLUTION";
static constexpr const char* kMinUnit = "MIN_UNIT";

namespace {
	std::string str(const char* text) {
		return (text != nullptr ? text : "");
	}
}

DocumentPropertiesParser::DocumentPropertiesParser(Document& document) :
	_document{document}
{}

DocumentPropertiesParser::~DocumentPropertiesParser()
{}

bool DocumentPropertiesParser::VisitEnter(const tinyxml2::XMLElement& element, const tinyxml2::XMLAttribute* attribute)
{
	std::string eName {str(element.Name())};

	if (eName == kMeasureUnits) {
		std::string units(str(element.GetText()));
		_document.SetUnits(ToLower(units));
	}
	else if (eName == kResolution) {
		DLog() << "Unused property resolution";
	}
	else if (eName == kMinUnit) {
		DLog() << "Unused property minUnits";
	}
	else if (eName == kWidth) {
		std::string strWidth(str(element.GetText()));
		_document.SetCanvasWidth(ToDouble(strWidth));
	}
	else if (eName == kHeight) {
		std::string strHeight(str(element.GetText()));
		_document.SetCanvasHeight(ToDouble(strHeight));
	}
	else if (eName != kElementName) {
		WLog() << "Unknown element name \"" << eName << "\"";
	}
	return (eName == kElementName);
}
