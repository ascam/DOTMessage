#ifndef MACSA_LINX_FONT_PARSER_HPP
#define MACSA_LINX_FONT_PARSER_HPP

#include "dom/components/font.hpp"
#include "dom/components/textboxproperties.hpp"
#include "tinyxml2.h"

namespace macsa {
	namespace linx {
		class FontParser : public tinyxml2::XMLVisitor
		{
			public:
				FontParser(dot::Font& font, dot::TextBoxProperties& textBoxProperties);
				virtual ~FontParser() = default;

				bool VisitEnter(const tinyxml2::XMLElement& element, const tinyxml2::XMLAttribute* firstAttribute) override;

			private:
				dot::Font& _font;
				dot::TextBoxProperties& _textBoxProperties;
		};
	}
}

#endif
