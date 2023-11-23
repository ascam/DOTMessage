#ifndef MACSA_NISX_ELLIPSE_PARSER_HPP
#define MACSA_NISX_ELLIPSE_PARSER_HPP

#include "primitiveparser.hpp"

namespace macsa {
	namespace nisx {
		class EllipseParser : public PrimitiveParser
		{
			public:
				EllipseParser(dot::Object* primitive);
				virtual ~EllipseParser() = default;

				static bool GetRegistered()
				{
					return _registered;
				}

			private:
				static bool _registered;
		};
	}
}

#endif
