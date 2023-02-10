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

Object::~Object()
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
	float left = _geometry.position.x;
	float right = left + _geometry.size.width;
	float top = _geometry.position.y;
	float bottom = top + _geometry.size.height;

	if (left > geometry.position.x + geometry.size.width || right < geometry.position.x ||
		top < geometry.position.y + geometry.size.height || bottom < geometry.position.y) {
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
		SelectedChanged.Emit(std::forward<bool>(_selected));
	}
}

void Object::SetPrintable(bool printable)
{
	if (_printable != printable) {
		_printable = printable;
		PrintableChanged.Emit(std::forward<bool>(_printable));
	}
}

void Object::SetLinked(bool linked)
{
	if (_linked.enabled != linked) {
		_linked.enabled = linked;
		LinkedChanged.Emit(std::forward<bool>(_linked.enabled));
	}
}

void Object::SetLinkedObject(const std::string& objectId)
{
	if (!objectId.length() && _linked.enabled) {
		_linked.objectId = "";
		SetLinked(false);
		return;
	}
	else if (objectId.length()) {
		if (!_linked.enabled) {
			_linked.objectId = objectId;
			SetLinked(true);
			return;
		}
		else if (_linked.objectId != objectId) {
			_linked.objectId = objectId;
			LinkedChanged.Emit(std::forward<bool>(_linked.enabled));
		}
	}
}

void Object::SetLayer(uint32_t layer)
{
	if (_layer != layer) {
		_layer = layer;
		LayerChanged.Emit();
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
	_id = id;
}
