#include "dom/components/datasources/offsettime.hpp"
#include "utils/macsalogger.hpp"
#include <gtest/gtest.h>

using macsa::dot::OffsetTime;
using macsa::dot::NRoundingPolicy;
using macsa::utils::MacsaLogger;
using macsa::utils::NLogLevel;

const int daysInMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

class OffsetTimeUt : public ::testing::Test
{
	public:
		OffsetTimeUt()
		{
			// initialization code here
			MacsaLogger::SetCurrentLevel(NLogLevel::kNoLog);
		}

		~OffsetTimeUt() {
			// cleanup any pending stuff, but no exceptions allowed
		}

		void SetUp( ) {
			// code here will execute just before the test ensues
		}

		void TearDown( ) {
			// code here will be called just after the test completes
			// ok to through exceptions from here if need be
		}

	protected:
		OffsetTime _offsetTime;

		std::pair<time_t,struct tm> getCalendar(int year, int month, int day, int hour, int minutes, int seconds) const {
			struct tm calendar{};
			calendar.tm_year = year - 1900;
			calendar.tm_mon = month - 1;
			calendar.tm_mday = day;
			calendar.tm_hour = hour;
			calendar.tm_min = minutes;
			calendar.tm_sec = seconds;
			calendar.tm_gmtoff = 0;
			calendar.tm_zone = "UTC";

			setenv("TZ", "UTC",1);
			auto time = mktime(&calendar);
			unsetenv("TZ");

			return {time, calendar};
		}

		std::string toString(const struct tm& calendar) const {
			std::stringstream str;
			str << calendar.tm_mday << "/";
			str << calendar.tm_mon + 1 << "/";
			str << calendar.tm_year + 1900 << " ";
			str << calendar.tm_hour << ":";
			str << calendar.tm_min  << ":";
			str << calendar.tm_sec;
			return str.str();
		}

		inline struct tm getLocalTime(const time_t* time) const
		{
			struct tm calendar{};
		#if _WINDOWS
			localtime_s(&calendar, time);
		#else
			localtime_r(time, &calendar);
		#endif
			return calendar;
		}

		bool equal(const struct tm& a, const struct tm& b){
			return a.tm_year == b.tm_year &&
					a.tm_mon == b.tm_mon &&
					a.tm_mday == b.tm_mday &&
					a.tm_hour == b.tm_hour &&
					a.tm_min == b.tm_min &&
					a.tm_sec == b.tm_sec;
		}


};

// Test Offsets
TEST_F(OffsetTimeUt, OffsetTimeConstructor_returnExpectedCalendar)
{
	auto [time, calendar] = getCalendar(2020, 3, 12, 10, 45, 24);
	auto offsetCal = _offsetTime.GetTimeWithOffset(time);
	EXPECT_TRUE(equal(offsetCal, calendar));
}

// Test Offsets
TEST_F(OffsetTimeUt, PositiveOffsetYear_returnExpectedYear)
{
	int yearsOffset = 4;
	auto [time, calendar] = getCalendar(2020, 3, 12, 10, 45, 24);
	_offsetTime.SetOffsetYears(yearsOffset);
	auto offsetCal = _offsetTime.GetTimeWithOffset(time);
	EXPECT_EQ(offsetCal.tm_year, (calendar.tm_year + yearsOffset));
}

// Test Offsets
TEST_F(OffsetTimeUt, NegativeOffsetYear_returnExpectedYear)
{
	int yearsOffset = -4;
	auto [time, calendar] = getCalendar(2020, 3, 12, 10, 45, 24);
	_offsetTime.SetOffsetYears(yearsOffset);
	auto offsetCal = _offsetTime.GetTimeWithOffset(time);
	EXPECT_EQ(offsetCal.tm_year, (calendar.tm_year + yearsOffset));
}

// Test Offsets
TEST_F(OffsetTimeUt, PositiveOffsetMonthWithoutChangeYear_returnExpectedMonthAndYear)
{
	int monthOffset = 4;
	auto [time, calendar] = getCalendar(2020, 3, 12, 10, 45, 24);
	_offsetTime.SetOffsetMonths(monthOffset);
	auto offsetCal = _offsetTime.GetTimeWithOffset(time);
	EXPECT_EQ(offsetCal.tm_year, calendar.tm_year);
	EXPECT_EQ(offsetCal.tm_mon, (calendar.tm_mon + monthOffset));
}

