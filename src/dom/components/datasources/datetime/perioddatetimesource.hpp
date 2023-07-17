#ifndef DOT_MESSAGE_PERIODDATETIME_SOURCE_HPP
#define DOT_MESSAGE_PERIODDATETIME_SOURCE_HPP

#include <string>

#include "dom/components/datasources/datetimesource.hpp"
#include "datetimeformats.h"

namespace macsa
{
	namespace dot
	{
		namespace datetime
		{
			/**
			 * @brief Datasource DateTime Periods specifiers
			 * Include:
			 *  - t -> Period first char(options: "A" as AM / "P" as PM)
			 *  - tt -> Period(options: "AM" / "PM")
			 */
			class PeriodDateTimeSource : public DateTimeSource
			{
				public:
					explicit PeriodDateTimeSource(const std::string& format):
						DateTimeSource(format)
					{
						if (format != kFormatt && format != kFormattt) {
							_format = "";
						}
					}
					virtual ~PeriodDateTimeSource() = default;

				public:
					/**
					 * @brief Returns format specifier converted to value
					 */
					std::string GetData(Context* context) override
					{
						switch (_format.length())
						{
							case 1:     // t
								return context->time.tm_hour < 12 ? "A" : "P";
							case 2:     // tt
								return context->time.tm_hour < 12 ? "AM" : "PM";
							default:
								break;
						};
						return {};
					}
					/**
					 * @brief GetRefreshPolicy Returns Refresh Policy (by kCounter,  kSeconds, kMinutes,...)
					 * @return 'enum class RefreshPolicy'
					 */
					RefreshPolicy GetRefreshPolicy() override { return dot::RefreshPolicy::kNone; }
			};
		}
	}
}
#endif
