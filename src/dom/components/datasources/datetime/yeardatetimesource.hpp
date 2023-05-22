#ifndef DOT_MESSAGE_YEARDATETIME_SOURCE_HPP
#define DOT_MESSAGE_YEARDATETIME_SOURCE_HPP

#include <string>

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
			 * @brief Datasource DateTime Years specifiers
			 * Include:
			 *  - y -> Years(rane: 0 to 99)
			 *  - yy -> Years(range: 00 to 99)
			 *  - yyy -> Years with minimum of three digits(example: 090)
			 *  - yyyy -> Years with minimum of four digits(example: 0090)
			 * Not implemented:
			 *  - [L] -> Year last digit(example: 2018 -> 8)
			 *  - [LLL] -> Year last digit with three digits(example: 2018 -> 018)
			 */
			class YearDateTimeSource : public DateTimeSource
			{
				public:
					explicit YearDateTimeSource(const std::string& format):
						DateTimeSource(format)
					{
						if (format != kFormaty && format != kFormatyy &&
							format != kFormatyyy && format != kFormatyyyy) {
							_format = "";
						}
					}
					virtual ~YearDateTimeSource() = default;

				public:
					/**
					 * @brief Returns format specifier converted to value
					 */
					std::string GetData(Context* context) override
					{
						switch (_format.length())
						{
							case 1:     // y
								return utils::stringutils::ToString((context->time.tm_year + 1900) % 100);
							case 2:     // yy
								return utils::stringutils::ToString(
											(context->time.tm_year + 1900) % 100, 2);
							case 3:     // yyy
								return utils::stringutils::ToString(context->time.tm_year + 1900, 3);
							case 4:     // yyyy
								return utils::stringutils::ToString(context->time.tm_year + 1900, 4);
							default:
								break;
						};
						return {};
					}
					/**
					 * @brief GetRefreshPolicy Returns Refresh Policy (by kCounter,  kSeconds, kMinutes,...)
					 * @return 'enum class RefreshPolicy'
					 */
					RefreshPolicy GetRefreshPolicy() override { return dot::RefreshPolicy::kYears; }
			};
		}
	}
}
#endif
