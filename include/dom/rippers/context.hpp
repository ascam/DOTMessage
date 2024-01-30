#ifndef DOTMESSAGE_CONTEXT_HPP
#define DOTMESSAGE_CONTEXT_HPP

#include "model/datecodes.hpp"
#include "dom/document.hpp"

namespace macsa
{
	namespace dot
	{
		struct Context
		{
			unsigned int counter;
			DateCodes dateCodes;
			dot::Document* document;
			tm time;
		};
	}
}
#endif
