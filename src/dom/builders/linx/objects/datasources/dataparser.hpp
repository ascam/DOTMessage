#ifndef MACSA_LINX_DATA_PARSER_HPP
#define MACSA_LINX_DATA_PARSER_HPP

#include "dom/builders/linx/linxparsercontext.hpp"
#include "dom/variableobject.hpp"
#include "tinyxml2.h"
#include <string>

namespace macsa {
	namespace linx {
		enum class LinxDataType : int {
			kFixedOrUserInput = 0,
			kTime = 1,
			kDate = 2,
			kOffsetDate = 3,
			kCounter = 4,
			kComposite = 5,
			// 6 ??
			kStaticOffsetDateTime = 7 //userinput with date format
		};

		class DataParser : public tinyxml2::XMLVisitor
		{
			public:
				DataParser(dot::VariableObject* object, LinxParserContext& context);
				virtual ~DataParser() = default;

				bool VisitEnter( const tinyxml2::XMLElement& element, const tinyxml2::XMLAttribute* attribute) override;
				bool VisitExit( const tinyxml2::XMLElement& element) override;

			private:
				using CompositeElements = std::vector<std::pair<std::string, std::string>>;

				dot::VariableObject* _object;
				LinxParserContext& _context;
				struct OffsetDate _offsetDate;
				LinxDataType _dataType;
				uint _maxLength;
				std::string _defaultValue;
				std::string _formula;
				CompositeElements _srcItems;
				CompositeElements _gs1Values;
				bool _isGS1Format;

				void fillGs1Values(std::string value);
				void processGs1Value();
				std::string checkDateTimeFormat(std::string& datetime);

		};
	}
}


#endif
