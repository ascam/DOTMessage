#include "datetimeparser.hpp"
#include "datasourceparsersfactory.hpp"
#include "dom/builders/nisx/nisxcommonnames.hpp"
#include "utils/macsalogger.hpp"
#include "utils/stringutils.hpp"

using macsa::nisx::DateTimeParser;
using macsa::dot::VariableObject;
using tinyxml2::XMLElement;
using tinyxml2::XMLAttribute;
using macsa::utils::MacsaLogger;
using namespace macsa::utils::stringutils;

bool DateTimeParser::_registered = macsa::nisx::ConcreteDataSourceParserFactory<DateTimeParser>::Register(macsa::nisx::kDataSourceDatetime);

DateTimeParser::DateTimeParser(VariableObject* object) :
	DataSourceParser(object),
	_datetime{}
{}

bool DateTimeParser::VisitEnter(const XMLElement& element, const XMLAttribute* firstAttribute)
{
	std::string eName {ToString(element.Name())};

	if (eName == kDataSource) {
		_datetime = dynamic_cast<dot::DateTimeDataSource*>(_object->SetDatasource(dot::NDataSourceType::kDateTime));
		if (_datetime == nullptr) {
			ELog() << "Unable to create a date time data source object";
			return false; // Avoid continue parsing
		}
	}
	else if (eName == kFormat) {
		std::string eValue = {ToString(element.GetText())};
		_datetime->SetFormat(eValue);
	}
	else if (eName == kOffsetDays) {
		std::string eValue = {ToString(element.GetText())};
		_datetime->SetDaysOffset(ToInt(eValue));
	}
	else if (eName == kOffsetMonths) {
		std::string eValue = {ToString(element.GetText())};
		_datetime->SetMonthsOffset(ToInt(eValue));
	}
	else if (eName == kOffsetYears) {
		std::string eValue = {ToString(element.GetText())};
		_datetime->SetYearsOffset(ToInt(eValue));
	}
	else if (eName == kHourDayStart) {
		std::string eValue = {ToString(element.GetText())};
		_datetime->SetHourDaysStart(static_cast<uint32_t>(ToInt(eValue)));
	}
	else if (eName != kDateTime)  {
		std::stringstream trace;
		trace << "Unknown element (line " << element.GetLineNum() << "): " << element.Name();
		if (firstAttribute) {
			trace << "\n\tattribute: " << ToString(firstAttribute->Name());
		}
		WLog() << trace.str();
	}
	return (eName == kDataSource) || (eName == kDateTime);
}
