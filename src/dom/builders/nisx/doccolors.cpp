#include "doccolors.hpp"
#include "dom/builders/nisx/nisxcommonnames.hpp"
#include "utils/macsalogger.hpp"
#include "utils/stringutils.hpp"

using macsa::nisx::ColorsPaletteParser;
using macsa::dot::Document;
using macsa::utils::MacsaLogger;
using namespace macsa::utils::stringutils;

static constexpr const char* kElementName = "COLORS";
static constexpr const char* kTagColor  = "COLOR";
static constexpr const char* kAttrColor = "Color";

ColorsPaletteParser::ColorsPaletteParser(Document& document) :
	_doc(document),
	_palette{}
{}

bool ColorsPaletteParser::VisitEnter(const tinyxml2::XMLElement& element, const tinyxml2::XMLAttribute* attribute)
{
	std::string eName {ToString(element.Name())};
	if (eName == kTagColor) {
		dot::Color color;
		while (attribute) {
			if (attribute->Name() && attribute->Value()) {
				std::string attrName {attribute->Name()};
				std::string attrValue {attribute->Value()};
				if (attrName == kName) {
					color.SetName(attrValue);
				}
				else if (attrName == kAttrColor) {
					color.FromARGBString(attrValue);
				}
				else {
					WLog() << "Invalid unknown attribute \"" << attribute->Name() << "\"";
				}
			}
			attribute = attribute->Next();
		}
		_palette.insert({color.GetName(), color});
	}
	else if (eName != kElementName) {
		WLog() << "Unknown element name \"" << element.Name() << "\"";
	}
	return (eName == kElementName);
}

bool ColorsPaletteParser::VisitExit(const tinyxml2::XMLElement& element)
{
	std::string eName {ToString(element.Name())};
	if (eName == kElementName) {
		_doc.SetColorsPaletter(_palette);
	}
	return true;
}
