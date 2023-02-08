#ifndef DOT_MESSAGE_TEXT_BOX_PROPETIES_HPP
#define DOT_MESSAGE_TEXT_BOX_PROPETIES_HPP

#include <string>
#include "utils/smartenum.hpp"

namespace macsa
{
	namespace dot
	{
		/**
		 * @brief The TextVerticalAlignment smart enum.
		 */
		enum class NTextVerticalAlignment {
			kTop,
			kMiddle,
			kBottom
		};

		static constexpr const char* kTop    = "Top";
		static constexpr const char* kMiddle = "Middle";
		static constexpr const char* kBottom = "Bottom";

		class TextVerticalAlignment final : public utils::SmartEnum<NTextVerticalAlignment>
		{
			public:
				TextVerticalAlignment (const NTextVerticalAlignment& alignment = NTextVerticalAlignment::kTop) :
					utils::SmartEnum<NTextVerticalAlignment>(alignment)
				{}
				TextVerticalAlignment (const std::string& alignment) :
					utils::SmartEnum<NTextVerticalAlignment>(NTextVerticalAlignment::kTop)
				{
					fromString(alignment);
				}

				const TextVerticalAlignment& operator = (const std::string& alignment) {
					fromString(alignment);
					return *this;
				}
				const TextVerticalAlignment& operator = (NTextVerticalAlignment alignment) {
					_val = alignment;
					return *this;
				}

			private:
				const std::vector<std::pair<NTextVerticalAlignment,std::string>>& getData() const override{
					static const std::vector<std::pair<NTextVerticalAlignment,std::string>> kNTextVerticalAlignmentData {
						{NTextVerticalAlignment::kTop,    kTop},
						{NTextVerticalAlignment::kMiddle, kMiddle},
						{NTextVerticalAlignment::kBottom, kBottom}
					};
					return kNTextVerticalAlignmentData;
				}
		};

		enum class NTextHorizontalAlignment {
			kLeft,
			kCenter,
			kRight
		};

		static constexpr const char* kLeft    = "Left";
		static constexpr const char* kCenter = "Center";
		static constexpr const char* kRight = "Right";

		class TextHorizontalAlignment final : public utils::SmartEnum<NTextHorizontalAlignment>
		{
			public:
				TextHorizontalAlignment (const NTextHorizontalAlignment& alignment = NTextHorizontalAlignment::kLeft) :
					utils::SmartEnum<NTextHorizontalAlignment>(alignment)
				{}
				TextHorizontalAlignment (const std::string& alignment) :
					utils::SmartEnum<NTextHorizontalAlignment>(NTextHorizontalAlignment::kLeft)
				{
					fromString(alignment);
				}

				const TextHorizontalAlignment& operator = (const std::string& alignment) {
					fromString(alignment);
					return *this;
				}

				const TextHorizontalAlignment& operator = (NTextHorizontalAlignment alignment) {
					_val = alignment;
					return *this;
				}

			private:
				const std::vector<std::pair<NTextHorizontalAlignment,std::string>>& getData() const override{
					static const std::vector<std::pair<NTextHorizontalAlignment,std::string>> kNTextHorizontalAlignmentData {
						{NTextHorizontalAlignment::kLeft,   kLeft},
						{NTextHorizontalAlignment::kCenter, kCenter},
						{NTextHorizontalAlignment::kRight,  kRight}
					};
					return kNTextHorizontalAlignmentData;
				}
		};

		enum class NTextBoxAdjustment {
			kFitToBox,
			kParagraph
		};

		static constexpr const char* kFitToBox  = "FITTOBOX";
		static constexpr const char* kParagraph = "PARAGRAPH";

		class TextBoxAdjustment final : public utils::SmartEnum<NTextBoxAdjustment>
		{
			public:
				TextBoxAdjustment (const NTextBoxAdjustment& adjustment = NTextBoxAdjustment::kFitToBox) :
					utils::SmartEnum<NTextBoxAdjustment>(adjustment)
				{}
				TextBoxAdjustment (const std::string& adjustment) :
					utils::SmartEnum<NTextBoxAdjustment>(NTextBoxAdjustment::kFitToBox)
				{
					fromString(adjustment);
				}

				const TextBoxAdjustment& operator = (const std::string& adjustment) {
					fromString(adjustment);
					return *this;
				}

				const TextBoxAdjustment& operator = (NTextBoxAdjustment adjustment) {
					_val = adjustment;
					return *this;
				}

			private:
				const std::vector<std::pair<NTextBoxAdjustment,std::string>>& getData() const override{
					static const std::vector<std::pair<NTextBoxAdjustment,std::string>> kNTextBoxAdjustmentData {
						{NTextBoxAdjustment::kFitToBox,  kFitToBox},
						{NTextBoxAdjustment::kParagraph, kParagraph}
					};
					return kNTextBoxAdjustmentData;
				}
		};


