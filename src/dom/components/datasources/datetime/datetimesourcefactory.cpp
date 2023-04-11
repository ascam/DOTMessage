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
	std::regex formatQuotedStringRegex("[\",\'].*[\",\']");
	std::regex formatDCRegex("\\[DC:.*\\]");
	std::regex formatDateRegex("[d]{1,4}|[M]{1,4}|[y]{1,4}|[j]{1,3}|[w]{1,2}");
	std::regex formatTimeRegex("[h]{1,2}|[H]{1,2}|[m]{1,2}|[s]{1,2}|[t]{1,2}");
	std::regex formatTextRegex(".*");

	std::map<std::string, MatchResult> regexMatches;
	std::smatch resultQuotedStringRegex;
	std::smatch resultDCRegex;
	std::smatch resultDateRegex;
	std::smatch resultTimeRegex;
	std::smatch resultTextRegex;

	do
	{
		regexMatches.clear();

		if (std::regex_search(tempFormat, resultQuotedStringRegex, formatQuotedStringRegex, std::regex_constants::match_default))	{
			insertMatchResult(regexMatches, "QuotedString", resultQuotedStringRegex);
		}

		auto backSlashPos = tempFormat.find('\\');
		if (backSlashPos != std::string::npos)	{
			MatchResult mr;
			mr.format = tempFormat.substr(backSlashPos, 2);
			mr.position = backSlashPos;
			mr.suffix = tempFormat.substr(backSlashPos + 2);

			regexMatches.insert(std::make_pair<std::string, MatchResult>("Text", std::move(mr)));
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

		if (std::regex_search(tempFormat, resultTextRegex, formatTextRegex, std::regex_constants::match_default))	{

			if (resultTextRegex.position() == 0 && !regexMatches.empty())	{
				auto minIt = std::min_element(regexMatches.cbegin(), regexMatches.cend(), [&](const std::pair<std::string, MatchResult>& regexMath1, const std::pair<std::string, MatchResult>& regexMath2){
					return (regexMath1.second.position < regexMath2.second.position);
				});

				if (minIt->second.position != 0)	{ // em trobat un altre element amb zero position en el vector.
					MatchResult mr;
					mr.format = tempFormat.substr(0, minIt->second.position);
					mr.position = 0;
					mr.suffix = tempFormat.substr(minIt->second.position);

					regexMatches.insert(std::make_pair<std::string, MatchResult>("Text", std::move(mr)));
				}
			}
			else	{
				insertMatchResult(regexMatches, "Text", resultTextRegex);
			}
		}

		auto minIt = std::min_element(regexMatches.cbegin(), regexMatches.cend(), [&](const std::pair<std::string, MatchResult>& regexMath1, const std::pair<std::string, MatchResult>& regexMath2){
			return (regexMath1.second.position < regexMath2.second.position);
		});

		if (minIt != regexMatches.cend()) {
			tempFormat = minIt->second.suffix;

			pushDataSource(dateTimeSources, minIt->first, minIt->second.format);
		}
	}
	while(!regexMatches.empty() && !tempFormat.empty());

	return dateTimeSources;
}

void DateTimeSourceFactory::insertMatchResult(std::map<std::string, MatchResult>& regexMatches, const std::string& type, const std::smatch& match)
{
	MatchResult mr;
	mr.format = match.str();
	mr.position = match.position();
	mr.suffix = match.suffix();

	regexMatches.insert(std::make_pair<std::string, MatchResult>(type.c_str(), std::move(mr)));
}

void DateTimeSourceFactory::pushDataSource(std::vector<std::unique_ptr<DateTimeSource>>& dateTimeSources, const std::string& type, std::string format)
{
	if (type == "QuotedString" || type == "Text") {
		dateTimeSources.push_back(make_unique<FixedTextDateTimeSource>(format));
	}
	else if (type == "DC")	{
		dateTimeSources.push_back(make_unique<DateCodeDateTimeSource>(format));
	}
	else if (type == "Date" || type == "Time")	{
		dateTimeSources.push_back(getDateTimeSpecifiers(format));
	}
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
