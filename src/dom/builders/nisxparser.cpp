#include "dom/builders/nisxparser.hpp"
#include <clocale>
#include "utils/macsalogger.hpp"
#include "nisx/documentparser.hpp"

using macsa::dot::NisxParser;
using macsa::dot::Document;
using macsa::nisx::DocumentParser;
using macsa::utils::MacsaLogger;
using tinyxml2::XMLDocument;
using tinyxml2::XMLError;


bool parseDocument(XMLDocument& doc, Document& document, const std::string& fileName)
{
	document.Clear();
	document.SetName(fileName);
	DocumentParser visitor(document);
	return doc.Accept(&visitor);
}

std::string NisxParser::GetSupportedNisxVersion()
{
	return DocumentParser::GetSupportedNisxVersion();
}

bool NisxParser::BuildFromFile(const std::string& filepath, Document& document)
{
	std::setlocale(LC_ALL, "en_US.UTF-8");

	XMLDocument doc;
	XMLError error = doc.LoadFile(filepath.c_str());
	if (error != tinyxml2::XML_SUCCESS) {
		ELog() << "Failed to load xml file : " << filepath << " error : " << XMLDocument::ErrorIDToName(error);
		return false;
	}

	return parseDocument(doc, document, filepath);
}

bool NisxParser::BuildFromData(const char* data, uint length, Document& document)
{
	std::setlocale(LC_ALL, "en_US.UTF-8");

	XMLDocument doc;
	auto error = doc.Parse(data, length);
	if (error != tinyxml2::XML_SUCCESS) {
		ELog() << "Failed to load xml file from data. Error : " << XMLDocument::ErrorIDToName(error);
		return false;
	}

	return parseDocument(doc, document, "New document");
}
