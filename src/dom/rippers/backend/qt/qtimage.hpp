#ifndef RIPPER_BACKEND_QTIMAGE_HPP
#define RIPPER_BACKEND_QTIMAGE_HPP

#include <QPainter>
#include <QMap>
#include <QColor>
#include <QString>

#include "qtobject.hpp"
#include "image.hpp"

namespace macsa {
	namespace dot {
		class QtImage : public QtObject
		{
			public:
				QtImage(const Image* image, QPainter& painter,
						int vres, int hres, const ColorsPalette& palette);
				void Render() override;

			private:
				const Image* _image;

				void renderNormal(const QImage& image, const QRectF& rect, QPainter& painter);
				void renderFitToBox(const QImage& image, const QRectF& rect, QPainter& painter) const;
				void renderZoom(const QImage& image, const QRectF& rect, QPainter& painter) const;

				QRectF getImagePortion(const QImage& image) const;
		};
	}
}
#endif
