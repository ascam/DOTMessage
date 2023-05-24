#include "objectparser.hpp"
#include "utils/macsalogger.hpp"
#include "utils/stringutils.hpp"

using macsa::linx::ObjectParser;
using macsa::utils::MacsaLogger;
using tinyxml2::XMLElement;
using tinyxml2::XMLAttribute;
using namespace macsa::utils::stringutils;
using macsa::dot::Geometry;

static constexpr const char* kInverse = "Inverse";
static constexpr const char* kMirror = "Mirror";
static constexpr const char* kOverrideThis = "OverrideThis";
static constexpr const char* kPosX = "X";
static constexpr const char* kPosY = "Y";
static constexpr const char* kWidth = "W";
static constexpr const char* kHeight = "H";
static constexpr const char* kOrientation = "Orientation";

ObjectParser::ObjectParser()
{}

bool ObjectParser::parseCommonElements(const tinyxml2::XMLElement &element) const
{
	std::string eName {ToString(element.Name())};
	std::string eValue {ToString(element.GetText())};

	DLog() << eName << " : " << eValue;

	return (eName == kFldType ||
			eName == kCLSID	||
			eName == kLn ||
			eName == kLoggedField ||
			eName == kInverse ||
			eName == kMirror) ||
			eName == kOverrideThis;
}

bool ObjectParser::parseGeometry(const tinyxml2::XMLElement &element, dot::Geometry& geometry) const
{
	bool found = false;
	std::string eName {ToString(element.Name())};
	std::string eValue {ToString(element.GetText())};

	DLog() << eName << " : " << eValue;
	if (eName == kPosX) {
		found  = true;
		geometry.position.x = ToDouble(eValue);
	}
	else if (eName == kPosY) {
		found  = true;
		geometry.position.y = ToDouble(eValue);
	}
	else if (eName == kWidth) {
		found  = true;
		geometry.size.width = ToDouble(eValue);
	}
	else if (eName == kHeight) {
		found  = true;
		geometry.size.height = ToDouble(eValue);
	}
	else if (eName == kOrientation){
		found  = true;
		geometry.rotation = ToInt(eValue);
	}
	return found;
}
