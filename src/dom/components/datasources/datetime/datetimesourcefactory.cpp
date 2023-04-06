#include "datetimesourcefactory.hpp"

#include <string>
#include <vector>
#include <utility>
#include <memory>
#include <regex>
#include <iostream>

#include "dom/components/datasources/datetime/datecodedatetimesource.hpp"
#include "seconddatetimesource.hpp"
#include "daydatetimesource.hpp"
#include "yeardatetimesource.hpp"
#include "hourdatetimesource.hpp"
#include "minutedatetimesource.hpp"
#include "monthdatetimesource.hpp"
#include "juliandatetimesource.hpp"
#include "perioddatetimesource.hpp"
#include "weekdatetimesource.hpp"
#include "fixedtextdatetimesource.hpp"
//#include "datecodedatetimesource.hpp"
#include "datetimeformats.h"
// Non implemented DateTimeSource
// #include "eradatetimesource.hpp"
// #include "timezonedatetimesource.hpp"
// #include "timeoffsetdatetimesource.hpp"
// #include "secondmultiplesdatetimesource.hpp"

#include "utils/make_unique.hpp"


using namespace macsa::utils;
using namespace macsa::dot::datetime;

std::vector<std::unique_ptr<DateTimeSource>> DateTimeSourceFactory::parseFormatRegex(const std::string& format)
{
	std::vector<std::unique_ptr<DateTimeSource>> dateTimeSources;

	std::string tempFormat = format;
	std::regex formatStringAndCharRegex("[\",\'][a-z,0-9]*[\",\']");
	std::regex formatDCRegex("\\[DC:[a-z,A-Z].*\\]");
	std::regex formatDateRegex("[dMy]{1,4}|[j]{1,3}|[w]{1,2}");
	std::regex formatTimeRegex("[hHmst]{1,2}");
	std::regex formatSeparatorRegex("[:%/]{1,1}");

	std::map<std::string, MatchResult> regexMatches;
	std::smatch resultStringAndCharRegex;
	std::smatch resultDCRegex;
	std::smatch resultDateRegex;
	std::smatch resultTimeRegex;
	std::smatch resultSeparatorRegex;

	do
	{
		regexMatches.clear();

		if (std::regex_search(tempFormat, resultStringAndCharRegex, formatStringAndCharRegex, std::regex_constants::match_default))	{
			insertMatchResult(regexMatches, "StringAndChar", resultStringAndCharRegex);
		}

		if (std::regex_search(tempFormat, resultDCRegex, formatDCRegex, std::regex_constants::match_default))	{
			insertMatchResult(regexMatches, "DC", resultDCRegex);
		}

		if (std::regex_search(tempFormat, resultDateRegex, formatDateRegex, std::regex_constants::match_default))	{
			insertMatchResult(regexMatches, "Date", resultDateRegex);
		}

		if (std::regex_search(tempFormat, resultTimeRegex, formatTimeRegex, std::regex_constants::match_default))	{
			insertMatchResult(regexMatches, "Time", resultTimeRegex);
		}

		if (std::regex_search(tempFormat, resultSeparatorRegex, formatSeparatorRegex, std::regex_constants::match_default))	{
			insertMatchResult(regexMatches, "Separator", resultSeparatorRegex);
		}

		auto minIt = std::min_element(regexMatches.cbegin(), regexMatches.cend(), [&](const std::pair<std::string, MatchResult>& regexMath1, const std::pair<std::string, MatchResult>& regexMath2){
			return (regexMath1.second.position < regexMath2.second.position);
		});

		if (minIt != regexMatches.cend()) {
			tempFormat = minIt->second.suffix;

			pushDataSource(dateTimeSources, minIt->first, minIt->second.format);
		}
	}
	while(!regexMatches.empty());

	return dateTimeSources;
}

void DateTimeSourceFactory::insertMatchResult(std::map<std::string, MatchResult>& regexMatches, const std::string& type, const std::smatch& match)
{
	MatchResult mr;
	mr.format = match.str();
	mr.position = match.position();
	mr.suffix = match.suffix();

	auto pair = std::make_pair<std::string, MatchResult>(type.c_str(), std::move(mr));
	regexMatches.insert(pair);
}

void DateTimeSourceFactory::pushDataSource(std::vector<std::unique_ptr<DateTimeSource>>& dateTimeSources, const std::string& type, std::string format)
{
	std::cout << type << " : " << format << std::endl;

	if (type == "StringAndChar" || type == "Separator") {
		dateTimeSources.push_back(make_unique<FixedTextDateTimeSource>(format));
	}
	else if (type == "DC")	{
		dateTimeSources.push_back(make_unique<DateCodeDateTimeSource>(format));
	}
	else if (type == "Date" || type == "Time")	{
		dateTimeSources.push_back(getDateTimeSpecifiers(format));
	}
}

