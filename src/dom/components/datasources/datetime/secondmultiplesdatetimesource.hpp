#ifndef DOT_MESSAGE_SECONDMULTIPLETIME_SOURCE_HPP
#define DOT_MESSAGE_SECONDMULTIPLETIME_SOURCE_HPP

#include <string>

#include "dom/components/datasources/datetimesource.hpp"

namespace macsa
{
	namespace dot
	{
		namespace datetime
		{
			/**
			* @brief NOT IMPLEMENTED! : Datasource DateTime SecondMultiples specifiers
			* Include:
			*  - f -> tenths of a second
			*  - F -> if not 0, tenths of a second
			*  - ff -> hundredths of a second
			*  - FF -> if not 0, hundredths of a second
			*  - fff -> milliseconds
			*  - FFF -> if not 0, milliseconds
			*  - ffff -> ten thousandths of a second
			*  - FFFF -> if not 0, ten thousandths of a second
			*  - fffff -> hundredths of a second
			*  - FFFFF -> if not 0, hundredths of a second
			*  - ffffff -> millionths of a second
			*  - FFFFFF -> if not 0, millionths of a second
			*  - fffffff -> tenths of a second
			*  - FFFFFFF -> if not 0, tenths of a second
			*/
			class SecondMultiplesDateTimeSource : public DateTimeSource
			{
				public:
					explicit SecondMultiplesDateTimeSource(const std::string& format):
						DateTimeSource(format)
					{}
					virtual ~SecondMultiplesDateTimeSource() = default;

				public:
					/**
					 * @brief Returns format specifier converted to value
					 * - Check if format is uppercase(ex: FFF) or lowercase(ex: fff)
					 */
					std::string GetData(Context* context) override
					{
						switch (_format.length())
						{
							case 1:     // f and F
							case 2:     // ff and FF
							case 3:     // fff and FFF
							case 4:     // ffff and FFFF
							case 5:     // fffff and FFFFF
							case 6:     // ffffff and FFFFFF
							case 7:     // fffffff and FFFFFFF
							default:
								break;
						};
						return {};
					}
					/**
					 * @brief GetRefreshPolicy Returns Refresh Policy (by kCounter,  kSeconds, kMinutes,...)
					 * @return 'enum class RefreshPolicy'
					 */
					RefreshPolicy GetRefreshPolicy() override { return dot::RefreshPolicy::kSeconds; } //TODO: Review
			};
		}
	}
}
#endif
