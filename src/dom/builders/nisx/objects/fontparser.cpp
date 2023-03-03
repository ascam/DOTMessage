#include "fontparser.hpp"
#include "dom/builders/nisx/nisxcommonnames.hpp"
#include "utils/macsalogger.hpp"
#include "utils/stringutils.hpp"

using macsa::nisx::FontParser;
using macsa::dot::Font;
using tinyxml2::XMLElement;
using tinyxml2::XMLAttribute;
using macsa::utils::MacsaLogger;
using namespace macsa::utils::stringutils;

constexpr const char* kElementName = macsa::nisx::kFont;

FontParser::FontParser(Font& font) :
	_font(font)
{}

bool FontParser::VisitEnter(const XMLElement& element, const XMLAttribute* firstAttribute)
{
	std::string eName {ToString(element.Name())};

	if (eName == kElementName) {
		if (firstAttribute) {
			parserFont(firstAttribute);
		}
	}
	else if (eName == kBold) {
		_font.bold = ToBool(ToString(element.GetText()));
	}
	else if (eName == kItalic) {
		_font.italic = ToBool(ToString(element.GetText()));
	}
	else if (eName == kUnderline) {
		_font.underline = ToBool(ToString(element.GetText()));
	}
	else if (eName == kStrikeout) {
		_font.strikeout = ToBool(ToString(element.GetText()));
	}
	else {
		std::stringstream trace;
		trace << "Unknown element (line " << element.GetLineNum() << "): " << element.Name();
		if (firstAttribute && firstAttribute->Name()) {
			trace << "\n\tattribute: " << firstAttribute->Name();
		}
		ILog() << trace.str();
	}

	return (eName == kElementName);
}

void FontParser::parserFont(const XMLAttribute* attribute)
{
	while (attribute) {
		if (attribute->Name() && attribute->Value()) {
			std::string attrName {attribute->Name()};
			std::string attrValue {attribute->Value()};
			if (attrName == kName) {
				_font.family = attrValue;
			}
			else if (attrName == kSize) {
				_font.size = ToInt(attrValue);
			}
			else {
				WLog() << "Invalid unknown attribute \"" << attribute->Name() << "\"";
			}
		}
		attribute = attribute->Next();
	}
}
