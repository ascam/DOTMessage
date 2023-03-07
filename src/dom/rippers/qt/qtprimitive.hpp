#ifndef RIPPER_BACKEND_QTPRIMITIVE_HPP
#define RIPPER_BACKEND_QTPRIMITIVE_HPP

#include <vector>
#include <QPainter>
#include <QMap>
#include <QColor>
#include <QString>

#include "qtobject.hpp"
#include "dom/primitives.hpp"

namespace macsa {
	namespace dot {
		class QtPrimitive : public QtObject
		{
			public:
				QtPrimitive(const Primitive* primitive, QPainter& painter, int vres, int hres,
							const ColorsPalette& palette);

			protected:
				virtual QPen getPen() const;
				virtual QBrush getBrush() const;
				virtual void scaleForResolution(QPainter& painter, int angle, QRectF& rect) const;

			private:
				const Primitive* _primitive;
		};
	}
}
#endif