std::vector<std::unique_ptr<DateTimeSource>> DateTimeSourceFactory::parseFormat(const std::string& format)
{
	std::vector<std::unique_ptr<DateTimeSource>> dateTimeSources;

	for (auto formatIndex = 0u; formatIndex < format.length();) {
		const char c = format.at(formatIndex);
		// String
		if (c == *kFormatString || c == *kFormatCharString) { // \" or \'
			auto endPos = format.find(c, formatIndex + 1);
			if (endPos == std::string::npos) {
				++formatIndex;
				// next char we go back to for!
				// continue!
			}
			else {
				//int strLen = endPos - (formatIndex + 1);
				//dateTimeSources.push_back(make_unique<FixedTextDateTimeSource>(std::string(1, c), format.substr(formatIndex + 1, strLen)));
				formatIndex = endPos + 1;
			}
		}
		// Escape char
		else if (c == *kFormatEscapeChar) {
			if (formatIndex + 1  < format.length()) {
				//dateTimeSources.push_back(make_unique<FixedTextDateTimeSource>(std::string(1, c), format.substr(formatIndex + 1, 1)));
			}
			formatIndex += 2;
		}
		// DateCodes
		else if (format.find("[DC:", formatIndex) == formatIndex) {
			size_t closeBrackedPos = format.find_first_of(']', formatIndex);
			if (closeBrackedPos == std::string::npos) {
				break;
			}
			std::string strFormat = format.substr(formatIndex, closeBrackedPos - formatIndex + 1);
			dateTimeSources.push_back(make_unique<DateCodeDateTimeSource>(strFormat));
			formatIndex += strFormat.length();
		}
		// Date Time specifiers
		else {
			std::unique_ptr<DateTimeSource> dateTimeSource = nullptr;
			if (dateTimeSource != nullptr) {
				dateTimeSources.push_back(std::move(dateTimeSource));
			}

			++formatIndex;
		}
	}

	return dateTimeSources;
}

int DateTimeSourceFactory::containsFormat(const std::string& source, const std::string& format, int pos)
{
	if (source.find(format, pos) == static_cast<size_t>(pos)) {
		return format.size();
	}

	return 0;
}

