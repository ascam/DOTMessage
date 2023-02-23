#include "message/primitives.hpp"
#include "message/documentvisitor.hpp"
#include "factories/abstractobjectfactory.hpp"

using macsa::dot::Primitive;
using macsa::dot::Geometry;
using macsa::dot::Rectangle;
using macsa::dot::Ellipse;
using macsa::dot::Diamond;
using macsa::dot::Line;
using macsa::dot::NObjectType;
using macsa::dot::IDocumentVisitor;

namespace  {
	static const bool RectangleFactoryRegistered = macsa::dot::ConcreteObjectsFactory<Rectangle>::Register(macsa::dot::NObjectType::kRectangle);
	static const bool EllipseFactoryRegistered = macsa::dot::ConcreteObjectsFactory<Ellipse>::Register(macsa::dot::NObjectType::kEllipse);
	static const bool DiamondFactoryRegistered = macsa::dot::ConcreteObjectsFactory<Diamond>::Register(macsa::dot::NObjectType::kDiamond);
	static const bool LineFactoryRegistered = macsa::dot::ConcreteObjectsFactory<Line>::Register(macsa::dot::NObjectType::kLine);
}

Primitive::Primitive(const std::string& id, const Geometry& geometry, const macsa::dot::ObjectType& primitiveType) :
	Object(id, primitiveType, geometry),
	_pen{},
	_brush{},
	_filled{false},
	_border{true}
{}

void Primitive::SetPen(const macsa::dot::Pen& pen)
{
	if (_pen != pen) {
		_pen = pen;
		Changed.Emit();
	}
}

void Primitive::SetBrush(const macsa::dot::Color& brush)
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

Rectangle::Rectangle(const std::string& id, const Geometry& geometry) :
	Primitive(id, geometry, NObjectType::kRectangle)
{}

bool Rectangle::Accept(IDocumentVisitor* visitor)
{
	if (visitor) {
		return visitor->Visit(*this);
	}
	return false;
}

Ellipse::Ellipse(const std::string& id, const Geometry& geometry) :
	Primitive(id, geometry, NObjectType::kEllipse)
{}

bool Ellipse::Accept(IDocumentVisitor* visitor)
{
	if (visitor) {
		return visitor->Visit(*this);
	}
	return false;
}

Diamond::Diamond(const std::string& id, const Geometry& geometry) :
	Primitive(id, geometry, NObjectType::kDiamond)
{}

bool Diamond::Accept(IDocumentVisitor* visitor)
{
	if (visitor) {
		return visitor->Visit(*this);
	}
	return false;
}

Line::Line(const std::string& id, const Geometry& geometry) :
	Primitive(id, geometry, NObjectType::kLine)
{}

bool Line::Accept(IDocumentVisitor* visitor)
{
	if (visitor) {
		return visitor->Visit(*this);
	}
	return false;
}
