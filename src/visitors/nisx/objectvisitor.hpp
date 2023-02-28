#ifndef MACSA_NISX_OBJECT_VISITOR_HPP
#define MACSA_NISX_OBJECT_VISITOR_HPP

#include "dom/object.hpp"
#include "dom/font.hpp"
#include "tinyxml2.h"

namespace macsa {
	namespace nisx {
		class ObjectVisitor
		{
			public:
				ObjectVisitor(tinyxml2::XMLDocument& document);
				virtual ~ObjectVisitor() = default;

			protected:
				tinyxml2::XMLDocument& _xmlDocument;

				bool visitObject(const dot::Object& object, tinyxml2::XMLElement* element);
				bool visitFont(const dot::Font& font, tinyxml2::XMLElement* parent);
		};
	}
}

#endif
