#include "builders/nisx/objects/datasources/databaseparser.hpp"
#include "builders/nisx/objects/datasources/datasourceparsersfactory.hpp"
#include "builders/nisx/nisxcommonnames.hpp"
#include "utils/macsalogger.hpp"

using macsa::nisx::DatabaseParser;
using macsa::dot::VariableObject;
using tinyxml2::XMLElement;
using tinyxml2::XMLAttribute;
using macsa::utils::MacsaLogger;

namespace macsa {
	namespace nisx {
		namespace  {
			static const bool FactoryRegistered = ConcreteDataSourceParserFactory<DatabaseParser>::Register(kDataSourceDatabase);

			std::string str(const char* text) {
				return (text != nullptr ? text : "");
			}
		}
	}
}

DatabaseParser::DatabaseParser(VariableObject* object) :
	DataSourceParser(object),
	_database{}
{}

DatabaseParser::~DatabaseParser()
{}

bool DatabaseParser::VisitEnter(const XMLElement& element, const XMLAttribute* firstAttribute)
{
	std::string eName {str(element.Name())};
	if (eName == kDataSource) {
		_database = dynamic_cast<dot::DatabaseDataSource*>(_object->SetDatasource(dot::NDataSourceType::kDataBase));
		if (_database == nullptr) {
			ELog() << "Unable to create a database data source object";
			return false; // Avoid continue parsing
		}
	}
	else if (eName != kFieldName) {
		std::string eValue = {str(element.GetText())};
		_database->SetFieldName(eValue);
	}
	else if (eName != kDefaultValue) {
		std::string eValue = {str(element.GetText())};
		_database->SetDefaultValue(eValue);
	}
	else if (eName != kDatabase) {
		std::stringstream trace;
		trace << "Unknown element (line " << element.GetLineNum() << "): " << element.Name();
		if (firstAttribute) {
			trace << "\n\tattribute: " << str(firstAttribute->Name());
		}
		WLog() << trace.str();
	}
	return (eName == kDataSource) || (eName == kDatabase);
}
