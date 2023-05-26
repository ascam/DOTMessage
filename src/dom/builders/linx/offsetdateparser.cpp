#include "offsetdateparser.hpp"
#include "utils/macsalogger.hpp"
#include "utils/stringutils.hpp"

using namespace macsa::linx;
using macsa::utils::MacsaLogger;
using macsa::linx::OffsetDateParser;
using namespace macsa::utils::stringutils;

static constexpr const char* kDateOffset = "DateOffset";
static constexpr const char* kName = "Name";
static constexpr const char* kDefaultOffset = "DefaultOffset";
static constexpr const char* kDay = "Day";
static constexpr const char* kMonth = "Month";
static constexpr const char* kYear = "Year";
static constexpr const char* kCurrentOffset = "CurrentOffset";
static constexpr const char* kPrompt = "Prompt";
static constexpr const char* kResetOnSel = "ResetOnSel";
static constexpr const char* kMinOffset = "MinOffset";
static constexpr const char* kMaxOffset = "MaxOffset";

OffsetDateParser::OffsetDateParser(LinxParserContext &context):
	_context{context}
{}

bool macsa::linx::OffsetDateParser::VisitEnter(const tinyxml2::XMLElement &element, const tinyxml2::XMLAttribute *attribute)
{
	std::string eName {ToString(element.Name())};
	if (eName == kDateOffset) {
		while (attribute) {
			std::string attName {attribute->Name()};
			if (attName == kName) {
				_offsetName = ToString(attribute->Value());
			}
			attribute = attribute->Next();
		}
		return true;
	}
	else if (eName == kDefaultOffset) {
		return true;
	}
	else if (eName == kDay) {
		_offsetDate.day = ToInt(element.GetText());
		return false;
	}
	else if (eName == kMonth) {
		_offsetDate.month = ToInt(element.GetText());
		return false;
	}
	else if (eName == kYear) {
		_offsetDate.year = ToInt(element.GetText());
		return false;
	}
	else if (eName == kPrompt) {
		_offsetDate.prompt = ToString(element.GetText());
		WLog() << " OFFSET PROMPT : " << _offsetDate.prompt;
		return false;
	}
	else if (eName == kResetOnSel) {
		return false;
	}
	else if (eName == kCurrentOffset) {
		return false;
	}
	else if (eName == kMinOffset) {
		return false;
	}
	else if (eName == kMaxOffset) {
		return false;
	}
	else {
		std::stringstream trace;
		trace << "Unknown element (line " << element.GetLineNum() << "): " << element.Name();
		if (attribute) {
			trace << "\n\tattribute: " << attribute->Name();
		}
		WLog() << trace.str();
		return false;
	}
	return eName == kDateOffset;
}

bool macsa::linx::OffsetDateParser::VisitExit(const tinyxml2::XMLElement &element)
{
	std::string eName {ToString(element.Name())};
	if (eName == kDateOffset) {
		if (!_offsetName.empty()) {
			_context.AddOffsetDate(_offsetName, _offsetDate);
		}
	}
	return true;
}
