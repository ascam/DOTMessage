#include "qtprimitive.hpp"

#include <string>

using macsa::dot::QtPrimitive;
using macsa::dot::LineStyle;

QtPrimitive::QtPrimitive(const Primitive* primitive, QPainter& painter, int vres, int hres, const ColorsPalette& colorsPalette) :
	QtObject(primitive, painter, vres, hres, colorsPalette),
	_primitive(primitive)
{}

QBrush QtPrimitive::getBrush() const
{
	QBrush brush(Qt::transparent);

	if (_primitive->IsFilled()) {
		brush.setColor(GetColor(_primitive->GetBrush()));
	}

	return brush;
}

void QtPrimitive::scaleForResolution(QPainter &painter, int angle, QRectF &rect) const
{
	double hScale = 1.0, vScale = 1.0;
	bool scale = false;

	if (angle == 90 || angle == 270) {
		if (_vres > _hres) {
			hScale = _vres / _hres;
			scale = true;
		}
		else if (_vres < _hres) {
			vScale = _hres / _vres;
			scale = true;
		}
	}
	else {
		if (_vres > _hres) {
			vScale = _vres / _hres;
			scale = true;
		}
		else if (_vres < _hres) {
			hScale = _hres / _vres;
			scale = true;
		}
	}

	if (scale) {
		rect = QRectF(0, 0, rect.width() / hScale, rect.height() / vScale);
		painter.scale(hScale, vScale);
	}
}

QPen QtPrimitive::getPen() const
{
	QPen qPen = Qt::NoPen;

	if (_primitive->HasBorder()) {
		auto pen = _primitive->GetPen();
		auto color = pen.GetColor();
		if (!_primitive->GetPrintable())	{
			color.SetAlpha(128);
		}
		qPen.setColor(GetColor(pen.GetColor()));

		switch (pen.GetStyle().GetLineStyle()()) {
			case NLineStyle::kSolid:
				qPen.setStyle(Qt::SolidLine);
				break;
			case NLineStyle::kDash:
				qPen.setStyle(Qt::DashLine);
				break;
			case NLineStyle::kDot:
				qPen.setStyle(Qt::DotLine);
				break;
			case NLineStyle::kDashDot:
				qPen.setStyle(Qt::DashDotLine);
				break;
			case NLineStyle::kDashDotDot:
				qPen.setStyle(Qt::DashDotDotLine);
				break;
			case NLineStyle::kCustom:
				{
					qPen.setStyle(Qt::CustomDashLine);
					auto dashValues = pen.GetStyle().GetCustomDashedPattern();

#if (QT_VERSION >= QT_VERSION_CHECK(5, 14, 0)) // fromStdVector is deprecated
					qPen.setDashPattern(QVector<qreal>(dashValues.begin(), dashValues.end()));
#else
					std::vector<qreal> qrealValues(dashValues.begin(), dashValues.end());
					qPen.setDashPattern(QVector<qreal>::fromStdVector(qrealValues));
#endif
				}
			default:
				break;
		}
		qPen.setWidth(pen.GetWidth() + 1);
	}

	return qPen;
}
