#ifndef DOTMESSAGE_CONTEXT_HPP
#define DOTMESSAGE_CONTEXT_HPP

#include "printer/datecodes.hpp"

namespace macsa
{
	namespace dot
	{
		struct Context
		{
			int counter;
			macsa::printers::DateCodes dateCodes;
		};
	}
}
#endif
