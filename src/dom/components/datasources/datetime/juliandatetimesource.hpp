#ifndef DOT_MESSAGE_JULIANDATETIME_SOURCE_HPP
#define DOT_MESSAGE_JULIANDATETIME_SOURCE_HPP

#include <string>
#include <locale>
#include <iostream>

#include "dom/components/datasources/datetimesource.hpp"
#include "datetimeformats.h"

namespace macsa
{
	namespace dot
	{
		namespace datetime
		{
			/**
			 * @brief Datasource DateTime Julian date specifiers
			 * Include:
			 *  - J -> Julian date(range: 1 to 356)
			 *  - JJJ -> Julian date(range: 001 to 356)
			 *  - DEPRECATED [J] -> Julian date(rane: 1 to 356), automatic set as J
			 *  - DEPRECATED [JJJ] -> Julian date(range: 001 to 356), automatic set as JJJ
			 */
			class JulianDateTimeSource : public DateTimeSource
			{
				public:
					explicit JulianDateTimeSource(const std::string& format):
						DateTimeSource(format)
					{
						if (format != kFormatJ && format != kFormatJJJ) {
							_format = "";
						}
					}
					virtual ~JulianDateTimeSource() = default;

				public:
					/**
					 * @brief Returns format specifier converted to value
					 */
					std::string GetData(Context* context) override
					{
						char buffer[kBufferSize] = {0};
						switch (_format.length())
						{
							case 1:     // J
								strftime(buffer, kBufferSize, "%j", &context->time);

								std::cout << buffer << std::endl;

								for (auto& b : buffer) {
									if (b != '0') {
										return &b;
									}
								}
								break;
							case 3:     // JJJ
								strftime(buffer, kBufferSize, "%j", &context->time);
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
					RefreshPolicy GetRefreshPolicy() override { return dot::RefreshPolicy::kNone; }
			};
		}
	}
}
#endif
