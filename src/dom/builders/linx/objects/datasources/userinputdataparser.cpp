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

bool UserInputDataParser::VisitEnter(const tinyxml2::XMLElement &element, const tinyxml2::XMLAttribute *firstAttribute)
{
	if (_userInput){
		std::string eName {ToString(element.Name())};
		std::string eValue {ToString(element.GetText())};
		if (eName == kVarText){
			DLog() << eName;
		}
		else if (eName == kPrompt){
			DLog() << eName << " : " << eValue;
			_userInput->SetPrompt(eValue);
		}
		else if (eName == kMask){
			DLog() << eName << " : " << eValue;
			_userInput->SetDataTypeMode(getMask(eValue));
		}
		else if (eName == kUserEnterData){
			DLog() << eName << " : " << eValue;
			_userInput->SetUserText(eValue);
		}
		else if (eName == kResetOnSel){
			DLog() << eName << " : " << eValue;
		}
		else{
			std::stringstream trace;
			trace << "Unknown element (line " << element.GetLineNum() << "): " << element.Name();
			if (firstAttribute) {
				trace << "\n\tattribute: " << ToString(firstAttribute->Name());
			}
			WLog() << trace.str();
		}
	}
	else{
		WLog() << "Object not valid";
	}
	return (_userInput != nullptr);
}

DataTypeMode UserInputDataParser::getMask(const std::string &mask)
{
	DLog() << "Mask = " << mask;
	DataTypeMode mode;
	if (mask == "0-9"){
		mode = NDataTypeMode::kNumeric;
	}
//	else if (){ ##TODO alex: crear un userinput de otro tipo
//
//	}
	return mode;
}
