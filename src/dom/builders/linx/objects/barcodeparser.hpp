#ifndef MACSA_LINX_BARCODE_PARSER_HPP
#define MACSA_LINX_BARCODE_PARSER_HPP

#include <memory>
#include "dom/barcode.hpp"
#include "dom/builders/linx/linxparsercontext.hpp"
#include "objectparser.hpp"
#include "tinyxml2.h"

namespace macsa {
	namespace linx {
		class BarcodeInfoParser;
		class BarcodeParser : public ObjectParser
		{
			public:
				BarcodeParser(dot::Object* barcode, LinxParserContext& context);
				virtual ~BarcodeParser() = default;

				bool VisitEnter( const tinyxml2::XMLElement& element, const tinyxml2::XMLAttribute* attribute) override;
				bool VisitExit( const tinyxml2::XMLElement& element) override;

			private:
				dot::Barcode* _barcode;
				LinxParserContext& _context;
				dot::Geometry _geometry;
		};
		class BarcodeInfoParser : public tinyxml2::XMLVisitor
		{
			public:
				BarcodeInfoParser(dot::Barcode* barcode);
				virtual ~BarcodeInfoParser() = default;

				bool VisitEnter( const tinyxml2::XMLElement& element, const tinyxml2::XMLAttribute* attribute) override;
				bool VisitExit( const tinyxml2::XMLElement& element) override;

			private:
				dot::Barcode* _barcode;
				dot::Font _font;
		};
	}
}

#endif
