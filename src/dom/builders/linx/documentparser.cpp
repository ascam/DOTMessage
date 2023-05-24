#include "documentparser.hpp"
#include "docproperties.hpp"
#include "dom/builders/linx/objects/textparser.hpp"
#include "dom/builders/linx/objects/barcodeparser.hpp"
#include "dom/builders/linx/objects/imageparser.hpp"
#include "dom/builders/linx/objects/primitiveparser.hpp"
#include "dom/builders/linx/offsetdateparser.hpp"
#include "utils/macsalogger.hpp"
#include "utils/stringutils.hpp"

using namespace macsa::linx;
using macsa::linx::DocumentParser;
using macsa::utils::MacsaLogger;
using macsa::linx::OffsetDateParser;
using namespace macsa::utils::stringutils;

static constexpr const char* kImageDesign = "ImageDesign";
static constexpr const char* kVersion = "Version";
static constexpr const char* kHeader = "Header";
static constexpr const char* kClStVersionInfo = "ClStVersionInfo";
static constexpr const char* kLastDownloaded = "LastDownloaded";
static constexpr const char* kDesignedFor = "DesignedFor";
static constexpr const char* kDesignedWith = "DesignedWith";
static constexpr const char* kUnits = "Units";
static constexpr const char* kSubImage = "SubImage";
static constexpr const char* kSubHeader = "SubHeader";
static constexpr const char* kDateOffset = "DateOffset";
static constexpr const char* kDataSource = "DataSource";
static constexpr const char* kGenericSettings = "GenericSettings";
static constexpr const char* kName = "Name";
static constexpr const char* kMillimeters = "mm";
static constexpr uint8_t kSupportedVersion = 23;

//Field types
static constexpr const char* kText = "Text"; //userfields are FixedText objects
static constexpr const char* kBarcodeField = "Barcode";
static constexpr const char* kImageField = "StaticGraphic"; //img
static constexpr const char* kPrimitiveField = "GraphicPrimitive";
static constexpr const char* kMergeField = "MergeField";

DocumentParser::DocumentParser(macsa::dot::Document& document) :
	_doc{document},
	_context{_doc}
{
	_offsetDateMap.clear();
	dot::ColorsPalette palette;
	palette.emplace("black", dot::Color("black", 0, 0, 0));
	palette.emplace("white", dot::Color("white", 255, 255, 255));
	palette.emplace("transparent", dot::Color("transparent", 255, 255, 255, 0));
	_doc.SetColorsPalette(palette);
	_doc.SetUnits(kMillimeters);
}

std::string DocumentParser::GetSupportedLinxVersion()
{
	std::stringstream version;
	version << kSupportedVersion;
	return version.str();
}

bool DocumentParser::VisitEnter(const tinyxml2::XMLElement& element, const tinyxml2::XMLAttribute* attribute)
{
	std::string eName {ToString(element.Name())};
	std::string eAttName;
	if (attribute){
		eAttName = ToString(attribute->Name());
	}

	DLog() << "element (line " << element.GetLineNum() << "): \"" << element.Name() << "\"";

	if (eName == kImageDesign) {
		if (eAttName == kVersion) {
			std::string version {ToString(attribute->Value())};
			_doc.SetVersion(getDocumentVersion(version));
			if (utils::stringutils::ToInt(version) > kSupportedVersion){
				WLog() << "Document version not supported : " << version;
			}
		}
		else {
			WLog() << "Document's version is not available";
		}
		return true;
	}
	else if (eName == kHeader){
		while (attribute){
			if (eAttName == kDesignedFor){
				DLog() << "Document designed for: " << ToString(attribute->Value());
			}
			else if (eAttName == kDesignedWith){
				DLog() << "Document designed for: " << ToString(attribute->Value());
			}
			attribute = attribute->Next();
		}
		return true;
	}
	else if (eName == kClStVersionInfo){
		return false;
	}
	else if (eName == kLastDownloaded){
		return false;
	}
	else if (eName == kUnits){
		std::string eUnits = ToString(element.GetText());
		_context.SetUnits(ToLower(eUnits));
		return false;
	}
	else if (eName == kDateOffset) {
		OffsetDateParser offsetDateParser(_offsetDateMap);
		element.Accept(&offsetDateParser);
		return false;
	}
	else if (eName == kDataSource) {
		return false;
	}
	else if (eName == kSubImage) {
		return true;
	}
	else if (eName == kSubHeader) {
		DocumentPropertiesParser properties(_context);
		element.Accept(&properties);
		return false;
	}
	else if (eName == kField) {
		std::string attrName = ToString(element.FirstAttribute()->Name());
		std::string firstChildName = element.FirstAttribute() ? ToString(element.FirstChildElement()->Name()) : "";
		if (attrName == kName && firstChildName == kFldType){
			std::string fieldName {ToString(element.FirstAttribute()->Value())};
			if (fieldName.empty()){
				fieldName.append(std::to_string(_doc.GetObjects().size()));
				WLog() << "Missing field name, new name = " << fieldName;
			}
			std::string fieldType {ToString(element.FirstChildElement(kFldType)->GetText())};
			parseConcreteField(element, fieldName, fieldType);
		}
		else{
			WLog() << "No valid field: " << eName;
		}
		return false;
	}
	else if (eName == kGenericSettings) {
		return false;
	}
	else {
		std::stringstream trace;
		trace << "Unknown element (line " << element.GetLineNum() << "): " << element.Name();
		if (attribute) {
			trace << "\n\tattribute: " << attribute->Name();
		}
		WLog() << trace.str();
	}
	return true; //Continue parsing
}

