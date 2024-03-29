#ifndef DOT_MESSAGE_OFFSETTIME_HPP
#define DOT_MESSAGE_OFFSETTIME_HPP

#include <string>

constexpr int kMaxHourDay = 23;

namespace macsa
{
	namespace dot
	{
		/**
		* @brief The OffsetTime class
		*/
		class OffsetTime
		{
			public:
				OffsetTime();
				OffsetTime(int offsetDays, int offsetMonths, int offsetYears, int _hourDayStart);
				virtual ~OffsetTime() = default;

			public:
				struct tm GetTimeWithOffset();
				struct tm GetTimeWithOffset(time_t rawtime);

				int GetOffsetDays() const 	{
					return _offsetDays;
				}

				void SetOffsetDays(int offsetDays)
				{
					_offsetDays = offsetDays;
					_lastOffsetUpdate = -1;
				}

				int GetOffsetMonths() const
				{
					return _offsetMonths;
				}

				void SetOffsetMonths(int offsetMonths)
				{
					_offsetMonths = offsetMonths;
					_lastOffsetUpdate = -1;
				}

				int GetOffsetYears() const {
					return _offsetYears;
				}

				void SetOffsetYears(int offsetYears)
				{
					_offsetYears = offsetYears;
					_lastOffsetUpdate = -1;
				}

				int GetHourDaysStart() const {
					return _hourDayStart;
				}

				void SetHourDaysStart(int hourDayStart)
				{
					_hourDayStart = (hourDayStart > kMaxHourDay) ? (hourDayStart % kMaxHourDay) : hourDayStart;
					_lastOffsetUpdate = -1;
				}

				struct tm operator()()
				{
					return GetTimeWithOffset();
				}

			private:
				time_t _internalOffset;
				time_t _lastOffsetUpdate;
				int _offsetDays;
				int _offsetMonths;
				int _offsetYears;
				int _hourDayStart;

			private:
				/**
				 * @brief Calculate internal offset
				 */
				void internalOffset(time_t rawtime, int days, int months, int year, int hourDayStart);
				inline struct tm getLocalTime(const time_t* time) const;
		};
	}
}
#endif
