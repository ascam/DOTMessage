#include "qttext.hpp"

#include <algorithm>
#include <cmath>

#include "utils/macsalogger.hpp"

constexpr const char* kDefaultFontFamily =  "Garuda";

using macsa::dot::QtText;
using macsa::utils::MacsaLogger;

QtText::QtText(const Text* text, QPainter& painter, QFontDatabase& fonts, int vres, int hres, const QMap<QString, QColor>& colorsPalette) :
	QtObject(text, painter, vres, hres, colorsPalette),
	_text(text),
	_fontsDb(fonts)
{}

void QtText::Render(const std::string& text)
{
	if (text.empty()) {
		WLog() << "No text to render";
		return;
	}

	_painter.save();

	QColor bgColor = GetColor(_text->GetBackgroundColor());
	if (bgColor == QColor{0xFF,0xFF,0xFF,0x0}) {
		_painter.setBackground(QBrush(Qt::transparent));
	}
	else {
		_painter.setBackground(QBrush(bgColor));
	}

	QColor fgColor = GetColor(_text->GetForegroundColor());

	if (fgColor == QColor{0xFF,0xFF,0xFF,0x0}) {
		_painter.setPen(Qt::black);
	}
	else {
		if (!fgColor.alpha()) {
			fgColor.setAlpha(255);
		}
		_painter.setPen(fgColor);
	}

	if (!_text->GetPrintable())	{
		_painter.setOpacity(0.5);
	}

	int angle = _text->GetGeometry().rotation;
	QRectF rect = GetRect();

	//Change painter coords and angle
	changePainterCoords(_painter, angle, rect);

	if (_text->GetTextBoxProperties().GetBoxAdjustment() == NTextBoxAdjustment::kFitToBox) {
		renderFitToBox(text, rect);
	}
	else {
		renderParagraph(text, rect);
	}

	_painter.restore();

#if defined(EDITOR_MODE)
	QtObject::Render();
#endif
}

void QtText::Render()
{
	Render(_text->GetText());
}

void QtText::renderFitToBox(const std::string& text, QRectF rect)
{
	QFont qfont = getFont(_text->GetFont());

	double fontSize = rect.height();
	qfont.setPointSizeF(fontSize);

	QFontMetrics fm(qfont, _painter.device());
	QString qtext = QString::fromUtf8(text.c_str(), static_cast<int>(text.length()));
	//	QRect r(rect.x(), rect.y(), rect.width(), rect.height());
	QRectF textRect = fm.tightBoundingRect(qtext);
	QRectF fontRect = fm.boundingRect(qtext);

	float scaleH = static_cast<float>(rect.width() / textRect.width());
	float scaleV = static_cast<float>(rect.height() / textRect.height());

	// Virtual rect realocation to fit text in box with scaled paint
	rect.moveTop(rect.top() - (std::abs(textRect.top() - fontRect.top())));
	rect.moveLeft(rect.left() - fm.leftBearing(qtext.at(0)));

	if(scaleV > 0 && scaleH > 0) {
		_painter.scale(scaleH, scaleV);
	}

	_painter.setFont(qfont);
	const int flags = Qt::AlignTop | Qt::AlignLeft | Qt::TextDontClip | Qt::TextSingleLine;
	_painter.drawText(rect, flags, qtext);
}

void QtText::renderParagraph(const std::string& text, QRectF rect)
{
	auto font = _text->GetFont();

	if(font.size < 1) {
		WLog() << "Invalid font size, using default font size 12pt";
		font.size = 12;
	}

	// Get Scale factor
	auto geometry = _text->GetGeometry();
	double height = geometry.size.height / kMMPerInch;// Size in inches
	double width = geometry.size.width / kMMPerInch;	 // Size in inches

	if (geometry.rotation == 90 || geometry.rotation == 270) {
		std::swap(width, height);
	}

	double xDpi = 1.0, yDpi = 1.0;
	if (_painter.device()) {
		xDpi = _painter.device()->logicalDpiX();
		yDpi = _painter.device()->logicalDpiY();
	}
	height *= yDpi;
	width *= xDpi;

	double xScale = rect.width() / width;
	double yScale = rect.height() / height;

	auto qfont = getFont(font);

	_painter.setFont(qfont);

	int flags = Qt::TextWrapAnywhere;
	// Horizontal alignment options
	if (_text->GetTextBoxProperties().GetHorizontalAlignment() == NHorizontalAlignment::kLeft) {
		flags |= Qt::AlignLeft;
	}
	else if (_text->GetTextBoxProperties().GetHorizontalAlignment() == NHorizontalAlignment::kRight) {
		flags |= Qt::AlignRight;
	}
	else {
		flags |= Qt::AlignHCenter;
	}

	// Vertical alignment options
	if (_text->GetTextBoxProperties().GetVerticalAlignment() == NVerticalAlignment::kTop) {
		flags |= Qt::AlignTop;
	}
	else if (_text->GetTextBoxProperties().GetVerticalAlignment() == NVerticalAlignment::kBottom) {
		flags |= Qt::AlignBottom;
	}
	else {
		flags |= Qt::AlignVCenter;
	}

	rect.setWidth(rect.width() / xScale);
	rect.setHeight(rect.height() / yScale);
	_painter.scale(xScale, yScale);

	_painter.drawText(rect, flags, text.c_str());
}


QFont QtText::getFont(const macsa::dot::Font& font)
{
	std::string fontName = font.family;

	if (_fontsDb.families().filter(fontName.c_str(), Qt::CaseInsensitive).size() == 0) {
		WLog() << "Missing font " << fontName << " using default font " << kDefaultFontFamily;
		fontName = kDefaultFontFamily;
	}

	QFont qfont(fontName.c_str());

	qfont.setPointSize(font.size);

	qfont.setBold(font.bold);
	qfont.setItalic(font.italic);
	qfont.setStrikeOut(font.strikeout);
	qfont.setUnderline(font.underline);
#if ARM
	qfont.setStyleStrategy(QFont::NoAntialias);
#endif

	return qfont;
}
