#ifndef MACSA_LINX_DOCUMENT_PROPERTIES_PARSER_HPP
#define MACSA_LINX_DOCUMENT_PROPERTIES_PARSER_HPP

#include "dom/builders/linx/linxparsercontext.hpp"
#include "tinyxml2.h"

namespace macsa {
	namespace linx {
		class DocumentPropertiesParser : public tinyxml2::XMLVisitor
		{
			public:
				DocumentPropertiesParser(LinxParserContext& context);
				virtual ~DocumentPropertiesParser();

				bool VisitEnter( const tinyxml2::XMLElement& element, const tinyxml2::XMLAttribute* firstAttribute) override;
				virtual bool VisitExit( const tinyxml2::XMLElement& element) override;

			private:
				LinxParserContext& _context;
				double _width;
				double _height;
				uint16_t _canvasRotated;
		};
	}
}

#endif
