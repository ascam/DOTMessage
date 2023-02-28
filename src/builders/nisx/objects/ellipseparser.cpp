#include "ellipseparser.hpp"
#include "builders/nisx/nisxcommonnames.hpp"
#include "objectparserfactory.hpp"

using macsa::nisx::EllipseParser;

namespace macsa {
	namespace nisx {
		namespace  {
			static const bool FactoryRegistered = ConcreteObjectParserFactory<EllipseParser>::Register(macsa::nisx::kEllipseField);
		}
	}
}

EllipseParser::EllipseParser(macsa::dot::Object *primitive) :
	PrimitiveParser(macsa::nisx::kEllipseField, primitive)
{}
