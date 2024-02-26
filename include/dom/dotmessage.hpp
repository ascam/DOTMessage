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
#ifdef _WINDOWS
				static const bool RegisterFactories();
#endif
		};
	}
}

#endif
