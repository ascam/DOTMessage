#include "message/document.hpp"

#include <algorithm>
#include "message/object.hpp"
#include "message/documentvisitor.hpp"
#include "factories/abstractobjectfactory.hpp"
#include "utils/macsalogger.hpp"

using macsa::dot::Document;
using macsa::dot::Point;
using macsa::dot::Size;
using macsa::dot::Object;
using macsa::dot::ObjectType;
using macsa::dot::IDocumentVisitor;
using macsa::utils::MacsaLogger;

std::string Document::GetLibraryVersion()
{
	std::stringstream version;
	version << DOT_MESSAGE_LIB_VERSION_MAJOR << "."
			<< DOT_MESSAGE_LIB_VERSION_MINOR << "."
			<< DOT_MESSAGE_LIB_VERSION_BUILD;
	return version.str();
}

Document::Document(const std::string &name) :
	_name{name},
	_versions{},
	_colors{},
	_canvasGeometry{},
	_viewport{},
	_gsLevels{},
	_dom{}
{}

Document::~Document()
{}

void Document::SetName(const std::string &name)
{
	_name = name;
}

void Document::SetVersion(const std::array<uint8_t,3> &versions)
{
	_versions = versions;
}

void Document::SetUnits(const std::string &units)
{
	_units = units;
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

std::deque<Object*> Document::GetObjects() const
{
	std::deque<Object*> dom;

	for (const auto& object : _dom) {
		dom.emplace_back(object.get());
	}

	std::sort(dom.begin(), dom.end(), [](const Object* a, const Object*b) {
		return *a > *b;
	});

	return dom;
}

Object* Document::GetObjectById(const std::string &id) const
{
	for (auto&& obj : _dom) {
		if (obj->GetId() == id) {
			return obj.get();
		}
	}
	return nullptr;
}

Object *Document::AddObject(const std::string& objectId, const ObjectType& type, const Geometry& geometry)
{
	if (GetObjectById(objectId) == nullptr) {
		Object* object = ObjectsFactory::Get(objectId, type, geometry);
		if (object) {
			_dom.emplace_back(object);
		}
		return object;
	}
	else{
		ELog() << "Unable to create new object with \"" << objectId << "\" id. This id is already in use.";
	}
	return nullptr;
}

bool Document::RemoveObject(const std::string &id)
{
	DOM::iterator objIt = std::find_if(_dom.begin(), _dom.end(), [&id](const pObject& obj){
		return obj->GetId() == id;
	});

	if (objIt != _dom.end()) {
		_dom.erase(objIt);
		return true;
	}
	return false;
}

void Document::Clear()
{
	_dom.clear();
	_name = "NewDocument";
	_versions = {0,0,0};
	_colors.clear();
	_canvasGeometry = {};
	_gsLevels = {0};
}

bool Document::RenameObject(const std::string &oldId, const std::string &newId) const
{
	if (GetObjectById(newId) == nullptr) {
		auto* object = GetObjectById(oldId);
		if (object != nullptr) {
			object->setId(newId);
			return true;
		}
		else {
			WLog() << "Unable to rename object: \"" << oldId << "\" is not a valid id";
		}
	}
	else {
		WLog() << "Unable to rename object: \"" << newId << "\" id is already in use.";
	}

	return false;
}

void Document::AddColor(const std::string &name, const macsa::dot::Color &color)
{
	if (_colors.find(name) == _colors.end()) {
		_colors.emplace(name, color);
	}
	else {
		WLog() << "Unable to add the color \"" << name << "\" this color is already in the palette.";
	}
}

void Document::DeleteColor(const std::string &name)
{
	auto colorIt = _colors.find(name);
	if (colorIt != _colors.end()) {
		_colors.erase(colorIt);
	}
	else {
		WLog() << "Unable to remove the color \"" << name << "\" this color is not in the palette.";
	}
}

bool Document::Accept(IDocumentVisitor* visitor)
{
	if (visitor->VisitEnter(*this)) {
		for (auto& obj : _dom) {
			if (!obj->Accept(visitor)) {
				break;
			}
		}
	}
	return visitor->VisitExit(*this);
}
