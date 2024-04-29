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

	applyRounding(timeInfo, policy, roundingDay);

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

void OffsetTime::applyRounding(struct tm& calendar, const RoundingPolicy& policy, int roundingDay)
{
	//daysInMonth
	switch (_roundingPolicy()) {
		case NRoundingPolicy::kRoundFDM:
			calendar.tm_mday = 1;
			break;
		case NRoundingPolicy::kRoundLDM:
			calendar.tm_mday = daysInMonth(calendar);
			break;
		case NRoundingPolicy::kRoundDoM:
			if (roundingDay) {
				int maxDays = daysInMonth(calendar);
				if (roundingDay > maxDays) {
					roundingDay = maxDays;
				}
				calendar.tm_mday = roundingDay;
			}
			else {
				calendar.tm_mday = 1;
			}
			break;
		case NRoundingPolicy::kRoundDoW:
			{
				roundingDay %= 7;
				if (roundingDay == 0) {
					roundingDay = 7;
				}
				auto dow = calendar.tm_wday;
				dow = (dow == 0 ? 7 : dow);
				auto offset = roundingDay - dow;
				calendar.tm_mday += offset;
				mktime(&calendar);
			}
			break;
		case NRoundingPolicy::kNoRound:
		default:
			break;
	}
}

int OffsetTime::daysInMonth(int month, int year)
{
	month = month % 12;

	int days = kDaysInMonths[month];
	if (month == kFebrary && isLeepYear(year)) {
		days++;
	}
	return days;
}

int OffsetTime::daysInMonth(tm& calendar)
{
	return daysInMonth(calendar.tm_mon, calendar.tm_year);
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
