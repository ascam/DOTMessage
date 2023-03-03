#include "dom/writers/nisxwriter.hpp"
#include "nisx/documentvisitor.hpp"
#include "tinyxml2.h"

using macsa::dot::NisxWriter;

static constexpr const char* kSupportedNisxVersion = "1.3";

std::string NisxWriter::GetWriterNisxVersion()
{
	return kSupportedNisxVersion;
}

bool NisxWriter::Write(const std::string& filepath, dot::Document& document)
{
	tinyxml2::XMLDocument xmlDocument;
	nisx::DocumentVisitor visitor(xmlDocument, document);
	document.Accept(&visitor);
	return (xmlDocument.SaveFile(filepath.c_str()) != tinyxml2::XMLError::XML_SUCCESS);
}

bool NisxWriter::Write(ByteArray& data, dot::Document& document)
{
	tinyxml2::XMLDocument xmlDocument;
	nisx::DocumentVisitor visitor(xmlDocument, document);
	bool success = document.Accept(&visitor);

	// Save to buffer
	tinyxml2::XMLPrinter printer;
	xmlDocument.Print(&printer);
	const char* cStr = printer.CStr();
	const uint lenght = printer.CStrSize();
	for (uint byte = 0; byte < lenght; byte++) {
		data.emplace_back(*(cStr + byte));
	}

	return success;
}
