#include <string>

#include "qtobject.hpp"

using macsa::dot::QtObject;

QtObject::QtObject(const Object* obj, QPainter& painter, int vres, int hres, const ColorsPalette& palette) :
	_painter(painter),
	_obj(obj),
	_vres(vres),
	_hres(hres),
	_colorsPalette(palette)
{}

QRectF QtObject::GetRect()
{
	Geometry geo = _obj->GetGeometry();
	double hratio = _hres / kMMPerInch;
	double vratio = _vres / kMMPerInch;

	return QRectF(QPointF(geo.position.x * hratio, geo.position.y * vratio),
				  QSize(geo.size.width * hratio, geo.size.height * vratio));
}

void QtObject::Render()
{
	if (_obj->GetSelected()) {
		_painter.save();
		_painter.setBrush(Qt::transparent);
		QPen pen;
		pen.setColor(QColor(255,0,0,255));
		_painter.setPen(pen);
		_painter.drawRect(GetRect());
		_painter.restore();
	}
}

void QtObject::drawRect(const QRectF &rect, Qt::GlobalColor color, Qt::PenStyle style, int width)
{
	_painter.save();
	_painter.setBrush(Qt::transparent);
	QPen pen;
	pen.setColor(color);
	pen.setWidth(width);
	pen.setStyle(style);
	_painter.setPen(pen);
	_painter.drawRect(rect);
	_painter.restore();
}

void QtObject::changePainterCoords(QPainter &painter, int angle, QRectF& rect) const
{
	switch (angle) {
		case 0:
			painter.translate(rect.x(), rect.y());
			rect = QRectF(0, 0, rect.width(), rect.height());
			break;
		case 90:
			painter.translate(rect.x() + rect.width(), rect.y());
			rect = QRectF(0, 0, rect.height(), rect.width());
			break;
		case 180:
			painter.translate(rect.x() + rect.width(), rect.y() + rect.height());
			rect = QRectF(0, 0, rect.width(), rect.height());
			break;
		case 270:
			painter.translate(rect.x(), rect.y() + rect.height());
			rect = QRectF(0, 0, rect.height(), rect.width());
			break;
		default:
			break;
	}
	if (angle) {
		painter.rotate(angle);
	}
}

QColor QtObject::GetColor(const Color& color) const
{
	QColor returnValue;

	if (_colorsPalette.find(color.GetName().c_str()) != _colorsPalette.end()) {
		returnValue = _colorsPalette[color.GetName().c_str()];
	}
	else	{
		returnValue = {color.GetRed(), color.GetGreen(), color.GetBlue(), color.GetAlpha()};
	}

	return returnValue;
}
