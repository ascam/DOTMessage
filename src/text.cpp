#include "message/text.hpp"
#include "factories/abstractobjectfactory.hpp"

using macsa::dot::Text;
using macsa::dot::RefreshPolicy;
using macsa::dot::Font;
using macsa::dot::TextBoxProperties;

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

std::string Text::GetData() const
{
	if (IsVariable()) {
		return _datasource->GetData();
	}
	return _text;
}

RefreshPolicy Text::GetRefreshPolicy() const
{
	if (IsVariable()) {
		return _datasource->GetRefreshPolicy();
	}
	return RefreshPolicy::kNone;
}

bool Text::IsVariable() const
{
	return _datasource.get() != nullptr;
}

void Text::SetText(const std::string& text)
{
	if (_text != text) {
		_text = text;
		TextChanged.Emit();
	}
}

void Text::SetFont(const Font &font)
{
	if (_font != font) {
		_font = font;
		FontChanged.Emit();
	}
}

void Text::SetForegroundColor(const std::string &foreColor)
{
	if (_foreColor != foreColor){
		_foreColor = foreColor;
		ForegroundColorChanged.Emit();
	}
}

void Text::SetBackgroundColor(const std::string &backgroundColor)
{
	if (_backgroundColor != backgroundColor) {
		_backgroundColor = backgroundColor;
		BackgroundColorChanged.Emit();
	}
}

void Text::SetTextBoxProperties(const TextBoxProperties &boxProps)
{
	if (_textBoxProperties != boxProps) {
		_textBoxProperties = boxProps;
		TextBoxPropertiesChanged.Emit();
	}
}
