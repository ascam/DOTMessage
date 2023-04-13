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
#include "datecodedatetimesource.hpp"
#include "datetimeformats.h"
#include "utils/macsalogger.hpp"

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
	std::regex formatBackSlashRegex("\\\\.{1,1}");
	std::regex formatDateRegex("[d]{1,4}|[M]{1,4}|[y]{1,4}|[J]{1,3}|[w]{1,2}");
	std::regex formatTimeRegex("[h]{1,2}|[H]{1,2}|[m]{1,2}|[s]{1,2}|[t]{1,2}");
	std::regex formatTextRegex(".*");

	std::map<std::string, MatchResult> regexMatches;
	std::smatch matchResult;

	do
	{
		regexMatches.clear();

		if (std::regex_search(tempFormat, matchResult, formatQuotedStringRegex, std::regex_constants::match_default))	{
			insertMatchResult(regexMatches, "QuotedString", matchResult);
		}

		if (std::regex_search(tempFormat, matchResult, formatBackSlashRegex, std::regex_constants::match_default))	{
			insertMatchResult(regexMatches, "Text", matchResult);
		}

		if (std::regex_search(tempFormat, matchResult, formatDCRegex, std::regex_constants::match_default))	{
			insertMatchResult(regexMatches, "DC", matchResult);
		}

		if (std::regex_search(tempFormat, matchResult, formatDateRegex, std::regex_constants::match_default))	{
			insertMatchResult(regexMatches, "Date", matchResult);
		}

		if (std::regex_search(tempFormat, matchResult, formatTimeRegex, std::regex_constants::match_default))	{
			insertMatchResult(regexMatches, "Time", matchResult);
		}

		if (std::regex_search(tempFormat, matchResult, formatTextRegex, std::regex_constants::match_default))	{

			if (matchResult.position() == 0 && !regexMatches.empty())	{
				auto minIt = std::min_element(regexMatches.cbegin(), regexMatches.cend(), [&](const std::pair<std::string, MatchResult>& regexMath1, const std::pair<std::string, MatchResult>& regexMath2){
					return (regexMath1.second.position < regexMath2.second.position);
				});

				if (minIt->second.position != 0) {
					MatchResult mr;
					mr.format = tempFormat.substr(0, minIt->second.position);
					mr.position = 0;
					mr.suffix = tempFormat.substr(minIt->second.position);

					regexMatches.insert(std::make_pair<std::string, MatchResult>("Text", std::move(mr)));
				}
			}
			else {
				insertMatchResult(regexMatches, "Text", matchResult);
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

std::unique_ptr<DateTimeSource> DateTimeSourceFactory::getDateTimeSpecifiers(const std::string& format)
{
	std::unique_ptr<DateTimeSource> returnValue;

	if (format == kFormatdddd || format == kFormatddd || format == kFormatdd || format == kFormatd) {
		returnValue = make_unique<DayDateTimeSource>(format);
	}
	else if (format == kFormatyyyy || format == kFormatyyy || format == kFormatyy || format == kFormaty) {
		returnValue = make_unique<YearDateTimeSource>(format);
	}
	else if (format == kFormatHH || format == kFormathh || format == kFormatH || format == kFormath) {
		returnValue = make_unique<HourDateTimeSource>(format);
	}
	else if (format == kFormatm || format == kFormatmm) {
		returnValue = make_unique<MinuteDateTimeSource>(format);
	}
	else if (format == kFormatMMMM || format == kFormatMMM || format == kFormatMM || format == kFormatM) {
		returnValue = make_unique<MonthDateTimeSource>(format);
	}
	else if (format == kFormatJJJ || format == kFormatJ) {
		returnValue = make_unique<JulianDateTimeSource>(format);
	}
	else if (format == kFormats || format == kFormatss) {
		returnValue = make_unique<SecondDateTimeSource>(format);
	}
	else if (format == kFormattt || format == kFormatt) {
		returnValue = make_unique<PeriodDateTimeSource>(format);
	}
	else if (format == kFormatw || format == kFormatww) {
		returnValue = make_unique<WeekDateTimeSource>(format);
	}
	else{
		WLog() << "unknown datetime source for format : " << format;
		returnValue = make_unique<FixedTextDateTimeSource>(format);
	}

	return returnValue;
}
