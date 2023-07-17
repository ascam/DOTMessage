#ifndef DOT_MESSAGE_SECONDDATETIME_SOURCE_HPP
#define DOT_MESSAGE_SECONDDATETIME_SOURCE_HPP

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
			 * @brief Datasource DateTime Seconds specifiers
			 * Include:
			 *   - s -> Seconds(rane: 0 to 59)
			 *   - ss -> Seconds(range: 00 to 59)
			 */
			class SecondDateTimeSource : public DateTimeSource
			{
				public:
					explicit SecondDateTimeSource(const std::string& format):
						DateTimeSource(format)
					{
						if (format != kFormats && format != kFormatss) {
							_format = "";
						}
					}
					virtual ~SecondDateTimeSource() = default;

				public:
					/**
					 * @brief Returns format specifier converted to value
					 */
					std::string GetData(Context* context) override
					{
						switch (_format.length())
						{
							case 1:     // s
								return utils::stringutils::ToString(context->time.tm_sec);
							case 2:     // ss
								return utils::stringutils::ToString(context->time.tm_sec, 2);
							default:
								break;
						};
						return {};
					}
					/**
					 * @brief GetRefreshPolicy Returns Refresh Policy (by kCounter,  kSeconds, kMinutes,...)
					 * @return 'enum class RefreshPolicy'
					 */
					RefreshPolicy GetRefreshPolicy() override { return dot::RefreshPolicy::kSeconds; }
			};
		}
	}
}
#endif
