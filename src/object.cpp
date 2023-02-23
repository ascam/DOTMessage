#include "message/object.hpp"

using macsa::dot::Object;
using macsa::dot::Geometry;
using macsa::dot::Point;
using macsa::dot::Size;

Object::Object(const std::string& id, const ObjectType& type, const Geometry& geometry) :
	_id{id},
	_type{type},
	_geometry{geometry},
	_layer{0},
	_zOrder{0},
	_linked({false, ""}),
	_selected{false},
	_printable{true}
{}

void Object::SetGeometry(const Geometry& geometry)
{
	if (_geometry != geometry) {
		_geometry = geometry;
		GeometryChanged.Emit();
	}
}

void Object::SetPosition(const Point& position)
{
	if (_geometry.position != position) {
		_geometry.position = position;
		GeometryChanged.Emit();
	}
}

void Object::SetXPosition(float x)
{
	if (_geometry.position.x != x) {
		_geometry.position.x = x;
		GeometryChanged.Emit();
	}
}

void Object::SetYPosition(float y)
{
	if (_geometry.position.y != y) {
		_geometry.position.y = y;
		GeometryChanged.Emit();
	}
}

void Object::SetSize(const Size& size)
{
	if (_geometry.size != size) {
		_geometry.size = size;
		GeometryChanged.Emit();
	}
}

void Object::SetWidth(float width)
{
	if (_geometry.size.width != width) {
		_geometry.size.width = width;
		GeometryChanged.Emit();
	}
}

void Object::SetHeight(float height)
{
	if (_geometry.size.height != height) {
		_geometry.size.height = height;
		GeometryChanged.Emit();
	}
}

void Object::SetRotation(int rotation)
{
	if (_geometry.rotation != rotation) {
		_geometry.rotation = rotation;
		GeometryChanged.Emit();
	}
}

bool Object::Collides(const Object& other) const
{
	if (_layer == other._layer) {
		return Collides(other.GetGeometry());
	}
	else {
		return false;
	}
}

bool Object::Collides(const Geometry& geometry) const
{
	float myLeft = _geometry.position.x;
	float myRight = myLeft + _geometry.size.width;
	float myTop = _geometry.position.y;
	float myBottom = myTop + _geometry.size.height;

	float otherLeft = geometry.position.x;
	float otherRight = otherLeft + geometry.size.width;
	float otherTop = geometry.position.y;
	float otherBottom = otherTop + geometry.size.height;

	if (myLeft >= otherRight || myTop >= otherBottom || myRight <= otherLeft || myBottom <= otherTop) {
		return false;
	}
	return true;
}

bool Object::Collides(const Point& point) const
{
	if (_geometry.position.x > point.x || (_geometry.position.x + _geometry.size.width) < point.x ||
		_geometry.position.y > point.y || (_geometry.position.y + _geometry.size.height) < point.y) {
		return false;
	}
	return true;
}


void Object::SetSelected(bool select)
{
	if (_selected != select) {
		_selected = select;
		SelectedChanged.Emit();
	}
}

void Object::SetPrintable(bool printable)
{
	if (_printable != printable) {
		_printable = printable;
		PrintableChanged.Emit();
	}
}

void Object::SetLinked(bool linked)
{
	if (_linked.enabled != linked) {
		_linked.enabled = linked;
		LinkedChanged.Emit();
	}
}

void Object::SetLinkedObject(const std::string& objectId)
{
	if (objectId != _linked.objectId) {
		_linked.objectId = objectId;
		LinkedObjectChanged.Emit();
	}
}

void Object::SetLayer(uint32_t layer)
{
	if (_layer != layer) {
		_layer = layer;
		ZOrderChanged.Emit();
	}
}

void Object::SetZOrder(int32_t zOrder)
{
	if (_zOrder != zOrder) {
		_zOrder = zOrder;
		ZOrderChanged.Emit();
	}
}

void Object::setId(const std::string& id)
{
	if (_id != id)	{
		_id = id;
		IdChanged.Emit();
	}
}
