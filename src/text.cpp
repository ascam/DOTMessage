#include "text.hpp"
#include "factories/abstractobjectfactory.hpp"

using macsa::dot::Text;
using macsa::dot::RefreshPolicy;

namespace macsa {
	namespace dot {
		namespace  {
			static const bool FactoryRegistered = ConcreteObjectsFactory<Text>::Register(NObjectType::kText);
		}
	}
}

Text::Text(const std::string &id) :
	Object(id, NObjectType::kText)
{}

Text::Text(const std::string &id, const macsa::dot::Geometry &geometry) :
	Object(id, NObjectType::kText, geometry)
{}

Text::~Text()
{}

RefreshPolicy Text::GetRefreshPolicy() const
{
	// TODO(iserra): check policy with data sources
	return RefreshPolicy::kNone;
}

bool Text::IsVariable() const
{
	// TODO(iserra): check policy with data sources
	return false;
}

void Text::SetText(const std::string &text)
{
	if (_text != text) {
		_text = text;
		TextChanged.Emit(std::forward<std::string>(_text));
	}
}

