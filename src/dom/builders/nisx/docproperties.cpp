#include "docproperties.hpp"
#include "dom/builders/nisx/nisxcommonnames.hpp"
#include "utils/macsalogger.hpp"
#include "utils/stringutils.hpp"

using macsa::nisx::DocumentPropertiesParser;
using macsa::dot::Document;
using macsa::utils::MacsaLogger;
using namespace macsa::utils::stringutils;

static constexpr const char* kSubHeader = "PROPERTIES";
static constexpr const char* kMeasureUnits = "MEASURE_UNITS";
static constexpr const char* kResolution = "RESOLUTION";
static constexpr const char* kMinUnit = "MIN_UNIT";

DocumentPropertiesParser::DocumentPropertiesParser(Document& document) :
	_document{document}
{}

bool DocumentPropertiesParser::VisitEnter(const tinyxml2::XMLElement& element, const tinyxml2::XMLAttribute* attribute)
{
	std::string eName {ToString(element.Name())};

	if (eName == kMeasureUnits) {
		std::string strUnits(ToString(element.GetText()));
		_document.SetUnits(ToLower(strUnits));
	}
	else if (eName == kResolution) {
		std::string strResolution(ToString(element.GetText()));
		_document.SetResolution(ToUInt(strResolution));
	}
	else if (eName == kMinUnit) {
		DLog() << "Unused property minUnits";
	}
	else if (eName == kWidth) {
		std::string strWidth(ToString(element.GetText()));
		_document.SetCanvasWidth(ToDouble(strWidth));
	}
	else if (eName == kHeight) {
		std::string strHeight(ToString(element.GetText()));
		_document.SetCanvasHeight(ToDouble(strHeight));
	}
	else if (eName != kSubHeader) {
		WLog() << "Unknown element name \"" << eName << "\"";
	}
	return (eName == kSubHeader);
}
