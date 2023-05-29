#include "dataparser.hpp"

#include "dom/barcode.hpp"
#include "dom/text.hpp"
#include "userinputdataparser.hpp"
#include "counterdataparser.hpp"
#include "dom/components/datasources/userinputdatasource.hpp"
#include "dom/components/datasources/datetimedatasource.hpp"
#include "dom/components/datasources/compositedatasource.hpp"
#include "utils/macsalogger.hpp"
#include "utils/stringutils.hpp"

#include <regex>

static constexpr const char* kData = "Data";
static constexpr const char* kObject = "Object";
static constexpr const char* kDataType = "DataType";
static constexpr const char* kMaxNoOfChars = "MaxNoOfChars";
static constexpr const char* kDefault = "Default";
static constexpr const char* kFixedLen = "FixedLen";
static constexpr const char* kLocale = "Locale";
static constexpr const char* kVarText = "VarText";
static constexpr const char* kOffsetDate = "OffsetDate";
static constexpr const char* kSrcOffset = "SrcOffset";
static constexpr const char* kCounterText = "CounterText";
static constexpr const char* kSrcField = "SrcField";
static constexpr const char* kSrcFieldName = "SrcFieldName";
static constexpr const char* kGs1Char = "æ";
static constexpr const char* kGs1Char2 = "~1";
static constexpr const char* kFormulaSeparator = "|";
static constexpr const char* kFormulaField = "Field|";
static constexpr const char* kFormulaChars = "(Fixed\\|)|(Field\\|)|(\\|)|(\")";
static constexpr const char* kFormulaFixed = "Fixed|";


using macsa::linx::DataParser;
using namespace macsa::dot;
using macsa::utils::MacsaLogger;
using namespace macsa::utils::stringutils;

DataParser::DataParser(VariableObject *object, macsa::linx::LinxParserContext &context):
	_object{object},
	_context{context},
	_offsetDate{},
	_dataType{},
	_maxLength{},
	_srcItems{},
	_isGS1Format{false}
{}

bool DataParser::VisitEnter(const tinyxml2::XMLElement &element, const tinyxml2::XMLAttribute *attribute)
{
		std::string eName {ToString(element.Name())};

		if (eName == kData) {
			return true;
		}
		else if (eName == kObject) {
			return true;
		}
		else if (eName == kDataType) {
			if (_dataType != LinxDataType::kComposite) {
				_dataType = static_cast<LinxDataType>(element.IntText());
				if (_dataType == LinxDataType::kStaticOffsetDateTime) {
					_object->SetDatasource(dot::NDataSourceType::kUserInput);
				}
			}
			return false;
		}
		else if (eName == kMaxNoOfChars) {
			_maxLength = element.IntText();
			return false;
		}
		else if (eName == kDefault) {
			_defaultValue = {ToString(element.GetText())};
			fillGs1Values(_defaultValue);
			return false;
		}
		else if (eName == kFixedLen) {;
			return false;
		}
		else if (eName == kSrcField) {
			if (attribute && ToString(attribute->Name()) == kSrcFieldName) {
				std::string attValue = ToString(attribute->Value());
				std::stringstream source;
				source << kFormulaField << attValue << kFormulaSeparator;
				_formula.append(source.str());
				if (_isGS1Format) {
					_gs1Values.back().second = source.str();
					_srcItems.emplace_back(attValue, _defaultValue);
				}
			}
			return false;
		}
		else if (eName == kLocale) {
			return false;
		}
		else if (eName == kOffsetDate) {
			if (attribute && ToString(attribute->Name()) == kSrcOffset) {
				std::string offsetName {ToString(attribute->Value())};
				auto offset = _context.GetOffsetDateMap().find(offsetName);
					if (offset != _context.GetOffsetDateMap().end()) {
						_offsetDate.day = offset->second.day;
						_offsetDate.month = offset->second.month;
						_offsetDate.year = offset->second.year;
						_offsetDate.prompt = offset->second.prompt;
					}
			}
			return false;
		}
		else if (eName == kVarText) {
			_object->SetDatasource(dot::NDataSourceType::kUserInput);
			UserInputDataParser userinputParser(_object);
			element.Accept(&userinputParser);
			return false;
		}
		else if (eName == kCounterText) {
			_object->SetDatasource(dot::NDataSourceType::kCounter);
			CounterDataParser counterParser(_object);
			element.Accept(&counterParser);
			return false;
		}
		else{
			std::stringstream trace;
			trace << "Unknown element (line " << element.GetLineNum() << "): " << eName;
			if (attribute) {
				trace << "\n\tattribute: " << attribute->Name();
			}
			WLog() << trace.str();
		}

	return (eName == kData);
}

