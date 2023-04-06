#ifndef DOT_MESSAGE_DAYDATETIME_SOURCE_HPP
#define DOT_MESSAGE_DAYDATETIME_SOURCE_HPP

#include <string>
#include <locale>

#include "dom/components/datasources/datetimesource.hpp"
#include "datetimeformats.h"
#include "utils/stringutils.hpp"

namespace macsa
{
	namespace dot
	{
		namespace datetime
		{
			/**
			* @brief Datasource DateTime Days specifiers
			* Include:
			*  - d -> Day of month(range: 1 to 31)
			*  - dd -> Day of month(range: 01 to 31)
			*  - ddd -> day of the week abbreviations(example: mon)
			*  - dddd -> day of the week(example: monday)
			*  - [ddd] -> day of the week abbreviations uppercase(example: MON)
			*  - [dddd] -> day of the week uppercase(example: MONDAY)
			*/
			class DayDateTimeSource : public DateTimeSource
			{
				public:
					explicit DayDateTimeSource(const std::string& format, const bool& uppercase = false):
						DateTimeSource(format),
						_uppercase(uppercase)
					{
						// Check for correct format
						if (format != kFormatd && format != kFormatdd &&
							format != kFormatddd && format != kFormatdddd) {
							_format = "";
						}
					}

					virtual ~DayDateTimeSource() = default;

				public:

					/**
					 * @brief Returns format specifier converted to value
					 */
					std::string GetData(Context* context) override
					{
						char buffer[kBufferSize] = {0};
						switch (_format.length())
						{
							case 1:     // d
								return utils::stringutils::ToString(context->time.tm_mday);
							case 2:     // dd
								return utils::stringutils::ToString(context->time.tm_mday, 2);
							case 3:     // ddd and [ddd]
								strftime(buffer, kBufferSize, "%a", &context->time);
								return (_uppercase) ? utils::stringutils::ToUpper(buffer) : buffer;
							case 4:     // dddd and [dddd]
								strftime(buffer, kBufferSize, "%A", &context->time);
								return (_uppercase) ? utils::stringutils::ToUpper(buffer) : buffer;
							default:
								break;
						};
						return {};
					}

					/**
					 * @brief Return format
					 */
					std::string GetFormat() override
					{
						return (_uppercase) ? "[" + _format + "]" : _format;
					}

				private:
					bool _uppercase;
			};
		}
	}
}
#endif
