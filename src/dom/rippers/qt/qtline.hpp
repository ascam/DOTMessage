#ifndef RIPPER_BACKEND_QTLINE_HPP
#define RIPPER_BACKEND_QTLINE_HPP

#include <QPainter>
#include <QMap>
#include <QColor>
#include <QString>

#include "qtprimitive.hpp"
#include "dom/primitives.hpp"

namespace macsa {
	namespace dot {
		class QtLine : public QtPrimitive
		{
			public:
				QtLine(const Line* line, QPainter& painter, int vres, int hres,
					   const ColorsPalette& colorsPalette);
				void Render() override;

			private:
				const Line* _line;

				QPen getPen() const override;
		};
	}
}
#endif
