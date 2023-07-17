#ifndef MACSA_LINX_IMAGE_PARSER_HPP
#define MACSA_LINX_IMAGE_PARSER_HPP

#include "dom/builders/linx/linxparsercontext.hpp"
#include "dom/image.hpp"
#include "objectparser.hpp"
#include "tinyxml2.h"

namespace macsa {
	namespace linx {
		class ImageParser : public ObjectParser
		{
			public:
				ImageParser(dot::Object* image, LinxParserContext& context);
				virtual ~ImageParser() = default;

				bool VisitEnter(const tinyxml2::XMLElement& element, const tinyxml2::XMLAttribute* attribute) override;
				bool VisitExit( const tinyxml2::XMLElement& element) override;

			private:
				dot::Image* _image;
				LinxParserContext& _context;
				dot::Geometry _geometry;
		};
	}
}

#endif
