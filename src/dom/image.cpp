#include "dom/image.hpp"
#include "dom/documentvisitor.hpp"
#include "dom/factories/abstractobjectfactory.hpp"

using macsa::dot::Image;
using macsa::dot::Geometry;
using macsa::dot::IDocumentVisitor;

bool Image::_registered = macsa::dot::ConcreteObjectsFactory<Image>::Register(macsa::dot::NObjectType::kImage);

Image::Image(const std::string& id, const Geometry& geometry) :
	Object(id, NObjectType::kImage, geometry),
	_data{},
	_filepath{},
	_boxAdjustment{NImageBoxAdjustment::kZoom},
	_verticalAlignment{NVerticalAlignment::kTop},
	_horizontalAlignment{NHorizontalAlignment::kLeft},
	_algorithm{},
	_topThreshold{},
	_downThreshold{}
{}

bool Image::Accept(IDocumentVisitor* visitor) const
{
	if (visitor) {
		return visitor->Visit(*this);
	}
	return false;
}

void Image::SetData(const Image::ByteArray &data)
{
	if (_data != data) {
		_data = data;
		ImageDataChanged.Emit();
	}
}

void Image::SetFilepath(const std::string& filepath)
{
	if (_filepath != filepath) {
		_filepath = filepath;
		PathChanged.Emit();
	}
}

void Image::SetBoxAdjustment(const macsa::dot::ImageBoxAdjustment& adjustment)
{
	if (_boxAdjustment != adjustment){
		_boxAdjustment = adjustment;
		AdjustmentChanged.Emit();
	}
}

void Image::SetVerticalAlignment(const macsa::dot::VerticalAlignment& alignment)
{
	if (_verticalAlignment != alignment) {
		_verticalAlignment = alignment;
		AdjustmentChanged.Emit();
	}
}

void Image::SetHorizontalAlignment(const macsa::dot::HorizontalAlignment& alignment)
{
	if (_horizontalAlignment != alignment) {
		_horizontalAlignment = alignment;
		AdjustmentChanged.Emit();
	}
}

void Image::SetAlgorithm(const std::string& algorithm)
{
	if (_algorithm != algorithm){
		_algorithm = algorithm;
		ImageDataChanged.Emit();
	}
}

void Image::SetTopThreshold(uint32_t threshold)
{
	if (_topThreshold != threshold){
		_topThreshold = threshold;
		ImageDataChanged.Emit();
	}
}

void Image::SetDownThreshold(uint32_t threshold)
{
	if (_downThreshold != threshold){
		_downThreshold = threshold;
		ImageDataChanged.Emit();
	}
}
