#ifndef MACSA_NISX_BARCODE_PARSER_HPP
#define MACSA_NISX_BARCODE_PARSER_HPP

#include "dom/barcode.hpp"
#include "objectparser.hpp"
#include "tinyxml2.h"

namespace macsa {
	namespace nisx {
		class BarcodeParser : public ObjectParser
		{
			public:
				BarcodeParser(dot::Object* barcode);
				virtual ~BarcodeParser() = default;

				bool VisitEnter( const tinyxml2::XMLElement& element, const tinyxml2::XMLAttribute* firstAttribute) override;
				bool VisitExit( const tinyxml2::XMLElement& element) override;

				static bool GetRegistered()
				{
					return _registered;
				}

			private:
				dot::Barcode* _barcode;
				dot::Font _font;
				static bool _registered;
		};
	}
}

#endif
