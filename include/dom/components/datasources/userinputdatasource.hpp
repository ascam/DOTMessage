#ifndef DOT_MESSAGE_USER_INPUT_DATASOURCE_HPP
#define DOT_MESSAGE_USER_INPUT_DATASOURCE_HPP

#include <string>

#include "signal/signal.hpp"
#include "dom/rippers/context.hpp"
#include "dom/components/datasources/datasource.hpp"

namespace macsa {
	namespace dot {
		class IDocumentVisitor;

		/**
		 * @brief User input prompt behavior
		 */
		enum class NPromptBehavior
		{
			kDefaultValue,
			kBlankValue,
			kLastValue
		};

		/**
		 * @brief User input prompt behavior smart enum
		 */
		class PromptBehavior final : public utils::SmartEnum<NPromptBehavior>
		{
			public:
				PromptBehavior(const NPromptBehavior& behavior = NPromptBehavior::kDefaultValue) :
					utils::SmartEnum<NPromptBehavior>(behavior)
				{}

				PromptBehavior(const std::string& behavior) :
					utils::SmartEnum<NPromptBehavior>(NPromptBehavior::kDefaultValue)
				{
					fromString(behavior);
				}

				const PromptBehavior& operator = (const std::string& val) {
					fromString(val);
					return *this;
				}

			private:
				const std::vector<std::pair<NPromptBehavior,std::string>>& getData() const override;
		};

		/**
		 * @brief User input padding type
		 */
		enum class NPaddingType
		{
			kNone,
			kLeft,
			kRight
		};

		/**
		 * @brief User input padding type smart enum
		 */
		class PaddingType final : public utils::SmartEnum<NPaddingType>
		{
			public:
				PaddingType(const NPaddingType& type = NPaddingType::kNone) :
					utils::SmartEnum<NPaddingType>(type)
				{}

				PaddingType(const std::string& type) :
					utils::SmartEnum<NPaddingType>(NPaddingType::kNone)
				{
					fromString(type);
				}

				const PaddingType& operator = (const std::string& val) {
					fromString(val);
					return *this;
				}

			private:
				const std::vector<std::pair<NPaddingType,std::string>>& getData() const override;
		};

		/**
		 * @brief User input data type.
		 */
		enum class NDataType
		{
			kString,
			kInteger,
			kFloat
		};

		/**
		 * @brief User input data type smart enum
		 */
		class DataType final : public utils::SmartEnum<NDataType>
		{
			public:
				DataType(const NDataType& type = NDataType::kString) :
					utils::SmartEnum<NDataType>(type)
				{}

				DataType(const std::string& type) :
					utils::SmartEnum<NDataType>(NDataType::kString)
				{
					fromString(type);
				}

				const DataType& operator = (const std::string& val) {
					fromString(val);
					return *this;
				}

			private:
				const std::vector<std::pair<NDataType,std::string>>& getData() const override;
		};

		/**
		 * @brief User input data type mode
		 */
		enum class NDataTypeMode
		{
			kAlphanum,
			kNumeric,
			kAlphabetic
		};

		/**
		 * @brief Data type mode smart enum
		 */
		class DataTypeMode final : public utils::SmartEnum<NDataTypeMode>
		{
			public:
				DataTypeMode(const NDataTypeMode& mode = NDataTypeMode::kAlphanum) :
					utils::SmartEnum<NDataTypeMode>(mode)
				{}

				DataTypeMode(const std::string& mode) :
					utils::SmartEnum<NDataTypeMode>(NDataTypeMode::kAlphanum)
				{
					fromString(mode);
				}

				const DataTypeMode& operator = (const std::string& val) {
					fromString(val);
					return *this;
				}

			private:
				const std::vector<std::pair<NDataTypeMode,std::string>>& getData() const override;
		};

		/**
		 * @brief The UserInputDataSource class. This class allow the objects
		 * to return variable data from a user input
		 */
		class UserInputDataSource final : public DataSource
		{
			public:
				/**
				 * @brief The UserInfo struct. This struct has the information
				 * about who was the last user that changed the value.
				 */
				struct UserInfo {
					std::string device;
					std::string timestamp;

