#ifndef DOT_MESSAGE_WEEKDATETIME_SOURCE_HPP
#define DOT_MESSAGE_WEEKDATETIME_SOURCE_HPP

#include <string>
#include <locale>

#include "dom/components/datasources/datetimesource.hpp"
#include "datetimeformats.h"

namespace macsa
{
	namespace dot
	{
		namespace datetime
		{
			/**
			 * @brief Datasource DateTime Weeks specifiers
			 * Include:
			 *  - w -> Weeks of the year(rane: 1 to 53)
			 *  - ww -> Weeks of the year(range: 01 to 53)
			 */
			class WeekDateTimeSource : public DateTimeSource
			{
				public:
					explicit WeekDateTimeSource(const std::string& format):
						DateTimeSource(format)
					{
						if (format != kFormatw && format != kFormatww) {
							_format = "";
						}
					}
					virtual ~WeekDateTimeSource() = default;

				public:
					/**
					 * @brief Returns format specifier converted to value
					 * @param time
					 * @return
					 */
					std::string GetData(Context* context) override
					{
						char buffer[kBufferSize] = {0};
						switch (_format.length())
						{
							case 1:
								strftime(buffer, kBufferSize, "%V", &context->time);
								return (*buffer == '0') ? buffer + 1 : buffer;
							case 2:
								strftime(buffer, kBufferSize, "%V", &context->time);
								return buffer;
							default:
								break;
						};
						return {};
					}
					/**
					 * @brief GetRefreshPolicy Returns Refresh Policy (by kCounter,  kSeconds, kMinutes,...)
					 * @return 'enum class RefreshPolicy'
					 */
					RefreshPolicy GetRefreshPolicy() override { return dot::RefreshPolicy::kWeeks; }
			};
		}
	}
}
#endif
