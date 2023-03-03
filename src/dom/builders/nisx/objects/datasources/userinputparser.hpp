#ifndef MACSA_NISX_OBJECT_USERINPUT_DATASOURCE_PARSER_HPP
#define MACSA_NISX_OBJECT_USERINPUT_DATASOURCE_PARSER_HPP

#include "datasourceparser.hpp"
#include "dom/components/datasources/userinputdatasource.hpp"

namespace macsa {
	namespace nisx {
		class UserInputParser: public DataSourceParser
		{
			public:
				UserInputParser(dot::VariableObject* object);
				virtual ~UserInputParser() = default;

				bool VisitEnter(const tinyxml2::XMLElement& element, const tinyxml2::XMLAttribute* firstAttribute) override;

			private:
				dot::UserInputDataSource* _userInput;
		};

		class UserInfoParser: public tinyxml2::XMLVisitor
		{
			public:
				UserInfoParser(dot::UserInputDataSource* userInput);
				virtual ~UserInfoParser() = default;

				bool VisitEnter(const tinyxml2::XMLElement& element, const tinyxml2::XMLAttribute* firstAttribute) override;
				bool VisitExit(const tinyxml2::XMLElement& element) override;

			private:
				dot::UserInputDataSource* _userInput;
				dot::UserInputDataSource::UserInfo _userInfo;
		};

		class InputTextAttributesParser: public tinyxml2::XMLVisitor
		{
			public:
				InputTextAttributesParser(dot::UserInputDataSource* userInput);
				virtual ~InputTextAttributesParser() = default;

				bool VisitEnter(const tinyxml2::XMLElement& element, const tinyxml2::XMLAttribute* firstAttribute) override;
				bool VisitExit(const tinyxml2::XMLElement& element) override;

			private:
				dot::UserInputDataSource* _userInput;
				dot::UserInputDataSource::InputTextAttributes _textAttributes;
		};
	}
}

#endif
