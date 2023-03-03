#include "objectparser.hpp"
#include "dom/builders/nisx/nisxcommonnames.hpp"
#include "utils/macsalogger.hpp"
#include "utils/stringutils.hpp"

using macsa::nisx::ObjectParser;
using macsa::dot::Object;
using macsa::dot::Color;
using macsa::utils::MacsaLogger;
using tinyxml2::XMLElement;
using tinyxml2::XMLAttribute;
using namespace macsa::utils::stringutils;

ObjectParser::ObjectParser(const std::string& fieldType, Object* object) :
	_fieldType(fieldType)
{}

bool ObjectParser::parseCommonElements(const XMLElement &element, const XMLAttribute* firstAttribute, Object* object) const
{
	std::string eName {ToString(element.Name())};

	if (eName == kPosX) {
		std::string eValue {ToString(element.GetText())};
		object->SetXPosition(ToDouble(eValue));
		return true;
	}
	else if (eName == kPosY) {
		std::string eValue {ToString(element.GetText())};
		object->SetYPosition(ToDouble(eValue));
		return true;
	}
	else if (eName == kWidth) {
		std::string eValue {ToString(element.GetText())};
		object->SetWidth(ToDouble(eValue));
		return true;
	}
	else if (eName == kHeight) {
		std::string eValue {ToString(element.GetText())};
		object->SetHeight(ToDouble(eValue));
		return true;
	}
	else if (eName == kAngle) {
		std::string eValue {ToString(element.GetText())};
		object->SetRotation(ToInt(eValue));
		return true;
	}
	else if (eName == kPrintable) {
		std::string eValue {ToString(element.GetText())};
		object->SetPrintable(ToBool(eValue));
		return true;
	}
	else if (eName == kLinked) {
		if (firstAttribute) {
			std::string value = ToString(firstAttribute->Name());
			if (value == kAttrValue && firstAttribute->Value()) {
				object->SetLinked(ToBool(firstAttribute->Value()));
			}
		}
		return true;
	}
	else if (eName == kLinkedObject) { //TODO(iserra): review the NisX XML Format: missing documentation example.
		std::string eValue {ToString(element.GetText())};
		object->SetLinkedObject(eValue);
		return true;
	}
	else if (eName == kLayer) {
		std::string eValue {ToString(element.GetText())};
		object->SetLayer(static_cast<uint>(ToInt(eValue)));
		return true;
	}
	else if (eName == kZOrder) {
		std::string eValue {ToString(element.GetText())};
		object->SetZOrder(static_cast<uint>(ToInt(eValue)));
		return true;
	}

	return false;
}

Color ObjectParser::parseObjectColor(const XMLAttribute* attribute) const
{
	Color color;
	while (attribute) {
		std::string attrName {ToString(attribute->Name())};
		std::string attrValue {ToString(attribute->Value())};
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
