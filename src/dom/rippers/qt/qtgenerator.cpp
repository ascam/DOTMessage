#include "qtgenerator.hpp"

#include <cmath>
#include <chrono>
#ifndef BACKEND_QT_NATIVE
#include <QApplication>
#endif
#include <QFontDatabase>
#include <QPaintDevice>
#include <QDir>
#include <QDataStream>

#include "qttext.hpp"
#include "qtbarcode.hpp"
#include "qtimage.hpp"
#include "qtline.hpp"
#include "qtrectangle.hpp"
#include "qtellipse.hpp"
#include "qtdiamond.hpp"

#include "visitors/qtdocumentvisitor.hpp"

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
	_colorsPalette(),
	_pixmapFixed(),
	_pixmapFull()
{}

QtGenerator::~QtGenerator()
{
	_pixmapFixed.reset();
	_pixmapFull.reset();
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
	return _pixmapFull->width();
}

uint32_t QtGenerator::GetHeight() const
{
	return _pixmapFull->height();
}

int QtGenerator::GetRawData(bitmap& buff) const
{
	QImage img = _pixmapFull->toImage().convertToFormat(QImage::Format_Mono, Qt::ThresholdDither);
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
	if (!_pixmapFull || _pixmapFull->isNull()) {
		WLog() << "Unable to get buffer. Invalid pixmap pointer";
		return;
	}

	QImage img = _pixmapFull->toImage().convertToFormat(QImage::Format_Mono, Qt::ThresholdDither);
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
	if (_pixmapFull == nullptr) {return;}

	QImage img = _pixmapFull->toImage().convertToFormat(QImage::Format_Mono, Qt::ThresholdDither);

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

void QtGenerator::Update(Document* doc, Context* context)
{
	DLog() << "Updating bmp in " << _hres << "x" << _vres << " rotation : " << doc->GetCanvasRotation();

	if (!doc) {
		ELog() << "Invalid DOM";
		return;
	}

	// Get size in pixels taking in mind the resolution
	int w = 0, h = 0;
	if (doc->GetCanvasRotation() == 90) { // TODO : @jsubi, cal implementar la rotació dels missatges.
		h = std::round(static_cast<double>(_hres) * doc->GetCanvasWidth()  / kMMPerInch);
		w = std::round(static_cast<double>(_vres) * doc->GetCanvasHeight() / kMMPerInch);
	}
	else {
		w = std::round(static_cast<double>(_hres) * doc->GetCanvasWidth()  / kMMPerInch);
		h = std::round(static_cast<double>(_vres) * doc->GetCanvasHeight() / kMMPerInch);
	}

	if (!buildCanvas(w, h)) {
		ELog() << "Unable to build de painter device";
		return;
	}

	_colorsPalette.clear();
	const auto palette = doc->GetColorsPalette();
	for (const auto& color : palette) {
		_colorsPalette.insert(color.first.c_str(),
				 QColor(color.second.GetRed(), color.second.GetGreen(), color.second.GetBlue(), color.second.GetAlpha()));
	}

	// Points the painter to the base pixmap
	QPainter painter (_pixmapFull.get());
	painter.setRenderHint(QPainter::HighQualityAntialiasing);
	painter.setBackgroundMode(Qt::OpaqueMode);
	painter.setBackground(QBrush(Qt::white));

	if (doc->GetCanvasRotation() == 90) {
		painter.translate(QPointF(w, 0));
		painter.rotate(doc->GetCanvasRotation());
	}

	auto start_time = std::chrono::high_resolution_clock::now();

	classifyObjects(doc->GetObjects());
	renderFixedFields(painter);
	renderVariableFields(painter, context);


	//QtDocumentVisitor visitor(doc, context, &painter, _vres, _hres, _colorsPalette);
	//doc->Accept(&visitor);

	auto end_time = std::chrono::high_resolution_clock::now();
	std::cout << "Elapsed time in milliseconds: " << std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time).count()	<< " ms" << std::endl;
}

void QtGenerator::UpdateVariableFields(Document* doc, Context* context)
{
	if (!doc) {
		WLog() << "Invalid DOM";
		return;
	}

	if (!_pixmapFixed) {
		WLog() << "Invalid pixmap base. Load full file needed";
		return;
	}

	//Restore the full pixmap with the stored fixed pixmap
	_pixmapFull.reset(new QPixmap(*_pixmapFixed));

	// Points the painter to the base pixmap
	QPainter painter(_pixmapFull.get());
	painter.setRenderHint(QPainter::HighQualityAntialiasing);
	painter.setBackgroundMode(Qt::OpaqueMode);
	painter.setBackground(QBrush(Qt::white));

	classifyObjects(doc->GetObjects());
	renderVariableFields(painter, context);
}

void QtGenerator::SaveToBmpFile(const std::string& filename)
{
	if (_pixmapFull != nullptr && !_pixmapFull->isNull() &&
		_pixmapFull->width() > 0 &&	_pixmapFull->height() > 0)
	{
		DLog() << "Saving image to: " << filename;
		_pixmapFull->save(filename.c_str()) ;
	}
}

