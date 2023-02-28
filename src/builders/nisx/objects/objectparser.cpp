#include "objectparser.hpp"
#include "builders/nisx/nisxcommonnames.hpp"
#include "utils/macsalogger.hpp"
#include "utils/stringutils.hpp"

using macsa::nisx::ObjectParser;
using macsa::dot::Object;
using macsa::dot::Color;
using macsa::utils::MacsaLogger;
using tinyxml2::XMLElement;
using tinyxml2::XMLAttribute;
using namespace macsa::utils::stringutils;

namespace {
	std::string str(const char* text) {
		return (text != nullptr ? text : "");
	}
}

ObjectParser::ObjectParser(const std::string& fieldType, Object* object) :
	_fieldType(fieldType)
{}

ObjectParser::~ObjectParser()
{}

bool ObjectParser::parseCommonElements(const XMLElement &element, const XMLAttribute* firstAttribute, Object* object) const
{
	std::string eName {str(element.Name())};

	if (eName == kPosX) {
		std::string eValue {str(element.GetText())};
		object->SetXPosition(ToDouble(eValue));
		return true;
	}
	else if (eName == kPosY) {
		std::string eValue {str(element.GetText())};
		object->SetYPosition(ToDouble(eValue));
		return true;
	}
	else if (eName == kWidth) {
		std::string eValue {str(element.GetText())};
		object->SetWidth(ToDouble(eValue));
		return true;
	}
	else if (eName == kHeight) {
		std::string eValue {str(element.GetText())};
		object->SetHeight(ToDouble(eValue));
		return true;
	}
	else if (eName == kAngle) {
		std::string eValue {str(element.GetText())};
		object->SetRotation(ToInt(eValue));
		return true;
	}
	else if (eName == kPrintable) {
		std::string eValue {str(element.GetText())};
		object->SetPrintable(ToBool(eValue));
		return true;
	}
	else if (eName == kLinked) {
		if (firstAttribute) {
			std::string value = str(firstAttribute->Name());
			if (value == kAttrValue && firstAttribute->Value()) {
				object->SetLinked(ToBool(firstAttribute->Value()));
			}
		}
		return true;
	}
	else if (eName == kLinkedObject) { //TODO(iserra): review the NisX XML Format: missing documentation example.
		std::string eValue {str(element.GetText())};
		object->SetLinkedObject(eValue);
		return true;
	}
	else if (eName == kLayer) {
		std::string eValue {str(element.GetText())};
		object->SetLayer(static_cast<uint>(ToInt(eValue)));
		return true;
	}
	else if (eName == kZOrder) {
		std::string eValue {str(element.GetText())};
		object->SetZOrder(static_cast<uint>(ToInt(eValue)));
		return true;
	}

	return false;
}

Color ObjectParser::parseObjectColor(const XMLAttribute* attribute) const
{
	Color color;

	while (attribute) {
		std::string attrName {str(attribute->Name())};
		std::string attrValue {str(attribute->Value())};
		if (attrName == kName) {
			color.SetName(attrValue);
		}
		else if (attrName == kAttrValue) {
			color.FromARGBString(attrValue);
		}
		attribute = attribute->Next();
	}

	return color;
}
