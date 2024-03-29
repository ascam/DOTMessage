#ifndef DOT_MESSAGE_DATETIME_SOURCEFACTORY_HPP
#define DOT_MESSAGE_DATETIME_SOURCEFACTORY_HPP

#include <memory>
#include <string>
#include <vector>
#include <regex>

#include "dom/components/datasources/datetimesource.hpp"

namespace macsa
{
	namespace dot
	{
		namespace datetime
		{
			/**
			 * @brief Factory class to parse format from string to vector<DateTimeSource*>
			 */
			class DateTimeSourceFactory
			{
				public:
					explicit DateTimeSourceFactory() = default;
					virtual ~DateTimeSourceFactory() = default;

					/**
					 * @brief Convert format specifiers into the corresponding DateTimeSource sub-class
					 */
					std::vector<std::unique_ptr<DateTimeSource>> parseFormatRegex(const std::string& format);

				private:
					/**
					 * @brief struct to group result data from regex matches.
					 * @param position: index of the match in the searched string
					 * @param format: found text that matches de regex.
					 * @suffix: remaining text that is not a regex match.
					 */
					struct MatchResult
					{
						int position;
						std::string format;
						std::string suffix;
					};

					/**
					 * @brief Allocate DateTimeSource derived class corresponding to the given format
					 */
					std::unique_ptr<DateTimeSource> getDateTimeSpecifiers(const std::string& format);

					void pushDataSource(std::vector<std::unique_ptr<DateTimeSource>>& dateTimeSources, const std::string& type, std::string format);
					void insertMatchResult(std::map<std::string, MatchResult>& regexMatches, const std::string& type, const std::smatch& match);
			};
		}
	}
}
#endif
