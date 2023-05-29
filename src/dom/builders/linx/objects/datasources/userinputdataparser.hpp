#ifndef MACSA_LINX_UI_PARSER_HPP
#define MACSA_LINX_UI_PARSER_HPP

#include "dom/components/datasources/userinputdatasource.hpp"
#include "dom/variableobject.hpp"
#include "tinyxml2.h"

namespace macsa {
	namespace linx {
		class UserInputDataParser : public tinyxml2::XMLVisitor
		{
			public:
				UserInputDataParser(dot::VariableObject* obj);
				virtual ~UserInputDataParser() = default;

				bool VisitEnter( const tinyxml2::XMLElement& element, const tinyxml2::XMLAttribute* firstAttribute) override;

			private:
				dot::VariableObject* _object;
				dot::UserInputDataSource* _userInput;

				dot::DataTypeMode getInputMask(const std::string & mask);
		};
	}
}
#endif