					UserInfo();

					bool operator == (const UserInfo& other) const {
						return device == other.device && timestamp == other.timestamp;
					}
					bool operator != (const UserInfo& other) const {
						return device != other.device || timestamp != other.timestamp;
					}
				};

				/**
				 * @brief The Limits struct. This struct has the limits
				 * of the value when is a numeric input.
				 */
				struct Limits {
					unsigned int min;
					unsigned int max;

					Limits();

					bool operator == (const Limits& other) const {
						return min == other.min && max == other.max;
					}
					bool operator != (const Limits& other) const {
						return min != other.min && max != other.max;
					}
				};

				/**
				 * @brief The InputTextAttributes struct. This struct has the
				 * parameters of the input text.
				 * limits: min and max input lenght.
				 * padding: side of the text where the padding is applied.
				 * paddingChar: Padding character.
				 * range: range of values if the input is numeric.
				 */
				struct InputTextAttributes {
					Limits limits;
					PaddingType padding;
					char paddingChar;
					Limits range;

					InputTextAttributes();

					bool operator == (const InputTextAttributes& other) const {
						return limits == other.limits &&
								padding == other.padding &&
								paddingChar == other.paddingChar &&
								range == other.range;
					}
					bool operator != (const InputTextAttributes& other) const {
						return limits != other.limits ||
								padding != other.padding ||
								paddingChar != other.paddingChar ||
								range != other.range;
					}
				};

			public:
				UserInputDataSource();
				virtual ~UserInputDataSource() = default;

				/**
				 * @brief Accept: Allow the visitor to visit this object.
				 * @param visitor: Visitor object
				 * @return boolean with the result of the visit method
				 * of the visitor object.
				 */
				bool Accept(IDocumentVisitor* visitor) override;

				/**
				 * @brief GetPrompt. Getter method for the prompt shown to the user.
				 * @return An string to show to the user when the data is requested.
				 */
				const std::string& GetPrompt() const {
					return _prompt;
				}

				/**
				 * @brief SetPrompt. Setter method for the prompt shown to the user.
				 * @param value: string to show to the user when the data is requested.
				 */
				void SetPrompt(const std::string& prompt) {
					if (prompt != _prompt)	{
						_prompt = prompt;
						PromptChanged.Emit();
					}
				}

				/**
				 * @brief GetValue. Getter method for the current user value.
				 * @return The current text to render
				 */
				const std::string& GetValue() const {
					return _value;
				}

				/**
				 * @brief SetValue. Setter method for the current user value.
				 * @param value: The text to be rendered
				 */
				void SetValue(const std::string& value) {
					if (value != _value)	{
						_value = value;
						ValueChanged.Emit();
					}
				}

				/**
				 * @brief GetDefaultValue. Getter method for default value.
				 * @return the default value of the input if is not changed by
				 * a user.
				 */
				const std::string& GetDefaultValue() const {
					return _defaultValue;
				}

				/**
				 * @brief SetDefaultValue. Setter method for default value.
				 * @param value: the default value of the input.
				 */
				void SetDefaultValue(const std::string& value) {
					if (value != _defaultValue)	{
						_defaultValue = value;
						DefaultValueChanged.Emit();
					}
				}

				/**
				 * @brief GetUserText. Getter method for the value changed by a user
				 * @return the value changed by a user
				 */
				const std::string& GetUserText() const {
					return _userText;
				}

				/**
				 * @brief SetUserText. Setter method for the value changed by a user
				 * @param value: the value changed by a user
				 */
				void SetUserText(const std::string& value) {
					if (value != _userText)	{
						_userText = value;
						UserTextChanged.Emit();
					}
				}

				/**
				 * @brief GetUserInfo. Getter method of the user info struct
				 * @return the user info struct that contains the info about
				 * the last user that changes the value.
				 */
				const UserInfo& GetUserInfo() const {
					return _userInfo;
				}

