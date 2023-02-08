#ifndef DOT_MESSAGE_TEXT_OBJECT_HPP
#define DOT_MESSAGE_TEXT_OBJECT_HPP

#include <string>
#include "object.hpp"
#include "font.hpp"
#include "textboxproperties.hpp"

namespace macsa {
	namespace dot {

		// TODO(iserra) Add data sources

		/**
		 * @brief The Text class.
		 *
		 * This class contains the text object definition.
		 */
		class Text : public Object
		{
			public:
				Text(const std::string& id);
				Text(const std::string& id, const Geometry& geometry);
				Text(const Text&) = delete;
				virtual ~Text();

				/**
				 * @brief GetData. Getter method to get the current
				 * value of the text resolving the variable fields.
				 * @return The text that must be rendered after resolving
				 * variable fields.
				 */
				virtual std::string GetData() const;

				/**
				 * @brief GetRefreshPolicy. Overrided method of
				 * Object::GetRefreshPolicy
				 * @return The refresh policy of the object.
				 */
				RefreshPolicy GetRefreshPolicy() const override;
				/**
				 * @brief IsVariable. Overrided method of Object::IsVariable
				 * @return true if the object can change the inner value,
				 * false if the object is static.
				 */
				bool IsVariable() const override;

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

//				NisxDatasource* GetDatasource() const {return _datasource.get();}
//				void SetDatasource(NisxDatasource* datasource);

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
//				std::unique_ptr<NisxDatasource> _datasource;
		};
	}
}

#endif
