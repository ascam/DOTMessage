#ifndef DOT_MESSAGE_MONTHDATETIME_SOURCE_HPP
#define DOT_MESSAGE_MONTHDATETIME_SOURCE_HPP

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
			* @brief Datasource DateTime Months specifiers
			* Include:
			*  - M -> Month(range: 1 to 12)
			*  - MM -> Month(range: 01 to 12)
			*  - MMM -> Month abbreviations(example: Jun)
			*  - MMMM -> Month(example: June)
			*  - [MMM] -> Month abbreviations uppercase(example: JUN)
			*  - [MMMM] -> Month uppercase(example: JUNE)
			*/
			class MonthDateTimeSource : public DateTimeSource
			{
				public:
					explicit MonthDateTimeSource(const std::string& format,
												 const bool& uppercase = false):
						DateTimeSource(format),
						_uppercase(uppercase)
					{
						if (format != kFormatM && format != kFormatMM &&
							format != kFormatMMM && format != kFormatMMMM) {
							_format = "";
						}
					}
					virtual ~MonthDateTimeSource() = default;

				public:
					/**
					 * @brief Returns format specifier converted to value
					 */
					std::string GetData(Context* context) override
					{
						char buffer[kBufferSize] = {0};
						switch (_format.length())
						{
							case 1:     // M
								// tm_mon range is 0-11, expected range 1-12
								return utils::stringutils::ToString(context->time.tm_mon + 1);
							case 2:     // MM
								// tm_mon range is 0-11, expected range 01-12
								return utils::stringutils::ToString(context->time.tm_mon + 1, 2);
							case 3:     // MMM and [MMM]
								strftime(buffer, kBufferSize, "%b", &context->time);
								return (_uppercase) ? utils::stringutils::ToUpper(buffer) : buffer;
							case 4:     // MMMM and [MMMM]
								strftime(buffer, kBufferSize, "%B", &context->time);
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
					/**
					 * @brief GetRefreshPolicy Returns Refresh Policy (by kCounter,  kSeconds, kMinutes,...)
					 * @return 'enum class RefreshPolicy'
					 */
					RefreshPolicy GetRefreshPolicy() override { return dot::RefreshPolicy::kMonths; }

				private:
					bool _uppercase;
			};
		}
	}
}
#endif
