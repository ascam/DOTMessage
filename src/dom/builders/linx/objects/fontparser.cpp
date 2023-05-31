#include "fontparser.hpp"
#include "utils/macsalogger.hpp"
#include "utils/stringutils.hpp"

using macsa::linx::FontParser;
using macsa::dot::Font;
using tinyxml2::XMLElement;
using tinyxml2::XMLAttribute;
using macsa::utils::MacsaLogger;
using namespace macsa::utils::stringutils;

constexpr const char* kText = "Text";
constexpr const char* kHRFont = "HRFont";
constexpr const char* kFont = "Font";
constexpr const char* kFace = "Face";
constexpr const char* kFamily = "Family";
constexpr const char* kPitch = "Pitch";
constexpr const char* kTTSize = "TTSize";
constexpr const char* kTxtDir = "TxtDir";
constexpr const char* kXMag = "XMag";
constexpr const char* kPitchResolution = "PitchResolution";
constexpr const char* kBold = "Bold";
constexpr const char* kItalic = "Italic";
constexpr const char* kUnderline = "Underline";
constexpr const char* kStrikeout = "Strikeout";
constexpr const char* kBlock = "Block";

FontParser::FontParser(Font& font, dot::TextBoxProperties& textBoxProperties) :
	_font(font),
	_textBoxProperties(textBoxProperties)
{}

bool FontParser::VisitEnter(const XMLElement& element, const XMLAttribute* attribute)
{
	std::string eName {ToString(element.Name())};

	if (eName == kText || eName == kHRFont) {
		return true;
	}
	else if (eName == kFont) {
		return true;
	}
	else if (eName == kFace || eName == kFamily) {
		_font.family = ToString(element.GetText());
		return true;
	}
	else if (eName == kPitch) {
		_font.size = element.IntText();
		return true;
	}
	else if (eName == kPitchResolution) {
		int pitchRes = element.IntText();
		if (pitchRes) {
			_font.size /= pitchRes;
		}
		return false;
	}
	else if (eName == kTTSize) {
		return false;
	}
	else if (eName == kTxtDir) {
		return false;
	}
	else if (eName == kXMag) {
		return false;
	}
	else if (eName == kBold) {
		_font.bold = element.BoolText();
		return false;
	}
	else if (eName == kItalic) {
		_font.italic = element.BoolText();
		return false;
	}
	else if (eName == kUnderline) {
		_font.underline = element.BoolText();
		return false;
	}
	else if (eName == kStrikeout) {
		_font.strikeout = element.BoolText();
		return false;
	}
	else if (eName == kBlock) {
		_textBoxProperties.SetBoxAdjustment(dot::NTextBoxAdjustment::kParagraph);
		return false;
	}
	else {
		std::stringstream trace;
		trace << "Unknown element (line " << element.GetLineNum() << "): " << element.Name();
		if (attribute && attribute->Name()) {
			trace << "\n\tattribute: " << attribute->Name();
		}
		WLog() << trace.str();
		return true;
	}
	return (eName == kText || eName == kHRFont);
}
