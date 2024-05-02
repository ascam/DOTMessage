#include "variableobjectvisitor.hpp"
#include "nisxcommonnames.hpp"
#include "xmltools/xmlwriter.hpp"
#include "utils/macsalogger.hpp"
#include "utils/stringutils.hpp"

using macsa::nisx::VariableObjectVisitor;
using macsa::dot::Color;
using macsa::dot::CounterDataSource;
using macsa::dot::DatabaseDataSource;
using macsa::dot::DateTimeDataSource;
using macsa::dot::UserInputDataSource;
using macsa::dot::CompositeDataSource;
using macsa::xmltools::XmlWriter;
using macsa::utils::MacsaLogger;
using tinyxml2::XMLDocument;
using tinyxml2::XMLElement;
using namespace macsa::utils::stringutils;

// DataSources
static constexpr const char* kDataSource = "DATASOURCE";
static constexpr const char* kFormat = "FORMAT";
static constexpr const char* kDefaultValue = "DEFAULT_VALUE";
static constexpr const char* kValue = "VALUE";
  // Counter Data Source
static constexpr const char* kCounter = "COUNTER";
static constexpr const char* kDataSourceCounter = "CibNeoDsCounter";
static constexpr const char* kMinValue = "MIN_VALUE";
static constexpr const char* kMaxValue = "MAX_VALUE";
static constexpr const char* kRepeat = "REPEAT_COUNT";
static constexpr const char* kStep = "STEP";
  // DateTime Data Source
static constexpr const char* kDateTime = "DATETIME";
static constexpr const char* kDataSourceDatetime = "CibNeoDsDateTime";
static constexpr const char* kOffsetDays = "OFFSETDAYS";
static constexpr const char* kOffsetMonths = "OFFSETMONTHS";
static constexpr const char* kOffsetYears = "OFFSETYEARS";
static constexpr const char* kHourDayStart = "HOURDAYSTART";
static constexpr const char* kRoundingPolicy = "ROUNDINGPOLICY";
static constexpr const char* kRoundingDay = "ROUNDINGDAY";
  // Composite Data Source
static constexpr const char* kComposite = "COMPOSITE";
static constexpr const char* kDataSourceComposite = "CibNeoDsCompositeField";
static constexpr const char* kFormula = "FORMULA";
  // Database Data Source
static constexpr const char* kDatabase = "DATABASE";
static constexpr const char* kDataSourceDatabase = "CibNeoDsDatabase";
static constexpr const char* kFieldName = "FIELDNAME";
static constexpr const char* kConnection = "CONNECTION";
static constexpr const char* kTableName = "TABLENAME";
  // User inputs Data Source
static constexpr const char* kUserInput = "USERINPUT";
static constexpr const char* kDataSourceUserInput = "CibNeoDsUserInput";
static constexpr const char* kPrompt = "PROMPT";
static constexpr const char* kUserText = "USER_TEXT";
static constexpr const char* kUserInfo = "USER_INFO";
static constexpr const char* kDevice = "DEVICE";
static constexpr const char* kDate = "DATE";
static constexpr const char* kPromptValueBehavior = "PROMPT_VALUE_BEHAVIOR";
static constexpr const char* kRequired = "REQUIRED";
static constexpr const char* kDataType = "DATATYPE";
static constexpr const char* kAttrMode = "Mode";
static constexpr const char* kLength = "LENGTH";
static constexpr const char* kMin = "MIN";
static constexpr const char* kMax = "MAX";
static constexpr const char* kAttrMin = "Min";
static constexpr const char* kAttrMax = "Max";
static constexpr const char* kPad = "PAD";
static constexpr const char* kPaddingChar = "PADDING_CHAR";
static constexpr const char* kRange = "RANGE";

VariableObjectVisitor::VariableObjectVisitor(XMLDocument& document, const dot::Document& dom) :
	ObjectVisitor(document),
	_dom(dom),
	_xmlDocument{document},
	_xmlElement{},
	_xmlDataSource{}
{}

