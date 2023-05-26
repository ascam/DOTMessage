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

				virtual bool Visit(const tinyxml2::XMLDeclaration& declaration);
				virtual bool Visit(const tinyxml2::XMLText& text);
				virtual bool Visit(const tinyxml2::XMLComment& comment);
				virtual bool Visit(const tinyxml2::XMLUnknown& unknown);

			private:
				dot::Document& _doc;
				LinxParserContext _context;
				std::array<uint8_t,3> getDocumentVersion(const std::string& versionAttribute) const;
				void parseConcreteField(const tinyxml2::XMLElement& element, std::string& fieldName, std::string& fieldType);
		};
	}
}

#endif
