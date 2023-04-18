#ifndef DOT_MESSAGE_DATECODE_DATETIME_HPP
#define DOT_MESSAGE_DATECODE_DATETIME_HPP

#include <string>
#include <locale>

#include "dom/components/datasources/datetimesource.hpp"
#include "printer/datecodes.hpp"

namespace macsa
{
	namespace dot
	{
		namespace datetime
		{
			/**
			* @brief Datasource DateTime DateCode specifiers
			* Include:
			* - [DC:m] -> Minutes codes
			* - [DC:H] -> Hours codes
			* - [DC:dd] -> Days of the month codes
			* - [DC:ddd] -> Days of the week codes
			* - [DC:M] -> Months codes
			* - [DC:J] -> Days of the year codes
			* - [DC:Y] -> Years codes
			* - [DC:w] -> Weeks of the year codes
			* - [DC:S] -> Days of the week plus Hours codes
			*/
			class DateCodeDateTimeSource : public DateTimeSource
			{
				public:
					DateCodeDateTimeSource(const std::string& format):
						DateTimeSource(format)
					{}
					virtual ~DateCodeDateTimeSource() = default;

				public:
					/**
					 * @brief Returns format specifier converted to value
					 */
					std::string GetData(Context* context) override
					{
						return context->dateCodes.parserDateTime(_format, context->time);
					}
			};
		}
	}
}
#endif
