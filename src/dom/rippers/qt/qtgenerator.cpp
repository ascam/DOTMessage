#include "qtgenerator.hpp"
#include "dom/rippers/qt/qtobject.hpp"

#include <cmath>
#include <chrono>
#ifndef BACKEND_QT_NATIVE
#include <QApplication>
#endif
#include <QFontDatabase>
#include <QPaintDevice>
#include <QDir>
#include <QDataStream>

#include "utils/macsalogger.hpp"
#include "utils/stringutils.hpp"

using macsa::dot::QtGenerator;
using namespace macsa::utils;

#ifndef BACKEND_QT_NATIVE
#if defined (ZYNQ)
const int numArgs = 3;
const char* argv[numArgs] = {"DOTRipperQt", "-platform", "offscreen"};
int argc = numArgs;
#elif defined (ARM) || defined(LOCO)
const int numArgs = 2;			// TODO(iserra): Review
const char* argv[numArgs] = {"DOTRipperQt", "-qws"}; // TODO(iserra): Review
int argc = numArgs;
#else
const int numArgs = 0;			// TODO(iserra): Review
const char* argv[1] = {nullptr}; // TODO(iserra): Review
int argc = numArgs;
#endif
#endif

// look up table to invert bytes
constexpr uint8_t lookupTable[16] = {
	0x0, 0x8, 0x4, 0xc, 0x2, 0xa, 0x6, 0xe,
	0x1, 0x9, 0x5, 0xd, 0x3, 0xb, 0x7, 0xf
};

QtGenerator::QtGenerator() : BitmapGenerator(),
#ifndef BACKEND_QT_NATIVE
	_app(argc, const_cast<char**>(argv)),
	_idth(std::this_thread::get_id()),
#endif
	_bgColor(Qt::white),
	_colorsPalette()
{}

QtGenerator::~QtGenerator()
{
#ifndef BACKEND_QT_NATIVE
	if (std::this_thread::get_id() != _idth) {
		ELog() << "Invalid thread. QtGenerator must be managed in the same thread" << std::endl << " This Generator was created in the thread: "
	#ifdef THREADS_MAP
			   << "\"" << ThreadsMap::instance().GetThreadName(_idth) << "\"";
	#else
			   << "0x" << std::hex << _idth;
	#endif
	}
	_app.quit();
#endif

}

uint32_t QtGenerator::GetWidth() const
{
	return _pixmap.width();
}

uint32_t QtGenerator::GetHeight() const
{
	return _pixmap.height();
}

int QtGenerator::GetRawData(bitmap& buff) const
{
	QImage img = _pixmap.toImage().convertToFormat(QImage::Format_Mono, Qt::ThresholdDither);
	unsigned size = img.height() * img.bytesPerLine();
	buff.clear();
	buff.reserve(size);
	bitmap::iterator it = buff.begin();
	for (int y = 0; y < img.height(); y++) {
		uint8_t *raw = new uint8_t[img.bytesPerLine()];
		if (raw) {
			memcpy(img.scanLine(y), raw, img.bytesPerLine());
			bitmap line(raw, raw + img.bytesPerLine());
			buff.insert(it, line.begin(), line.end());
			it += line.size();
			delete [] raw;
		}
	}

	return buff.size();
}

void QtGenerator::GetBitmapMono(bitmap& buffer, bool invertBytes) const
{
	if (_pixmap.isNull()) {
		WLog() << "Unable to get buffer. Invalid pixmap pointer";
		return;
	}

	QImage img = _pixmap.toImage().convertToFormat(QImage::Format_Mono, Qt::ThresholdDither);
	// TODO(jpinyot): Compare printig using QImage::Format_Mono and invertBytes() with
	// QImage::Format_MonoLSB

	// rotate image
	//	if (!_rotated) {
	//		WLog() << __FUNCTION__ << "Weird rotation required. Getting single buffer of a non rotated image.";
	//		img = img.transformed(QTransform().rotate(90), Qt::SmoothTransformation);
	//	}

	// get a const pointer to the firts bit of the image
	auto bits = img.constBits();
	if (bits == nullptr) {return; }
	// get bytes count from image
#if QT_VERSION_MAJOR >= 5
	auto size = img.sizeInBytes();
#else
	auto size = img.byteCount();
#endif
	// clear buffer and reseve space
	buffer.clear();
	buffer = bitmap(size, 0);

	// set image to buffer
	for (int i = 0; i < size; i++) {
		auto bit = invertBytes ? invertByte(bits[i]) : bits[i];
		buffer[i] = bit;
	}
}

