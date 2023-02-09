#include "message/image.hpp"
#include "factories/abstractobjectfactory.hpp"

using macsa::dot::Image;
using macsa::dot::Geometry;

namespace macsa {
	namespace dot {
		namespace  {
			static const bool FactoryRegistered = ConcreteObjectsFactory<Image>::Register(NObjectType::kImage);
		}
	}
}


Image::Image(const std::string &id, const Geometry &geometry) :
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

Image::~Image()
{}

void Image::SetData(const Image::ByteArray &data)
{
	if (_data != data) {
		_data = data;
		ImageDataChanged.Emit();
	}
}

void Image::SetFilepath(const std::string &filepath)
{
	if (_filepath != filepath) {
		_filepath = filepath;
		PathChanged.Emit(std::forward<std::string>(_filepath));
	}
}

void Image::SetBoxAdjustment(const macsa::dot::ImageBoxAdjustment &adjustment)
{
	if (_boxAdjustment != adjustment){
		_boxAdjustment = adjustment;
		AdjustmentChanged.Emit();
	}
}

void Image::SetVerticalAlignment(const macsa::dot::VerticalAlignment &alignment)
{
	if (_verticalAlignment != alignment) {
		_verticalAlignment = alignment;
		if (_boxAdjustment == NImageBoxAdjustment::kNormal) {
			AdjustmentChanged.Emit();
		}
	}
}

void Image::SetHorizontalAlignment(const macsa::dot::HorizontalAlignment &alignment)
{
	if (_horizontalAlignment != alignment) {
		_horizontalAlignment = alignment;
		if (_boxAdjustment == NImageBoxAdjustment::kNormal) {
			AdjustmentChanged.Emit();
		}
	}
}

void Image::SetAlgorithm(const std::string &algorithm)
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


