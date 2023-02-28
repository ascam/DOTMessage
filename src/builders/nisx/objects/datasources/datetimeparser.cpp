#include "builders/nisx/objects/datasources/datetimeparser.hpp"
#include "builders/nisx/objects/datasources/datasourceparsersfactory.hpp"
#include "builders/nisx/nisxcommonnames.hpp"
#include "utils/macsalogger.hpp"
#include "utils/stringutils.hpp"

using macsa::nisx::DateTimeParser;
using macsa::dot::VariableObject;
using tinyxml2::XMLElement;
using tinyxml2::XMLAttribute;
using macsa::utils::MacsaLogger;
using namespace macsa::utils::stringutils;

namespace macsa {
	namespace nisx {
		namespace  {
			static const bool FactoryRegistered = ConcreteDataSourceParserFactory<DateTimeParser>::Register(kDataSourceDatetime);

			std::string str(const char* text) {
				return (text != nullptr ? text : "");
			}
		}
	}
}

DateTimeParser::DateTimeParser(VariableObject* object) :
	DataSourceParser(object),
	_datetime{}
{}

DateTimeParser::~DateTimeParser()
{}


bool DateTimeParser::VisitEnter(const XMLElement& element, const XMLAttribute* firstAttribute)
{
	std::string eName {str(element.Name())};

	if (eName == kDataSource) {
		_datetime = dynamic_cast<dot::DateTimeDataSource*>(_object->SetDatasource(dot::NDataSourceType::kDateTime));
		if (_datetime == nullptr) {
			ELog() << "Unable to create a date time data source object";
			return false; // Avoid continue parsing
		}
	}
	else if (eName == kFormat) {
		std::string eValue = {str(element.GetText())};
		_datetime->SetFormat(eValue);
	}
	else if (eName == kOffsetDays) {
		std::string eValue = {str(element.GetText())};
		_datetime->SetDaysOffset(ToInt(eValue));
	}
	else if (eName == kOffsetMonths) {
		std::string eValue = {str(element.GetText())};
		_datetime->SetMonthsOffset(ToInt(eValue));
	}
	else if (eName == kOffsetYears) {
		std::string eValue = {str(element.GetText())};
		_datetime->SetYearsOffset(ToInt(eValue));
	}
	else if (eName == kHourDayStart) {
		std::string eValue = {str(element.GetText())};
		_datetime->SetHourDaysStart(static_cast<uint>(ToInt(eValue)));
	}
	else if (eName != kDateTime)  {
		std::stringstream trace;
		trace << "Unknown element (line " << element.GetLineNum() << "): " << element.Name();
		if (firstAttribute) {
			trace << "\n\tattribute: " << str(firstAttribute->Name());
		}
		WLog() << trace.str();
	}
	return (eName == kDataSource) || (eName == kDateTime);
}
