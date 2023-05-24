#include "fieldsparser.hpp"
#include "objects/objectparserfactory.hpp"
#include "utils/macsalogger.hpp"
#include "linxcommonnames.hpp"

using macsa::linx::FieldsParser;
using macsa::dot::Document;
using macsa::utils::MacsaLogger;
using tinyxml2::XMLElement;
using tinyxml2::XMLAttribute;
using macsa::dot::NObjectType;

static constexpr const char* kElementName = "Field";
static constexpr const char* kName = "Name";

namespace {
	std::string str(const char* text) {
		return (text != nullptr ? text : "");
	}
}

FieldsParser::FieldsParser(dot::Document &doc) :
	_dom(doc)
{}

FieldsParser::~FieldsParser()
{}

bool FieldsParser::VisitEnter(const XMLElement& element, const XMLAttribute* firstAttribute)
{
	std::string eField {str(element.Name())};
	if (eField != kElementName) {
		std::string fieldType = element.FirstChildElement()->GetText();
		auto objectType = GetObjectsMap().find(fieldType);
		if (objectType != GetObjectsMap().end()) {
			std::string objectId = "NewItem";
			if (!firstAttribute || strcmp(firstAttribute->Name(), kName) != 0) {
				WLog() << "Missing name attribute";
				objectId.append(std::to_string(_dom.GetObjects().size()));
			}
			else{
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
	return (eField == kElementName);
}

bool FieldsParser::VisitExit(const XMLElement &element)
{
	return true;
}

const std::map<std::string, macsa::dot::NObjectType>& FieldsParser::GetObjectsMap()
{
	static std::map<std::string,macsa::dot::NObjectType> kObjectsMap = {
		{kFixedTextField, NObjectType::kText},
		{kDateTextField, NObjectType::kText},
		{kCounterTextField, NObjectType::kText},
		{kBarcodeField, NObjectType::kBarcode},
		{kImageField, NObjectType::kImage},
		{kPrimitiveField, NObjectType::kRectangle}
	};
	return kObjectsMap;
}
