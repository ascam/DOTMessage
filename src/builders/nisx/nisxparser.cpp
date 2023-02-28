#include "dom/builders/nisxparser.hpp"
#include <clocale>
#include "utils/macsalogger.hpp"
#include "documentparser.hpp"
#include "tinyxml2.h"

using macsa::dot::NisxParser;
using macsa::dot::Document;
using macsa::nisx::DocumentParser;
using macsa::utils::MacsaLogger;
using tinyxml2::XMLDocument;
using tinyxml2::XMLError;

NisxParser::NisxParser()
{}

NisxParser::~NisxParser()
{}

std::string NisxParser::GetSupportedNisxVersion()
{
	return DocumentParser::GetSupportedNisxVersion();
}

bool NisxParser::Parse(const std::string& filepath, Document& document)
{
	std::setlocale(LC_ALL, "en_US.UTF-8");

	XMLDocument doc;
	XMLError error = doc.LoadFile(filepath.c_str());
	if (error != tinyxml2::XML_SUCCESS) {
		ELog() << "Failed to load xml file : " << filepath << " error : " << XMLDocument::ErrorIDToName(error);
		return false;
	}
	else {
		document.Clear();
		document.SetName(filepath);
		DocumentParser visitor(document);
		return doc.Accept(&visitor);
	}
	return false;
}

bool NisxParser::Parse(const char *data, uint length, Document& document)
{
	std::setlocale(LC_ALL, "en_US.UTF-8");

	XMLDocument doc;
	auto error = doc.Parse(data, length);
	if (error != tinyxml2::XML_SUCCESS) {
		ELog() << "Failed to load xml file from data. Error : " << XMLDocument::ErrorIDToName(error);
		return false;
	}
	else {
		document.Clear();
		document.SetName("New document");
		DocumentParser visitor(document);
		return doc.Accept(&visitor);
	}
	return false;
}
