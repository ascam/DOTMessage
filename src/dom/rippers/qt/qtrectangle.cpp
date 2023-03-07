#include "qtrectangle.hpp"

#include <string>

using macsa::dot::QtRectangle;
using macsa::dot::NLineStyle;

QtRectangle::QtRectangle(const Rectangle* rectangle, QPainter& painter,
						 int vres, int hres, const ColorsPalette& colorsPalette) :
	QtPrimitive(rectangle, painter, vres, hres, colorsPalette),
	_rectangle(rectangle)
{}

void QtRectangle::Render()
{
	_painter.save();

	QRectF rect = GetRect();

	int angle = _rectangle->GetGeometry().rotation;
	changePainterCoords(_painter, angle, rect);
	scaleForResolution(_painter, angle, rect);

	_painter.setBrush(getBrush());
	_painter.setPen(getPen());

	if (!_rectangle->GetPrintable())	{
		_painter.setOpacity(0.5);
	}
	_painter.drawRect(rect);
	_painter.restore();

#if defined(EDITOR_MODE)
	QtObject::Render();
#endif
}