				/**
				 * @brief SetUserInfo. Setter method of the user info struct
				 * @param info: the user info struct to set .
				 */
				void SetUserInfo(const UserInfo& info) {
					if (_userInfo != info) {
						_userInfo = info;
						UserInfoChanged.Emit();
					}
				}

				/**
				 * @brief GetDataType. Getter method of the input data type.
				 * @return The current configured input data type.
				 */
				const DataType& GetDataType() const {
					return _dataType;
				}

				/**
				 * @brief SetDataType. Setter method of the input data type.
				 * @param type: The input data type to configure.
				 */
				void SetDataType(const DataType& type) {
					if (type != _dataType)	{
						_dataType = type;
						DataTypeChanged.Emit();
					}
				}

				/**
				 * @brief GetDataTypeMode. Getter method of the available input data type.
				 * @return the available input data type.
				 */
				const DataTypeMode& GetDataTypeMode() const {
					return _dataTypeMode;
				}

				/**
				 * @brief SetDataTypeMode. Setter method of the available input data type.
				 * @param type: the available input data type.
				 */
				void SetDataTypeMode(const DataTypeMode& type) {
					if (type != _dataTypeMode)	{
						_dataTypeMode = type;
						DataTypeModeChanged.Emit();
					}
				}

				/**
				 * @brief GetPromptBehavior. Getter method for the behaviour of the
				 * prompted text
				 * @return The prompted text behaviour.
				 */
				const PromptBehavior& GetPromptBehavior() const {
					return _promptBehavior;
				}

				/**
				 * @brief SetPromptBehavior. Setter method for the behaviour of the
				 * prompted text
				 * @param behaviour: The prompted text behaviour.
				 */
				void SetPromptBehavior(const PromptBehavior& behaviour) {
					if (behaviour != _promptBehavior)	{
						_promptBehavior = behaviour;
						PromptBehaviorChanged.Emit();
					}
				}

				/**
				 * @brief GetInputTextAttributes. Getter method of the input text
				 * attributs.
				 * @return The structure of the input text attributes.
				 */
				const InputTextAttributes& GetInputTextAttributes() const {
					return _inputTextAttributes;
				}

				/**
				 * @brief SetInputTextAttributes. Setter method of the input text
				 * attributs.
				 * @param attributes: The structure of the input text attributes to
				 * apply.
				 */
				void SetInputTextAttributes(const InputTextAttributes& attributes) {
					if (_inputTextAttributes != attributes)	{
						_inputTextAttributes = attributes;
						InputTextAttributesChanged.Emit();
					}
				}

				/**
				 * @brief GetRequired. Getter method of the required parameter.
				 * This parameter force the request of the input before the messages
				 * is selected to print.
				 * @return true if the input is required to print the message or false
				 * if is not required.
				 */
				bool GetRequired() const {
					return _required;
				}

				/**
				 * @brief SetRequired. Setter method of the required parameter.
				 * @param required: bool to force the request of the input before
				 * to print the message.
				 */
				void SetRequired(bool required) {
					if (required != _required)	{
						_required = required;
						RequiredChanged.Emit();
					}
				}

				/**
				* @brief GetData. Get data source updated data result.
				* @return data source text result data.
				*/
				std::string GetData(Context* context) const override;

			public:
				Signal<> PromptChanged;
				Signal<> ValueChanged;
				Signal<> UserTextChanged;
				Signal<> UserInfoChanged;
				Signal<> DefaultValueChanged;
				Signal<> DataTypeChanged;
				Signal<> DataTypeModeChanged;
				Signal<> PromptBehaviorChanged;
				Signal<> InputTextAttributesChanged;
				Signal<> RequiredChanged;

			private:
				std::string _prompt;
				std::string _value;
				std::string _userText;
				UserInfo _userInfo;
				std::string _defaultValue;
				DataType _dataType;
				DataTypeMode _dataTypeMode;
				PromptBehavior _promptBehavior;
				InputTextAttributes _inputTextAttributes;
				bool _required;
		};
	}
}

#endif