		class TextBoxProperties
		{
			public:
				TextBoxProperties() :
					_boxAdjustment{},
					_verticalAlignment{},
					_horizontalAlignment{},
					_maxCharsLine{0},
					_clipping{true},
					_lineSpacing{1.0}
				{}

				/**
				 * @brief GetBoxAdjustment. Getter method for text adjustment
				 * of the text inside a container box.
				 * @return The current box adjustment.
				 */
				const TextBoxAdjustment& GetBoxAdjustment() const {
					return _boxAdjustment;
				}
				/**
				 * @brief SetBoxAdjustment. Setter method for text adjustment
				 * of the text inside a container box.
				 * @param adjustment: The text adjustment in the box.
				 */
				void SetBoxAdjustment(const TextBoxAdjustment& adjustment) {
					_boxAdjustment = adjustment;
				}
				/**
				 * @brief GetVerticalAlignment. Getter method for the
				 * vertical alignment of the text in the container box.
				 * This property only applies in a paragraph ajustmment.
				 * @return The current text vertical alignment.
				 */
				const TextVerticalAlignment& GetVerticalAlignment() const {
					return _verticalAlignment;
				}
				/**
				 * @brief SetVerticalAlignment. Setter method for the
				 * vertical alignment of the text in the container box.
				 * This property only applies in a paragraph ajustmment.
				 * @param alignment: The text vertical alignment to apply.
				 */
				void SetVerticalAlignment(const TextVerticalAlignment& alignment) {
					_verticalAlignment = alignment;
				}

				/**
				 * @brief GetHorizontalAlignment. Getter method for the
				 * horizontal alignment of the text in the container box.
				 * This property only applies in a paragraph ajustmment.
				 * @return The current text horizontal alignment.
				 */
				const TextHorizontalAlignment& GetHorizontalAlignment() const {
					return _horizontalAlignment;
				}
				/**
				 * @brief SetHorizontalAlignment. Setter method for the
				 * horizontal alignment of the text in the container box.
				 * This property only applies in a paragraph ajustmment.
				 * @param alignment: The text horizontal alignment to apply.
				 */
				void SetHorizontalAlignment(const TextHorizontalAlignment& alignment) {
					_horizontalAlignment = alignment;
				}

				/**
				 * @brief GetMaxCharsLine. Getter method for max chars line
				 * in a Fit to box adjustment. This property sets the maximum
				 * characters that can be shown in a line for fit to box
				 * adjustment
				 * @return The maximum characters in a fit to box line.
				 */
				uint32_t GetMaxCharsLine() const {
					return _maxCharsLine;
				}
				/**
				 * @brief SetMaxCharsLine. Setter method for max chars line
				 * in a Fit to box adjustment.
				 * @param maxCharsLine: The maximum characters in a fit to
				 * box line.
				 */
				void SetMaxCharsLine(uint32_t maxCharsLine) {
					_maxCharsLine = maxCharsLine;
				}

				/**
				 * @brief GetClipText. Getter method for text clipping.
				 * In a paragraph adjustment this parameters force a
				 * to hide all the text that overflows the container box.
				 * @return true if the text will be clipped or false if
				 * the text does not clipped.
				 */
				bool GetClipText() const {
					return _clipping;
				}
				/**
				 * @brief SetClipText. Setter method for text clipping.
				 * @param clip: true for clip the text in the container
				 * box.
				 */
				void SetClipText(bool clip) {
					_clipping = clip;
				}

				/**
				 * @brief GetLineSpacing. Getter method for text line
				 * spacing.
				 * @return The current text line spacing.
				 */
				float GetLineSpacing() const {
					return _lineSpacing;
				}
				/**
				 * @brief SetLineSpacing. Setter method for text line
				 * spacing.
				 * @param lineSpacing: The line spacing to apply.
				 */
				void SetLineSpacing(float lineSpacing) {
					_lineSpacing = lineSpacing;
				}

				bool operator == (const TextBoxProperties& other) const {
					return equal(other);
				}

				bool operator != (const TextBoxProperties& other) const {
					return !equal(other);
				}

			private:
				TextBoxAdjustment _boxAdjustment;
				TextVerticalAlignment _verticalAlignment;
				TextHorizontalAlignment _horizontalAlignment;
				uint32_t _maxCharsLine;
				bool _clipping;
				float _lineSpacing;

				bool equal(const TextBoxProperties& other) const {
					if (_boxAdjustment != other._boxAdjustment ||
						_verticalAlignment != other._verticalAlignment ||
						_horizontalAlignment != other._horizontalAlignment ||
						_maxCharsLine != other._maxCharsLine ||
						_clipping != other._clipping ||
						_lineSpacing != other._lineSpacing)
					{
						return false;
					}
					return true;
				}
		};
	}
}
#endif
