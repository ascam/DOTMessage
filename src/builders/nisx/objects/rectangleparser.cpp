#include "rectangleparser.hpp"
#include "builders/nisx/nisxcommonnames.hpp"
#include "objectparserfactory.hpp"

using macsa::nisx::RectangleParser;

namespace macsa {
	namespace nisx {
		namespace  {
			static const bool FactoryRegistered = ConcreteObjectParserFactory<RectangleParser>::Register(macsa::nisx::kRectangleField);
		}
	}
}


RectangleParser::RectangleParser(macsa::dot::Object *primitive) :
	PrimitiveParser(macsa::nisx::kRectangleField, primitive)
{}
