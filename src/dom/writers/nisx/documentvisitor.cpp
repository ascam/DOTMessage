#include "documentvisitor.hpp"
#include "dom/writers/nisxwriter.hpp"
#include "dom/object.hpp"
#include "dom/variableobject.hpp"
#include "dom/text.hpp"
#include "dom/barcode.hpp"
#include "dom/primitives.hpp"
#include "dom/image.hpp"
#include "textvisitor.hpp"
#include "barcodevisitor.hpp"
#include "imagevisitor.hpp"
#include "primitivesvisitor.hpp"
#include "nisxcommonnames.hpp"
#include "xmltools/xmlwriter.hpp"
#include "utils/stringutils.hpp"
#include "utils/macsalogger.hpp"

using macsa::nisx::DocumentVisitor;
using macsa::dot::Document;
using macsa::utils::MacsaLogger;
using macsa::xmltools::XmlWriter;
using namespace macsa::utils::stringutils;

static constexpr const char* kXmlDeclaration = "xml version=\"1.0\" encoding=\"utf-8\"";
static constexpr const char* kNeoFile = "NEOFILE";
static constexpr const char* kVersionAttr = "Version";
static constexpr const char* kProperties = "PROPERTIES";
static constexpr const char* kMeasureUnits = "MEASURE_UNITS";
static constexpr const char* kResolution = "RESOLUTION";
static constexpr const char* kMinUnit = "MIN_UNIT";
static constexpr const char* kFields = "FIELDS";

DocumentVisitor::DocumentVisitor(tinyxml2::XMLDocument& xmlDocument, const dot::Document& dom) :
	_dom(dom),
	_xmlDocument(xmlDocument)
{}

bool DocumentVisitor::VisitEnter(const dot::Document& document)
{
	_xmlDocument.Clear();
	auto* xmlDeclaration = _xmlDocument.NewDeclaration(kXmlDeclaration);
	if (xmlDeclaration) {
		_xmlDocument.InsertEndChild(xmlDeclaration);
	}

	auto* xmlNeoFile = _xmlDocument.NewElement(kNeoFile);
	if (xmlNeoFile) {
		xmlNeoFile->SetAttribute(kVersionAttr, dot::NisxWriter::GetWriterNisxVersion().c_str());
		_xmlDocument.InsertEndChild(xmlNeoFile);

		if (!writeProperties(xmlNeoFile, document)) {
			ELog() << "Unable to set document properties";
			return false;
		}
		if (!writeColorsPallete(xmlNeoFile, document)) {
			WLog() << "Unable to set document colors palette";
		}

		auto xmlFields = XmlWriter::CreateChildNode(_xmlDocument, kFields, xmlNeoFile);
		if (xmlFields.second) {
			_xmlFields = xmlFields.first;
		}
		else {
			ELog() <<  "Unable to set document fields";
			return false;
		}
	}

	ILog() << "Document " << document.GetName() << " generated!";

	return true;
}

bool DocumentVisitor::VisitExit(const dot::Document& document)
{
	ILog() << "Document " << document.GetName();
	return true;
}

bool DocumentVisitor::VisitEnter(const dot::Text& text)
{
	DLog() << "Text " << text.GetId();
	TextVisitor visitor(_xmlDocument, _xmlFields, _dom);
	return text.Accept(&visitor);
}

bool DocumentVisitor::VisitEnter(const dot::Barcode& barcode)
{
	DLog() << "Barcode " << barcode.GetId();
	BarcodeVisitor visitor(_xmlDocument, _xmlFields, _dom);
	return barcode.Accept(&visitor);
}

bool DocumentVisitor::Visit(const dot::Image& image)
{
	DLog() << "Image " << image.GetId();
	ImageVisitor visitor(_xmlDocument, _xmlFields);
	return image.Accept(&visitor);
}

bool DocumentVisitor::Visit(const dot::Rectangle& rectangle)
{
	DLog() << "Rectangle " << rectangle.GetId();
	PrimitivesVisitor visitor(_xmlDocument, _xmlFields, _dom);
	return rectangle.Accept(&visitor);
}

bool DocumentVisitor::Visit(const dot::Ellipse& ellipse)
{
	DLog() << "Ellipse " << ellipse.GetId();
	PrimitivesVisitor visitor(_xmlDocument, _xmlFields, _dom);
	return ellipse.Accept(&visitor);
}

bool DocumentVisitor::Visit(const dot::Diamond& diamond)
{
	DLog() << "Diamond " << diamond.GetId();
	PrimitivesVisitor visitor(_xmlDocument, _xmlFields, _dom);
	return diamond.Accept(&visitor);
}

bool DocumentVisitor::Visit(const dot::Line& line)
{
	DLog() << "Line " << line.GetId();
	PrimitivesVisitor visitor(_xmlDocument, _xmlFields, _dom);
	return line.Accept(&visitor);
}

bool DocumentVisitor::writeProperties(tinyxml2::XMLElement* parent, const Document& document)
{
	auto xmlProperties = XmlWriter::CreateChildNode(_xmlDocument, kProperties, parent);
	if (xmlProperties.second) {
		XmlWriter::CreateTextChildNode(_xmlDocument, kMeasureUnits, document.GetUnits(), xmlProperties.first);
		XmlWriter::CreateTextChildNode(_xmlDocument, kResolution, "300", xmlProperties.first);
		XmlWriter::CreateTextChildNode(_xmlDocument, kMinUnit, "0.01", xmlProperties.first);
		XmlWriter::CreateTextChildNode(_xmlDocument, kWidth, ToString(document.GetCanvasWidth(), 2), xmlProperties.first);
		XmlWriter::CreateTextChildNode(_xmlDocument, kHeight, ToString(document.GetCanvasHeight(), 2), xmlProperties.first);
	}
	return xmlProperties.second;
}

bool DocumentVisitor::writeColorsPallete(tinyxml2::XMLElement* parent, const Document& document)
{
	auto xmlColors = XmlWriter::CreateChildNode(_xmlDocument, kColors, parent);
	if (xmlColors.second) {
		const auto& palette {document.GetColorsPalette()};
		for (const auto& color : palette) {
			auto xmlColor = XmlWriter::CreateChildNode(_xmlDocument, kColor, xmlColors.first);
			if (xmlColor.second) {
				xmlColor.first->SetAttribute(kAttrName, color.first.c_str());
				xmlColor.first->SetAttribute(kAttrColor, color.second.ToARGBString().c_str());
			}
		}
	}
	return xmlColors.second;
}
