#include "dom/components/datasources/offsettime.hpp"

#include <locale>

// Return true if 'y' is leep year
template<typename T> T isLeepYear(T y)
{return ((y %4) == 0) && (((y % 100) != 0) || ((y % 400) == 0));}

constexpr int kSecondsInADay = 86400;
constexpr int kFebrary = 1;
constexpr int kDaysInMonths[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

using namespace macsa::dot;

OffsetTime::OffsetTime():
	_internalOffset(0),
	_lastOffsetUpdate(-1),
	_offsetDays(0), _offsetMonths(0), _offsetYears(0),
	_hourDayStart(0),
	_roundingPolicy(),
	_roundingDay()
{}

OffsetTime::OffsetTime(int offsetDays, int offsetMonths,
					   int offsetYears, int hourDayStart,
					   const RoundingPolicy& policy, int roundingDay):
	_internalOffset(0),
	_lastOffsetUpdate(-1),
	_offsetDays(offsetDays), _offsetMonths(offsetMonths), _offsetYears(offsetYears),
	_hourDayStart(hourDayStart),
	_roundingPolicy(policy),
	_roundingDay(roundingDay)
{}

struct tm OffsetTime::GetTimeWithOffset()
{
	time_t rawTime = std::time(0);
	return GetTimeWithOffset(rawTime);
}

struct tm OffsetTime::GetTimeWithOffset(time_t rawTime)
{
	if (_lastOffsetUpdate < 0 || rawTime < _lastOffsetUpdate ||
		(rawTime - _lastOffsetUpdate) >= kSecondsInADay) {
		// Update offset.
		internalOffset(rawTime, _offsetDays, _offsetMonths, _offsetYears, _hourDayStart, _roundingPolicy, _roundingDay);
	}
	time_t offsetTime = rawTime + _internalOffset;
	return getLocalTime(&offsetTime);
}

void OffsetTime::internalOffset(time_t rawtime, int days,
								int months, int year, int hourDayStart,
								const RoundingPolicy& policy, int roundingDay)
{
	time_t offsetTime = rawtime;
	struct tm timeInfo {getLocalTime(&offsetTime)};
	timeInfo.tm_gmtoff = 0;
	timeInfo.tm_zone = "utc";
	setenv("TZ", "zulu", 1);

	if (year) {
		// Years offset
		timeInfo.tm_year += year;
	}
	// Months offset
	if (months) {
		timeInfo.tm_mon += months;
	}
	// Struct tm after year and month offset
	mktime(&timeInfo);

	timeInfo.tm_mday += days;

	// HourDayStart
	if (hourDayStart != 0 && timeInfo.tm_hour >= hourDayStart) {
		timeInfo.tm_mday += 1;
	}

	// Struct tm after days offset
	mktime(&timeInfo);


	_internalOffset = std::mktime(&timeInfo) - rawtime;

	// Set last offset update time
	struct tm updateOffset {getLocalTime(&rawtime)};

	updateOffset.tm_hour = hourDayStart;
	_lastOffsetUpdate = mktime(&updateOffset);
	if (rawtime < _lastOffsetUpdate) {
		_lastOffsetUpdate -= kSecondsInADay;
	}
	unsetenv("TZ");
}

inline struct tm OffsetTime::getLocalTime(const time_t* time) const
{
	struct tm calendar{};
#if _WINDOWS
	localtime_s(&calendar, time);
#else
	localtime_r(time, &calendar);
#endif
	return calendar;
}
