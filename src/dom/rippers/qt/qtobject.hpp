#ifndef RIPPER_BACKEND_QTOBJECT_HPP
#define RIPPER_BACKEND_QTOBJECT_HPP

#include <QPainter>
#include <QMap>
#include <QString>
#include <QColor>

#include "dom/object.hpp"

constexpr double kMMPerInch = 25.4;

namespace macsa {
	namespace dot {
		class QtObject
		{
			public:
				using ColorsPalette = QMap<QString, QColor>;

				QtObject(const Object* obj, QPainter& painter, int vres, int hres,
						 const ColorsPalette& palette);

				virtual void Render();
				QRectF GetRect();
				QPointF GetTopLeft();

			protected:
				QPainter& _painter;
				const Object* _obj;
				int _vres;
				int _hres;
				const ColorsPalette& _colorsPalette;

				void drawRect(const QRectF& rect, Qt::GlobalColor color = Qt::black,
							  Qt::PenStyle style = Qt::SolidLine, int width = 1);

				/**
				 * @brief changePainterCoords Move and rotate the given painter and modify the given rect to fit the equivalent
				 * rect without translatin or rotating the painter
				 */
				void changePainterCoords(QPainter& painter, int angle, QRectF& rect) const;

				/**
				 * @brief GetColor Direct access to color from palette. If color name doesn't found returns black
				 */
				QColor GetColor(const Color& color) const;
		};
	}
}

#endif
