#ifndef MACSA_LINX_DOCUMENT_PARSER_HPP
#define MACSA_LINX_DOCUMENT_PARSER_HPP

#include "dom/document.hpp"
#include "linxparsercontext.hpp"
#include "tinyxml2.h"

namespace macsa {
	namespace linx {
		class DocumentParser : public tinyxml2::XMLVisitor
		{
			public:
				DocumentParser(dot::Document& document);
				virtual ~DocumentParser() = default;

				static std::string GetSupportedLinxVersion();
				virtual bool VisitEnter( const tinyxml2::XMLElement& element, const tinyxml2::XMLAttribute* firstAttribute);

			private:
				dot::Document& _doc;
				LinxParserContext _context;
				void parseConcreteField(const tinyxml2::XMLElement &element, const std::string& fieldName, const std::string& fieldType);
		};
	}
}

#endif