void QtGenerator::Clear()
{
	_colorsPalette.clear();
	_pixmapFixed.reset();
	_pixmapFull.reset();
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

bool QtGenerator::buildCanvas(int width, int height)
{
	// clear smart pointers
	_pixmapFixed.reset();

	// Build the pixmap base
	_pixmapFull.reset(new QPixmap(width, height));
	if (!_pixmapFull) {
		return false;
	}

	_pixmapFull->fill(_bgColor); //Fill pixmap with background color

	return true;
}

void QtGenerator::classifyObjects(const std::deque<Object*>& objects)
{
	_variableObjects.clear();
	_fixedObject.clear();
	for (const auto* object : objects) {
		if (object->GetPrintable() || _printHiddenItems) {
			if(object->IsVariable()) {
				_variableObjects.emplace_back(object);
			}
			else {
				_fixedObject.emplace_back(object);
			}
		}
	}
}

void QtGenerator::renderFixedFields(QPainter& painter)
{
	if (!_pixmapFull) {
		ELog() << "Invalid base pixmap";
		return;
	}

	for (const auto object : _fixedObject) {
		const auto type = object->GetType();
		if (type == NObjectType::kText){
			renderText(object, painter);
		}
		else if (type == NObjectType::kBarcode) {
			renderBarcode(object, painter);
		}
		else if (type == NObjectType::kImage) {
			renderImage(object, painter);
		}
		else if (type == NObjectType::kRectangle) {
			renderRectangle(object, painter);
		}
		else if (type == NObjectType::kLine) {
			renderLine(object, painter);
		}
		else if (type == NObjectType::kEllipse) {
			renderEllipse(object, painter);
		}
		else if (type == NObjectType::kDiamond) {
			renderDiamond(object, painter);
		}
		else {
			WLog() << "Skipping Fixed element: " << object->GetId();
		}
	}

	// Store the current pixmap with only the static elements
	_pixmapFixed.reset(new QPixmap(*_pixmapFull));
}

void QtGenerator::renderVariableFields(QPainter& painter, Context* context)
{
	if (!_pixmapFull) {
		ELog() << "Invalid base pixmap";
		return;
	}

	for (auto object : _variableObjects) {
		const auto& type = object->GetType();
		if (type == NObjectType::kText){
			renderText(object, painter);
		}
		else if (type == NObjectType::kBarcode) {
			renderBarcode(object, painter);
		}
		else {
			WLog() << "Skipping variable element: " << object->GetId();
		}
	}
}

void QtGenerator::renderText(const Object* object, QPainter& painter)
{
	const auto text = dynamic_cast<const Text*>(object);
	if (!text) {
		ELog() << "unable to morph DOM Object to DOM Text type";
		return;
	}

	QtText label(text, painter, _fonts, _vres, _hres, _colorsPalette);
	label.Render();
}

void QtGenerator::renderBarcode(const Object* object, QPainter& painter)
{
	const auto barcode = dynamic_cast<const Barcode*>(object);
	if (!barcode) {
		ELog() << "unable to morph DOM Object to DOM Barcode type";
		return;
	}

	QtBarcode qBcode(barcode, painter, _vres, _hres, _colorsPalette);
	qBcode.Render();
}

void QtGenerator::renderImage(const Object* object, QPainter& painter)
{
	const auto image = dynamic_cast<const Image*>(object);
	if (!image) {
		ELog() << "unable to morph DOM Object to DOM Image type";
		return;
	}

	QtImage qImage(image, painter, _vres, _hres, _colorsPalette);
	qImage.Render();
}

void QtGenerator::renderRectangle(const Object* object, QPainter& painter)
{
	const Rectangle* rectangle = dynamic_cast<const Rectangle*>(object);
	if (!rectangle) {
		ELog() << "unable to morph DOM Object to DOM Rectangle type";
		return;
	}

	QtRectangle qRectangle(rectangle, painter, _vres, _hres, _colorsPalette);
	qRectangle.Render();
}

void QtGenerator::renderLine(const Object* object, QPainter& painter)
{
	const auto line = dynamic_cast<const Line*>(object);
	if (!line) {
		ELog() << "unable to morph DOM Object to DOM Line type";
		return;
	}

	QtLine qLine(line, painter, _vres, _hres, _colorsPalette);
	qLine.Render();
}

void QtGenerator::renderEllipse(const Object* object, QPainter& painter)
{
	const auto ellipse = dynamic_cast<const Ellipse*>(object);
	if (!ellipse) {
		ELog() << "unable to morph DOM Object to DOM Ellipse type";
		return;
	}

	QtEllipse qEllipse(ellipse, painter, _vres, _hres, _colorsPalette);
	qEllipse.Render();
}

void QtGenerator::renderDiamond(const Object* object, QPainter& painter)
{
	const Diamond* diamond = dynamic_cast<const Diamond*>(object);
	if (!diamond) {
		ELog() << "unable to morph DOM Object to DOM Diamond type";
		return;
	}

	QtDiamond qDiamond(diamond, painter, _vres, _hres, _colorsPalette);
	qDiamond.Render();
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
