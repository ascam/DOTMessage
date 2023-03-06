#ifndef RIPPER_BACKEND_QTDIAMOND_HPP
#define RIPPER_BACKEND_QTDIAMOND_HPP

#include <QPainter>

#include "qtprimitive.hpp"
#include "primitives.hpp"

namespace macsa {
	namespace dot {
		class QtDiamond : public QtPrimitive
		{
			public:
				QtDiamond(const Diamond* diamond, QPainter& painter, int vres, int hres,
						  const ColorsPalette& palette);
				void Render() override;

			private:
				const Diamond* _diamond;
		};
	}
}
#endif
