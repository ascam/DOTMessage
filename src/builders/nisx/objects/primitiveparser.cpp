#include "primitiveparser.hpp"
#include "builders/nisx/nisxcommonnames.hpp"
#include "utils/macsalogger.hpp"
#include "utils/stringutils.hpp"

using macsa::nisx::PrimitiveParser;
using macsa::nisx::PenParser;
using macsa::nisx::BrushParser;
using macsa::dot::Primitive;
using macsa::utils::MacsaLogger;
using tinyxml2::XMLElement;
using tinyxml2::XMLAttribute;
using namespace macsa::utils::stringutils;

namespace macsa {
	namespace nisx {
		namespace  {
			std::string str(const char* text) {
				return (text != nullptr ? text : "");
			}
		}
	}
}


PrimitiveParser::PrimitiveParser(const std::string& fieldType, macsa::dot::Object* primitive) :
	ObjectParser(fieldType, primitive),
	_primitive{dynamic_cast<Primitive*>(primitive)}
{
	if (!primitive || !_primitive) {
		std::stringstream message;
		message << "Unable to parse primitive field to a ";
		if (!primitive) {
			message << "nullptr object";
		}
		else {
			message << primitive->GetType().toString() << " object";
		}
		throw (std::invalid_argument(message.str()));
	}
}

bool PrimitiveParser::VisitEnter(const XMLElement& element, const XMLAttribute* attribute)
{
	std::string eName {str(element.Name())};
	if (!parseCommonElements(element, attribute, _primitive)) {
		if (eName == kPen) {
			PenParser parser(_primitive);
			element.Accept(&parser);
		}
		else if (eName == kBrush) {
			BrushParser parser(_primitive);
			element.Accept(&parser);
		}
		else if (eName == kFilled) {
			std::string eValue {str(element.GetText())};
			_primitive->SetFilled(ToBool(eValue));
		}
		else if (eName == kPrintBorder) {
			std::string eValue {str(element.GetText())};
			_primitive->ShowBorder(ToBool(eValue));
		}
		else if (eName == kDashStyle) {
			macsa::dot::LineStyle style{str(element.GetText())};
			macsa::dot::Pen pen {_primitive->GetPen()};
			pen.SetStyle(style);
			_primitive->SetPen(pen);
		}
		else if (eName == kDashStyle) {
			macsa::dot::Pen pen {_primitive->GetPen()};
			macsa::dot::PenStyle style {pen.GetStyle()};
			style.SetCustomDashedPattern({str(element.GetText())});
			pen.SetStyle(style);
			_primitive->SetPen(pen);
		}
		else if (eName != _fieldType) {
			std::stringstream trace;
			trace << "Unknown element (line " << element.GetLineNum() << "): " << element.Name();
			if (attribute) {
				trace << "\n\tattribute: " << attribute->Name();
			}
			ILog() << trace.str();
		}
	}
	return (eName == _fieldType);
}

PenParser::PenParser(dot::Primitive *primitive) :
	_primitive {primitive},
	_pen {_primitive->GetPen()}
{}

bool PenParser::VisitEnter(const XMLElement& element, const XMLAttribute* attribute)
{
	std::string eName {str(element.Name())};
	if (eName == kColor) {
		while (attribute) {
			std::string attrName {str(attribute->Name())};
			std::string attrValue {str(attribute->Value())};
			if (attrName == kName) {
				_primitive->SetBrush(attrValue);
			}
			else if (attrName == kAttrValue) {
//				color.FromARGBString(attrValue);
			}
			attribute = attribute->Next();
		}
	}
	else if (eName == kWidth) {
		if (attribute) {
			std::string attrName {str(attribute->Name())};
			std::string attrValue {str(attribute->Value())};
			if (attrName == kAttrValue) {
				_pen.SetWidth(ToDouble(attrValue));
			}
			else {
				WLog() << "Unknown width attribute \"" <<  attrName << "\"";
			}
		}
	}
	else if (eName != kPen) {
		std::stringstream trace;
		trace << "Unknown element (line " << element.GetLineNum() << "): " << element.Name();
		if (attribute) {
			trace << "\n\tattribute: " << attribute->Name();
		}
		ILog() << trace.str();
	}
	return (eName == kPen);
}

bool PenParser::VisitExit(const XMLElement& element)
{
	std::string eName {str(element.Name())};
	if (eName == kPen) {
		_primitive->SetPen(_pen);
	}
	return (eName == kPen);
}

BrushParser::BrushParser(dot::Primitive *primitive) :
	_primitive {primitive}
{}

bool BrushParser::VisitEnter(const XMLElement& element, const XMLAttribute* attribute)
{
	std::string eName {str(element.Name())};
	if (eName == kColor) {
		while (attribute) {
			std::string attrName {str(attribute->Name())};
			std::string attrValue {str(attribute->Value())};
			if (attrName == kName) {
				_primitive->SetBrush(attrValue);
			}
			else if (attrName == kAttrValue) {
//				color.FromARGBString(attrValue);
			}
			attribute = attribute->Next();
		}
	}
	else if (eName != kBrush) {
		std::stringstream trace;
		trace << "Unknown element (line " << element.GetLineNum() << "): " << element.Name();
		if (attribute) {
			trace << "\n\tattribute: " << attribute->Name();
		}
		ILog() << trace.str();
	}
	return (eName == kBrush);
}
