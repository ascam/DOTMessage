#ifndef DOT_MESSAGE_PRIMITIVE_PEN_HPP
#define DOT_MESSAGE_PRIMITIVE_PEN_HPP

#include <cstdint>
#include <sstream>
#include <vector>
#include "color.hpp"
#include "utils/smartenum.hpp"

namespace macsa {
	namespace dot {

		/**
		 * @brief Line style smart enum
		 */
		enum class NLineStyle
		{
			// Continues line
			kSolid,
			// Line formed by dashes
			kDash,
			// Line formed by points
			kDot,
			// Line formed by the repetition of the dash dot pattern
			kDashDot,
			// Line formed by the repetition of the dash dot dor pattern
			kDashDotDot,
			// Custom dash format specified by user using dashValues
			kCustom,
		};

		static constexpr const char* kLineStyleSolid = "Solid";
		static constexpr const char* kLineStyleDash = "Dash";
		static constexpr const char* kLineStyleDot = "Dot";
		static constexpr const char* kLineStyleDashDot = "DashDot";
		static constexpr const char* kLineStyleDashDotDot = "DashDotDot";
		static constexpr const char* kLineStyleCustom = "Custom";

		/**
		 * @brief Dash style smart enum
		 */
		class LineStyle final : public utils::SmartEnum<NLineStyle>
		{
			public:
				LineStyle(const NLineStyle& style = NLineStyle::kSolid) :
					utils::SmartEnum<NLineStyle>(style)
				{}

				LineStyle(const std::string& style) :
					utils::SmartEnum<NLineStyle>(NLineStyle::kSolid)
				{
					fromString(style);
				}

				const LineStyle& operator = (const std::string& val) {
					fromString(val);
					return *this;
				}

			private:
				const std::vector<std::pair<NLineStyle,std::string>>& getData() const override{
					static const std::vector<std::pair<NLineStyle,std::string>> kNLineStyleData {
						{NLineStyle::kSolid, kLineStyleSolid},
						{NLineStyle::kDash, kLineStyleDash},
						{NLineStyle::kDot, kLineStyleDot},
						{NLineStyle::kDashDot, kLineStyleDashDot},
						{NLineStyle::kDashDotDot, kLineStyleDashDotDot},
						{NLineStyle::kCustom, kLineStyleCustom}
					};
					return kNLineStyleData;
				}
		};

		class PenStyle
		{
			public:
				PenStyle(const LineStyle& style = NLineStyle::kSolid) :
					_lineStyle{style},
					_customDashPattern{}
				{}

				/**
				 * @brief SetCustomDashedPattern. Method to set the dashes pattern.
				 * To set the custom patter pass a string with a sequence of number where
				 * the first number define the long of the line and the second number define
				 * the long of the space and then the next number will define the long of
				 * a line and the next the long of the space and so on.
				 * @verbatim
				 * std::string pattern = "2,1,3,2" // -- ---  -- ---
				 * @endverbatim
				 *
				 * @param str: String with the pattern.
				 */
				void SetCustomDashedPattern(const std::string& str)
				{
					_customDashPattern.clear();
					std::stringstream ss(str);
					std::string value;
					while (getline(ss, value, ',')) {
						_customDashPattern.push_back(std::stof(value));
					}
					if (_customDashPattern.size() % 2 != 0) {
						_customDashPattern.pop_back();
					}
				}
				/**
				 * @brief GetCustomDashedPattern. Method to get the custom dash pattern.
				 * @return The pattern in a sequence numbers.
				 */
				std::string GetCustomDashedPattern()
				{
					std::string pattern;
					if (!_customDashPattern.empty()) {
						std::stringstream ss;
						for (auto lenght : _customDashPattern) {
							ss << lenght << ",";
						}
						pattern = ss.str();
						pattern.pop_back();
					}
					return pattern;
				}

				bool operator==(const PenStyle& other) const {return equal(other);}
				bool operator!=(const PenStyle& other) const {return !equal(other);}

			private:
				LineStyle _lineStyle;
				std::vector<uint32_t> _customDashPattern;

				bool equal(const PenStyle& other) const {
					if (_lineStyle != other._lineStyle) {
						return false;
					}
					if (_lineStyle == NLineStyle::kCustom) {
						return _customDashPattern == other._customDashPattern;
					}
					return true;
				}
		};

		/**
		 * @brief The Pen class. Class that defines the line style of a
		 * primitive object.
		 */
		class Pen
		{
			public:
				Pen() :
					_color{"black"},
					_style{},
					_width{1.0}
				{}
				Pen(const Pen& pen) :
					_color{pen._color},
					_style{pen._style},
					_width{pen._width}
				{}

				/**
				 * @brief GetColor. Getter method for pen color.
				 * @return The current pen color.
				 */
				const Color& GetColor() const {
					return _color;
				}
				/**
				 * @brief SetColor. Setter method for pen color.
				 * @param color: The pen color to use.
				 */
				void SetColor(const Color& color) {
					_color = color;
				}
				/**
				 * @brief GetStyle. Getter method for pen line style.
				 * @return The current pen line style.
				 */
				const PenStyle& GetStyle() const {
					return _style;
				}
				/**
				 * @brief SetStyle. Setter method for pen line style.
				 * @param style: The pen line style to use.
				 */
				void SetStyle(const PenStyle& style) {
					_style = style;
				}
				/**
				 * @brief GetWidth. Getter method for pen width.
				 * @return the current pen width.
				 */
				float GetWidth() const {
					return _width;
				}
				/**
				 * @brief SetWidth. Setter method for pen width.
				 * @param width: the pen width to use.
				 */
				void SetWidth(float width) {
					_width = width;
				}

				bool operator==(const Pen& other) const {return equal(other);}
				bool operator!=(const Pen& other) const {return !equal(other);}

			private:
				Color _color;
				PenStyle _style;
				float _width;

				bool equal(const Pen& pen) const {
					if (_color != pen._color ||
						_style != pen._style ||
						_width != pen._width)
					{
						return false;
					}
					return true;
				}
		};
	}
}

#endif
