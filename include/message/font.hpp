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
		};
		bool operator == (const Font& a, const Font& b) {
			if (a.family != b.family ||
				a.size != b.size ||
				a.bold != b.bold ||
				a.italic != b.italic ||
				a.underline != b.underline ||
				a.strikeout != b.strikeout)
			{
				return false;
			}
			return true;
		}
		bool operator != (const Font& a, const Font& b) {
			if (a.family != b.family ||
				a.size != b.size ||
				a.bold != b.bold ||
				a.italic != b.italic ||
				a.underline != b.underline ||
				a.strikeout != b.strikeout)
			{
				return true;
			}
			return false;
		}
	}
}
#endif
