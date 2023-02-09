#ifndef DOT_MESSAGE_COLORS_HPP
#define DOT_MESSAGE_COLORS_HPP

#include <string>
#include <cstdint>
#include <unordered_map>

namespace macsa
{
	namespace dot
	{
		/**
		 * @brief The Color class.
		 *  Class to define colors.
		 *
		 *  TODO (iserra): Remove color name?
		 *  TODO (iserra): add CMYK and grayscale conversions
		 */
		class Color
		{
			public:

				Color() = default;
				Color(const std::string& name, uint8_t r = 0, uint8_t g = 0, uint8_t b = 0, uint8_t alpha = 0xFF);

				std::string GetName() const { return _colorName; }
				void SetName(const std::string& name) { _colorName = name;}

				uint8_t GetAlpha() const { return _alpha;}
				void SetAlpha(uint8_t alpha) {_alpha = alpha;}

				uint8_t GetRed() const { return _red;}
				void SetRed(uint8_t red) {_red = red;}

				uint8_t GetGreen() const { return _green;}
				void SetGreen(uint8_t green) {_green = green;}

				uint8_t GetBlue() const { return _blue;}
				void SetBlue(uint8_t blue) {_blue = blue;}

				// Convert color to string
				std::string ToARGBString() const;
				std::string ToRGBAString() const;
				std::string ToRGBString() const;

				// Set colors from string
				void FromARGBString(const std::string& rgba);
				void FromRGBAString(const std::string& rgba);
				void FromRGBString(const std::string& rgba);

				bool operator == (const Color& other) const { return equal(other); };
				bool operator != (const Color& other) const { return !equal(other); };
				void operator = (const Color& other);

			private:
				uint8_t _red;
				uint8_t _green;
				uint8_t _blue;
				uint8_t _alpha;
				std::string _colorName;

				bool equal(const Color& other) const;
		};

		using ColorsPalette = std::unordered_map<std::string,Color>;
	}
}
#endif
