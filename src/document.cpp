#include "document.hpp"

#include <algorithm>
#include "object.hpp"
#include "factories/abstractobjectfactory.hpp"

using macsa::dot::Document;
using macsa::dot::Point;
using macsa::dot::Size;
using macsa::dot::Object;
using macsa::dot::ObjectType;

Document::Document(const std::string &name) :
	_name{name}
{}

void Document::SetName(const std::string &name)
{
	_name = name;
}

void Document::SetCanvasXOffset(float x)
{
	_canvasGeometry.position.x = x;
}

void Document::SetCanvasYOffset(float y)
{
	_canvasGeometry.position.y = y;
}

void Document::SetCanvasOffset(const Point& pos)
{
	_canvasGeometry.position = pos;
}

void Document::SetCanvasWidth(float width)
{
	_canvasGeometry.size.width = width;
}

void Document::SetCanvasHeight(float height)
{
	_canvasGeometry.size.height = height;
}

void Document::SetCanvasSize(const Size &size)
{
	_canvasGeometry.size = size;
}

void Document::SetCanvasRotation(int rotation)
{
	_canvasGeometry.rotation = rotation;
}

void Document::SetViewportWidth(float width)
{
	_viewport.width = width;
}

void Document::SetViewportHeight(float height)
{
	_viewport.height = height;
}

void Document::SetViewportSize(const macsa::dot::Size &size)
{
	_viewport = size;
}

Object const *Document::AddObject(const std::string& objectId, const ObjectType& type)
{
	Object* object = ObjectsFactory::Get(objectId, type);
	if (object) {
		_dom.emplace_back(object);
		std::sort(_dom.begin(), _dom.end());
	}
	return object;
}
