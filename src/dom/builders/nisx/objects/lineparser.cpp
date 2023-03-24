#include "lineparser.hpp"
#include "dom/builders/nisx/nisxcommonnames.hpp"
#include "objectparserfactory.hpp"

using macsa::nisx::LineParser;

bool LineParser::_registered = macsa::nisx::ConcreteObjectParserFactory<LineParser>::Register(macsa::nisx::kLineField);

LineParser::LineParser(macsa::dot::Object *primitive) :
	PrimitiveParser(macsa::nisx::kLineField, primitive)
{}
