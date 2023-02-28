#include "fieldsparser.hpp"
#include "objects/objectparserfactory.hpp"
#include "utils/macsalogger.hpp"
#include "nisxcommonnames.hpp"

using macsa::nisx::FieldsParser;
using macsa::dot::Document;
using macsa::utils::MacsaLogger;
using tinyxml2::XMLElement;
using tinyxml2::XMLAttribute;
using macsa::dot::NObjectType;

static constexpr const char* kElementName = "FIELDS";

namespace {
	std::string str(const char* text) {
		return (text != nullptr ? text : "");
	}
}

FieldsParser::FieldsParser(Document &doc) :
	_dom(doc)
{}

FieldsParser::~FieldsParser()
{}

bool FieldsParser::VisitEnter(const XMLElement& element, const XMLAttribute* firstAttribute)
{
	std::string fieldType {str(element.Name())};
	if (fieldType != kElementName) {
		auto objectType = GetObjectsMap().find(fieldType);
		if (objectType != GetObjectsMap().end()) {
			std::string objectId = "NewItem";
			if (!firstAttribute || strcmp(firstAttribute->Name(), "Name") != 0) {
				WLog() << "Missing name attribute";
				objectId.append(std::to_string(_dom.GetObjects().size()));
			}
			else {
				objectId = firstAttribute->Value();
			}
			auto* object = _dom.AddObject(objectId, objectType->second);
			if (object) {
				ObjectParser* parser {ObjectParsersFactory::Get(objectType->first, object)};
				if (parser){
					element.Accept(parser);
					delete parser;
				}
				else {
					ELog() << "Unable to parser field of type " << fieldType << ". PARSER NOT IMPLEMENTED.";
				}
			}
			else {
				WLog() << "Unable to create a new object in the document with the id: \"" << objectId << "\"";
			}
		}
		else {
			ELog() << "Unable to parser field of type " << fieldType << ". NOT IMPLEMENTED.";
		}
	}
	return (fieldType == kElementName);
}

bool FieldsParser::VisitExit(const XMLElement &element)
{
	return true;
}

const std::map<std::string, macsa::dot::NObjectType>& FieldsParser::GetObjectsMap()
{
	static std::map<std::string,macsa::dot::NObjectType> kObjectsMap = {
		{macsa::nisx::kTextField,      NObjectType::kText},
		{macsa::nisx::kBarcodeField,   NObjectType::kBarcode},
		{macsa::nisx::kImageField,     NObjectType::kImage},
		{macsa::nisx::kRectangleField, NObjectType::kRectangle},
		{macsa::nisx::kEllipseField,   NObjectType::kEllipse},
		{macsa::nisx::kLineField,      NObjectType::kLine},
		{macsa::nisx::kDiamondField,   NObjectType::kDiamond},
	};
	return kObjectsMap;
}
