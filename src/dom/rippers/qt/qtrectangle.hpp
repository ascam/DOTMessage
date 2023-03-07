#ifndef RIPPER_BACKEND_QTRECTANGLE_HPP
#define RIPPER_BACKEND_QTRECTANGLE_HPP

#include <QPainter>
#include <QMap>
#include <QString>
#include <QColor>

#include "qtprimitive.hpp"
#include "dom/primitives.hpp"

namespace macsa {
	namespace dot {
		class QtRectangle : public QtPrimitive
		{
			public:
				QtRectangle(const Rectangle* rectangle, QPainter& painter,
							int vres, int hres, const ColorsPalette& colorsPalette);
				void Render() override;

			private:
				const Rectangle* _rectangle;
		};
	}
}
#endif
