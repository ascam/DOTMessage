#include "linxparsercontext.hpp"
#include "utils/macsalogger.hpp"

using namespace macsa::dot;
using macsa::utils::MacsaLogger;
using macsa::linx::LinxParserContext;
using macsa::linx::OffsetDateMap;

constexpr const char* kDots = "dots";
constexpr uint8_t kPrecision = 100;
constexpr uint8_t k90Degrees = 90;
constexpr uint16_t k270Degrees = 270;

LinxParserContext::LinxParserContext(macsa::dot::Document& doc):
	_doc{doc},
	_units{"mm"},
	_unitsRatio{0.12},
	_offsetDateMap{}
{}

Document &LinxParserContext::GetDocument() const
{
	return _doc;
}

void LinxParserContext::SetUnits(const std::string &units)
{
	_units = units;
}

void LinxParserContext::SetUnitsRatio(double ratio)
{
	_unitsRatio = ratio;
}

double LinxParserContext::ConvertUnits(double units)
{
	double convertedUnits = units / kPrecision;
	if(_units == kDots) {
		convertedUnits /= _unitsRatio;
	}
	return convertedUnits;
}

Geometry LinxParserContext::CheckGeometry(dot::Geometry geometry)
{
	if (geometry.rotation == k90Degrees || geometry.rotation == k270Degrees) {
		std::swap(geometry.size.width, geometry.size.height);
	}
	if(_units == kDots) {
		geometry.position.x  /= _unitsRatio * kPrecision;
		geometry.position.y  /= _unitsRatio * kPrecision;
		geometry.size.height /= _unitsRatio * kPrecision;
		geometry.size.width  /= _unitsRatio * kPrecision;
	}
	else {
		geometry.position.x  /= kPrecision;
		geometry.position.y  /= kPrecision;
		geometry.size.height /= kPrecision;
		geometry.size.width  /= kPrecision;
	}
	return geometry;
}

OffsetDateMap& LinxParserContext::GetOffsetDateMap(){
	return _offsetDateMap;
}

void LinxParserContext::AddOffsetDate(std::string& name, OffsetDate& offset)
{
	_offsetDateMap.emplace(name, offset);
}
