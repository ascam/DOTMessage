#ifndef MACSA_NISX_PRIMITIVES_VISITOR_HPP
#define MACSA_NISX_PRIMITIVES_VISITOR_HPP

#include "dom/documentvisitor.hpp"
#include "objectvisitor.hpp"

namespace macsa {
	namespace nisx {

		class PrimitivesVisitor :  public dot::IDocumentVisitor, public ObjectVisitor
		{
			public:
				PrimitivesVisitor(tinyxml2::XMLDocument& document, tinyxml2::XMLElement* parent, const dot::Document& dom);
				virtual ~PrimitivesVisitor() = default;

				/**
				 * @brief Visit. Visits a rectangle object
				 * @param rectangle: Rectangle object to visit.
				 * @return true to continue the hierarchical visit, false to stop.
				 */
				bool Visit(const dot::Rectangle& rectangle) override;

				/**
				 * @brief Visit. Visits an ellipse object
				 * @param ellipse: Ellipse object to visit.
				 * @return true to continue the hierarchical visit, false to stop.
				 */
				bool Visit(const dot::Ellipse& ellipse) override;

				/**
				 * @brief Visit. Visits a diamond object
				 * @param diamond: Diamond object to visit.
				 * @return true to continue the hierarchical visit, false to stop.
				 */
				bool Visit(const dot::Diamond& diamond) override;

				/**
				 * @brief Visit. Visits a line object
				 * @param line: line object to visit.
				 * @return true to continue the hierarchical visit, false to stop.
				 */
				bool Visit(const dot::Line& line) override;

			protected:
				const dot::Document& _dom;
				tinyxml2::XMLElement* _xmlParent;
				tinyxml2::XMLElement* _xmlElement;

				bool buildPrimitiveField(const std::string& type, const dot::Primitive& primitive);
				bool writePen(const dot::Pen& pen, tinyxml2::XMLElement* parent) const;
				bool writePoligonsProperties(const dot::Primitive& primitive, tinyxml2::XMLElement* parent) const;
				bool writeColor(const dot::Color& color, tinyxml2::XMLElement* parent) const;
				dot::Color getColor(const std::string& name) const;
		};
	}
}

#endif
