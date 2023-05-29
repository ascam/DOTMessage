#ifndef MACSA_LINX_PRIMITIVE_PARSER_HPP
#define MACSA_LINX_PRIMITIVE_PARSER_HPP

#include "dom/builders/linx/linxparsercontext.hpp"
#include "dom/components/pen.hpp"
#include "objectparser.hpp"
#include "tinyxml2.h"

namespace macsa {
	namespace linx {
		class PrimitiveParser : public ObjectParser
		{
			public:
				PrimitiveParser(LinxParserContext& context, std::string& fieldName);
				virtual ~PrimitiveParser() = default;

				bool VisitEnter( const tinyxml2::XMLElement& element, const tinyxml2::XMLAttribute* attribute) override;
				bool VisitExit( const tinyxml2::XMLElement& element) override;

			private:
				LinxParserContext& _context;
				std::string& _fieldName;
				dot::Geometry _geometry;
				dot::NObjectType _objectType;
				dot::Pen _pen;
				int _rotation;
				bool _filled;
				bool _displayed;
		};
	}
}

#endif
