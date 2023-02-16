#include "message/color.hpp"
#include <sstream>
#include "utils/stringutils.hpp"

using macsa::dot::Color;
using namespace macsa::utils;

constexpr int kColorLengh = 2;
constexpr int kColorStrLenght = 4 * kColorLengh;

Color::Color() :
	_red{},
	_green{},
	_blue{},
	_alpha{0xFF} // Opaque
{}

Color::Color(const std::string &name, uint8_t r, uint8_t g, uint8_t b, uint8_t alpha) :
	_red{r},
	_green{g},
	_blue{b},
	_alpha{alpha},
	_colorName{name}
{}

std::string Color::ToARGBString() const
{
	std::stringstream color;

	color << stringutils::IntToHex(_alpha, kColorLengh);
	color << stringutils::IntToHex(_red, kColorLengh);
	color << stringutils::IntToHex(_green, kColorLengh);
	color << stringutils::IntToHex(_blue, kColorLengh);

	return color.str();
}

std::string Color::ToRGBAString() const
{
	std::stringstream color;

	color << stringutils::IntToHex(_red, kColorLengh);
	color << stringutils::IntToHex(_green, kColorLengh);
	color << stringutils::IntToHex(_blue, kColorLengh);
	color << stringutils::IntToHex(_alpha, kColorLengh);

	return color.str();
}

std::string Color::ToRGBString() const
{
	std::stringstream color;

	color << stringutils::IntToHex(_red, kColorLengh);
	color << stringutils::IntToHex(_green, kColorLengh);
	color << stringutils::IntToHex(_blue, kColorLengh);

	return color.str();
}

void Color::FromARGBString(const std::string &rgba)
{
	// When input format isn't correct, color will not change
	if (rgba.size() == kColorStrLenght) {
		_alpha = stringutils::HexToUInt(rgba.substr(0, kColorLengh));
		_red = stringutils::HexToUInt(rgba.substr(2, kColorLengh));
		_green = stringutils::HexToUInt(rgba.substr(4, kColorLengh));
		_blue = stringutils::HexToUInt(rgba.substr(6, kColorLengh));
	}
}

void Color::FromRGBAString(const std::string &rgba)
{
	// When input format isn't correct, color will not change
	if (rgba.size() == kColorStrLenght) {
		_red = stringutils::HexToUInt(rgba.substr(0, kColorLengh));
		_green = stringutils::HexToUInt(rgba.substr(2, kColorLengh));
		_blue = stringutils::HexToUInt(rgba.substr(4, kColorLengh));
		_alpha = stringutils::HexToUInt(rgba.substr(6, kColorLengh));
	}
}

void Color::FromRGBString(const std::string &rgba)
{
	if (rgba.size() == (kColorStrLenght - kColorLengh)) {
		_red = stringutils::HexToUInt(rgba.substr(0, kColorLengh));
		_green = stringutils::HexToUInt(rgba.substr(2, kColorLengh));
		_blue = stringutils::HexToUInt(rgba.substr(4, kColorLengh));
	}
}

void Color::operator = (const Color &other)
{
	_red = other._red;
	_green = other._green;
	_blue = other._blue;
	_alpha = other._alpha;
}

bool Color::equal(const Color &other) const
{
	return  _red == other._red &&
			_green == other._green &&
			_blue == other._blue &&
			_alpha == other._alpha;
}
