#ifndef MACSA_QT_RASTER_VISITOR_HPP
#define MACSA_QT_RASTER_VISITOR_HPP

#include <QPainter>
#include <QFontDatabase>

#include "dom/documentvisitor.hpp"
#include "dom/rippers/context.hpp"

namespace macsa {
	namespace dot {
		class QtRasterVisitor : public dot::IDocumentVisitor
		{
			public:
				QtRasterVisitor(dot::Document* doc, Context* context, QPainter* painter, uint32_t vres, uint32_t hres, QMap<QString, QColor>& colorsPalette);
				virtual ~QtRasterVisitor() = default;

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
				const dot::Document* _doc;
				Context* _context;
				QPainter* _painter;
				uint32_t _vres;
				uint32_t _hres;
				QFontDatabase _fonts;
				QMap<QString, QColor>& _colorsPalette;
		};
	}
}

#endif
