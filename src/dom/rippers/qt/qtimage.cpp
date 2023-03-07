#include "qtimage.hpp"

#include <string>

#include <QImage>
#include <QRectF>

using macsa::dot::QtImage;
using macsa::dot::ImageBoxAdjustment;

QtImage::QtImage(const Image* image, QPainter& painter, int vres, int hres, const ColorsPalette& palette) :
	QtObject(image, painter, vres, hres, palette),
	_image(image)
{}

void QtImage::Render()
{
	_painter.save();

	QRectF rect = GetRect();
	// Move painter and rotate painter to equivalent top left corner of the image
	changePainterCoords(_painter, _image->GetGeometry().rotation, rect);
	const std::vector<uint8_t>& rawData = _image->GetData();
	QImage img;
	img.loadFromData(rawData.data(), rawData.size());

	if (!_image->GetPrintable())	{
		_painter.setOpacity(0.5);
	}

	switch (_image->GetBoxAdjustment()()) {
		case NImageBoxAdjustment::kNormal:
			renderNormal(img, rect, _painter);
			break;
		case NImageBoxAdjustment::kFitToBox:
			renderFitToBox(img, rect, _painter);
			break;
		case NImageBoxAdjustment::kZoom:
			renderZoom(img, rect, _painter);
			break;
	}

	_painter.restore();

#if defined(EDITOR_MODE)
	QtObject::Render();
#endif
}
void QtImage::renderNormal(const QImage& image, const QRectF& rect, QPainter& painter)
{
	// Get the portion rect of the image to render
	QRectF portion = getImagePortion(image);
	painter.drawImage(rect, image, portion);
}

void QtImage::renderFitToBox(const QImage& image, const QRectF& rect, QPainter& painter) const
{
	painter.drawImage(rect, image);
}

void QtImage::renderZoom(const QImage& image, const QRectF& rect, QPainter& painter) const
{
	painter.save();

	float w = image.width();
	float h = image.height();
	int angle = _image->GetGeometry().rotation;
	if (angle == 90 || angle == 270) {
		if (_vres > _hres) {
			w *= _vres / _hres;
		}
		else if (_vres < _hres) {
			h *= _hres / _vres;
		}
	}
	else {
		if (_vres > _hres) {
			h *= _vres / _hres;
		}
		else if (_vres < _hres) {
			w *= _hres / _vres;
		}
	}

	float ratioW = w / rect.width();
	float ratioH = h / rect.height();

	float maxRatio = std::max(ratioW, ratioH);

	float width = w / maxRatio;
	float height = h / maxRatio;


	QRectF target(QPointF(rect.width() / 2 - width / 2, rect.height() / 2 - height / 2),
				  QSizeF(width, height));
	painter.drawImage(target, image);

	painter.restore();
}

QRectF QtImage::getImagePortion(const QImage &image) const
{
	double w = static_cast<double>(image.width()) / image.logicalDpiX();  // image width in inches
	double h = static_cast<double>(image.height()) / image.logicalDpiY(); // image height in inches
	auto geo = _image->GetGeometry();
	double rw = geo.size.width / kMMPerInch;  // Item width in inches
	double rh = geo.size.height / kMMPerInch; // Item height in inches
	double wSizeRatio = rw / w;
	double hSizeRatio = rh / h;

	QRectF portion(QPointF(0, 0),
				   QSizeF(static_cast<double>(image.width())  * wSizeRatio,
						  static_cast<double>(image.height()) * hSizeRatio));

	auto verticalAlignment = _image->GetVerticalAlignment();
	auto horitzontalAlignment = _image->GetHorizontalAlignment();


	if (verticalAlignment == NVerticalAlignment::kTop && horitzontalAlignment == NHorizontalAlignment::kLeft) {
		portion.moveTopLeft(QPointF(0,0));
		portion.moveLeft(0);
	}
	else if (verticalAlignment == NVerticalAlignment::kTop && horitzontalAlignment == NHorizontalAlignment::kCenter) {
		portion.moveCenter(QPointF(image.rect().center()));
		portion.moveTop(0);
	}
	else if (verticalAlignment == NVerticalAlignment::kTop && horitzontalAlignment == NHorizontalAlignment::kRight) {
		portion.moveRight(image.rect().right());
		portion.moveTop(0);
	}
	else if (verticalAlignment == NVerticalAlignment::kMiddle && horitzontalAlignment == NHorizontalAlignment::kLeft) {
		portion.moveCenter(QPointF(image.rect().center()));
		portion.moveLeft(0);
	}
	else if (verticalAlignment == NVerticalAlignment::kMiddle && horitzontalAlignment == NHorizontalAlignment::kCenter) {
		portion.moveCenter(QPointF(image.rect().center()));
	}
	else if (verticalAlignment == NVerticalAlignment::kMiddle && horitzontalAlignment == NHorizontalAlignment::kRight) {
		portion.moveCenter(QPointF(image.rect().center()));
		portion.moveRight(image.rect().right());
	}
	else if (verticalAlignment == NVerticalAlignment::kBottom && horitzontalAlignment == NHorizontalAlignment::kLeft) {
		portion.moveBottom(image.rect().bottom());
		portion.moveLeft(0);
	}
	else if (verticalAlignment == NVerticalAlignment::kBottom && horitzontalAlignment == NHorizontalAlignment::kCenter) {
		portion.moveCenter(QPointF(image.rect().center()));
		portion.moveBottom(image.rect().bottom());
	}
	else if (verticalAlignment == NVerticalAlignment::kBottom && horitzontalAlignment == NHorizontalAlignment::kRight) {
		portion.moveBottom(image.rect().bottom());
		portion.moveRight(image.rect().right());
	}

	return portion;
}
