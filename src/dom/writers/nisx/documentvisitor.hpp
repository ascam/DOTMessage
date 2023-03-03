#ifndef MACSA_NISX_DOCUMENT_VISITOR_HPP
#define MACSA_NISX_DOCUMENT_VISITOR_HPP

#include "dom/documentvisitor.hpp"
#include "tinyxml2.h"

namespace macsa {
	namespace nisx {
		class DocumentVisitor : public dot::IDocumentVisitor
		{
			public:
				DocumentVisitor(tinyxml2::XMLDocument& xmlDocument, const dot::Document& dom);
				virtual ~DocumentVisitor() = default;

				/**
				 * @brief VisitEnter. Start the visit in the DOM document
				 * @param document: DOM document to visit.
				 * @return true to continue the hierarchical visit, false to stop.
				 */
				bool VisitEnter(const dot::Document&) override;

				/**
				 * @brief VisitExit. Exits the visit in the DOM document
				 * @param document: DOM document to visit.
				 * @return true to continue the hierarchical visit, false to stop.
				 */
				bool VisitExit(const dot::Document&) override;

				/**
				 * @brief VisitEnter. Start the visit in a Text object
				 * @param text: Text object to visit.
				 * @return true to continue the hierarchical visit, false to stop.
				 */
				bool VisitEnter(const dot::Text&) override;

				/**
				 * @brief VisitEnter. Start the visit in a Barcode object
				 * @param barcode: Barcode object to visit.
				 * @return true to continue the hierarchical visit, false to stop.
				 */
				bool VisitEnter(const dot::Barcode& barcode) override;

				/**
				 * @brief Visit. Visits a Image object
				 * @param image: Image object to visit.
				 * @return true to continue the hierarchical visit, false to stop.
				 */
				bool Visit(const dot::Image& image) override;

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

			private:
				const dot::Document& _dom;
				tinyxml2::XMLDocument& _xmlDocument;
				tinyxml2::XMLElement* _xmlFields;

				bool writeProperties(tinyxml2::XMLElement* parent, const dot::Document& document);
				bool writeColorsPallete(tinyxml2::XMLElement* parent, const dot::Document& document);
		};
	}
}

#endif
