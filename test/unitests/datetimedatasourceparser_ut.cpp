#include <memory>
#include <time.h>
#include <gtest/gtest.h>

#include "utils/macsalogger.hpp"
#include "utils/stringutils.hpp"
#include "dom/rippers/context.hpp"
#include "dom/components/datasources/datetime/datetimesourcefactory.hpp"

using macsa::utils::MacsaLogger;
using macsa::utils::NLogLevel;
using namespace macsa::dot::datetime;
using namespace macsa::dot;

class DateTimeDataSourceParserUt : public ::testing::Test
{
	public:
		DateTimeDataSourceParserUt()
		{
			time_t rawTime = std::time(0);
			struct  tm timeInfo;
			localtime_r(&rawTime, &timeInfo);
			_context.time = timeInfo;

			// initialization code here
			MacsaLogger::SetCurrentLevel(NLogLevel::kNoLog);
		}

		~DateTimeDataSourceParserUt() {
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
		DateTimeSourceFactory _dateTimeFactoryParser;
		Context _context;
};

// Test day parse
TEST_F(DateTimeDataSourceParserUt, ParseDay_ReturnExpectedDay)
{
	const static std::string format = "dd";

	auto dataSources = _dateTimeFactoryParser.parseFormatRegex(format);
	EXPECT_EQ(dataSources.size(), 1);

	auto& dataSource = dataSources.front();
	auto&& result = dataSource->GetData(&_context);

	EXPECT_EQ(result, macsa::utils::stringutils::ToString(_context.time.tm_mday, 2));
}

// Test month parse
TEST_F(DateTimeDataSourceParserUt, ParseMonth_ReturnExpectedMonth)
{
	const static std::string format = "MM";

	auto dataSources = _dateTimeFactoryParser.parseFormatRegex(format);
	EXPECT_EQ(dataSources.size(), 1);

	auto& dataSource = dataSources.front();
	auto&& result = dataSource->GetData(&_context);

	EXPECT_EQ(result, macsa::utils::stringutils::ToString(_context.time.tm_mon + 1, 2));
}

// Test year parse
TEST_F(DateTimeDataSourceParserUt, ParseYear_ReturnExpectedYear)
{
	const static std::string format = "yyyy";

	auto dataSources = _dateTimeFactoryParser.parseFormatRegex(format);
	EXPECT_EQ(dataSources.size(), 1);

	auto& dataSource = dataSources.front();
	auto&& result = dataSource->GetData(&_context);

	EXPECT_EQ(result, macsa::utils::stringutils::ToString(_context.time.tm_year + 1900, 4));
}

// Test complete day
TEST_F(DateTimeDataSourceParserUt, ParseCompleteDate_ReturnExpectedCompleteDay)
{
	const static std::string format = "dd/MM/yyyy";

	auto dataSources = _dateTimeFactoryParser.parseFormatRegex(format);
	EXPECT_EQ(dataSources.size(), 5);

	std::stringstream ss;
	std::for_each(dataSources.cbegin(), dataSources.cend(), [&ss, this](const std::unique_ptr<DateTimeSource>& dataSource){
		ss << dataSource->GetData(&_context);
	});

	auto&& day = macsa::utils::stringutils::ToString(_context.time.tm_mday, 2);
	auto&& month = macsa::utils::stringutils::ToString(_context.time.tm_mon + 1, 2);
	auto&& year = macsa::utils::stringutils::ToString(_context.time.tm_year + 1900, 4);

	EXPECT_EQ(ss.str(), day+"/"+month+"/"+year);
}

// Test double quote string parse
TEST_F(DateTimeDataSourceParserUt, ParseDoubleQuoteString_ReturnExpectedString)
{
	const static std::string format = "\"macsa\"";

	auto dataSources = _dateTimeFactoryParser.parseFormatRegex(format);
	EXPECT_EQ(dataSources.size(), 1);

	auto& dataSource = dataSources.front();
	auto&& result = dataSource->GetData(&_context);

	EXPECT_EQ(result, "macsa");
}

// Test single quote string parse
TEST_F(DateTimeDataSourceParserUt, ParseSingleQuoteString_ReturnExpectedString)
{
	const static std::string format = "'macsa'";

	auto dataSources = _dateTimeFactoryParser.parseFormatRegex(format);
	EXPECT_EQ(dataSources.size(), 1);

	auto& dataSource = dataSources.front();
	auto&& result = dataSource->GetData(&_context);

	EXPECT_EQ(result, "macsa");
}

// Test back slash
TEST_F(DateTimeDataSourceParserUt, ParseBackSlash_ReturnExpectedString)
{
	const static std::string format = "\\d";

	auto dataSources = _dateTimeFactoryParser.parseFormatRegex(format);
	EXPECT_EQ(dataSources.size(), 1);

	auto& dataSource = dataSources.front();
	auto&& result = dataSource->GetData(&_context);

	EXPECT_EQ(result, "d");
}

// Test Hour
TEST_F(DateTimeDataSourceParserUt, ParseHour_ReturnExpectedHour)
{
	const static std::string format = "HH";

	auto dataSources = _dateTimeFactoryParser.parseFormatRegex(format);
	EXPECT_EQ(dataSources.size(), 1);

	auto& dataSource = dataSources.front();
	auto&& result = dataSource->GetData(&_context);

	EXPECT_EQ(result, macsa::utils::stringutils::ToString(_context.time.tm_hour, 2));
}

// Test Minute
TEST_F(DateTimeDataSourceParserUt, ParseMinute_ReturnExpectedMinute)
{
	const static std::string format = "mm";

	auto dataSources = _dateTimeFactoryParser.parseFormatRegex(format);
	EXPECT_EQ(dataSources.size(), 1);

	auto& dataSource = dataSources.front();
	auto&& result = dataSource->GetData(&_context);

	EXPECT_EQ(result, macsa::utils::stringutils::ToString(_context.time.tm_min, 2));
}

// Test Second
TEST_F(DateTimeDataSourceParserUt, ParseSecond_ReturnExpectedSecond)
{
	const static std::string format = "ss";

	auto dataSources = _dateTimeFactoryParser.parseFormatRegex(format);
	EXPECT_EQ(dataSources.size(), 1);

	auto& dataSource = dataSources.front();
	auto&& result = dataSource->GetData(&_context);

	EXPECT_EQ(result, macsa::utils::stringutils::ToString(_context.time.tm_sec, 2));
}

// Test composite string
TEST_F(DateTimeDataSourceParserUt, ParseCompositeFormat_ReturnExpectedString)
{
	const static std::string format = "\\j 'macsa' \"'macsa'\" dd.MM.yyyy # HH:mm:ss \"id\"";

	auto dataSources = _dateTimeFactoryParser.parseFormatRegex(format);
	EXPECT_EQ(dataSources.size(), 17);

	std::stringstream ss;
	std::for_each(dataSources.cbegin(), dataSources.cend(), [&ss, this](const std::unique_ptr<DateTimeSource>& dataSource){
		ss << dataSource->GetData(&_context);
	});

	auto&& day = macsa::utils::stringutils::ToString(_context.time.tm_mday, 2);
	auto&& month = macsa::utils::stringutils::ToString(_context.time.tm_mon + 1, 2);
	auto&& year = macsa::utils::stringutils::ToString(_context.time.tm_year + 1900, 4);

	auto&& hour = macsa::utils::stringutils::ToString(_context.time.tm_hour, 2);
	auto&& minute = macsa::utils::stringutils::ToString(_context.time.tm_min, 2);
	auto&& second = macsa::utils::stringutils::ToString(_context.time.tm_sec, 2);

	std::stringstream ssExpectedResult;
	ssExpectedResult << "j macsa 'macsa' ";
	ssExpectedResult << (day+"."+month+"."+year);
	ssExpectedResult << " # ";
	ssExpectedResult << (hour+":"+minute+":"+second);
	ssExpectedResult << " id";

	EXPECT_EQ(ss.str(), ssExpectedResult.str());
}

// Test composite string
TEST_F(DateTimeDataSourceParserUt, ParseComplexCompositeFormat_ReturnExpectedString)
{
	const static std::string format = "HH:mm:ss JJJ w_ww*hh:mm:sstt\" Hola \"d-dd 'Mundo \"disco\"'";

	auto dataSources = _dateTimeFactoryParser.parseFormatRegex(format);
	EXPECT_EQ(dataSources.size(), 24);

	std::stringstream ss;
	std::for_each(dataSources.cbegin(), dataSources.cend(), [&ss, this](const std::unique_ptr<DateTimeSource>& dataSource){
		ss << dataSource->GetData(&_context);
	});

	int hour = _context.time.tm_hour;
	if (hour > 12)	{
		hour -= 12;
	}
	else if (hour == 0)	{
		hour = 12;
	}

	auto&& hour12 = macsa::utils::stringutils::ToString(hour, 2);
	auto&& minute = macsa::utils::stringutils::ToString(_context.time.tm_min, 2);
	auto&& second = macsa::utils::stringutils::ToString(_context.time.tm_sec, 2);

	char julianDate[kBufferSize] = {0};
	strftime(julianDate, kBufferSize, "%j", &_context.time);

	char weekDate[kBufferSize] = {0};
	strftime(weekDate, kBufferSize, "%V", &_context.time);
	std::string singleDigitWeekDate = weekDate;
	if (singleDigitWeekDate.front() == '0')	{
		singleDigitWeekDate.erase(0,1);
	}

	char doubleWeekDate[kBufferSize] = {0};
	strftime(doubleWeekDate, kBufferSize, "%V", &_context.time);

	auto&& hour24 = macsa::utils::stringutils::ToString(_context.time.tm_hour, 2);
	auto period = _context.time.tm_hour < 12 ? "AM" : "PM";

	std::stringstream ssExpectedResult;
	ssExpectedResult << (hour24+":"+minute+":"+second);
	ssExpectedResult << " ";
	ssExpectedResult << julianDate;
	ssExpectedResult << " ";
	ssExpectedResult << singleDigitWeekDate;
	ssExpectedResult << "_";
	ssExpectedResult << doubleWeekDate;
	ssExpectedResult << "*";
	ssExpectedResult << (hour12+":"+minute+":"+second+period);
	ssExpectedResult << " Hola ";
	ssExpectedResult << macsa::utils::stringutils::ToString(_context.time.tm_mday);
	ssExpectedResult << "-";
	ssExpectedResult << macsa::utils::stringutils::ToString(_context.time.tm_mday, 2);
	ssExpectedResult << " Mundo \"disco\"";

	EXPECT_EQ(ss.str(), ssExpectedResult.str());
}
