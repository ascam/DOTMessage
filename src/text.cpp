#include "message/text.hpp"
#include "message/documentvisitor.hpp"
#include "factories/abstractobjectfactory.hpp"

using macsa::dot::Text;
using macsa::dot::RefreshPolicy;
using macsa::dot::Font;
using macsa::dot::TextBoxProperties;
using macsa::dot::IDocumentVisitor;

namespace macsa {
	namespace dot {
		namespace  {
			static const bool FactoryRegistered = ConcreteObjectsFactory<Text>::Register(NObjectType::kText);
		}
	}
}

Text::Text(const std::string &id, const macsa::dot::Geometry &geometry) :
	VariableObject(id, NObjectType::kText, geometry),
	_text{},
	_font{},
	_foreColor{},
	_backgroundColor{},
	_textBoxProperties{}
{}

Text::~Text()
{}

bool Text::IsVariable() const
{
	return _datasource.get() != nullptr;
}

bool Text::Accept(IDocumentVisitor* visitor)
{
	if (visitor) {
		if (visitor->VisitEnter(*this)) {
			if (IsVariable()) {
				_datasource->Accept(visitor);
			}
		}
		return visitor->VisitExit(*this);
	}
	return false;
}

void Text::SetText(const std::string &text)
{
	if (_text != text) {
		_text = text;
		TextChanged.Emit(std::forward<std::string>(_text));
	}
}

void Text::SetFont(const Font &font)
{
	if (_font != font) {
		_font = font;
		FontChanged.Emit(std::forward<Font>(_font));
	}
}

void Text::SetForegroundColor(const std::string &foreColor)
{
	if (_foreColor != foreColor){
		_foreColor = foreColor;
		ForegroundColorChanged.Emit(std::forward<std::string>(_foreColor));
	}
}

void Text::SetBackgroundColor(const std::string &backgroundColor)
{
	if (_backgroundColor != backgroundColor) {
		_backgroundColor = backgroundColor;
		BackgroundColorChanged.Emit(std::forward<std::string>(_backgroundColor));
	}
}

void Text::SetTextBoxProperties(const TextBoxProperties &boxProps)
{
	if (_textBoxProperties != boxProps) {
		_textBoxProperties = boxProps;
		TextBoxPropertiesChanged.Emit();
	}
}
