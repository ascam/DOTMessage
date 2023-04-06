#ifndef DOT_MESSAGE_ERADATETIME_SOURCE_HPP
#define DOT_MESSAGE_ERADATETIME_SOURCE_HPP

#include <string>

#include "dom/components/datasources/datetimesource.hpp"

namespace macsa
{
	namespace dot
	{
		namespace datetime
		{
			/**
			 * @brief Datasource DateTime Era specifiers
			 *        Include:
			 *        - g -> Era(example: A.D.)
			 *       - gg -> Era(example: A.D.)
			 */
			class EraDateTimeSource : public DateTimeSource
			{
				public:
					explicit EraDateTimeSource(const std::string& format):
						DateTimeSource(format)
					{}
					virtual ~EraDateTimeSource() = default;

				public:
					/**
					 * @brief NOT IMPLEMENTED : Returns format specifier converted to value
					 */
					std::string GetData(const struct tm& time) override
					{
						switch (_format.length())
						{
							case 1:     // g
							case 2:     // gg
							default:
								break;
						};
						return {};
					}
			};
		}
	}
}
#endif
