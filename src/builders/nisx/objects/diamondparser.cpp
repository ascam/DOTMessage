#include "diamondparser.hpp"
#include "builders/nisx/nisxcommonnames.hpp"
#include "objectparserfactory.hpp"

using macsa::nisx::DiamondParser;

namespace macsa {
	namespace nisx {
		namespace  {
			static const bool FactoryRegistered = ConcreteObjectParserFactory<DiamondParser>::Register(macsa::nisx::kDiamondField);
		}
	}
}

DiamondParser::DiamondParser(macsa::dot::Object *primitive) :
	PrimitiveParser(macsa::nisx::kDiamondField, primitive)
{}
