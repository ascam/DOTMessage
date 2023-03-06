#ifndef RIPPER_BACKEND_QTELLIPSE_HPP
#define RIPPER_BACKEND_QTELLIPSE_HPP

#include <QPainter>
#include <QMap>
#include <QColor>
#include <QString>

#include "qtprimitive.hpp"
#include "primitives.hpp"

namespace macsa {
	namespace dot {
		class QtEllipse : public QtPrimitive
		{
			public:
				QtEllipse(const Ellipse* ellipse, QPainter& painter,
						  int vres, int hres, const ColorsPalette& palette);
				void Render() override;

			private:
				const Ellipse* _ellipse;
		};
	}
}
#endif