// Test Offsets
TEST_F(OffsetTimeUt, PositiveOffsetMonthWithChangingYear_returnExpectedMonthAndYear)
{
	int monthOffset = 10;
	auto [time, calendar] = getCalendar(2020, 3, 12, 10, 45, 24);
	_offsetTime.SetOffsetMonths(monthOffset);
	auto offsetCal = _offsetTime.GetTimeWithOffset(time);
	EXPECT_EQ(offsetCal.tm_year, calendar.tm_year + (calendar.tm_mon + monthOffset) / 12);
	EXPECT_EQ(offsetCal.tm_mon, (calendar.tm_mon + monthOffset) % 12);
}

// Test Offsets
TEST_F(OffsetTimeUt, NegativeOffsetMonthWithoutChangeYear_returnExpectedMonthAndYear)
{
	int monthOffset = -2;
	auto [time, calendar] = getCalendar(2020, 3, 12, 10, 45, 24);
	_offsetTime.SetOffsetMonths(monthOffset);
	auto offsetCal = _offsetTime.GetTimeWithOffset(time);
	EXPECT_EQ(offsetCal.tm_year, calendar.tm_year);
	EXPECT_EQ(offsetCal.tm_mon, (calendar.tm_mon + monthOffset));
}

// Test Offsets
TEST_F(OffsetTimeUt, NegativeOffsetMonthWithChangingYear_returnExpectedMonthAndYear)
{
	int monthOffset = -18;
	auto [time, calendar] = getCalendar(2020, 3, 12, 10, 45, 24);
	_offsetTime.SetOffsetMonths(monthOffset);
	auto offsetCal = _offsetTime.GetTimeWithOffset(time);

	int expectedMonth = calendar.tm_mon + monthOffset;
	int expectedYear = calendar.tm_year;
	if (expectedMonth >= 12) {
		expectedYear += expectedMonth / 12;
		expectedMonth %= 12;
	}

	while (expectedMonth < 0) {
		expectedMonth += 12;
		expectedYear -= 1;
	}

	EXPECT_EQ(offsetCal.tm_year, expectedYear);
	EXPECT_EQ(offsetCal.tm_mon, expectedMonth);
}

// Test Offsets
TEST_F(OffsetTimeUt, PositiveDaysOffset_returnExpectedDayAndMonth)
{
	int offsetDays = 10;
	int offsetMonths = 1;
	auto [time, calendar] = getCalendar(2023, 3, 12, 10, 45, 24);
	_offsetTime.SetOffsetDays(offsetDays);
	_offsetTime.SetOffsetMonths(offsetMonths);
	auto offsetCal = _offsetTime.GetTimeWithOffset(time);

	int expectedMonth = calendar.tm_mon + offsetMonths;
	int expectedDay = calendar.tm_mday + offsetDays;

	EXPECT_EQ(offsetCal.tm_mon, expectedMonth);
	EXPECT_EQ(offsetCal.tm_mday, expectedDay);
}

// Test Offsets
TEST_F(OffsetTimeUt, NegativeDaysOffset_returnExpectedDayAndMonth)
{
	int offsetDays = -12;
	int offsetMonths = 4;
	auto [time, calendar] = getCalendar(2023, 3, 12, 10, 45, 24);
	_offsetTime.SetOffsetDays(offsetDays);
	_offsetTime.SetOffsetMonths(offsetMonths);
	auto offsetCal = _offsetTime.GetTimeWithOffset(time);

	int expectedMonth = calendar.tm_mon + offsetMonths - 1;
	int expectedDay = daysInMonth[expectedMonth];
	EXPECT_EQ(offsetCal.tm_mon, expectedMonth);
	EXPECT_EQ(offsetCal.tm_mday, expectedDay);
}

