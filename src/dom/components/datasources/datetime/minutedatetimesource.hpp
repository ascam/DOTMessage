#ifndef DOT_MESSAGE_MINUTEDATETIME_SOURCE_HPP
#define DOT_MESSAGE_MINUTEDATETIME_SOURCE_HPP

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
			 * @brief Datasource DateTime Minutes specifiers
			 * Include:
			 *  - m -> Minutes(rane: 0 to 59)
			 *  - mm -> Minutes(range: 00 to 59)
			 */
			class MinuteDateTimeSource : public DateTimeSource
			{
				public:
					explicit MinuteDateTimeSource(const std::string& format):
						DateTimeSource(format)
					{
						if (format != kFormatm && format != kFormatmm) {
							_format = "";
						}
					}
					virtual ~MinuteDateTimeSource() = default;

				public:
					/**
					 * @brief Returns format specifier converted to value
					 */
					std::string GetData(Context* context) override
					{
						switch (_format.length())
						{
							case 1:     // m
								return utils::stringutils::ToString(context->time.tm_min);
							case 2:     // mm
								return utils::stringutils::ToString(context->time.tm_min, 2);
							default:
								break;
						};
						return {};
					}
					/**
					 * @brief GetRefreshPolicy Returns Refresh Policy (by kCounter,  kSeconds, kMinutes,...)
					 * @return 'enum class RefreshPolicy'
					 */
					RefreshPolicy GetRefreshPolicy() override { return dot::RefreshPolicy::kMinutes; }
			};
		}
	}
}
#endif
