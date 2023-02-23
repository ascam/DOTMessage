#ifndef DOT_MESSAGE_TEXT_OBJECT_HPP
#define DOT_MESSAGE_TEXT_OBJECT_HPP

#include <string>
#include "variableobject.hpp"
#include "font.hpp"
#include "textboxproperties.hpp"

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
				virtual ~Text();

				/**
				 * @brief IsVariable. Overrided method of Object::IsVariable
				 * @return true if the object can change the inner value,
				 * false if the object is static.
				 */
				bool IsVariable() const override;

				/**
				 * @brief Accept: Allow the visitor to visit this object.
				 * @param visitor: Visitor object
				 * @return boolean with the result of the visit method
				 * of the visitor object.
				 */
				bool Accept(IDocumentVisitor* visitor) override;

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
				const std::string& GetForegroundColor() const {return _foreColor;}
				/**
				 * @brief SetForegroundColor. Setter method for the foreground color
				 * to apply to the text.
				 * @param foreColor: The color to apply to the text.
				 */
				void SetForegroundColor(const std::string& foreColor);

				/**
				 * @brief GetBackgroundColor. Getter method for the background color
				 * to apply to the text box.
				 * @return The current background color.
				 */
				const std::string& GetBackgroundColor() const {return _backgroundColor;}
				/**
				 * @brief SetBackgroundColor. Setter method for the background color
				 * to apply to the text box.
				 * @param backgroundColor: The color to apply to the text background.
				 */
				void SetBackgroundColor(const std::string& backgroundColor);

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
				Signal<std::string> TextChanged;
				Signal<Font> FontChanged;
				Signal<std::string> ForegroundColorChanged;
				Signal<std::string> BackgroundColorChanged;
				Signal<> TextBoxPropertiesChanged;

			private:
				std::string _text;
				Font _font;
				std::string _foreColor;
				std::string _backgroundColor;
				TextBoxProperties _textBoxProperties;
		};
	}
}

#endif
