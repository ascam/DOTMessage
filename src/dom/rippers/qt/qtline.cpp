#include "qtline.hpp"

#include <string>

using macsa::dot::QtLine;
using macsa::dot::NLineStyle;

QtLine::QtLine(const Line* line, QPainter& painter, int vres, int hres, const QMap<QString, QColor>& colorsPalette) :
	QtPrimitive(line, painter, vres, hres, colorsPalette),
	_line(line)
{}

void QtLine::Render()
{
	_painter.save();

	QRectF rect = GetRect();

	int angle = _line->GetGeometry().rotation;
	changePainterCoords(_painter, angle, rect);
	scaleForResolution(_painter, angle, rect);

	_painter.setPen(getPen());
	if (!_line->GetPrintable())	{
		_painter.setOpacity(0.5);
	}
	_painter.drawLine(QPointF(rect.left(), rect.height() / 2), QPointF(rect.right(), rect.height()/2));
	_painter.restore();

#if defined(EDITOR_MODE)
	QtObject::Render();
#endif
}

QPen QtLine::getPen() const
{
	QPen qPen = Qt::NoPen;
	qPen.setCapStyle(Qt::FlatCap);
	qPen.setJoinStyle(Qt::RoundJoin);

	auto pen = _line->GetPen();
	auto color = pen.GetColor();
	if (!_line->GetPrintable())	{
		color.SetAlpha(128);
	}
	qPen.setColor(GetColor(pen.GetColor().GetName().c_str(), pen.GetColor()));

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
				QVector<qreal> dashLine;
				for (auto val : pen.GetStyle().GetCustomDashedPattern()) {
					dashLine << val;
				}
				qPen.setDashPattern(dashLine);
			}
			break;
		default:
			break;
	}
	qPen.setWidth(pen.GetWidth());

	return qPen;
}
