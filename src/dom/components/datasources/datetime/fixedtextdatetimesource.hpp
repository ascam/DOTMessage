#ifndef DOT_MESSAGE_FIXEDTEXTDATETIME_SOURCE_HPP
#define DOT_MESSAGE_FIXEDTEXTDATETIME_SOURCE_HPP

#include <string>
#include <tuple>
#include <algorithm>

#include "dom/components/datasources/datetimesource.hpp"
#include "datetimeformats.h"

namespace macsa
{
	namespace dot
	{
		namespace datetime
		{
			/**
			* @brief Datasource DateTime Fixed Text specifiers
			* Include:
			*   - : -> Time separator(example: 12:42)
			*   - / -> Time separator(example: 12/42)
			*   - "string" -> Fixed text(example: "Text" -> Text)
			*   - 'string' -> Fixed text(example: 'Text' -> Text)
			*   - \ -> Escape char(example: /h -> h)
			*   - Unknown char -> Non specified char(example: $ -> $)*
			*/
			class FixedTextDateTimeSource : public DateTimeSource
			{
				public:
					FixedTextDateTimeSource(const std::string& format) :
						DateTimeSource(format),
						_fixedText{}
					{
						// separators ':', '/' and '%'
						if (_format == kFormatColon || _format == kFormatSlash || format == kFormatPercentage) {
							_fixedText = _format;
						}
						else if (format == kFormatSlash) { //@jsubi work in progress!!
							_fixedText = _format;
						}
						// "string"
						else if (_format.find(kFormatCharString) != std::string::npos)	{
							_fixedText = _format;
							_fixedText.erase(std::remove(_fixedText.begin(), _fixedText.end(), *kFormatCharString), _fixedText.end());
						}
						// 'string'
						else if (_format.find(kFormatString) != std::string::npos)	{
							_fixedText = _format;
							_fixedText.erase(std::remove(_fixedText.begin(), _fixedText.end(), *kFormatString), _fixedText.end());
						}
					}
					virtual ~FixedTextDateTimeSource() = default;

				public:

					/**
					 * @brief Returns format specifier converted to value
					 */
					std::string GetData(Context* context) override
					{
						// Avoid compile warnning
						std::ignore = context;
						return _fixedText;
					}

				private:
					std::string _fixedText;
			};
		}
	}
}
#endif