bool VariableObjectVisitor::Visit(const CounterDataSource& counter)
{
	_xmlDataSource = _xmlDocument.NewElement(kDataSource);
	if (_xmlDataSource) {
		_xmlDataSource->SetAttribute(kAttrType, kDataSourceCounter);
		auto xmlCounterResult = XmlWriter::CreateChildNode(_xmlDocument, kCounter, _xmlDataSource);
		if (xmlCounterResult.second) {
			auto* xmlCounter = xmlCounterResult.first;
			XmlWriter::CreateTextChildNode(_xmlDocument, kFormat, std::string(counter.GetLeadingZeros(), '0'), xmlCounter);
			XmlWriter::CreateTextChildNode(_xmlDocument, kMinValue, ToString(counter.GetMinValue()), xmlCounter);
			XmlWriter::CreateTextChildNode(_xmlDocument, kMaxValue, ToString(counter.GetMaxValue()), xmlCounter);
			XmlWriter::CreateTextChildNode(_xmlDocument, kRepeat, ToString(counter.GetRepeatCounter()), xmlCounter);
			XmlWriter::CreateTextChildNode(_xmlDocument, kStep, ToString(counter.GetStep()), xmlCounter);
			return true;
		}
	}
	return false;
}

bool VariableObjectVisitor::Visit(const DatabaseDataSource& database)
{
	_xmlDataSource = _xmlDocument.NewElement(kDataSource);
	if (_xmlDataSource) {
		_xmlDataSource->SetAttribute(kAttrType, kDataSourceDatabase);
		auto xmlDatabaseResult = XmlWriter::CreateChildNode(_xmlDocument, kDatabase, _xmlDataSource);
		if (xmlDatabaseResult.second) {
			auto* xmlDatabase = xmlDatabaseResult.first;
			XmlWriter::CreateTextChildNode(_xmlDocument, kFieldName, database.GetFieldName(), xmlDatabase);
			XmlWriter::CreateTextChildNode(_xmlDocument, kDefaultValue, database.GetDefaultValue(), xmlDatabase);
			XmlWriter::CreateTextChildNode(_xmlDocument, kConnection, database.GetConnectionName(), xmlDatabase);
			XmlWriter::CreateTextChildNode(_xmlDocument, kValue, database.GetValue(), xmlDatabase);
			XmlWriter::CreateTextChildNode(_xmlDocument, kTableName, database.GetTableName(), xmlDatabase);
			return true;
		}
	}
	return false;
}

bool VariableObjectVisitor::Visit(const DateTimeDataSource& datetime)
{
	_xmlDataSource = _xmlDocument.NewElement(kDataSource);
	if (_xmlDataSource) {
		_xmlDataSource->SetAttribute(kAttrType, kDataSourceDatetime);
		auto xmlDatetimeResult = XmlWriter::CreateChildNode(_xmlDocument, kDateTime, _xmlDataSource);
		if (xmlDatetimeResult.second) {
			auto* xmlDatetime = xmlDatetimeResult.first;
			XmlWriter::CreateTextChildNode(_xmlDocument, kOffsetDays, ToString(datetime.GetDaysOffset()), xmlDatetime);
			XmlWriter::CreateTextChildNode(_xmlDocument, kOffsetMonths, ToString(datetime.GetMonthsOffset()), xmlDatetime);
			XmlWriter::CreateTextChildNode(_xmlDocument, kOffsetYears, ToString(datetime.GetYearsOffset()), xmlDatetime);
			XmlWriter::CreateTextChildNode(_xmlDocument, kHourDayStart, ToString(datetime.GetHourDaysStart()), xmlDatetime);
			XmlWriter::CreateTextChildNode(_xmlDocument, kRoundingPolicy, datetime.GetRoundingPolicy().toString(), xmlDatetime);
			XmlWriter::CreateTextChildNode(_xmlDocument, kRoundingDay, ToString(datetime.GetRoundingDay()), xmlDatetime);
			XmlWriter::CreateTextChildNode(_xmlDocument, kFormat, datetime.GetFormat(), xmlDatetime);
			return true;
		}
	}
	return false;
}

