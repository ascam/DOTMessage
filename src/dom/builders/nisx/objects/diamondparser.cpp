#include "diamondparser.hpp"
#include "dom/builders/nisx/nisxcommonnames.hpp"
#include "objectparserfactory.hpp"

using macsa::nisx::DiamondParser;

bool DiamondParser::_registered = macsa::nisx::ConcreteObjectParserFactory<DiamondParser>::Register(macsa::nisx::kDiamondField);

DiamondParser::DiamondParser(macsa::dot::Object *primitive) :
	PrimitiveParser(macsa::nisx::kDiamondField, primitive)
{}
