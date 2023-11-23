#ifndef MACSA_NISX_LINE_PARSER_HPP
#define MACSA_NISX_LINE_PARSER_HPP

#include "primitiveparser.hpp"

namespace macsa {
	namespace nisx {
		class LineParser : public PrimitiveParser
		{
			public:
				LineParser(dot::Object* primitive);
				virtual ~LineParser() = default;

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
