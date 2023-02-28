#include "builders/nisx/objects/datasources/userinputparser.hpp"
#include "builders/nisx/objects/datasources/datasourceparsersfactory.hpp"
#include "builders/nisx/nisxcommonnames.hpp"
#include "utils/macsalogger.hpp"
#include "utils/stringutils.hpp"

using macsa::nisx::UserInputParser;
using macsa::nisx::UserInfoParser;
using macsa::nisx::InputTextAttributesParser;
using macsa::dot::VariableObject;
using tinyxml2::XMLElement;
using tinyxml2::XMLAttribute;
using macsa::utils::MacsaLogger;
using namespace macsa::utils::stringutils;

namespace macsa {
	namespace nisx {
		namespace  {
			static const bool FactoryRegistered = ConcreteDataSourceParserFactory<UserInputParser>::Register(kDataSourceUserInput);

			std::string str(const char* text) {
				return (text != nullptr ? text : "");
			}
		}
	}
}

UserInputParser::UserInputParser(VariableObject* object) :
	DataSourceParser(object),
	_userInput{}
{}

UserInputParser::~UserInputParser()
{}

bool UserInputParser::VisitEnter(const XMLElement& element, const XMLAttribute* attribute)
{
	std::string eName {str(element.Name())};
	std::string eValue {str(element.GetText())};
	if (eName == kDataSource) {
		_userInput = dynamic_cast<dot::UserInputDataSource*>(_object->SetDatasource(dot::NDataSourceType::kUserInput));
		if (_userInput == nullptr) {
			ELog() << "Unable to create a user input data source object";
			return false; // Avoid continue parsing
		}
	}
	else if (eName == kPrompt) {
		_userInput->SetPrompt(eValue);
	}
	else if (eName == kValue) {
		_userInput->SetValue(eValue);
	}
	else if (eName == kUserText) {
		_userInput->SetUserText(eValue);
	}
	else if (eName == kUserInfo) {
		UserInfoParser parser(_userInput);
		element.Accept(&parser);
	}
	else if (eName == kDefaultValue) {
		_userInput->SetDefaultValue(eValue);
	}
	else if (eName == kPromptValueBehavior) {
		_userInput->SetPromptBehavior(eValue);
	}
	else if (eName == kRequired) {
		_userInput->SetRequired(ToBool(eValue));
	}
	else if (eName == kDataType) {
		_userInput->SetDataType(eValue);
		if (attribute) {
			std::string attrName {str(attribute->Name())};
			if (attrName == kMode) {
				_userInput->SetDataTypeMode(str(attribute->Value()));
			}
			else {
				WLog() << "Unknow attribute \"" << attrName << "\" at " << eName << " element";
			}
		}
	}
	else if (eName == kLength) {
		InputTextAttributesParser parser(_userInput);
		element.Accept(&parser);
	}
	else if (eName == kRange) {
		dot::UserInputDataSource::InputTextAttributes textAttributes = _userInput->GetInputTextAttributes();
		while (attribute) {
			std::string attrName {str(attribute->Name())};
			std::string attrValue {str(attribute->Value())};
			if (attrName == kAttrMin) {
				textAttributes.range.min = static_cast<uint>(ToInt(attrValue));
			}
			else if (attrName == kAttrMax) {
				textAttributes.range.max = static_cast<uint>(ToInt(attrValue));
			}
			attribute = attribute->Next();
		}
		_userInput->SetInputTextAttributes(textAttributes);
	}
	else if (eName != kUserInput)  {
		std::stringstream trace;
		trace << "Unknown element (line " << element.GetLineNum() << "): " << element.Name();
		if (attribute) {
			trace << "\n\tattribute: " << str(attribute->Name());
		}
		WLog() << trace.str();
	}
	return (eName == kDataSource) || (eName == kUserInput);
}

UserInfoParser::UserInfoParser(dot::UserInputDataSource *userInput) :
	_userInput(userInput),
	_userInfo{userInput->GetUserInfo()}
{}

bool UserInfoParser::VisitEnter(const XMLElement& element, const XMLAttribute* firstAttribute)
{
	std::string eName {str(element.Name())};
	std::string eValue = {str(element.GetText())};
	if (eName == kDevice) {
		_userInfo.device = eValue;
	}
	else if (eName == kDate) {
		_userInfo.device = eValue;
	}
	else {
		std::stringstream trace;
		trace << "Unknown element (line " << element.GetLineNum() << "): " << element.Name();
		if (firstAttribute) {
			trace << "\n\tattribute: " << str(firstAttribute->Name());
		}
		WLog() << trace.str();
	}
	return (eName == kUserInfo);
}

bool UserInfoParser::VisitExit(const XMLElement& element)
{
	std::string eName {str(element.Name())};
	if (eName == kUserInfo) {
		_userInput->SetUserInfo(_userInfo);
	}
	return (eName == kUserInfo);
}

InputTextAttributesParser::InputTextAttributesParser(dot::UserInputDataSource* userInput) :
	_userInput(userInput),
	_textAttributes{userInput->GetInputTextAttributes()}
{}

bool InputTextAttributesParser::VisitEnter(const XMLElement& element, const XMLAttribute* firstAttribute)
{
	std::string eName {str(element.Name())};
	std::string eValue = {str(element.GetText())};
	if (eName == kMin) {
		_textAttributes.limits.min = static_cast<uint>(ToInt(eValue));
	}
	else if (eName == kMax) {
		_textAttributes.limits.max = static_cast<uint>(ToInt(eValue));
	}
	else if (eName == kPad) {
		_textAttributes.padding = eValue;
	}
	else if (eName == kPaddingChar && eValue.length()) {
		_textAttributes.paddingChar = eValue.at(0);
	}
	else {
		std::stringstream trace;
		trace << "Unknown element (line " << element.GetLineNum() << "): " << element.Name();
		if (firstAttribute) {
			trace << "\n\tattribute: " << str(firstAttribute->Name());
		}
		WLog() << trace.str();
	}
	return (eName == kLength);
}

bool InputTextAttributesParser::VisitExit(const XMLElement& element)
{
	std::string eName {str(element.Name())};
	if (eName == kLength) {
		_userInput->SetInputTextAttributes(_textAttributes);
	}
	return (eName == kUserInfo);
}
