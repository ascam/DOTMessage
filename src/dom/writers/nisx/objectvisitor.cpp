#include "objectvisitor.hpp"
#include "nisxcommonnames.hpp"
#include "xmltools/xmlwriter.hpp"
#include "utils/stringutils.hpp"
#include "utils/macsalogger.hpp"

using macsa::nisx::ObjectVisitor;
using macsa::dot::Object;
using macsa::dot::Font;
using macsa::xmltools::XmlWriter;
using macsa::utils::MacsaLogger;
using tinyxml2::XMLElement;
using tinyxml2::XMLDocument;
using namespace macsa::utils::stringutils;

static constexpr const char* kPrintable = "PRINTABLE";
static constexpr const char* kLinked = "LINKED";
static constexpr const char* kLinkedObject = "LINKED_OBJECT";
static constexpr const char* kZOrder = "ZORDER";
static constexpr const char* kLayer = "LAYOUT";
// Fonts related tags
static constexpr const char* kFont = "FONT";
static constexpr const char* kAttrSize = "Size";
static constexpr const char* kBold = "BOLD";
static constexpr const char* kItalic = "ITALIC";
static constexpr const char* kUnderline = "UNDERLINE";
static constexpr const char* kStrikeout = "STRIKEOUT";

ObjectVisitor::ObjectVisitor(XMLDocument& document) :
	_xmlDocument{document}
{}

bool ObjectVisitor::visitObject(const Object& object, XMLElement* element)
{
	if (element) {
		const auto& geometry = object.GetGeometry();
		XmlWriter::CreateTextChildNode(_xmlDocument, kPosX, ToString(geometry.position.x, 2), element);
		XmlWriter::CreateTextChildNode(_xmlDocument, kPosY, ToString(geometry.position.y, 2), element);
		XmlWriter::CreateTextChildNode(_xmlDocument, kWidth, ToString(geometry.size.width, 2), element);
		XmlWriter::CreateTextChildNode(_xmlDocument, kHeight, ToString(geometry.size.height, 2), element);
		XmlWriter::CreateTextChildNode(_xmlDocument, kAngle, ToString(geometry.rotation), element);
		XmlWriter::CreateTextChildNode(_xmlDocument, kPrintable, ToString(object.GetPrintable()).c_str(), element);
		auto xmlLinkedResult = XmlWriter::CreateChildNode(_xmlDocument, kLinked, element);
		if (xmlLinkedResult.second) {
			xmlLinkedResult.first->SetAttribute(kAttrValue, ToString(object.GetLinked()).c_str());
			if (object.GetLinked()) {
				XmlWriter::CreateTextChildNode(_xmlDocument, kLinkedObject, object.GetLinkedObject().c_str(), xmlLinkedResult.first);
			}
		}
		XmlWriter::CreateTextChildNode(_xmlDocument, kZOrder, ToString(object.GetZOrder()), element);
		XmlWriter::CreateTextChildNode(_xmlDocument, kLayer, ToString(object.GetLayer()), element);
		return true;
	}
	else {
		WLog() << "Unable to write object properties: Missing parent xml element";
		return false;
	}
}

bool ObjectVisitor::visitFont(const Font& font, XMLElement* parent)
{
	if (parent) {
		auto xmlFontResult = XmlWriter::CreateChildNode(_xmlDocument, kFont, parent);
		if (xmlFontResult.second) {
			auto* xmlFont = xmlFontResult.first;
			xmlFont->SetAttribute(kAttrName, font.family.c_str());
			xmlFont->SetAttribute(kAttrSize, ToString(font.size).c_str());
			XmlWriter::CreateTextChildNode(_xmlDocument, kBold, ToString(font.bold).c_str(), xmlFont);
			XmlWriter::CreateTextChildNode(_xmlDocument, kItalic, ToString(font.italic).c_str(), xmlFont);
			XmlWriter::CreateTextChildNode(_xmlDocument, kUnderline, ToString(font.underline).c_str(), xmlFont);
			XmlWriter::CreateTextChildNode(_xmlDocument, kStrikeout, ToString(font.strikeout).c_str(), xmlFont);
			return true;
		}
		else {
			WLog() << "Unable to create a font xml element";
		}
	}
	else {
		WLog() << "Unable to write font properties: Missing parent xml element";
	}
	return false;
}
