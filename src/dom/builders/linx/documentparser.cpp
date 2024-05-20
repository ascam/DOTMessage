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
static constexpr uint32_t kSupportedVersion = 23;

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
	_doc.SetColorsPalette(_context.GetColorsPalette());
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

	DLog() << "element (line " << element.GetLineNum() << "): \"" << element.Name() << "\"";

	if (eName == kImageDesign) {
		if (attribute && ToString(attribute->Name()) == kVersion) {
			std::array<uint8_t, 3> version{};
			version[0] = static_cast<uint8_t>(attribute->IntValue());
			_doc.SetVersion(version);
			if (version[0] > kSupportedVersion) {
				WLog() << "Document's version not supported : " << version[0];
			}
		}
		else {
			WLog() << "Document's version is not available";
		}
		return true;
	}
	else if (eName == kHeader) {
		while (attribute) {
			std::string eAttName = ToString(attribute->Name());
			if (eAttName == kDesignedFor) {
				DLog() << "Document designed for: " << ToString(attribute->Value());
			}
			else if (eAttName == kDesignedWith) {
				DLog() << "Document designed with: " << ToString(attribute->Value());
			}
			attribute = attribute->Next();
		}
		return true;
	}
	else if (eName == kClStVersionInfo) {
		return false;
	}
	else if (eName == kLastDownloaded) {
		return false;
	}
	else if (eName == kUnits) {
		std::string eUnits = ToString(element.GetText());
		_context.SetUnits(ToLower(eUnits));
		return false;
	}
	else if (eName == kDateOffset) {
		OffsetDateParser offsetDateParser(_context);
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
		std::string attrName {attribute ? ToString(attribute->Name()) : ""};
		std::string firstChildName {element.FirstChildElement() ? ToString(element.FirstChildElement()->Name()) : ""};
		if (attrName == kName && firstChildName == kFldType) {
			std::string fieldType {ToString(element.FirstChildElement(kFldType)->GetText())};
			std::string fieldName {attribute ? ToString(attribute->Value()) : ""};
			if (fieldName.empty()) {
				fieldName = fieldType;
				fieldName.append(std::to_string(_doc.GetObjects().size()));
				WLog() << "Missing field name, new name = " << fieldName;
			}
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
	return true;
}

void DocumentParser::parseConcreteField(const tinyxml2::XMLElement& element, const std::string& fieldName, const std::string& fieldType)
{
	DLog() << " FieldName: " << fieldName;
	DLog() << " FieldType: " << fieldType;
	if (utils::stringutils::EndsWith(fieldType, kText)) {
		auto* text = _doc.AddObject(fieldName, dot::NObjectType::kText);
		if (!text) {
			ELog() << "Unable to add new text object: " << fieldName;
			return;
		}
		try {
			TextParser textParser(text, _context);
			element.Accept(&textParser);
		}
		catch(const std::exception& exc) {
			ELog() << "Unable to create a TextParser" << exc.what();
		}
	}
	else if (fieldType == kBarcodeField) {
		auto* barcode = _doc.AddObject(fieldName, dot::NObjectType::kBarcode);
		if (!barcode) {
			ELog() << "Unable to add new barcode object: " << fieldName;
			return;
		}
		try {
			BarcodeParser barcodeParser(barcode, _context);
			element.Accept(&barcodeParser);
		}
		catch(const std::exception& exc) {
			ELog() << "Unable to create a BarcodeParser" << exc.what();
		}
	}
	else if (fieldType == kImageField) {
		auto* image = _doc.AddObject(fieldName, dot::NObjectType::kImage);
		if (!image) {
			ELog() << "Unable to add new barcode object: " << fieldName;
		}
		try {
			ImageParser imageParser(image, _context);
			element.Accept(&imageParser);
		}
		catch(const std::exception& exc) {
			ELog() << "Unable to create a ImageParser" << exc.what();
		}
	}
	else if (fieldType == kPrimitiveField) {
		PrimitiveParser primitiveParser(_context, fieldName);
		element.Accept(&primitiveParser);
	}
	else if (fieldType == kMergeField) {
		WLog() << " FieldType 'MergeField' is not supported. (line" << element.GetLineNum() << ")";
	}
	else{
		std::stringstream trace;
		trace << "Unknown element (line " << element.GetLineNum() << "): " << fieldType;
		ELog() << trace.str();
	}
}
