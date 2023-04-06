#ifndef DOT_MESSAGE_TIMEOFFSETDATETIME_SOURCE_HPP
#define DOT_MESSAGE_TIMEOFFSETDATETIME_SOURCE_HPP

#include <string>

#include "dom/components/datasources/datetimesource.hpp"

namespace macsa
{
	namespace dot
	{
		namespace datetime
		{
			/**
			 * @brief Datasource DateTime TimeOffset specifiers
			 * Include:
			 * - z -> Hours offset respect UTC(example: -7)
			 * - zz -> Hours offset as two digits respect UTC(example: -07)
			 * - zzz -> Time offset respect UTC(example: -07:00)
			 */
			class TimeOffsetDateTimeSource : public DateTimeSource
			{
				public:
					explicit TimeOffsetDateTimeSource(const std::string& format):
						DateTimeSource(format)
					{}
					virtual ~TimeOffsetDateTimeSource() = default;

				public:
					/**
					 * @brief Returns format specifier converted to value
					 */
					std::string GetData(const struct tm& time) override
					{
						switch (_format.length())
						{
							case 1:     // z
							case 2:     // zz
							case 3:     // zzz
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