void QtGenerator::GetDoubleColBitmapMono(bitmap& buffer1, bitmap& buffer2,
										 uint32_t colOffset, bool invertBytes) const
{
	QImage img = _pixmap.toImage().convertToFormat(QImage::Format_Mono, Qt::ThresholdDither);

	// get buffer size
#if QT_VERSION_MAJOR >= 5
	auto bufferSize = (img.sizeInBytes() / 2) + (colOffset * img.height());
#else
	auto bufferSize = (img.byteCount() / 2) + (colOffset * img.height());
#endif

	// get count of bytes per line
	auto bytesPerLine = img.bytesPerLine();
	// clear buffers and reseve space
	buffer1.clear();
	buffer1 = bitmap(bufferSize, 0);
	buffer2.clear();
	buffer2 = bitmap(bufferSize, 0);

	// set buffer iterator to zero
	uint32_t buffer1It = 0;
	uint32_t buffer2It = colOffset;

	for (int i = 0; i < img.height(); i++) {
		// get image data from current line
		const auto bits = img.constScanLine(i);
		if (bits == nullptr) {return; }

		// insert line to buffer one
		if (i % 2) {
			buffer1It += insertLine(bits, bytesPerLine, buffer1, buffer1It, false);
		}
		// insert line to buffer two
		else {
			buffer2It += insertLine(bits, bytesPerLine, buffer2, buffer2It, false);
			buffer2It += colOffset;
		}
	}
}

std::pair<QSize, QPoint> QtGenerator::getOutOfCanvasBounds(Document* doc)
{
	float canvasWidth = doc->GetCanvasWidth();
	float canvasHeight = doc->GetCanvasHeight();

	float canvasXOffset = 0.;
	float canvasYOffset = 0.;

	const auto& objects = doc->GetObjects();

	auto itMaxXObj = std::max_element(objects.cbegin(), objects.cend(), [](const auto& obj1, const auto& obj2){
		return (obj1->GetGeometry().position.x + obj1->GetGeometry().size.width) < (obj2->GetGeometry().position.x + obj2->GetGeometry().size.width);
	});

	if (itMaxXObj != objects.cend())	{
		auto geometry = (*itMaxXObj)->GetGeometry();
		if ((geometry.position.x + geometry.size.width) > canvasWidth)	{
			canvasWidth = (geometry.position.x + geometry.size.width);
		}
	}

	auto itMaxYObj = std::max_element(objects.cbegin(), objects.cend(), [](const auto& obj1, const auto& obj2){
		return (obj1->GetGeometry().position.y + obj1->GetGeometry().size.height) < (obj2->GetGeometry().position.y + obj2->GetGeometry().size.height);
	});

	if (itMaxYObj != objects.cend())	{
		auto geometry = (*itMaxYObj)->GetGeometry();
		if ((geometry.position.y + geometry.size.height) > canvasHeight )	{
			canvasHeight = (geometry.position.y + geometry.size.height);
		}
	}

	auto itMinXObj = std::min_element(objects.cbegin(), objects.cend(), [](const auto& obj1, const auto& obj2){
		return obj1->GetGeometry().position.x < obj2->GetGeometry().position.x;
	});

	if (itMinXObj != objects.cend())	{
		auto geometry = (*itMinXObj)->GetGeometry();
		if (geometry.position.x < 0)	{
			_canvasOffset.setX(geometry.position.x);
			canvasXOffset = -geometry.position.x;
			canvasWidth += -geometry.position.x;
		}
	}

	auto itMinYObj = std::max_element(objects.cbegin(), objects.cend(), [](const auto& obj1, const auto& obj2){
		return obj1->GetGeometry().position.y > obj2->GetGeometry().position.y;
	});

	if (itMinYObj != objects.cend())	{
		auto geometry = (*itMinYObj)->GetGeometry();
		if (geometry.position.y < 0)	{
			_canvasOffset.setY(geometry.position.y);
			canvasYOffset = -geometry.position.y;
			canvasHeight += -geometry.position.y;
		}
	}

	int canvasPixelWidth = std::round(GetHorizontalResolution() * (canvasWidth / kMMPerInch));
	int canvasPixelHeight = std::round(GetVerticalResolution() * (canvasHeight / kMMPerInch));

	int canvasPixelXOffset = std::round(GetHorizontalResolution() * (canvasXOffset / kMMPerInch));
	int canvasPixelYOffset = std::round(GetVerticalResolution() * (canvasYOffset/ kMMPerInch));

	QPoint point{canvasPixelXOffset, canvasPixelYOffset};
	QSize size{canvasPixelWidth, canvasPixelHeight};

	return {size, point};
}

