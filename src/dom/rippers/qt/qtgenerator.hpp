#ifndef RIPPER_BACKEND_QTGENERATOR_HPP
#define RIPPER_BACKEND_QTGENERATOR_HPP

#include <memory>
#include <array>
#include <thread>

#include <QApplication>
#include <QFontDatabase>
#include <QMap>
#include <QString>
#include <QColor>
#include <QPainter>
#include <QPixmap>

#include "dom/document.hpp"
#include "dom/rippers/context.hpp"
#include "dom/rippers/bitmapgenerator.hpp"
#include "dom/rippers/qt/visitors/qtrastervisitor.hpp"

namespace macsa
{
	namespace dot
	{
		class QtGenerator : public BitmapGenerator
		{
			public:
				QtGenerator();
				virtual ~QtGenerator();

				void* NativeHandler() const override
				{
					return  (void*) &_pixmap;
				}
				uint32_t GetWidth() const override;
				uint32_t GetHeight() const override;
				int GetRawData(bitmap& buff) const override;

				/**
				 * @brief GetBitmapMono Get image in bitmap form (1 bit per pixel)
				 * TODO(iserra): Allow variants (CMYK, Grayscale...)
				 * invertBytes reverse the order of bits in each bytes
				 */
				void GetBitmapMono(bitmap& buff, bool invertByte = true) const override;
				void GetDoubleColBitmapMono(bitmap& buff1, bitmap& buff2, uint32_t colOffset,
											bool invertByte = true) const override;

				void Update(Document* doc, Context* context, bool editorMode = false) override;
				void UpdateVariableFields(Document* doc, Context* context) override;
				void SaveToBmpFile(const std::string& filename) override;
				void Clear() override;

				void AddFontsDirectory(const std::string& fullpath) override;
				void AddFontFamily(const std::string& fullpath) override;

				void SetBackgroundColorFromRGBA(const std::string& rgba) override;
				void SetBackgroundColorFromRGBA(uint32_t rgba) override;

				std::pair<float, float> getCanvasOffset() const override
				{
					return {_canvasOffset.x(), _canvasOffset.y()};
				}

			private:
#ifndef BACKEND_QT_NATIVE
				QApplication _app;
				std::thread::id _idth;
#endif
				QFontDatabase _fonts;
				QColor _bgColor;
				QMap<QString, QColor> _colorsPalette;
				QPixmap _pixmapFixed;
				QPixmap _pixmap;
				std::vector<const Object*>  _fixedObject;
				std::vector<const Object*>  _variableObjects;
				QPointF _canvasOffset;

				void classifyObjects(const std::deque<Object*>& objects);
				void renderFixedFields(QtRasterVisitor* visitor);
				void renderVariableFields(QtRasterVisitor* visitor);
				uint8_t invertByte(uint8_t byte) const;

				/**
				 * @brief insertLine insert the given number of bytes to a bitmap
				 * @return the numbers of bytes copied
				 */
				uint32_t insertLine(const uchar *bytes, uint32_t size, bitmap& buffer, uint32_t pos, bool invertBytes) const;

				std::pair<QSize, QPoint> getOutOfCanvasBounds(Document* doc);

				void preparePainterBeforeRendering(QPainter& painter, QPointF offset, uint16_t rotation) const;
		};
	}
}
#endif
