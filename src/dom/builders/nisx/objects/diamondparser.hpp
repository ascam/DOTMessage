#ifndef MACSA_NISX_DIAMOND_PARSER_HPP
#define MACSA_NISX_DIAMOND_PARSER_HPP

#include "primitiveparser.hpp"

namespace macsa {
	namespace nisx {
		class DiamondParser : public PrimitiveParser
		{
			public:
				DiamondParser(dot::Object* primitive);
				virtual ~DiamondParser() = default;

			private:
				static bool _registered;
		};
	}
}

#endif
