#include "message/primitives.hpp"
#include "factories/abstractobjectfactory.hpp"

using macsa::dot::Primitive;
using macsa::dot::Geometry;
using macsa::dot::Rectangle;
using macsa::dot::Ellipse;
using macsa::dot::Diamond;
using macsa::dot::Line;
using macsa::dot::NObjectType;

namespace macsa {
	namespace dot {
		namespace  {
			static const bool RectangleFactoryRegistered = ConcreteObjectsFactory<Rectangle>::Register(NObjectType::kRectangle);
			static const bool EllipseFactoryRegistered = ConcreteObjectsFactory<Ellipse>::Register(NObjectType::kEllipse);
			static const bool DiamondFactoryRegistered = ConcreteObjectsFactory<Diamond>::Register(NObjectType::kDiamond);
			static const bool LineFactoryRegistered = ConcreteObjectsFactory<Line>::Register(NObjectType::kLine);
		}
	}
}

Primitive::Primitive(const std::string& id, const Geometry& geometry, const macsa::dot::ObjectType& primitiveType) :
	Object(id, primitiveType, geometry),
	_pen{},
	_brush{},
	_filled{false},
	_border{true}
{}

void Primitive::SetPen(const macsa::dot::Pen &pen)
{
	if (_pen != pen) {
		_pen = pen;
		Changed.Emit();
	}
}

void Primitive::SetBrush(const macsa::dot::Color &brush)
{
	if (_brush != brush) {
		_brush = brush;
		Changed.Emit();
	}
}

void Primitive::SetFilled(bool fill)
{
	if (_filled != fill) {
		_filled = fill;
		Changed.Emit();
	}
}

void Primitive::ShowBorder(bool show)
{
	if (_border != show) {
		_border = show;
		Changed.Emit();
	}
}

Rectangle::Rectangle(const std::string &id, const Geometry &geometry) :
	Primitive(id, geometry, NObjectType::kRectangle)
{}

Ellipse::Ellipse(const std::string &id, const Geometry &geometry) :
	Primitive(id, geometry, NObjectType::kEllipse)
{}

Diamond::Diamond(const std::string &id, const Geometry &geometry) :
	Primitive(id, geometry, NObjectType::kDiamond)
{}

Line::Line(const std::string &id, const Geometry &geometry) :
	Primitive(id, geometry, NObjectType::kLine)
{}