bool DataParser::VisitExit(const tinyxml2::XMLElement &element)
{
	std::string eName {ToString(element.Name())};
	if (eName == kData) {
		if (_isGS1Format) {
			processGs1Value();
		}
		switch (_dataType) {
			case LinxDataType::kFixedOrUserInput:
			case LinxDataType::kStaticOffsetDateTime:
				{
					auto* userInput = dynamic_cast<dot::UserInputDataSource*>(_object->GetDatasource());
					if (userInput) {
						DLog() << _object->GetId() << " is user input";
						if (_dataType == LinxDataType::kStaticOffsetDateTime) {
							userInput->SetPrompt(_offsetDate.prompt);
						}
						userInput->SetDefaultValue(_defaultValue);
						if (_object->GetType() == NObjectType::kText) {
							auto textAttributes {userInput->GetInputTextAttributes()};
							textAttributes.limits.max = _maxLength;
							userInput->SetInputTextAttributes(textAttributes);
						}
					}
					else{
						DLog() << _object->GetId() << " has no datasource";
					}
					break;
				}
			case LinxDataType::kDate:
			case LinxDataType::kTime:
			case LinxDataType::kOffsetDate:
				{
					auto* datasource = _object->SetDatasource(NDataSourceType::kDateTime);
					if (datasource) {
						auto* datetime = dynamic_cast<dot::DateTimeDataSource*>(datasource);
						datetime->SetFormat(checkDateTimeFormat(_defaultValue));
						datetime->SetDaysOffset(_offsetDate.day);
						datetime->SetMonthsOffset(_offsetDate.month);
						datetime->SetYearsOffset(_offsetDate.year);
					}
					else{
						DLog() << " has no datasource available";
					}
				}
				break;
			case LinxDataType::kCounter:
				{
					auto* datasource = _object->SetDatasource(NDataSourceType::kCounter);
					if (!datasource) {
						DLog() << " has no datasource available";
					}
				}
				break;
			case LinxDataType::kComposite:
				{
					auto* datasource = _object->SetDatasource(NDataSourceType::kComposite);
					if (datasource) {
						auto* composite = dynamic_cast<dot::CompositeDataSource*>(datasource);
						composite->SetFormula(_formula);
					}
					else{
						DLog() << " has no datasource available";
					}
				}
			default:
				break;
		}
	}
	return true;
}

void DataParser::fillGs1Values(std::string value)
{
	if (!_isGS1Format && (value == kGs1Char || value == kGs1Char2)) {
		_isGS1Format = true;
		DLog() << " Code has GS1 Format";
	}
	else if (_isGS1Format && value != kGs1Char && value != kGs1Char2) {
		if (!_gs1Values.empty() && _gs1Values.back().second.empty()) {
			_gs1Values.back().second = value;
		}
		else {
			_gs1Values.emplace_back(value, "");
		}
	}
}

void DataParser::processGs1Value()
{
	std::stringstream value;
	if (_dataType == LinxDataType::kComposite) {
		for (const auto& gs1Value : _gs1Values) {
			value << kFormulaFixed << "\"[" << gs1Value.first << "]\"" << kFormulaSeparator;
			if (gs1Value.second.find(kFormulaField) != std::string::npos) {
				value << gs1Value.second;
			}
			else{
				value << kFormulaFixed << "\"" << gs1Value.second << kFormulaSeparator;
			}
		}
		_formula = value.str();
	}
	else{
		for (const auto& gs1Value : _gs1Values) {
			value << "[" << gs1Value.first << "]" << gs1Value.second;
		}
	}
	_defaultValue = value.str();
	_defaultValue = std::regex_replace(_defaultValue, std::regex(kFormulaChars), "");
	for (const auto &srcItem : _srcItems) {
		_defaultValue = std::regex_replace(_defaultValue, std::regex(srcItem.first), srcItem.second);
	}

	auto objectType = _object->GetType();
	if (objectType == NObjectType::kBarcode) {
		dynamic_cast<Barcode*>(_object)->SetCode(_defaultValue);
	}
	else if (objectType == NObjectType::kText) {
		dynamic_cast<Text*>(_object)->SetText(_defaultValue);
	}
}

std::string DataParser::checkDateTimeFormat(std::string &datetime)
{
	datetime = std::regex_replace(datetime, std::regex("cl:"), "");
	datetime = std::regex_replace(datetime, std::regex("JJ | jj"), "JJJ");
	datetime = std::regex_replace(datetime, std::regex("j"), "J");
	return datetime;
}
