#ifndef MACSA_NISX_COLORS_PALETTE_PARSER_HPP
#define MACSA_NISX_COLORS_PALETTE_PARSER_HPP

#include "dom/document.hpp"
#include "tinyxml2.h"

namespace macsa {
	namespace nisx {
		class ColorsPaletteParser : public tinyxml2::XMLVisitor
		{
			public:
				ColorsPaletteParser(dot::Document& document);
				virtual ~ColorsPaletteParser();

				bool VisitEnter(const tinyxml2::XMLElement& element, const tinyxml2::XMLAttribute* firstAttribute) override;
				bool VisitExit(const tinyxml2::XMLElement& element) override;

			private:
				dot::Document& _doc;
				dot::ColorsPalette _palette;
		};
	}
}

#endif
