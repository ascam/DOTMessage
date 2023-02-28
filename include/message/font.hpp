#ifndef DOT_MESSAGE_FONT_HPP
#define DOT_MESSAGE_FONT_HPP

#include <string>

namespace macsa
{
	namespace dot
	{
		/**
		 * @brief Struct that contains the font parameters
		 */
		struct Font
		{
			std::string family = "";
			int size = 0;
			bool bold = false;
			bool italic = false;
			bool underline = false;
			bool strikeout = false;

			bool operator == (const Font& other) const {
				if (family != other.family ||
					size != other.size ||
					bold != other.bold ||
					italic != other.italic ||
					underline != other.underline ||
					strikeout != other.strikeout)
				{
					return false;
				}
				return true;
			}

			bool operator != (const Font& other) {
				if (family != other.family ||
					size != other.size ||
					bold != other.bold ||
					italic != other.italic ||
					underline != other.underline ||
					strikeout != other.strikeout)
				{
					return true;
				}
				return false;
			}
		};
	}
}
#endif
