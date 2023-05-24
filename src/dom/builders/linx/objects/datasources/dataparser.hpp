#ifndef MACSA_LINX_DATA_PARSER_HPP
#define MACSA_LINX_DATA_PARSER_HPP

#include "dom/builders/linx/offsetDate.hpp"
#include "dom/variableobject.hpp"
#include "tinyxml2.h"
#include <string>

namespace macsa {
	namespace linx {
		enum LinxDataType {
			FixedOrUserInput = 0,
			Time = 1,
			Date = 2,
			OffsetDate = 3,
			Counter = 4,
			Composite = 5,
			// 6 ??
			StaticOffsetDateTime = 7 //userinput with date format
		};

		class DataParser : public tinyxml2::XMLVisitor
		{
			public:
				DataParser(dot::VariableObject* object, OffsetDateMap& offsetDateMap);
				virtual ~DataParser() = default;

				bool VisitEnter( const tinyxml2::XMLElement& element, const tinyxml2::XMLAttribute* firstAttribute) override;
				bool VisitExit( const tinyxml2::XMLElement& element) override;

			private:
				dot::VariableObject* _object;
				OffsetDateMap& _offsetDateMap;
				struct OffsetDate _offsetDate;
				uint _dataType;
				uint _maxLength;
				std::string _defaultValue;
				std::string _formula;
				std::vector <std::pair<std::string, std::string>> _srcItems;
				bool _isGS1Format;
				std::vector<std::pair<std::string, std::string>> _gs1Values;

				void fillGs1Values(std::string value);
				void getGs1Value();
				std::string checkDateTimeFormat(std::string& datetime);
		};
	}
}


#endif
