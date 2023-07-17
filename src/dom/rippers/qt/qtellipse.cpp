#include "qtellipse.hpp"

#include <string>

using macsa::dot::QtEllipse;

QtEllipse::QtEllipse(const Ellipse* ellipse, QPainter& painter,
					 int vres, int hres, const ColorsPalette& palette) :
	QtPrimitive(ellipse, painter, vres, hres, palette),
	_ellipse(ellipse)
{}

void QtEllipse::Render()
{
	_painter.save();

	QRectF rect = GetRect();

	int angle = _ellipse->GetGeometry().rotation;
	changePainterCoords(_painter, angle, rect);
	scaleForResolution(_painter, angle, rect);

	_painter.setBrush(getBrush());
	_painter.setPen(getPen());
	if (!_ellipse->GetPrintable())	{
		_painter.setOpacity(0.5);
	}
	_painter.drawEllipse(rect);
	_painter.restore();

#if defined(EDITOR_MODE)
	QtObject::Render();
#endif
}
