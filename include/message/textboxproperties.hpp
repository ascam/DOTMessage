#ifndef DOT_MESSAGE_TEXT_BOX_PROPETIES_HPP
#define DOT_MESSAGE_TEXT_BOX_PROPETIES_HPP

#include <string>
#include "utils/smartenum.hpp"
#include "alignment.hpp"

namespace macsa
{
	namespace dot
	{
		enum class NTextBoxAdjustment {
			kFitToBox,
			kParagraph
		};

		static constexpr const char* kFitToBox  = "FitToBox";
		static constexpr const char* kParagraph = "Paragraph";

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
				const VerticalAlignment& GetVerticalAlignment() const {
					return _verticalAlignment;
				}
				/**
				 * @brief SetVerticalAlignment. Setter method for the
				 * vertical alignment of the text in the container box.
				 * This property only applies in a paragraph ajustmment.
				 * @param alignment: The text vertical alignment to apply.
				 */
				void SetVerticalAlignment(const VerticalAlignment& alignment) {
					_verticalAlignment = alignment;
				}

				/**
				 * @brief GetHorizontalAlignment. Getter method for the
				 * horizontal alignment of the text in the container box.
				 * This property only applies in a paragraph ajustmment.
				 * @return The current text horizontal alignment.
				 */
				const HorizontalAlignment& GetHorizontalAlignment() const {
					return _horizontalAlignment;
				}
				/**
				 * @brief SetHorizontalAlignment. Setter method for the
				 * horizontal alignment of the text in the container box.
				 * This property only applies in a paragraph ajustmment.
				 * @param alignment: The text horizontal alignment to apply.
				 */
				void SetHorizontalAlignment(const HorizontalAlignment& alignment) {
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
				VerticalAlignment _verticalAlignment;
				HorizontalAlignment _horizontalAlignment;
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
