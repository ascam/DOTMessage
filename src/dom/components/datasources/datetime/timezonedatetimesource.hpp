#ifndef DOT_MESSAGE_TIMEZONEDATETIME_SOURCE_HPP
#define DOT_MESSAGE_TIMEZONEDATETIME_SOURCE_HPP

#include <string>

#include "dom/components/datasources/datetimesource.hpp"

namespace macsa
{
	namespace dot
	{
		namespace datetime
		{
			/**
			 * @brief Datasource DateTime TimeZone specifiers
			 *        Include:
			 *          - K -> Time zone (example: -7:00)
			 */
			class TimeZoneDateTimeSource : public DateTimeSource
			{
				public:
					explicit TimeZoneDateTimeSource(const std::string& format):
						DateTimeSource(format)
					{}
					virtual ~TimeZoneDateTimeSource() = default;

				public:
					/**
					 * @brief NOT IMPLEMENTED : Returns format specifier converted to value
					 */
					std::string GetData(Context* context) override
					{
						switch (_format.length())
						{
							case 1:     // K
							default:
								break;
						};
						return {};
					}
			};
		}
	}
}
#endif