bool VariableObjectVisitor::Visit(const UserInputDataSource& userInput)
{
	_xmlDataSource = _xmlDocument.NewElement(kDataSource);
	if (_xmlDataSource) {
		_xmlDataSource->SetAttribute(kAttrType, kDataSourceUserInput);
		auto xmlUserInputResult = XmlWriter::CreateChildNode(_xmlDocument, kUserInput, _xmlDataSource);
		if (xmlUserInputResult.second) {
			auto* xmlUserInput = xmlUserInputResult.first;
			XmlWriter::CreateTextChildNode(_xmlDocument, kPrompt, userInput.GetPrompt(), xmlUserInput);
			XmlWriter::CreateTextChildNode(_xmlDocument, kValue, userInput.GetValue(), xmlUserInput);
			// NisX 1.3 properties
			auto xmlDataTypeResult = XmlWriter::CreateTextChildNode(_xmlDocument, kDataType, userInput.GetDataType().toString(), xmlUserInput);
			if (xmlDataTypeResult.second) {
				xmlDataTypeResult.first->SetAttribute(kAttrMode, userInput.GetDataTypeMode().toString().c_str());
			}
			else {
				WLog() << "Unable to set user input data type";
			}
			const auto& textAttributes = userInput.GetInputTextAttributes();
			auto xmlLenghtResult = XmlWriter::CreateChildNode(_xmlDocument, kLength, xmlUserInput);
			if (xmlLenghtResult.second) {
				auto* xmlLenght = xmlLenghtResult.first;
				XmlWriter::CreateTextChildNode(_xmlDocument, kMin, ToString(textAttributes.limits.min), xmlLenght);
				XmlWriter::CreateTextChildNode(_xmlDocument, kMax, ToString(textAttributes.limits.max), xmlLenght);
				XmlWriter::CreateTextChildNode(_xmlDocument, kPad, textAttributes.padding.toString(), xmlLenght);
				XmlWriter::CreateTextChildNode(_xmlDocument, kPaddingChar, {textAttributes.paddingChar}, xmlLenght);
			}
			else {
				WLog() << "Unable to set user input length constraints";
			}
			auto xmlRangeResult = XmlWriter::CreateChildNode(_xmlDocument, kRange, xmlUserInput);
			if (xmlRangeResult.second) {
				xmlRangeResult.first->SetAttribute(kAttrMin, textAttributes.range.min);
				xmlRangeResult.first->SetAttribute(kAttrMax, textAttributes.range.max);
			}
			else {
				WLog() << "Unable to set user input range constraints";
			}
			XmlWriter::CreateTextChildNode(_xmlDocument, kUserText, userInput.GetUserText(), xmlUserInput);
			auto xmlUserInfoResult = XmlWriter::CreateChildNode(_xmlDocument, kUserInfo, xmlUserInput);
			if (xmlUserInfoResult.second) {
				const auto& userInfo = userInput.GetUserInfo();
				XmlWriter::CreateTextChildNode(_xmlDocument, kDevice, userInfo.device, xmlUserInfoResult.first);
				XmlWriter::CreateTextChildNode(_xmlDocument, kDate, userInfo.timestamp, xmlUserInfoResult.first);
			}
			else {
				WLog() << "Unable to set user input users info";
			}
			XmlWriter::CreateTextChildNode(_xmlDocument, kDefaultValue, userInput.GetDefaultValue(), xmlUserInput);
			XmlWriter::CreateTextChildNode(_xmlDocument, kPromptValueBehavior, userInput.GetPromptBehavior().toString(), xmlUserInput);
			XmlWriter::CreateTextChildNode(_xmlDocument, kRequired, ToString(userInput.GetRequired()), xmlUserInput);
			return true;
		}
	}
	return false;
}

bool VariableObjectVisitor::Visit(const CompositeDataSource& composite)
{
	_xmlDataSource = _xmlDocument.NewElement(kDataSource);
	if (_xmlDataSource) {
		_xmlDataSource->SetAttribute(kAttrType, kDataSourceComposite);
		auto xmlCompositeResult = XmlWriter::CreateChildNode(_xmlDocument, kComposite, _xmlDataSource);
		if (xmlCompositeResult.second){
			XmlWriter::CreateTextChildNode(_xmlDocument, kFormula, composite.GetFormula(), xmlCompositeResult.first);
			return true;
		}
	}
	return false;
}

bool VariableObjectVisitor::writeColor(const Color& color, XMLElement* xmlColor) const
{
	if (xmlColor) {
		xmlColor->SetAttribute(kAttrName, color.GetName().c_str());
		xmlColor->SetAttribute(kAttrValue, color.ToARGBString().c_str());
		return true;
	}
	return false;
}