bool DocumentParser::Visit(const tinyxml2::XMLDeclaration& declaration)
{
	DLog() << "XMLDeclaration (line " << declaration.GetLineNum() << "): "
		   << macsa::utils::ColorLog::kLightGreen << declaration.Value()
		   << macsa::utils::ColorLog::kNoColor;
	return true;
}

bool DocumentParser::Visit(const tinyxml2::XMLText& text)
{
	ILog() << "text element line: " << text.GetLineNum() << " - " << text.Value();
	return true;
}

bool DocumentParser::Visit(const tinyxml2::XMLComment& comment)
{
	DLog() << "XMLComment line: " << comment.GetLineNum();
	return true;
}

bool DocumentParser::Visit(const tinyxml2::XMLUnknown& unknown)
{
	ELog() << "XMLUnknown line: " << unknown.GetLineNum();
	return true;
}

std::array<uint8_t,3> DocumentParser::getDocumentVersion(const std::string &versionAttribute) const
{
	std::array<uint8_t,3> docVersion{};
	auto version = Split(versionAttribute, ".");
	for (uint index = 0; index < 3; index++) {
		if (version.size() > index) {
			docVersion[index] = static_cast<uint8_t>(ToInt(version.at(index)));
		}
	}
	return docVersion;
}

void DocumentParser::parseConcreteField(const tinyxml2::XMLElement &element, std::string& fieldName, std::string &fieldType)
{
	DLog() << " FieldName: " << fieldName;
	DLog() << " FieldType: " << fieldType;
	if (utils::stringutils::EndsWith(fieldType, kText)){
		auto* text = _doc.AddObject(fieldName, dot::NObjectType::kText);
		if (!text) {
			ELog() << "Unable to add new text object: " << fieldName;
			return;
		}
		TextParser textParser(text, _context, _offsetDateMap);
		element.Accept(&textParser);
	}
	else if (fieldType == kBarcodeField){
		auto* barcode = _doc.AddObject(fieldName, dot::NObjectType::kBarcode);
		if (!barcode){
			ELog() << "Unable to add new barcode object: " << fieldName;
			return;
		}
		BarcodeParser barcodeParser(barcode, _context, _offsetDateMap);
		element.Accept(&barcodeParser);
	}

	else if (fieldType == kImageField){
		auto* image = _doc.AddObject(fieldName, dot::NObjectType::kImage);
		if (!image){
			ELog() << "Unable to add new barcode object: " << fieldName;
		}
		ImageParser imageParser(image, _context);
		element.Accept(&imageParser);
	}
	else if (fieldType == kPrimitiveField){
		PrimitiveParser primitiveParser(_context, fieldName);
		element.Accept(&primitiveParser);
	}
	else if (fieldType == kMergeField){
		WLog() << " FieldType 'MergeField' is not supported. (line" << element.GetLineNum() << ")";
	}
	else{
		std::stringstream trace;
		trace << "Unknown element (line " << element.GetLineNum() << "): " << fieldType;
		ELog() << trace.str();
	}
}
