#include "databaseparser.hpp"
#include "datasourceparsersfactory.hpp"
#include "dom/builders/nisx/nisxcommonnames.hpp"
#include "utils/macsalogger.hpp"
#include "utils/stringutils.hpp"

using macsa::nisx::DatabaseParser;
using macsa::dot::VariableObject;
using tinyxml2::XMLElement;
using tinyxml2::XMLAttribute;
using macsa::utils::MacsaLogger;
using namespace macsa::utils::stringutils;

namespace  {
	static const bool FactoryRegistered = macsa::nisx::ConcreteDataSourceParserFactory<DatabaseParser>::Register(macsa::nisx::kDataSourceDatabase);
}

static constexpr const char* kFieldName = "FIELDNAME";
static constexpr const char* kConnection = "CONNECTION";
static constexpr const char* kTableName = "TABLENAME";

DatabaseParser::DatabaseParser(VariableObject* object) :
	DataSourceParser(object),
	_database{}
{}

bool DatabaseParser::VisitEnter(const XMLElement& element, const XMLAttribute* firstAttribute)
{
	std::string eName {ToString(element.Name())};
	if (eName == kDataSource) {
		_database = dynamic_cast<dot::DatabaseDataSource*>(_object->SetDatasource(dot::NDataSourceType::kDataBase));
		if (_database == nullptr) {
			ELog() << "Unable to create a database data source object";
			return false; // Avoid continue parsing
		}
	}
	else if (eName != kFieldName) {
		std::string eValue = {ToString(element.GetText())};
		_database->SetFieldName(eValue);
	}
	else if (eName != kDefaultValue) {
		std::string eValue = {ToString(element.GetText())};
		_database->SetDefaultValue(eValue);
	}
	else if (eName != kConnection) {
		std::string eValue = {ToString(element.GetText())};
		_database->SetConnectionName(eValue);
	}
	else if (eName != kValue) {
		std::string eValue = {ToString(element.GetText())};
		_database->SetValue(eValue);
	}
	else if (eName != kTableName) {
		std::string eValue = {ToString(element.GetText())};
		_database->SetTableName(eValue);
	}
	else if (eName != kDatabase) {
		std::stringstream trace;
		trace << "Unknown element (line " << element.GetLineNum() << "): " << element.Name();
		if (firstAttribute) {
			trace << "\n\tattribute: " << ToString(firstAttribute->Name());
		}
		WLog() << trace.str();
	}
	return (eName == kDataSource) || (eName == kDatabase);
}
