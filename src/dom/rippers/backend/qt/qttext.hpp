#ifndef RIPPER_BACKEND_QTTEXT_HPP
#define RIPPER_BACKEND_QTTEXT_HPP

#include <QPainter>
#include <QFontDatabase>
#include <QColor>
#include <QMap>
#include <QString>

#include "qtobject.hpp"
#include "text.hpp"

namespace macsa {
	namespace dot {
		class QtText : public QtObject
		{
			public:
				QtText(const Text* text, QPainter& painter, QFontDatabase& fonts,
					   int vres, int hres, const ColorsPalette& colorsPalette);

				void Render() override;

			private:
				const Text* _text;
				QFontDatabase& _fontsDb;

				void renderFitToBox(const std::string& text, QRectF rect);
				void renderParagraph(const std::string& text, QRectF rect);

				QFont getFont(const Font& font);
		};
	}
}
#endif
