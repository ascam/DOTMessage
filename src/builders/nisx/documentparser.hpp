#ifndef MACSA_NISX_DOCUMENT_PARSER_HPP
#define MACSA_NISX_DOCUMENT_PARSER_HPP

#include "dom/document.hpp"
#include "tinyxml2.h"

namespace macsa {
	namespace nisx {
		class DocumentParser : public tinyxml2::XMLVisitor
		{
			public:
				DocumentParser(dot::Document& document);
				virtual ~DocumentParser();

				static std::string GetSupportedNisxVersion();

				virtual bool VisitEnter( const tinyxml2::XMLElement& element, const tinyxml2::XMLAttribute* firstAttribute);
				virtual bool VisitExit( const tinyxml2::XMLElement& element);


				virtual bool Visit(const tinyxml2::XMLDeclaration& declaration);
				virtual bool Visit(const tinyxml2::XMLText& text);
				virtual bool Visit(const tinyxml2::XMLComment& comment);
				virtual bool Visit(const tinyxml2::XMLUnknown& unknown);

			private:
				dot::Document& _doc;

				std::array<uint8_t,3> getDocumentVersion(const std::string& versionAttribute) const;
		};
	}
}

#endif