void QtGenerator::Update(Document* doc, Context* context, bool editorMode)
{
	if (doc == nullptr || context == nullptr) {
		ELog() << "Invalid DOM";
		return;
	}

	int canvasWidth = std::round(GetHorizontalResolution() * (doc->GetCanvasWidth() / kMMPerInch));
	int canvasHeight = std::round(GetVerticalResolution() * (doc->GetCanvasHeight() / kMMPerInch));

	int viewportWidth = 0;
	int viewportHeight = 0;

	int canvasXOffset = 0;
	int canvasYOffset = 0;

	_canvasOffset.setX(0.);
	_canvasOffset.setY(0.);

	if (editorMode)	{
		auto&& canvasOffset = getOutOfCanvasBounds(doc);

		viewportWidth = canvasOffset.first.width();
		viewportHeight = canvasOffset.first.height();

		canvasXOffset = canvasOffset.second.x();
		canvasYOffset = canvasOffset.second.y();
	}
	else	{
		viewportWidth = std::round(GetHorizontalResolution() * ((doc->GetViewportWidth() ? doc->GetViewportWidth(): doc->GetCanvasWidth()) / kMMPerInch));
		viewportHeight = std::round(GetVerticalResolution() * ((doc->GetViewportHeight() ? doc->GetViewportHeight() : doc->GetCanvasHeight())  / kMMPerInch));
	}

	if (doc->GetCanvasRotation() == 90 || doc->GetCanvasRotation() == 270) {
		std::swap(viewportWidth, viewportHeight);
		std::swap(canvasWidth, canvasHeight);
	}

	QPixmap pixmap(viewportWidth, viewportHeight);
	pixmap.fill(_bgColor);

	_pixmap = std::move(pixmap);

	_colorsPalette.clear();
	const auto& palette = doc->GetColorsPalette();
	for (const auto& color : palette) {
		_colorsPalette.insert(color.first.c_str(), QColor(color.second.GetRed(), color.second.GetGreen(), color.second.GetBlue(), color.second.GetAlpha()));
	}

	QPainter painter(&_pixmap);
	painter.save();

	if (doc->GetViewportWidth() != 0. && doc->GetViewportHeight() != 0. && !editorMode) {
		canvasXOffset = std::round(GetHorizontalResolution() * (doc->GetCanvasXOffset() / kMMPerInch));
		canvasYOffset = std::round(GetVerticalResolution() * (doc->GetCanvasYOffset() / kMMPerInch));
	}
	if (!editorMode) {
		painter.setClipRect(QRectF(canvasXOffset, canvasYOffset, canvasWidth, canvasHeight), Qt::IntersectClip);
	}

	if (canvasXOffset != 0. || canvasYOffset != 0.)	{
		QTransform transformation;
		transformation.translate(canvasXOffset, canvasYOffset);
		painter.setTransform(transformation);
	}

	painter.setRenderHint(QPainter::HighQualityAntialiasing);

	if (doc->GetCanvasRotation() == 90) {
		painter.translate(QPointF(canvasWidth, 0));
		painter.rotate(doc->GetCanvasRotation());
	}

	if (_bgColor != Qt::white)	{
		QBrush brush(Qt::white);
		painter.setBrush(brush);
		painter.setPen(Qt::white);
		painter.drawRect(0, 0, canvasWidth, canvasHeight);
	}



	classifyObjects(doc->GetObjects());
	QtRasterVisitor visitor(doc, context, &painter, _vres, _hres, _colorsPalette);
	renderFixedFields(&visitor);
	renderVariableFields(&visitor);
	painter.restore();
}