// Returns current specifier update frequency and allocates the corresponding DateTimeSource
// derived class to the input parameter format. Returns NONE when no match.
std::unique_ptr<DateTimeSource> DateTimeSourceFactory::getDateTimeSpecifiers(const std::string& format)
{
	auto pos = 0u;
	int length = 0;
	const char next = format.at(pos);

	std::unique_ptr<DateTimeSource> returnValue;

	if (next == *kFormatBracketsdddd) {
		// day
		if ((length = containsFormat(format, kFormatBracketsdddd, pos))) {
			pos += length;
			returnValue = make_unique<DayDateTimeSource>(kFormatdddd, true);
		}
		else if ((length = containsFormat(format, kFormatBracketsddd, pos))) {
			pos += length;
			returnValue = make_unique<DayDateTimeSource>(kFormatddd, true);
		}

		// month
		if ((length = containsFormat(format, kFormatBracketsMMMM, pos))) {
			pos += length;
			returnValue = make_unique<MonthDateTimeSource>(kFormatMMMM, true);
		}
		else if ((length = containsFormat(format, kFormatBracketsMMM, pos))) {
			pos += length;
			returnValue = make_unique<MonthDateTimeSource>(kFormatMMM, true);
		}

		// julian date -> deprecated
		if ((length = containsFormat(format, kFormatBracketsJJJ, pos))) {
			pos += length;
			returnValue = make_unique<JulianDateTimeSource>(kFormatJJJ);
		}
		else if ((length = containsFormat(format, kFormatBracketsJ, pos))) {
			pos += length;
			returnValue = make_unique<JulianDateTimeSource>(kFormatJ);
		}
	}

	// day
	if (next == *kFormatdddd) {
		if ((length = containsFormat(format, kFormatdddd, pos))) {
			pos += length;
			returnValue = make_unique<DayDateTimeSource>(kFormatdddd);
		}
		else if ((length = containsFormat(format, kFormatddd, pos))) {
			pos += length;
			returnValue = make_unique<DayDateTimeSource>(kFormatddd);
		}
		else if ((length = containsFormat(format, kFormatdd, pos))) {
			pos += length;
			returnValue = make_unique<DayDateTimeSource>(kFormatdd);
		}
		else if ((length = containsFormat(format, kFormatd, pos))) {
			pos += length;
			returnValue = make_unique<DayDateTimeSource>(kFormatd);
		}
	}
	// year
	else if (next == *kFormatyyyy) {
		if ((length = containsFormat(format, kFormatyyyy, pos))) {
			pos += length;
			returnValue = make_unique<YearDateTimeSource>(kFormatyyyy);
		}
		else if ((length = containsFormat(format, kFormatyyy, pos))) {
			pos += length;
			returnValue = make_unique<YearDateTimeSource>(kFormatyyy);
		}
		else if ((length = containsFormat(format, kFormatyy, pos))) {
			pos += length;
			returnValue = make_unique<YearDateTimeSource>(kFormatyy);
		}
		else if ((length = containsFormat(format, kFormaty, pos))) {
			pos += length;
			returnValue = make_unique<YearDateTimeSource>(kFormaty);
		}
	}
	// hour
	else if (next == *kFormathh || next == *kFormatHH) {
		if ((length = containsFormat(format, kFormathh, pos))) {
			pos += length;
			returnValue = make_unique<HourDateTimeSource>(kFormathh);
		}
		else if ((length = containsFormat(format, kFormath, pos))) {
			pos += length;
			returnValue = make_unique<HourDateTimeSource>(kFormath);
		}
		else if ((length = containsFormat(format, kFormatHH, pos))) {
			pos += length;
			returnValue = make_unique<HourDateTimeSource>(kFormatHH);
		}
		else if ((length = containsFormat(format, kFormatH, pos))) {
			pos += length;
			returnValue = make_unique<HourDateTimeSource>(kFormatH);
		}
	}
	// minute
	else if (next == *kFormatmm) {
		if ((length = containsFormat(format, kFormatmm, pos))) {
			pos += length;
			returnValue = make_unique<MinuteDateTimeSource>(kFormatmm);
		}
		else if ((length = containsFormat(format, kFormatm, pos))) {
			pos += length;
			returnValue = make_unique<MinuteDateTimeSource>(kFormatm);
		}
	}
	// month
	else if (next == *kFormatMMMM) {
		if ((length = containsFormat(format, kFormatMMMM, pos))) {
			pos += length;
			returnValue = make_unique<MonthDateTimeSource>(kFormatMMMM);
		}
		else if ((length = containsFormat(format, kFormatMMM, pos))) {
			pos += length;
			returnValue = make_unique<MonthDateTimeSource>(kFormatMMM);
		}
		else if ((length = containsFormat(format, kFormatMM, pos))) {
			pos += length;
			returnValue = make_unique<MonthDateTimeSource>(kFormatMM);
		}
		else if ((length = containsFormat(format, kFormatM, pos))) {
			pos += length;
			returnValue = make_unique<MonthDateTimeSource>(kFormatM);
		}
	}
	// julian date
	else if (next == *kFormatJJJ) {
		if ((length = containsFormat(format, kFormatJJJ, pos))) {
			pos += length;
			returnValue = make_unique<JulianDateTimeSource>(kFormatJJJ);
		}
		else if ((length = containsFormat(format, kFormatJ, pos))) {
			pos += length;
			returnValue = make_unique<JulianDateTimeSource>(kFormatJ);
		}
	}
	// second
	else if (next == *kFormatss) {
		if ((length = containsFormat(format, kFormatss, pos))) {
			pos += length;
			returnValue = make_unique<SecondDateTimeSource>(kFormatss);
		}
		else if ((length = containsFormat(format, kFormats, pos))) {
			pos += length;
			returnValue = make_unique<SecondDateTimeSource>(kFormats);
		}
	}
	// period
	else if (next == *kFormattt) {
		if ((length = containsFormat(format, kFormattt, pos))) {
			pos += length;
			returnValue = make_unique<PeriodDateTimeSource>(kFormattt);
		}
		else if ((length = containsFormat(format, kFormatt, pos))) {
			pos += length;
			returnValue = make_unique<PeriodDateTimeSource>(kFormatt);
		}
	}
	// week
	else if (next == *kFormatww) {
		if ((length = containsFormat(format, kFormatww, pos))) {
			pos += length;
			returnValue = make_unique<WeekDateTimeSource>(kFormatww);
		}
		else if ((length = containsFormat(format, kFormatw, pos))) {
			pos += length;
			returnValue = make_unique<WeekDateTimeSource>(kFormatw);
		}
	}

	return returnValue;
}
