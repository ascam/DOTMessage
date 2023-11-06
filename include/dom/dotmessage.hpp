#ifndef DOT_MESSAGE_HPP
#define DOT_MESSAGE_HPP

#include <string>

namespace macsa {
	namespace dot {
		class DOTMessage
		{
			public:
				static std::string GetLibraryVersion();
				static std::string GetLibraryName();
		};
	}
}

#endif

