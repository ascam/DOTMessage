#include "rectangleparser.hpp"
#include "dom/builders/nisx/nisxcommonnames.hpp"
#include "objectparserfactory.hpp"

using macsa::nisx::RectangleParser;

bool RectangleParser::_registered = macsa::nisx::ConcreteObjectParserFactory<RectangleParser>::Register(macsa::nisx::kRectangleField);

RectangleParser::RectangleParser(macsa::dot::Object *primitive) :
	PrimitiveParser(macsa::nisx::kRectangleField, primitive)
{}
