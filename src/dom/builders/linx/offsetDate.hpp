#ifndef MACSA_LINX_OFFSET_DATE_HPP
#define MACSA_LINX_OFFSET_DATE_HPP

#include <string>
#include <map>

namespace macsa {
	namespace linx {
		struct OffsetDate
		{
				int day;
				int month;
				int year;
				std::string prompt;

				OffsetDate() :
					day{},
					month{},
					year{},
					prompt{}
				{}
		};
		using OffsetDateMap = std::map<std::string, OffsetDate>;
	}
}

#endif
