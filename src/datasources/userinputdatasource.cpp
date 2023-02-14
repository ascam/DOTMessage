#include "message/datasources/userinputdatasource.hpp"
#include "factories/datasourcefactory.hpp"

using macsa::dot::UserInputDataSource;
using macsa::dot::RefreshPolicy;
using macsa::dot::PromptBehavior;
using macsa::dot::NPromptBehavior;
using macsa::dot::PaddingType;
using macsa::dot::NPaddingType;
using macsa::dot::DataType;
using macsa::dot::NDataType;
using macsa::dot::DataTypeMode;
using macsa::dot::NDataTypeMode;

namespace macsa {
	namespace dot {
		namespace  {
			static const bool UserInputFactoryRegistered = ConcreteDataSourceFactory<UserInputDataSource>::Register(NDataSourceType::kUserInput);
		}
	}
}

UserInputDataSource::UserInfo::UserInfo() :
	device{},
	timestamp{}
{}

UserInputDataSource::Limits::Limits() :
	min{},
	max{}
{}

UserInputDataSource::InputTextAttributes::InputTextAttributes():
	limits{},
	padding{},
	paddingChar{' '},
	range{}
{}

const std::vector<std::pair<NPromptBehavior, std::string>>& PromptBehavior::getData() const
{
	static const std::vector<std::pair<NPromptBehavior,std::string>> promptBehaviorData {
		{NPromptBehavior::kBlankValue,   "Blank"},
		{NPromptBehavior::kLastValue,    "LastValue"},
		{NPromptBehavior::kDefaultValue, "DEFAULT_VALUE"}
	};
	return promptBehaviorData;
}

const std::vector<std::pair<NPaddingType, std::string>>& PaddingType::getData() const
{
	static const std::vector<std::pair<NPaddingType,std::string>> paddingTypeData {
		{NPaddingType::kLeft,  "Left"},
		{NPaddingType::kRight, "Right"},
		{NPaddingType::kNone,  "None"}
	};
	return paddingTypeData;
}

const std::vector<std::pair<NDataType, std::string>>& DataType::getData() const{
	static const std::vector<std::pair<NDataType,std::string>> dataTypeData {
		{NDataType::kInteger, "Integer"},
		{NDataType::kFloat,   "Float"},
		{NDataType::kString,  "String"}
	};
	return dataTypeData;
}

const std::vector<std::pair<NDataTypeMode, std::string> > &DataTypeMode::getData() const
{
	static const std::vector<std::pair<NDataTypeMode,std::string>> kNDataTypeModeData {
		{NDataTypeMode::kNumeric,    "1"},
		{NDataTypeMode::kAlphabetic, "2"},
		{NDataTypeMode::kAlphanum,   "0"}
	};
	return kNDataTypeModeData;
}

UserInputDataSource::UserInputDataSource() :
	DataSource(NDataSourceType::kUserInput),
	_prompt{},
	_value{},
	_userText{},
	_userInfo{},
	_defaultValue{},
	_dataType{},
	_dataTypeMode{},
	_promptBehavior{},
	_inputTextAttributes{},
	_required{}
{}

std::string UserInputDataSource::GetData()
{
	return _defaultValue;
}

macsa::dot::RefreshPolicy UserInputDataSource::GetRefreshPolicy() const
{
	return RefreshPolicy::kNone;
}
