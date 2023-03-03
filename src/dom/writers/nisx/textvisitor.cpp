#include "textvisitor.hpp"
#include "nisxcommonnames.hpp"
#include "xmltools/xmlwriter.hpp"
#include "utils/macsalogger.hpp"
#include "utils/stringutils.hpp"

using macsa::nisx::TextVisitor;
using macsa::dot::Text;
using macsa::dot::TextBoxProperties;
using macsa::xmltools::XmlWriter;
using macsa::utils::MacsaLogger;
using namespace macsa::utils::stringutils;

static constexpr const char* kTextField = "TEXTFIELD";
static constexpr const char* kText = "TEXT";
static constexpr const char* kHorizontal = "HORIZONTAL";
static constexpr const char* kVertical = "VERTICAL";
static constexpr const char* kFitToBox = "FITTOBOX";
static constexpr const char* kParagraph = "PARAGRAPH";
static constexpr const char* kMaxCharsLine = "MAXCHARSLINE";
static constexpr const char* kAutoincrement = "AUTOINC";
static constexpr const char* kInterLine = "INTERLINE";

TextVisitor::TextVisitor(tinyxml2::XMLDocument &xmlDocument, tinyxml2::XMLElement *xmlParent, const dot::Document& dom) :
	VariableObjectVisitor(xmlDocument, dom),
	_xmlParent{xmlParent}
{}

bool TextVisitor::VisitEnter(const Text& text)
{
	if (_xmlParent) {
		auto xmlElementResult = XmlWriter::CreateChildNode(_xmlDocument, kTextField, _xmlParent);
		if (xmlElementResult.second){
			_xmlElement = xmlElementResult.first;
			_xmlElement->SetAttribute(kAttrName, text.GetId().c_str());
			if (!visitObject(text, _xmlElement)) {
				return false;
			}
			return true;
		}
		else {
			ELog() << "Unable to create new TEXFIELD component";
		}
	}
	else {
		ELog() << "Unable to create new TEXFIELD component: Missing xml parent element";
	}

	return false;
}

bool TextVisitor::VisitExit(const Text& text)
{
	DLog() << text.GetId();
	if (_xmlParent && _xmlElement) {
		if (_xmlDataSource != nullptr) {
			_xmlElement->InsertEndChild(_xmlDataSource);
		}
		XmlWriter::CreateTextChildNode(_xmlDocument, kText, text.GetText(), _xmlElement);
		if (!visitFont(text.GetFont(), _xmlElement)) {
			return false;
		}
		writeColor(text.GetForegroundColor(), XmlWriter::CreateChildNode(_xmlDocument, kForeColor, _xmlElement).first);
		writeColor(text.GetBackgroundColor(), XmlWriter::CreateChildNode(_xmlDocument, kBackColor, _xmlElement).first);
		visitTextBoxProperties(text.GetTextBoxProperties());
		return true;
	}
	return false;
}

bool TextVisitor::visitTextBoxProperties(const TextBoxProperties& textBox)
{
	auto xmlAdjustResult = XmlWriter::CreateChildNode(_xmlDocument, kAdjust, _xmlElement);
	if (xmlAdjustResult.second) {
		auto* xmlAdjust = xmlAdjustResult.first;
		XmlWriter::CreateTextChildNode(_xmlDocument, kHorizontal, textBox.GetHorizontalAlignment().toString(), xmlAdjust);
		XmlWriter::CreateTextChildNode(_xmlDocument, kVertical, textBox.GetVerticalAlignment().toString(), xmlAdjust);
		if (textBox.GetBoxAdjustment() == dot::NTextBoxAdjustment::kFitToBox) {
			auto xmlFitToBoxResult = XmlWriter::CreateChildNode(_xmlDocument, kFitToBox, xmlAdjust);
			if (xmlFitToBoxResult.second) {
				XmlWriter::CreateTextChildNode(_xmlDocument, kMaxCharsLine, ToString(textBox.GetMaxCharsLine()), xmlFitToBoxResult.first);
			}
		}
		else if (textBox.GetBoxAdjustment() == dot::NTextBoxAdjustment::kParagraph) {
			auto xmlParagraphResult = XmlWriter::CreateChildNode(_xmlDocument, kParagraph, xmlAdjust);
			if (xmlParagraphResult.second) {
				XmlWriter::CreateTextChildNode(_xmlDocument, kAutoincrement, ToString(!textBox.GetClipText()), xmlParagraphResult.first);
				XmlWriter::CreateTextChildNode(_xmlDocument, kInterLine, ToString(textBox.GetLineSpacing()), xmlParagraphResult.first);
			}
		}
		return true;
	}
	return false;
}
