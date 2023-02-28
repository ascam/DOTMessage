#ifndef MACSA_NISX_OBJECT_PARSER_HPP
#define MACSA_NISX_OBJECT_PARSER_HPP

#include "dom/object.hpp"
#include "dom/color.hpp"
#include "tinyxml2.h"

namespace macsa {
	namespace nisx {
		class ObjectParser : public tinyxml2::XMLVisitor
		{
			public:
				ObjectParser(const std::string& fieldType, dot::Object* object);
				virtual ~ObjectParser();

			protected:
				std::string _fieldType;
				bool parseCommonElements(const tinyxml2::XMLElement& element, const tinyxml2::XMLAttribute* firstAttribute, dot::Object* object) const;
				dot::Color parseObjectColor(const tinyxml2::XMLAttribute* firstAttribute) const;
		};
	}
}

#endif
