#include "userinputdataparser.hpp"
#include "utils/macsalogger.hpp"
#include "utils/stringutils.hpp"

using namespace macsa::dot;
using macsa::linx::UserInputDataParser;
using namespace macsa::utils::stringutils;
using macsa::utils::MacsaLogger;

static constexpr const char* kVarText = "VarText";
static constexpr const char* kPrompt = "Prompt";
static constexpr const char* kMask = "Mask";
static constexpr const char* kUserEnterData = "UserEnterData";
static constexpr const char* kResetOnSel = "ResetOnSel";

UserInputDataParser::UserInputDataParser(dot::VariableObject *obj):
	_object{obj},
	_userInput {dynamic_cast<dot::UserInputDataSource*>(_object->GetDatasource())}
{}

bool UserInputDataParser::VisitEnter(const tinyxml2::XMLElement& element, const tinyxml2::XMLAttribute* attribute)
{
	if (_userInput) {
		std::string eName {ToString(element.Name())};

		if (eName == kVarText) {
			return true;
		}
		else if (eName == kPrompt) {
			_userInput->SetPrompt(ToString(element.GetText()));
			return false;
		}
		else if (eName == kMask) {
			_userInput->SetDataTypeMode(getInputMask(ToString(element.GetText())));
			return false;
		}
		else if (eName == kUserEnterData) {
			_userInput->SetUserText(ToString(element.GetText()));
			return false;
		}
		else if (eName == kResetOnSel) {
			return false;
		}
		else{
			std::stringstream trace;
			trace << "Unknown element (line " << element.GetLineNum() << "): " << element.Name();
			if (attribute) {
				trace << "\n\tattribute: " << ToString(attribute->Name());
			}
			WLog() << trace.str();
		}
	}
	else{
		WLog() << "Object not valid";
	}
	return (_userInput != nullptr);
}

DataTypeMode UserInputDataParser::getInputMask(const std::string& mask)
{
	DataTypeMode mode;
	if (mask == "0-9") {
		mode = NDataTypeMode::kNumeric;
	}
	else{
		WLog() << "Mask not supported";
	}
	return mode;
}
