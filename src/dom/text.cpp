#include "dom/text.hpp"
#include "dom/documentvisitor.hpp"
#include "dom/factories/abstractobjectfactory.hpp"

using macsa::dot::Text;
using macsa::dot::Font;
using macsa::dot::TextBoxProperties;
using macsa::dot::IDocumentVisitor;

namespace  {
	static const bool FactoryRegistered = macsa::dot::ConcreteObjectsFactory<Text>::Register(macsa::dot::NObjectType::kText);
}

Text::Text(const std::string& id, const macsa::dot::Geometry& geometry) :
	VariableObject(id, NObjectType::kText, geometry),
	_text{},
	_font{},
	_foreColor{},
	_backgroundColor{},
	_textBoxProperties{}
{}

bool Text::IsVariable() const
{
	return _datasource.get() != nullptr;
}

bool Text::Accept(IDocumentVisitor* visitor) const
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

void Text::SetText(const std::string& text)
{
	if (_text != text) {
		_text = text;
		TextChanged.Emit();
	}
}

void Text::SetFont(const Font& font)
{
	if (_font != font) {
		_font = font;
		FontChanged.Emit();
	}
}

void Text::SetForegroundColor(const Color& foreColor)
{
	if (_foreColor != foreColor){
		_foreColor = foreColor;
		ForegroundColorChanged.Emit();
	}
}

void Text::SetBackgroundColor(const Color& backgroundColor)
{
	if (_backgroundColor != backgroundColor) {
		_backgroundColor = backgroundColor;
		BackgroundColorChanged.Emit();
	}
}

void Text::SetTextBoxProperties(const TextBoxProperties& boxProps)
{
	if (_textBoxProperties != boxProps) {
		_textBoxProperties = boxProps;
		TextBoxPropertiesChanged.Emit();
	}
}
