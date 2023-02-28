#ifndef MACSA_NISX_DOCUMENT_PROPERTIES_PARSER_HPP
#define MACSA_NISX_DOCUMENT_PROPERTIES_PARSER_HPP

#include "dom/document.hpp"
#include "tinyxml2.h"

namespace macsa {
	namespace nisx {
		class DocumentPropertiesParser : public tinyxml2::XMLVisitor
		{
			public:
				DocumentPropertiesParser(dot::Document& document);
				virtual ~DocumentPropertiesParser();

				bool VisitEnter( const tinyxml2::XMLElement& element, const tinyxml2::XMLAttribute* firstAttribute) override;

			private:
				dot::Document& _document;
		};
	}
}

#endif
