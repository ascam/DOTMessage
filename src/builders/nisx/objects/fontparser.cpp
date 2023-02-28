#include "fontparser.hpp"
#include "builders/nisx/nisxcommonnames.hpp"
#include "utils/macsalogger.hpp"
#include "utils/stringutils.hpp"

using macsa::nisx::FontParser;
using macsa::dot::Font;
using tinyxml2::XMLElement;
using tinyxml2::XMLAttribute;
using macsa::utils::MacsaLogger;
using namespace macsa::utils::stringutils;

constexpr const char* kElementName = macsa::nisx::kFont;

namespace {
	std::string str(const char* text) {
		return (text != nullptr ? text : "");
	}
}

FontParser::FontParser(Font& font) :
	_font(font)
{}

FontParser::~FontParser()
{}

bool FontParser::VisitEnter(const XMLElement& element, const XMLAttribute* firstAttribute)
{
	std::string eName {str(element.Name())};

	if (eName == kElementName) {
		if (firstAttribute) {
			parserFont(firstAttribute);
		}
	}
	else if (eName == kBold) {
		_font.bold = ToBool(str(element.GetText()));
	}
	else if (eName == kItalic) {
		_font.italic = ToBool(str(element.GetText()));
	}
	else if (eName == kUnderline) {
		_font.underline = ToBool(str(element.GetText()));
	}
	else if (eName == kStrikeout) {
		_font.strikeout = ToBool(str(element.GetText()));
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

bool FontParser::VisitExit(const XMLElement& element)
{
	return true;
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
