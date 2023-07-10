#include "linxparsercontext.hpp"
#include "utils/macsalogger.hpp"

using namespace macsa::dot;
using macsa::utils::MacsaLogger;
using macsa::linx::LinxParserContext;
using macsa::linx::OffsetDateMap;

static constexpr const char* kDots = "dots";
static constexpr const char* kMilimeters = "mm";
static constexpr uint8_t kPrecision = 100;
static constexpr uint8_t k90Degrees = 90;
static constexpr uint16_t k270Degrees = 270;
static constexpr double kDefaultUnitsRatio = 0.12;

LinxParserContext::LinxParserContext(macsa::dot::Document& doc):
	_doc{doc},
	_units{kMilimeters},
	_unitsRatio{kDefaultUnitsRatio},
	_offsetDateMap{},
	_colorsPalette{{kBlack, dot::Color(kBlack, 0, 0, 0)},
				   {kWhite, dot::Color(kWhite, 255, 255, 255)},
				   {kTransparent, dot::Color(kTransparent, 255, 255, 255, 0)}}
{}

Document& LinxParserContext::GetDocument() const
{
	return _doc;
}

void LinxParserContext::SetUnits(const std::string& units)
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

Geometry LinxParserContext::ConvertGeometry(dot::Geometry geometry)
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

OffsetDateMap& LinxParserContext::GetOffsetDateMap()
{
	return _offsetDateMap;
}

void LinxParserContext::AddOffsetDate(std::string& name, OffsetDate& offset)
{
	_offsetDateMap.emplace(name, offset);
}

ColorsPalette& LinxParserContext::GetColorsPalette()
{
	return _colorsPalette;
}
