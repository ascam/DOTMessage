#ifndef MACSA_LINX_PARSER_CONTEXT_HPP
#define MACSA_LINX_PARSER_CONTEXT_HPP

#include "dom/document.hpp"
#include <string>

namespace macsa {
	namespace linx {
		class LinxParserContext
		{
			public:
				LinxParserContext(dot::Document& doc);
				~LinxParserContext() = default;

				dot::Document& GetDocument() const;

				void SetUnits(const std::string& units);
				void SetUnitsRatio(double ratio);
				double ConvertUnits(double units);
				dot::Geometry CheckGeometry(dot::Geometry geometry);
				//dot::Geometry ConvertGeometry(const dot::Geometry& geometry) {

				//	dot::Geometry convertedGeometry{};
				//	convertedGeometry.position.x  = ConvertUnits(geometry.position.x);
				//	convertedGeometry.position.y  = ConvertUnits(geometry.position.y);
				//	convertedGeometry.size.height = ConvertUnits(geometry.size.height);
				//	convertedGeometry.size.width  = ConvertUnits(geometry.size.width);
				//	convertedGeometry.rotation = geometry.rotation;
				//	return convertedGeometry;
				//}

			private:
				dot::Document& _doc;
				std::string _units; // Smart enum?
				double _unitsRatio;
		};
	}
}

#endif
