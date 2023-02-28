#include "lineparser.hpp"
#include "builders/nisx/nisxcommonnames.hpp"
#include "objectparserfactory.hpp"

using macsa::nisx::LineParser;

namespace macsa {
	namespace nisx {
		namespace  {
			static const bool FactoryRegistered = ConcreteObjectParserFactory<LineParser>::Register(macsa::nisx::kLineField);
		}
	}
}

LineParser::LineParser(macsa::dot::Object *primitive) :
	PrimitiveParser(macsa::nisx::kLineField, primitive)
{}
