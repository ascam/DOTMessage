#ifndef DOT_MESSAGE_TEXT_OBJECT_HPP
#define DOT_MESSAGE_TEXT_OBJECT_HPP

#include <string>
#include "variableobject.hpp"
#include "components/font.hpp"
#include "components/textboxproperties.hpp"

namespace macsa {
	namespace dot {

		class IDocumentVisitor;

		/**
		 * @brief The Text class.
		 *
		 * This class contains the text object definition.
		 */
		class Text : public VariableObject
		{
			public:
				Text(const std::string& id, const Geometry& geometry = Geometry());
				Text(const Text&) = delete;
				virtual ~Text() = default;

				/**
				 * @brief Accept: Allow the visitor to visit this object.
				 * @param visitor: Visitor object
				 * @return boolean with the result of the visit method
				 * of the visitor object.
				 */
				bool Accept(IDocumentVisitor* visitor) const override;

				/**
				 * @brief GetText
				 * @return
				 */
				const std::string& GetText() const {return _text;}

				/**
				 * @brief SetText
				 * @param text
				 */
				void SetText(const std::string& text);

				/**
				 * @brief GetFont. Getter method for text font.
				 * @return The Font struct of the text object.
				 */
				const Font& GetFont() const {return _font;}

				/**
				 * @brief SetFont. Setter method for text font.
				 * @param font: The Font struct to be applied.
				 */
				void SetFont(const Font& font);

				/**
				 * @brief GetForegroundColor. Getter method for the foreground color
				 * to apply to the text.
				 * @return The current foreground color.
				 */
				const Color& GetForegroundColor() const {return _foreColor;}

				/**
				 * @brief SetForegroundColor. Setter method for the foreground color
				 * to apply to the text.
				 * @param foreColor: The color to apply to the text.
				 */
				void SetForegroundColor(const Color& foreColor);

				/**
				 * @brief GetBackgroundColor. Getter method for the background color
				 * to apply to the text box.
				 * @return The current background color.
				 */
				const Color& GetBackgroundColor() const {return _backgroundColor;}

				/**
				 * @brief SetBackgroundColor. Setter method for the background color
				 * to apply to the text box.
				 * @param backgroundColor: The color to apply to the text background.
				 */
				void SetBackgroundColor(const Color& backgroundColor);

				/**
				 * @brief GetTextBoxProperties. Getter method for the text box properties.
				 * @return The class with the text box properties.
				 */
				const TextBoxProperties& GetTextBoxProperties() const {return _textBoxProperties;}

				/**
				 * @brief SetTextBoxProperties. Setter method for the text box properties.
				 * @param boxProps: The text box properties to apply.
				 */
				void SetTextBoxProperties(const TextBoxProperties& boxProps);


			public:
				Signal<> TextChanged;
				Signal<> FontChanged;
				Signal<> ForegroundColorChanged;
				Signal<> BackgroundColorChanged;
				Signal<> TextBoxPropertiesChanged;

				static bool GetRegistered()
				{
					return _registered;
				}

			private:
				std::string _text;
				Font _font;
				Color _foreColor;
				Color _backgroundColor;
				TextBoxProperties _textBoxProperties;
				static bool _registered;
		};
	}
}

#endif
