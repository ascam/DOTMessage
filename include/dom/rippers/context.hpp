#ifndef DOTMESSAGE_CONTEXT_HPP
#define DOTMESSAGE_CONTEXT_HPP

#include "printer/datecodes.hpp"
#include "dom/document.hpp"

namespace macsa
{
	namespace dot
	{
		struct Context
		{
			int counter;
			macsa::printers::DateCodes dateCodes;
			dot::Document* document;
		};
	}
}
#endif
