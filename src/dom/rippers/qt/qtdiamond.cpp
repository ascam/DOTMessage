#include <string>

#include <QPolygonF>
#include <QVector>

#include "qtdiamond.hpp"

using macsa::dot::QtDiamond;

QtDiamond::QtDiamond(const Diamond *diamond, QPainter &painter,
					 int vres, int hres, const ColorsPalette &palette) :
	QtPrimitive(diamond, painter, vres, hres, palette),
	_diamond(diamond)
{}

void QtDiamond::Render()
{
	_painter.save();

	QRectF rect = GetRect();

	int angle = _diamond->GetGeometry().rotation;
	changePainterCoords(_painter, angle, rect);
	scaleForResolution(_painter, angle, rect);

	_painter.setBrush(getBrush());
	_painter.setPen(getPen());

	QPolygonF polygon;
	polygon << QPointF(rect.left(), rect.height()/2)
			<< QPointF(rect.width() / 2, rect.top())
			<< QPointF(rect.right(), rect.height()/2)
			<< QPointF(rect.width() / 2, rect.bottom())
			<< QPointF(rect.left(), rect.height()/2);

	if (!_diamond->GetPrintable())	{
		_painter.setOpacity(0.5);
	}
	_painter.drawPolygon(polygon);
	_painter.restore();

#if defined(EDITOR_MODE)
	QtObject::Render();
#endif
}
