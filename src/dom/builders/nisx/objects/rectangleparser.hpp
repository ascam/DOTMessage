#ifndef MACSA_NISX_RECTANGLE_PARSER_HPP
#define MACSA_NISX_RECTANGLE_PARSER_HPP

#include "primitiveparser.hpp"

namespace macsa {
	namespace nisx {
		class RectangleParser : public PrimitiveParser
		{
			public:
				RectangleParser(dot::Object* primitive);
				virtual ~RectangleParser() = default;
		};
	}
}

#endif
