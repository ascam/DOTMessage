#ifndef MACSA_NISX_FONT_PARSER_HPP
#define MACSA_NISX_FONT_PARSER_HPP

#include "dom/components/font.hpp"
#include "tinyxml2.h"

namespace macsa {
	namespace nisx {
		class FontParser : public tinyxml2::XMLVisitor
		{
			public:
				FontParser(dot::Font& font);
				virtual ~FontParser() = default;

				bool VisitEnter(const tinyxml2::XMLElement& element, const tinyxml2::XMLAttribute* firstAttribute) override;

			private:
				dot::Font& _font;

				void parserFont(const tinyxml2::XMLAttribute* firstAttribute);
		};
	}
}

#endif
