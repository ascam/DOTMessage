#ifndef MACSA_LINX_TEXT_PARSER_HPP
#define MACSA_LINX_TEXT_PARSER_HPP

#include <memory>
#include "tinyxml2.h"

#include "objectparser.hpp"
#include "datasources/dataparser.hpp"
#include "dom/text.hpp"
#include "dom/builders/linx/linxparsercontext.hpp"
#include "dom/builders/linx/offsetDate.hpp"

namespace macsa {
	namespace linx {
		class TextParser : public ObjectParser
		{
			public:
				TextParser(dot::Object* text, LinxParserContext& context, OffsetDateMap& offsetDateMap);
				virtual ~TextParser() = default;

				bool VisitEnter( const tinyxml2::XMLElement& element, const tinyxml2::XMLAttribute* firstAttribute) override;
				bool VisitExit( const tinyxml2::XMLElement& element) override;

			private:
				LinxParserContext& _context;
				OffsetDateMap& _offsetDateMap;
				dot::Text* _text;
				dot::Geometry _geometry;
				dot::Font _font;
				dot::TextBoxProperties _textBoxProperties;
				std::unique_ptr<DataParser> _dataParser;
		};
	}
}

#endif
