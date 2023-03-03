#ifndef MACSA_NISX_IMAGE_VISITOR_HPP
#define MACSA_NISX_IMAGE_VISITOR_HPP

#include "dom/documentvisitor.hpp"
#include "objectvisitor.hpp"

namespace macsa {
	namespace nisx {

		class ImageVisitor :  public dot::IDocumentVisitor, public ObjectVisitor
		{
			public:
				ImageVisitor(tinyxml2::XMLDocument& document, tinyxml2::XMLElement* parent);
				virtual ~ImageVisitor() = default;

				/**
				 * @brief Visit. Visits a Image object
				 * @param image: Image object to visit.
				 * @return true to continue the hierarchical visit, false to stop.
				 */
				virtual bool Visit(const dot::Image& image);

			protected:
				tinyxml2::XMLElement* _xmlParent;
				tinyxml2::XMLElement* _xmlElement;

				/**
				 * @brief contentToBase64. Convert a byte vector to an string in
				 * a base64 encoded data.
				 * @param content: uint8_t vector with the content of the file
				 * @return returns a string with the content of the vector.
				 */
				std::string contentToBase64(const std::vector<uint8_t>& content) const;

//				bool writeColor(const dot::Color& color, tinyxml2::XMLElement* xmlColor) const;
		};
	}
}

#endif
