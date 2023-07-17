#ifndef DOT_MESSAGE_HOURDATETIME_SOURCE_HPP
#define DOT_MESSAGE_HOURDATETIME_SOURCE_HPP

#include <string>

#include "dom/components/datasources/datetimesource.hpp"
#include "datetimeformats.h"
#include "utils/stringutils.hpp"

namespace macsa
{
	namespace dot
	{
		namespace datetime
		{

			/**
			* @brief Datasource DateTime Hours specifiers
			* Include:
			*  - h -> Hour using 12 hour clock(range: 1 to 12)
			*  - hh -> Hour using 12 hour clock(range: 01 to 12)
			*  - H -> Hour using 24 hour clock(range: 0 to 23)
			*  - HH -> Hour using 24 hour clock(range: 00 to 23)
			*/
			class HourDateTimeSource : public DateTimeSource
			{
				public:
					explicit HourDateTimeSource(const std::string& format):
						DateTimeSource(format),
						_12hClock(false)
					{
						// Format as a 12 hour clock
						if (format == kFormath || format == kFormathh) {
							_12hClock = true;
						}
					}
					virtual ~HourDateTimeSource() = default;

				public:
					// Returns format specifier converted to value
					std::string GetData(Context* context) override
					{
						// Change range if 12h clock
						int hour = context->time.tm_hour;
						if (_12hClock && hour > 12) {
							hour -= 12;
						}
						else if (_12hClock && hour == 0) {
							hour = 12;
						}

						switch (_format.length())
						{
							case 1:     // h and H
								return utils::stringutils::ToString(hour);
							case 2:     // hh and HH
								return utils::stringutils::ToString(hour, 2);
							default:
								break;
						};
						return {};
					}
					/**
					 * @brief GetRefreshPolicy Returns Refresh Policy (by kCounter,  kSeconds, kMinutes,...)
					 * @return 'enum class RefreshPolicy'
					 */
					RefreshPolicy GetRefreshPolicy() override { return dot::RefreshPolicy::kHours; }

				private:
					// Format specifier for strftime
					bool _12hClock;
			};
		}
	}
}
#endif
