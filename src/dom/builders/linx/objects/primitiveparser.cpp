#include "primitiveparser.hpp"
#include "dom/components/pen.hpp"
#include "dom/primitives.hpp"
#include "utils/macsalogger.hpp"
#include "utils/stringutils.hpp"
#include <cmath>

using tinyxml2::XMLElement;
using tinyxml2::XMLAttribute;
using macsa::linx::PrimitiveParser;
using macsa::utils::MacsaLogger;
using namespace macsa::utils::stringutils;

static constexpr const char* kGraphic = "Graphic";
static constexpr const char* kPrimitive = "Primitive";
static constexpr const char* kGfxW = "GfxW";
static constexpr const char* kGfxH = "GfxH";
static constexpr const char* kShape = "Shape";
static constexpr const char* kLineW = "LineW";
static constexpr const char* kFilledBox = "FilledBox";
static constexpr const char* kOutlineBox = "OutlineBox";
static constexpr const char* kFilledEllipse = "FilledEllipse";
static constexpr const char* kOutlineEllipse = "OutlineEllipse";
static constexpr const char* kBlack = "black";
static constexpr const float kDotsPerInch = 0.12;

PrimitiveParser::PrimitiveParser(LinxParserContext& context, std::string &fieldName):
	ObjectParser{},
	_context{context},
	_fieldName{fieldName},
	_displayed{true},
	_geometry{},
	_filled{false},
	_rotation{0}
{}

bool PrimitiveParser::VisitEnter(const tinyxml2::XMLElement &element, const tinyxml2::XMLAttribute *attribute)
{
	std::string eName {ToString(element.Name())};
	std::string eValue {ToString(element.GetText())};
	DLog() << eName << " : " << eValue;

	if (eName == kField){
		return true;
	}
	else if (eName == kDisplayed){
		_displayed = ToBool(element.GetText());
		return false;
	}
	else if (parseCommonElements(element)){
		return false;
	}
	else if (parseGeometry(element, _geometry)) {
		return false;
	}
	else if (eName == kData){
		return false;
	}
	else if (eName == kGraphic){
		return true;
	}
	else if (eName == kGfxW){
		return false;
	}
	else if (eName == kGfxH){
		return false;
	}
	else if (eName == kPrimitive){
		return true;
	}
	else if (eName == kShape){
		if (eValue == kFilledBox){
			_objectType = dot::NObjectType::kRectangle;
			_filled = true;
		}
		else if (eValue == kOutlineBox){
			_objectType = dot::NObjectType::kRectangle;
		}
		else if (eValue == kFilledEllipse){
			_objectType = dot::NObjectType::kEllipse;
			_filled = true;
		}
		else if (eValue == kOutlineEllipse){
			_objectType = dot::NObjectType::kEllipse;
		}
		else{
			_objectType = dot::NObjectType::kLine;
		}
		return false;
	}
	else if(eName == kLineW){
		int lineWidth = std::round(ToDouble(eValue)*kDotsPerInch);
		_pen.SetWidth(lineWidth);
		return false;
	}
	else{
		std::stringstream trace;
		trace << "Unknown element (line " << element.GetLineNum() << "): " << element.Name();
		if (attribute) {
			trace << "\n\tattribute: " << attribute->Name();
		}
		WLog() << trace.str();
	}
	return (eName == kField);
}

bool PrimitiveParser::VisitExit(const tinyxml2::XMLElement &element)
{
	std::string eName {ToString(element.Name())};
	if (eName == kField){
		auto* object = _context.GetDocument().AddObject(_fieldName, _objectType);
		if (object){
			object->SetPrintable(_displayed);
			auto* primitive = dynamic_cast<dot::Primitive*>(object);
			if (primitive){
				primitive->SetRotation(_rotation);
				primitive->SetGeometry(_geometry);
				primitive->SetFilled(_filled);
				primitive->SetPen(_pen);
				primitive->SetBrush(dot::Color(kBlack));
			}
			else{
				ELog() << "Primitive object is not avalaible - field name: " << _fieldName;
				return false;
			}
		}
		else{
			ELog() << "Unable to add new primitive object - field name: " << _fieldName;
			return false;
		}
		object->SetGeometry(_context.CheckGeometry(_geometry));
	}
	return true;
}
