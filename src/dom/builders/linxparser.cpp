#include "dom/builders/linxparser.hpp"
#include "linx/documentparser.hpp"
#include <locale>
#include "utfconverter/utfconverter.hpp"
#include "utils/macsalogger.hpp"
#include "tinyxml2.h"

using macsa::dot::LinxParser;
using macsa::dot::Document;
using macsa::linx::DocumentParser;
using macsa::utils::MacsaLogger;
using macsa::utils::UTFConverter;
using tinyxml2::XMLDocument;
using tinyxml2::XMLError;

LinxParser::LinxParser()
{}

LinxParser::~LinxParser()
{}

std::string LinxParser::GetSupportedLinxVersion()
{
	return DocumentParser::GetSupportedLinxVersion();
}

bool LinxParser::BuildFromFile(const std::string& filepath, Document& document)
{
	if (UTFConverter::IsUTF16(filepath)) {
		auto content = UTFConverter::ConvertFromUtf16ToUtf8(filepath);
		bool success = buildFromData(content.c_str(), content.size(), document);
		if (success){
			document.SetName(filepath);
		}
		return success;
	}
	else {
		std::setlocale(LC_ALL, "en_US.UTF-8");
		XMLDocument doc;
		XMLError error = doc.LoadFile(filepath.c_str());
		if (error != tinyxml2::XML_SUCCESS) {
			ELog() << "Failed to load xml file : " << filepath << " error : " << XMLDocument::ErrorIDToName(error) << std::endl
				   << doc.ErrorStr();
			return false;
		}
		else {
			document.Clear();
			document.SetName(filepath);
			DocumentParser visitor(document);
			return doc.Accept(&visitor);
		}
	}
	return false;
}

bool LinxParser::BuildFromData(const char* data, uint32_t length, Document& document)
{
	if (UTFConverter::IsUTF16(data, length)) {
		auto content = UTFConverter::ConvertFromUtf16ToUtf8(data, length);
		return buildFromData(content.c_str(), length, document);
	}
	else{
		return buildFromData(data, length, document);
	}
}

bool LinxParser::buildFromData(const char* data, uint32_t length, Document& document)
{
	std::setlocale(LC_ALL, "en_US.UTF-8");
	XMLDocument doc;
	auto error = doc.Parse(data, length);

	if (error != tinyxml2::XML_SUCCESS) {
		ELog() << "Failed to load xml file from data. Error : " << XMLDocument::ErrorIDToName(error) << std::endl
			   << doc.ErrorStr();
		return false;
	}
	else {
		document.Clear();
		DocumentParser visitor(document);
		return doc.Accept(&visitor);
	}
	return false;
}