void QtGenerator::UpdateVariableFields(Document* doc, Context* context)
{
	if (doc == nullptr) {
		WLog() << "Invalid DOM";
		return;
	}

	// Restore the full pixmap with the stored fixed pixmap
	_pixmap = _pixmapFixed;

	// Points the painter to the base pixmap
	QPainter painter(&_pixmap);
	painter.setRenderHint(QPainter::HighQualityAntialiasing);
	painter.setBackgroundMode(Qt::OpaqueMode);
	painter.setBackground(QBrush(Qt::white));

	QtRasterVisitor visitor(doc, context, &painter, _vres, _hres, _colorsPalette);
	classifyObjects(doc->GetObjects());
	renderVariableFields(&visitor);
}

void QtGenerator::SaveToBmpFile(const std::string& filename)
{
	if (!_pixmap.isNull() && _pixmap.width() > 0 &&	_pixmap.height() > 0)	{
		_pixmap.save(filename.c_str()) ;
	}
}

void QtGenerator::Clear()
{
	_colorsPalette.clear();
	_pixmap = QPixmap();
}

void QtGenerator::AddFontsDirectory(const std::string& fullpath)
{
	QDir fonts(fullpath.c_str());
	QStringList fontsFiles = fonts.entryList();
	for (auto& font : fontsFiles) {
		#if (QT_VERSION >= QT_VERSION_CHECK(5, 0, 0))
			QFontDatabase::addApplicationFont(QString("%1/%2").arg(fonts.canonicalPath(), font));
		#else
			QFontDatabase::addApplicationFont(QString("%1/%2").arg(fonts.canonicalPath()).arg(font));
		#endif
	}
}

void QtGenerator::AddFontFamily(const std::string& fullpath)
{
	QFontDatabase::addApplicationFont(fullpath.c_str());
}

void QtGenerator::SetBackgroundColorFromRGBA(const std::string& rgba)
{
	const int byteLenght = 2;
	if (rgba.size() == 9 && stringutils::StartsWith(rgba, "#")) {
		int red = stringutils::HexToUInt(rgba.substr(1, byteLenght));
		int green = stringutils::HexToUInt(rgba.substr(3, byteLenght));
		int blue = stringutils::HexToUInt(rgba.substr(5, byteLenght));
		int alpha = stringutils::HexToUInt(rgba.substr(7, byteLenght));

		_bgColor = QColor(red, green, blue, alpha);
	}
}

void QtGenerator::SetBackgroundColorFromRGBA(uint32_t rgba)
{
	int red   = (rgba >> 24) & 0xFF;
	int green = (rgba >> 16) & 0xFF;
	int blue  = (rgba >> 8)  & 0xFF;
	int alpha = rgba & 0xFF;

	_bgColor = QColor(red, green, blue, alpha);
}

void QtGenerator::classifyObjects(const std::deque<Object*>& objects)
{
	_variableObjects.clear();
	_fixedObject.clear();

	for (const auto object : objects) {
		if (object->GetPrintable() || _printHiddenItems) {
			if(object->IsVariable()) {
				_variableObjects.push_back(object);
			}
			else {
				_fixedObject.push_back(object);
			}
		}
	}
}

void QtGenerator::renderFixedFields(QtRasterVisitor* visitor)
{
	for (const auto obj : _fixedObject) {
		obj->Accept(visitor);
	}

	_pixmapFixed = _pixmap;
}

void QtGenerator::renderVariableFields(QtRasterVisitor* visitor)
{
	for (const auto obj : _variableObjects) {
		obj->Accept(visitor);
	}
}

uint8_t QtGenerator::invertByte(uint8_t byte) const
{
	// invert bytes using a lookup table
	return (lookupTable[byte &  0x0F] << 4) | lookupTable[byte >> 4];
}

uint32_t QtGenerator::insertLine(const uchar* bytes, uint32_t size, bitmap& buffer,
								 uint32_t pos, bool invertBytes) const
{
	// check for correct input arguments
	if (bytes == nullptr) {return 0;}

	uint32_t bufferIt = pos;
	for (uint32_t i = 0; i < size && bufferIt < buffer.size(); i++) {
		// invert bytes if needed
		auto byte = invertBytes ? invertByte(bytes[i]) : bytes[i];

		buffer[bufferIt] = byte;
		bufferIt++;
	}

	// return the numbers of bytes copied
	return bufferIt - pos;
}
