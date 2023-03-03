#include "ellipseparser.hpp"
#include "dom/builders/nisx/nisxcommonnames.hpp"
#include "objectparserfactory.hpp"

using macsa::nisx::EllipseParser;

namespace  {
	static const bool FactoryRegistered = macsa::nisx::ConcreteObjectParserFactory<EllipseParser>::Register(macsa::nisx::kEllipseField);
}

EllipseParser::EllipseParser(macsa::dot::Object *primitive) :
	PrimitiveParser(macsa::nisx::kEllipseField, primitive)
{}
