#include "primitivesvisitor.hpp"
#include <cmath>
#include "nisxcommonnames.hpp"
#include "utils/macsalogger.hpp"
#include "utils/stringutils.hpp"
#include "xmltools/xmlwriter.hpp"

using macsa::nisx::PrimitivesVisitor;
using macsa::dot::Primitive;
using macsa::dot::Rectangle;
using macsa::dot::Ellipse;
using macsa::dot::Diamond;
using macsa::dot::Line;
using macsa::dot::Pen;
using macsa::dot::Color;
using macsa::xmltools::XmlWriter;
using macsa::utils::MacsaLogger;
using tinyxml2::XMLDocument;
using tinyxml2::XMLElement;
using namespace macsa::utils::stringutils;

static constexpr const char* kRectangleField = "RECTANGLEFIELD";
static constexpr const char* kEllipseField = "ELLIPSEFIELD";
static constexpr const char* kLineField = "LINEFIELD";
static constexpr const char* kDiamondField = "DIAMONDFIELD";
static constexpr const char* kPen = "PEN";
static constexpr const char* kBrush = "BRUSH";
static constexpr const char* kFilled = "FILLED";
static constexpr const char* kPrintBorder = "PRINTBORDER";
static constexpr const char* kDashStyle = "DASHSTYLE";
static constexpr const char* kDashCustom =  "DASHCUSTOM";

PrimitivesVisitor::PrimitivesVisitor(XMLDocument& document, XMLElement* parent, const dot::Document& dom) :
	ObjectVisitor(document),
	_dom{dom},
	_xmlParent{parent},
	_xmlElement{}
{}

bool PrimitivesVisitor::Visit(const Rectangle& rectangle)
{
	if (!buildPrimitiveField(kRectangleField, rectangle)) {
		return false;
	}
	return writePoligonsProperties(rectangle, _xmlElement);
}

bool PrimitivesVisitor::Visit(const Ellipse& ellipse)
{
	if (!buildPrimitiveField(kEllipseField, ellipse)) {
		return false;
	}
	return writePoligonsProperties(ellipse, _xmlElement);
}

bool PrimitivesVisitor::Visit(const Diamond& diamond)
{
	if (!buildPrimitiveField(kDiamondField, diamond)) {
		return false;
	}
	return writePoligonsProperties(diamond, _xmlElement);
}

bool PrimitivesVisitor::Visit(const Line& line)
{
	return buildPrimitiveField(kLineField, line);
}

bool PrimitivesVisitor::buildPrimitiveField(const std::string& type, const Primitive& primitive)
{
	if (_xmlParent) {
		auto xmlElementResult = XmlWriter::CreateChildNode(_xmlDocument, type, _xmlParent);
		if (xmlElementResult.second){
			_xmlElement = xmlElementResult.first;
			_xmlElement->SetAttribute(kAttrName, primitive.GetId().c_str());
			if (!visitObject(primitive, _xmlElement)) {
				ELog() << "Unable to write common object properties for " << type << " component (id: " << primitive.GetId() << ")";
				return false;
			}
			if (!writePen(primitive.GetPen(), _xmlElement)) {
				ELog() << "Unable to write primitive pen properties for " << type << " component (id: " << primitive.GetId() << ")";
				return false;
			}
			return true;
		}
		else {
			ELog() << "Unable to create new " << type << " component";
		}
	}
	else {
		ELog() << "Unable to create new " << type << " component: Missing xml parent element";
	}
	return false;
}

bool PrimitivesVisitor::writePen(const Pen& pen, XMLElement* parent) const
{
	auto xmlPenResult = XmlWriter::CreateChildNode(_xmlDocument, kPen, parent);
	if (!xmlPenResult.second) {
		ELog() << "Unable to create new PEN component.";
		return false;
	}

	writeColor((getColor(pen.GetColor().GetName())), xmlPenResult.first);
	auto xmlPenWidthResult = XmlWriter::CreateChildNode(_xmlDocument, kWidth, xmlPenResult.first);
	if (xmlPenWidthResult.second) {
		xmlPenWidthResult.first->SetAttribute(kAttrValue, static_cast<uint>(std::round(pen.GetWidth())));
	}
	const auto& penStyle = pen.GetStyle();
	auto lineStyle = penStyle.GetLineStyle();
	XmlWriter::CreateTextChildNode(_xmlDocument, kDashStyle, lineStyle.toString(), parent);
	if (lineStyle() == dot::NLineStyle::kCustom) {
		XmlWriter::CreateTextChildNode(_xmlDocument, kDashCustom, penStyle.GetCustomDashedPattern(), parent);
	}

	return true;
}

bool PrimitivesVisitor::writePoligonsProperties(const macsa::dot::Primitive &primitive, tinyxml2::XMLElement *parent) const
{
	auto xmlBrushResult = XmlWriter::CreateChildNode(_xmlDocument, kBrush, parent);
	if (xmlBrushResult.second) {
		writeColor(getColor(primitive.GetBrush().GetName()), xmlBrushResult.first);
	}
	else {
		ELog() << "Unable to create new PEN component.";
		return false;
	}
	XmlWriter::CreateTextChildNode(_xmlDocument, kFilled, ToString(primitive.IsFilled()), parent);
	XmlWriter::CreateTextChildNode(_xmlDocument, kPrintBorder, ToString(primitive.HasBorder()), parent);
	return true;
}

bool PrimitivesVisitor::writeColor(const Color &color, XMLElement* parent) const
{
	auto xmlColorResult = XmlWriter::CreateChildNode(_xmlDocument, kColor, parent);
	if (xmlColorResult.second) {
		xmlColorResult.first->SetAttribute(kAttrName, color.GetName().c_str());
		xmlColorResult.first->SetAttribute(kAttrValue, color.ToARGBString().c_str());
		return true;
	}
	else {
		ELog() << "Unable to create new COLOR component.";
	}
	return false;
}

macsa::dot::Color PrimitivesVisitor::getColor(const std::string &name) const
{
	const auto& palette = _dom.GetColorsPalette();
	if (palette.find(name) != palette.end()) {
		return palette.at(name);
	}
	else {
		return Color(name);
	}
}

