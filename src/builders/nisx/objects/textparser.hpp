#ifndef MACSA_NISX_TEXT_PARSER_HPP
#define MACSA_NISX_TEXT_PARSER_HPP

#include "dom/text.hpp"
#include "objectparser.hpp"
#include "tinyxml2.h"

namespace macsa {
	namespace nisx {
		class TextParser : public ObjectParser
		{
			public:
				TextParser(dot::Object* text);
				virtual ~TextParser();

				bool VisitEnter( const tinyxml2::XMLElement& element, const tinyxml2::XMLAttribute* firstAttribute) override;
				bool VisitExit( const tinyxml2::XMLElement& element) override;

			private:
				dot::Text* _text;
				dot::Font _font;
		};

		class TextAdjustParser : public tinyxml2::XMLVisitor
		{
			public:
				TextAdjustParser(dot::Text* text);
				virtual ~TextAdjustParser();

				bool VisitEnter( const tinyxml2::XMLElement& element, const tinyxml2::XMLAttribute* firstAttribute) override;
				bool VisitExit( const tinyxml2::XMLElement& element) override;

			private:
				dot::Text* _text;
				dot::TextBoxProperties _boxProperties;
				const std::string _elementName;
		};
	}
}

#endif
