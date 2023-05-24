#ifndef MACSA_LINX_TEXT_PROPERTIES_PARSER_HPP
#define MACSA_LINX_TEXT_PROPERTIES_PARSER_HPP

#include "objects/objectparser.hpp"
#include "objects/fontparser.hpp"

#include "tinyxml2.h"

namespace macsa {
	namespace linx {
		class TextPropertiesParser : public tinyxml2::XMLVisitor
		{
			public:
				TextPropertiesParser(dot::Object* object);
				virtual ~TextPropertiesParser();

				bool VisitEnter(const tinyxml2::XMLElement& element, const tinyxml2::XMLAttribute* firstAttribute) override;
				bool VisitExit(const tinyxml2::XMLElement& element) override;

			private:
				dot::Font _font;


		};
	};
}

#endif
