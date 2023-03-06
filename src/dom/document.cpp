#include "dom/document.hpp"

#include <algorithm>
#include "dom/object.hpp"
#include "dom/documentvisitor.hpp"
#include "dom/factories/abstractobjectfactory.hpp"
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

Document::Document(const std::string& name) :
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

void Document::SetName(const std::string& name)
{
	if (_name != name){
		_name = name;
		NameChanged.Emit();
	}
}

void Document::SetVersion(const VersionEncodingArray& versions)
{
	_versions = versions;
	VersionEncodingChanged.Emit();
}

void Document::SetUnits(const std::string& units)
{
	if (_units != units){
		_units = units;
		UnitsChanged.Emit();
	}
}

void Document::SetCanvasXOffset(float x)
{
	if (_canvasGeometry.position.x != x)	{
		_canvasGeometry.position.x = x;
		CanvasGeometryChanged.Emit();
	}
}

void Document::SetCanvasYOffset(float y)
{
	if (_canvasGeometry.position.y != y)	{
		_canvasGeometry.position.y = y;
		CanvasGeometryChanged.Emit();
	}
}

void Document::SetCanvasOffset(const Point& pos)
{
	if (_canvasGeometry.position != pos){
		_canvasGeometry.position = pos;
		CanvasGeometryChanged.Emit();
	}
}

void Document::SetCanvasWidth(float width)
{
	if (_canvasGeometry.size.width != width)	{
		_canvasGeometry.size.width = width;
		CanvasGeometryChanged.Emit();
	}
}

void Document::SetCanvasHeight(float height)
{
	if(_canvasGeometry.size.height != height)	{
		_canvasGeometry.size.height = height;
		CanvasGeometryChanged.Emit();
	}
}

void Document::SetCanvasSize(const Size& size)
{
	if(_canvasGeometry.size != size)	{
		_canvasGeometry.size = size;
		CanvasGeometryChanged.Emit();
	}
}

void Document::SetCanvasRotation(int rotation)
{
	if (_canvasGeometry.rotation != rotation)	{
		_canvasGeometry.rotation = rotation;
		CanvasGeometryChanged.Emit();
	}
}

void Document::SetViewportWidth(float width)
{
	if (_viewport.width != width)	{
		_viewport.width = width;
		ViewPortSizeChanged.Emit();
	}
}

void Document::SetViewportHeight(float height)
{
	if (_viewport.height != height)	{
		_viewport.height = height;
		ViewPortSizeChanged.Emit();
	}
}

void Document::SetViewportSize(const macsa::dot::Size& size)
{
	if (_viewport != size)	{
		_viewport = size;
		ViewPortSizeChanged.Emit();
	}
}

std::deque<Object*> Document::GetObjects() const
{
	std::deque<Object*> dom;

	for (const auto& object : _dom) {
		dom.emplace_back(object.get());
	}

	std::sort(dom.begin(), dom.end(), [](const Object* a, const Object* b) {
		return *a > *b;
	});

	return dom;
}

Object* Document::GetObjectById(const std::string& id) const
{
	for (const auto& obj : _dom) {
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
			DomChanged.Emit();
		}
		return object;
	}
	else{
		ELog() << "Unable to create new object with \"" << objectId << "\" id. This id is already in use.";
	}
	return nullptr;
}

bool Document::RemoveObject(const std::string& id)
{
	DOM::iterator objIt = std::find_if(_dom.begin(), _dom.end(), [&id](const std::unique_ptr<Object>& obj){
		return obj->GetId() == id;
	});

	if (objIt != _dom.end()) {
		_dom.erase(objIt);
		DomChanged.Emit();
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
	DomChanged.Emit();
}

bool Document::RenameObject(const std::string& oldId, const std::string& newId)
{
	if (GetObjectById(newId) == nullptr) {
		auto* object = GetObjectById(oldId);
		if (object != nullptr) {
			object->setId(newId);
			DomChanged.Emit();
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

void Document::AddColor(const std::string& name, const macsa::dot::Color& color)
{
	if (_colors.find(name) == _colors.end()) {
		_colors.emplace(name, color);
		ColorsPaletteChanged.Emit();
	}
	else {
		WLog() << "Unable to add the color \"" << name << "\" this color is already in the palette.";
	}
}

void Document::DeleteColor(const std::string& name)
{
	auto colorIt = _colors.find(name);
	if (colorIt != _colors.end()) {
		_colors.erase(colorIt);
		ColorsPaletteChanged.Emit();
	}
	else {
		WLog() << "Unable to remove the color \"" << name << "\" this color is not in the palette.";
	}
}

bool Document::Accept(IDocumentVisitor* visitor) const
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
