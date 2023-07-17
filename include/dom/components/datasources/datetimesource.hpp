#ifndef DOT_MESSAGE_DATETIMESOURCE_HPP
#define DOT_MESSAGE_DATETIMESOURCE_HPP

#include <string>

#include "dom/rippers/context.hpp"
#include "dom/refreshpolicy.hpp"

constexpr int kBufferSize = 256;

namespace macsa
{
	namespace dot
	{
		namespace datetime
		{
			/**
			 * @brief Interface class to parse DateTime specifiers
			 *  Child classes:
			 *  DateCodeDateTimeSource
			 *  DayDateTimeSource
			 *  EraDateTimeSource -> Not implemented
			 *  FixedTextDateTimeSource
			 *  HourDateTimeSource
			 *  JulinaDateTimeSource
			 *  MinuteDateTimeSource
			 *  MonthDateTimeSource
			 *  PeriodDateTimeSource
			 *  SecondDateTimeSource
			 *  SecondMultiplesDateTimeSource -> Not implemented
			 *  TimeOffsetDateTimeSource -> Not implemented
			 *  TimeZoneDateTimeSource -> Not implemented
			 *  WeekDateTimeSource
			 *  YearDateTimeSource
			 */
			class DateTimeSource
			{
				public:
					explicit DateTimeSource(const std::string& format):
						_format(format)
					{}
					virtual ~DateTimeSource() = default;

				public:
					/**
					 * @brief GetData Returns format specifier converted to value
					 * @param time
					 * @return
					 */
					virtual std::string GetData(Context* context) = 0;
					virtual std::string GetFormat() {return _format;}

					/**
					 * @brief GetRefreshPolicy Returns Refresh Policy (by kCounter,  kSeconds, kMinutes,...)
					 * @return 'enum class RefreshPolicy'
					 */
					virtual RefreshPolicy GetRefreshPolicy() = 0;

				protected:
					std::string _format;
			};
		}
	}
}
#endif
