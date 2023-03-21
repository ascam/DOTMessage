#include "compositeparser.hpp"
#include "datasourceparsersfactory.hpp"
#include "dom/builders/nisx/nisxcommonnames.hpp"
#include "utils/macsalogger.hpp"
#include "utils/stringutils.hpp"

using macsa::nisx::CompositeParser;
using macsa::dot::VariableObject;
using tinyxml2::XMLElement;
using tinyxml2::XMLAttribute;
using macsa::utils::MacsaLogger;
using namespace macsa::utils::stringutils;

bool CompositeParser::_registered = macsa::nisx::ConcreteDataSourceParserFactory<CompositeParser>::Register(macsa::nisx::kDataSourceComposite);

CompositeParser::CompositeParser(VariableObject* object) :
	DataSourceParser(object),
	_composite{}
{}

bool CompositeParser::VisitEnter(const XMLElement& element, const XMLAttribute* firstAttribute)
{
	std::string eName {ToString(element.Name())};
	if (eName == kDataSource) {
		_composite = dynamic_cast<dot::CompositeDataSource*>(_object->SetDatasource(dot::NDataSourceType::kComposite));
		if (_composite == nullptr) {
			ELog() << "Unable to create a composite data source object";
			return false; // Avoid continue parsing
		}
	}
	else if (eName == kFormula) {
		_composite->SetFormula(ToString(element.GetText()));
	}
	else if (eName != kComposite)  {
		std::stringstream trace;
		trace << "Unknown element (line " << element.GetLineNum() << "): " << element.Name();
		if (firstAttribute) {
			trace << "\n\tattribute: " << ToString(firstAttribute->Name());
		}
		WLog() << trace.str();
	}
	return (eName == kDataSource) || (eName == kComposite);
}
