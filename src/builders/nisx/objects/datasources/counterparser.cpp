#include "builders/nisx/objects/datasources/counterparser.hpp"
#include "builders/nisx/objects/datasources/datasourceparsersfactory.hpp"
#include "builders/nisx/nisxcommonnames.hpp"
#include "utils/macsalogger.hpp"
#include "utils/stringutils.hpp"

using macsa::nisx::CounterParser;
using macsa::dot::VariableObject;
using tinyxml2::XMLElement;
using tinyxml2::XMLAttribute;
using macsa::utils::MacsaLogger;
using namespace macsa::utils::stringutils;

static constexpr const char* kCounter = "COUNTER";
static constexpr const char* kMaxValue = "MAX_VALUE";
static constexpr const char* kMinValue = "MIN_VALUE";
static constexpr const char* kRepeat = "REPEAT_COUNT";
static constexpr const char* kStep = "STEP";

namespace macsa {
	namespace nisx {
		namespace  {
			static const bool FactoryRegistered = ConcreteDataSourceParserFactory<CounterParser>::Register(kDataSourceCounter);

			std::string str(const char* text) {
				return (text != nullptr ? text : "");
			}
		}
	}
}

CounterParser::CounterParser(VariableObject* object) :
	DataSourceParser(object),
	_counter{}
{}

CounterParser::~CounterParser()
{}

bool CounterParser::VisitEnter(const XMLElement& element, const XMLAttribute* firstAttribute)
{
	std::string eName {str(element.Name())};
	if (eName == kDataSource) {
		_counter = dynamic_cast<dot::CounterDataSource*>(_object->SetDatasource(dot::NDataSourceType::kCounter));
		if (_counter == nullptr) {
			ELog() << "Unable to create a counter data source object";
			return false; // Avoid continue parsing
		}
	}
	else if (eName == kFormat) {
		std::string eValue = {str(element.GetText())};
		_counter->SetLeadingZeros(eValue.size());
	}
	else if (eName == kMaxValue) {
		std::string eValue = {str(element.GetText())};
		_counter->SetMaxValue(ToInt(eValue));
	}
	else if (eName == kMinValue) {
		std::string eValue = {str(element.GetText())};
		_counter->SetMinValue(ToInt(eValue));
	}
	else if (eName == kRepeat) {
		std::string eValue = {str(element.GetText())};
		_counter->SetRepeatCounter(ToBool(eValue));
	}
	else if (eName == kStep) {
		std::string eValue = {str(element.GetText())};
		_counter->SetStep(ToInt(eValue));
	}
	else if (eName != kCounter) {
		std::stringstream trace;
		trace << "Unknown element (line " << element.GetLineNum() << "): " << element.Name();
		if (firstAttribute) {
			trace << "\n\tattribute: " << str(firstAttribute->Name());
		}
		WLog() << trace.str();
	}
	return (eName == kDataSource) || (eName == kCounter);
}