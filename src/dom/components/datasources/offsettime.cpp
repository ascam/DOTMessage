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
	_hourDayStart(0)
{}

OffsetTime::OffsetTime(int offsetDays, int offsetMonths,
					   int offsetYears, int hourDayStart):
	_internalOffset(0),
	_lastOffsetUpdate(-1),
	_offsetDays(offsetDays), _offsetMonths(offsetMonths), _offsetYears(offsetYears),
	_hourDayStart(hourDayStart)
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
		internalOffset(rawTime, _offsetDays, _offsetMonths, _offsetYears, _hourDayStart);
	}
	time_t offsetTime = rawTime + _internalOffset;
	struct  tm timeInfo;
	localtime_s(&timeInfo, &offsetTime);
	return timeInfo;
}

void OffsetTime::internalOffset(time_t rawtime, int days,
								int months, int year, int hourDayStart)
{
	time_t offsetTime = rawtime;
	struct tm timeInfo;
	localtime_s(&timeInfo, &offsetTime);

	// HourDayStart
	if (hourDayStart != 0 && timeInfo.tm_hour >= hourDayStart) {
		offsetTime -= kSecondsInADay;
	}

	// Days offset
	offsetTime += days * kSecondsInADay;

	// Struct tm after days offset
	localtime_s(&timeInfo, &offsetTime);

	// Years offset
	timeInfo.tm_year += year;

	// Months offset
	if (months) {
		int monthsCount = months + timeInfo.tm_mon;
		timeInfo.tm_year += (monthsCount / 12);
		timeInfo.tm_mon = monthsCount % 12;
		if (timeInfo.tm_mon < 0) {
			timeInfo.tm_year -= 1;
			timeInfo.tm_mon += 12;
		}
		// Correct max day of the month
		if (timeInfo.tm_mday > kDaysInMonths[timeInfo.tm_mon]) {
			// Leep-year
			if (timeInfo.tm_mon == kFebrary && isLeepYear(timeInfo.tm_year)) {
				timeInfo.tm_mday = kDaysInMonths[timeInfo.tm_mon] + 1;
			}
			else {
				timeInfo.tm_mday = kDaysInMonths[timeInfo.tm_mon];
			}
		}
	}
	_internalOffset = std::mktime(&timeInfo) - rawtime;

	// Set last offset update time
	struct tm updateOffset;
	localtime_s(&updateOffset, &rawtime);

	updateOffset.tm_hour = hourDayStart;
	_lastOffsetUpdate = mktime(&updateOffset);
	if (rawtime < _lastOffsetUpdate) {
		_lastOffsetUpdate -= kSecondsInADay;
	}
}
