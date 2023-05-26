#ifndef MACSA_LINX_OFFSET_DATE_PARSER_HPP
#define MACSA_LINX_OFFSET_DATE_PARSER_HPP

#include "tinyxml2.h"
#include "linxparsercontext.hpp"

namespace macsa {
	namespace linx {
		class OffsetDateParser : public tinyxml2::XMLVisitor
		{
			public:
				OffsetDateParser(LinxParserContext& context);
				virtual ~OffsetDateParser() = default;

				virtual bool VisitEnter(const tinyxml2::XMLElement& element, const tinyxml2::XMLAttribute* attribute);
				virtual bool VisitExit( const tinyxml2::XMLElement& element);

			private:
				LinxParserContext& _context;
				std::string _offsetName;
				struct OffsetDate _offsetDate;
		};
	}
}
#endif
