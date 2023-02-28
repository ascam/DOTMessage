#include "documentparser.hpp"
#include "doccolors.hpp"
#include "docproperties.hpp"
#include "fieldsparser.hpp"
#include "utils/macsalogger.hpp"
#include "utils/stringutils.hpp"

using macsa::nisx::DocumentParser;
using macsa::utils::MacsaLogger;
using namespace macsa::utils::stringutils;

static constexpr const char* kNeoFile = "NEOFILE";
static constexpr const char* kVersion = "Version";
static constexpr const char* kProperties = "PROPERTIES";
static constexpr const char* kColors = "COLORS";
static constexpr const char* kFields  = "FIELDS";

static const uint8_t kSupportedMajorVersion = 1;
static const uint8_t kSupportedMinorVersion = 3;

namespace {
	std::string str(const char* text) {
		return (text != nullptr ? text : "");
	}
}

DocumentParser::DocumentParser(macsa::dot::Document& document) :
	_doc(document)
{}

DocumentParser::~DocumentParser()
{}

std::string DocumentParser::GetSupportedNisxVersion()
{
	std::stringstream version;
	version << kSupportedMajorVersion << "." << kSupportedMinorVersion;
	return version.str();
}

bool DocumentParser::VisitEnter(const tinyxml2::XMLElement& element, const tinyxml2::XMLAttribute* attribute)
{
	std::string eName {str(element.Name())};

	DLog() << "element (line " << element.GetLineNum() << "): \"" << element.Name() << "\"";
	if (eName == kNeoFile) {
		std::string attName {((attribute != nullptr) ? str(attribute->Name()) : "")};
		if (attName == kVersion) {
			std::string version {str(attribute->Value())};
			_doc.SetVersion(getDocumentVersion(version));
		}
		else {
			WLog() << "Invalid version attribute";
		}
		return true; //Continue parsing
	}
	else if (eName == kProperties) {
		DocumentPropertiesParser properties(_doc);
		element.Accept(&properties);
		return false; // Avoid reparsing
	}
	else if (eName == kColors) {
		ColorsPaletteParser colors(_doc);
		element.Accept(&colors);
		return false; // Avoid reparsing
	}
	else if (eName == kFields) {
		FieldsParser fields(_doc);
		element.Accept(&fields);
		return false; // Avoid reparsing
	}
	else {
		std::stringstream trace;
		trace << "Unknown element (line " << element.GetLineNum() << "): " << element.Name();
		if (attribute) {
			trace << "\n\tattribute: " << attribute->Name();
		}
		ELog() << trace.str();
	}
	return true; //Continue parsing
}

bool DocumentParser::VisitExit(const tinyxml2::XMLElement& element)
{
	DLog() << "element (line " << element.GetLineNum() << "): \"" << element.Name() << "\"";
	return true;
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
	ILog() << "text element line: " << text.GetLineNum();
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
