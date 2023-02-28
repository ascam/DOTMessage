#ifndef MACSA_NISX_IMAGE_PARSER_HPP
#define MACSA_NISX_IMAGE_PARSER_HPP

#include "dom/image.hpp"
#include "objectparser.hpp"
#include "tinyxml2.h"

namespace macsa {
	namespace nisx {
		class ImageParser : public ObjectParser
		{
			public:
				ImageParser(dot::Object* image);
				virtual ~ImageParser();

				bool VisitEnter( const tinyxml2::XMLElement& element, const tinyxml2::XMLAttribute* firstAttribute) override;

			private:
				dot::Image* _image;

				void parseAlignment(const std::string& adjust);
				/**
				 * @brief contentFromString. Helper method to convert an string in a byte vector.
				 * @param data: string with the content to be converted.
				 * @return Returns a vector of uint8_t with the data passed, the data content
				 * will be decoded from base64.
				 */
				std::vector<uint8_t> imageContentFromString(const char* data) const;
		};
	}
}

#endif
