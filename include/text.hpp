#ifndef DOT_MESSAGE_TEXT_OBJECT_HPP
#define DOT_MESSAGE_TEXT_OBJECT_HPP

#include <string>
#include "object.hpp"

namespace macsa {
	namespace dot {

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


				RefreshPolicy GetRefreshPolicy() const override;
				bool IsVariable() const override;


				const std::string& GetText() const {return _text;}
				void SetText(const std::string& text);


			public:
				Signal<std::string> TextChanged;

			private:
				std::string _text;
		};
	}
}

#endif
