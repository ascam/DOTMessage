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
#include "dom/rippers/bitmapgenerator.hpp"

namespace macsa
{
	namespace dot
	{
		class QtGenerator : public BitmapGenerator
		{
			public:
				QtGenerator();
				virtual ~QtGenerator();

				void* NativeHandler() const override {return  (void*)_pixmapFull.get();}
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

				void Update(Document* doc) override;
				void UpdateVariableFields(Document* doc) override;
				void SaveToBmpFile(const std::string& filename) override;
				void Clear() override;

				void AddFontsDirectory(const std::string& fullpath) override;
				void AddFontFamily(const std::string& fullpath) override;

				void SetBackgroundColorFromRGBA(const std::string& rgba) override;
				void SetBackgroundColorFromRGBA(uint32_t rgba) override;

			private:
#ifndef BACKEND_QT_NATIVE
				QApplication _app;
				std::thread::id _idth;
#endif
				QFontDatabase _fonts;
				QColor _bgColor;
				QMap<QString, QColor> _colorsPalette;
				std::unique_ptr<QPixmap>  _pixmapFixed;
				std::unique_ptr<QPixmap>  _pixmapFull;
				std::vector<const Object*>  _fixedObject;
				std::vector<const Object*>  _variableObjects;

				bool buildCanvas(int width, int height);
				void classifyObjects(const std::deque<Object*>& objects);
				void renderFixedFields(QPainter& painter);
				void renderVariableFields(QPainter& painter);
				void renderText(const Object* object, QPainter& painter);
				void renderBarcode(const Object* object, QPainter& painter);
				void renderImage(const Object* object, QPainter& painter);
				void renderRectangle(const Object* object, QPainter& painter);
				void renderLine(const Object* object, QPainter& painter);
				void renderEllipse(const Object* object, QPainter& painter);
				void renderDiamond(const Object* object, QPainter& painter);
				uint8_t invertByte(uint8_t byte) const;

				/**
				 * @brief insertLine insert the given number of bytes to a bitmap
				 * @return the numbers of bytes copied
				 */
				uint32_t insertLine(const uchar *bytes, uint32_t size, bitmap& buffer, uint32_t pos, bool invertBytes) const;
		};
	}
}
#endif
