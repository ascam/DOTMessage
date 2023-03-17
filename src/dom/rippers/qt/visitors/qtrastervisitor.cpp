#include "qtrastervisitor.hpp"

#include "dom/text.hpp"
#include "dom/barcode.hpp"
#include "dom/primitives.hpp"
#include "dom/image.hpp"

#include "dom/rippers/qt/qtline.hpp"
#include "dom/rippers/qt/qttext.hpp"
#include "dom/rippers/qt/qtimage.hpp"
#include "dom/rippers/qt/qtbarcode.hpp"
#include "dom/rippers/qt/qtdiamond.hpp"
#include "dom/rippers/qt/qtellipse.hpp"
#include "dom/rippers/qt/qtrectangle.hpp"

#include "utils/macsalogger.hpp"

using macsa::dot::Document;
using macsa::utils::MacsaLogger;
using macsa::dot::QtRasterVisitor;

QtRasterVisitor::QtRasterVisitor(dot::Document* doc, Context* context, QPainter* painter, uint32_t vres, uint32_t hres, QMap<QString, QColor>& colorsPalette) :
	dot::IDocumentVisitor(),
	_doc(doc),
	_context{context},
	_painter{painter},
	_vres{vres},
	_hres{hres},
	_colorsPalette(colorsPalette)
{}

bool QtRasterVisitor::VisitEnter(const dot::Text& text)
{
	QtText label(&text, *_painter, _fonts, _vres, _hres, _colorsPalette);
	label.Render();

	return true;
}

bool QtRasterVisitor::VisitEnter(const dot::Barcode& barcode)
{
	QtBarcode qBarcode(&barcode, *_painter, _vres, _hres, _colorsPalette);
	qBarcode.Render();

	return true;
}

bool QtRasterVisitor::Visit(const dot::Image& image)
{
	QtImage qImage(&image, *_painter, _vres, _hres, _colorsPalette);
	qImage.Render();

	return true;
}

bool QtRasterVisitor::Visit(const dot::Rectangle& rectangle)
{
	QtRectangle qRectangle(&rectangle, *_painter, _vres, _hres, _colorsPalette);
	qRectangle.Render();

	return true;
}

bool QtRasterVisitor::Visit(const dot::Ellipse& ellipse)
{
	QtEllipse qEllipse(&ellipse, *_painter, _vres, _hres, _colorsPalette);
	qEllipse.Render();

	return true;
}

bool QtRasterVisitor::Visit(const dot::Diamond& diamond)
{
	QtDiamond qDiamond(&diamond, *_painter, _vres, _hres, _colorsPalette);
	qDiamond.Render();

	return true;
}

bool QtRasterVisitor::Visit(const dot::Line& line)
{
	QtLine qLine(&line, *_painter, _vres, _hres, _colorsPalette);
	qLine.Render();

	return true;
}

bool QtRasterVisitor::Visit(const CounterDataSource& counter)
{
	return true;
}

bool QtRasterVisitor::Visit(const DatabaseDataSource& database)
{
	return true;
}

bool QtRasterVisitor::Visit(const DateTimeDataSource& datetime)
{
	return true;
}

bool QtRasterVisitor::Visit(const UserInputDataSource& userInput)
{
	return true;
}

bool QtRasterVisitor::Visit(const CompositeDataSource& composite)
{
	return true;
}
