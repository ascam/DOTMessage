#include "counterdataparser.hpp"
#include "utils/macsalogger.hpp"
#include "utils/stringutils.hpp"

using namespace macsa::dot;
using macsa::linx::CounterDataParser;
using namespace macsa::utils::stringutils;
using macsa::utils::MacsaLogger;

static constexpr const char* kCounterText = "CounterText";
static constexpr const char* kResetOnSel = "ResetOnSel";
static constexpr const char* kSubCnt = "SubCnt";
static constexpr const char* kNoOfChars = "NoOfChars";
static constexpr const char* kClrStCntType = "ClrStCntType";
static constexpr const char* kStartVal = "StartVal";
static constexpr const char* kEndVal = "EndVal";
static constexpr const char* kCurrVal = "CurrVal";
static constexpr const char* kPrnPerCnt = "PrnPerCnt";
static constexpr const char* kLeadingChars = "LeadingChars";
static constexpr const char* kStepSize = "StepSize";

CounterDataParser::CounterDataParser(dot::VariableObject* obj):
	_object{obj},
	_counter{dynamic_cast<dot::CounterDataSource*>(_object->GetDatasource())}
{}

bool CounterDataParser::VisitEnter(const tinyxml2::XMLElement &element, const tinyxml2::XMLAttribute *attribute)
{
	if (_counter){
		std::string eName {ToString(element.Name())};
		std::string eValue {ToString(element.GetText())};
		DLog() << eName << " : " << eValue;
		if (eName == kCounterText){
			return true;
		}
		else if (eName == kResetOnSel){
			return false;
		}
		else if (eName == kSubCnt){
			return true;
		}
		else if (eName == kPrnPerCnt){
			return false;
		}
		else if (eName == kNoOfChars){
			_counter->SetLeadingZeros(ToInt(eValue));
			return false;
		}
		else if (eName == kStartVal){
			_counter->SetMinValue(ToInt(eValue));
			return false;
		}
		else if (eName == kEndVal){
			_counter->SetMaxValue(ToInt(eValue));
			return false;
		}
		else if (eName == kCurrVal){
			return false;
		}
		else if (eName == kLeadingChars){
			return false;
		}
		else if (eName == kStepSize){
			std::string eValue = element.GetText();
			if (StartsWith(eValue, "-")){
				WLog() << " Counter negative steps are not available. Value: " << eValue;
			}
			else{
				_counter->SetStep(ToInt(Replace(eValue,"+","")));
			}
			return false;
		}
		else if (eName == kClrStCntType){
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
		ELog() << "No valid object datasource";
	}
	return (_counter != nullptr);
}