// Test Offsets
TEST_F(OffsetTimeUt, RoundToMonthFirst_returnExpectedDayAndMonth)
{
	int offsetMonths = 4;
	auto [time, calendar] = getCalendar(2023, 3, 12, 10, 45, 24);
	_offsetTime.SetRoundingPolicy(NRoundingPolicy::kRoundFDM);
	_offsetTime.SetOffsetMonths(offsetMonths);
	auto offsetCal = _offsetTime.GetTimeWithOffset(time);

	int expectedMonth = calendar.tm_mon + offsetMonths;
	int expectedDay = 1;
	EXPECT_EQ(offsetCal.tm_mon, expectedMonth);
	EXPECT_EQ(offsetCal.tm_mday, expectedDay);
}

// Test Offsets
TEST_F(OffsetTimeUt, RoundToMonthLast_returnExpectedDayAndMonth)
{
	int offsetMonths = 5;
	auto [time, calendar] = getCalendar(2023, 3, 12, 10, 45, 24);
	_offsetTime.SetRoundingPolicy(NRoundingPolicy::kRoundLDM);
	_offsetTime.SetOffsetMonths(offsetMonths);
	auto offsetCal = _offsetTime.GetTimeWithOffset(time);

	int expectedMonth = calendar.tm_mon + offsetMonths;
	int expectedDay = daysInMonth[expectedMonth];
	EXPECT_EQ(offsetCal.tm_mon, expectedMonth);
	EXPECT_EQ(offsetCal.tm_mday, expectedDay);
}

// Test Offsets
TEST_F(OffsetTimeUt, RoundToValidDayOfTheMonth_returnExpectedDayAndMonth)
{
	int offsetMonths = 5;
	int roundingDay = 20;
	auto [time, calendar] = getCalendar(2023, 3, 12, 10, 45, 24);
	_offsetTime.SetRoundingPolicy(NRoundingPolicy::kRoundDoM);
	_offsetTime.SetOffsetMonths(offsetMonths);
	_offsetTime.SetRoundingDay(roundingDay);
	auto offsetCal = _offsetTime.GetTimeWithOffset(time);

	int expectedMonth = calendar.tm_mon + offsetMonths;
	int expectedDay = roundingDay;
	EXPECT_EQ(offsetCal.tm_mon, expectedMonth);
	EXPECT_EQ(offsetCal.tm_mday, expectedDay);
}

// Test Offsets
TEST_F(OffsetTimeUt, RoundToInvalidDayOfTheMonth_returnExpectedLastDayOfTheMonth)
{
	int offsetMonths = -1;
	int roundingDay = 31;
	auto [time, calendar] = getCalendar(2023, 3, 12, 10, 45, 24);
	_offsetTime.SetRoundingPolicy(NRoundingPolicy::kRoundDoM);
	_offsetTime.SetOffsetMonths(offsetMonths);
	_offsetTime.SetRoundingDay(roundingDay);
	auto offsetCal = _offsetTime.GetTimeWithOffset(time);

	int expectedMonth = calendar.tm_mon + offsetMonths;
	int expectedDay = daysInMonth[expectedMonth];
	EXPECT_EQ(offsetCal.tm_mon, expectedMonth);
	EXPECT_EQ(offsetCal.tm_mday, expectedDay);
}

// Test Offsets
TEST_F(OffsetTimeUt, RoundToDayOfTheWeek_returnExpectedDayOfTheWeek)
{
	int offsetMonths = -1;
	int roundingWeekDay = 5;// Friday
	auto [time, calendar] = getCalendar(2023, 3, 12, 10, 45, 24);
	_offsetTime.SetRoundingPolicy(NRoundingPolicy::kRoundDoW);
	_offsetTime.SetOffsetMonths(offsetMonths);
	_offsetTime.SetRoundingDay(roundingWeekDay);
	auto offsetCal = _offsetTime.GetTimeWithOffset(time);

	int expectedMonth = calendar.tm_mon + offsetMonths;

	EXPECT_NE(calendar.tm_wday, roundingWeekDay);

	EXPECT_EQ(offsetCal.tm_mon, expectedMonth);
	EXPECT_EQ(offsetCal.tm_wday, roundingWeekDay);
}
