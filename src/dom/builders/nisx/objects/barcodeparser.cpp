#include "barcodeparser.hpp"
#include "fontparser.hpp"
#include "dom/builders/nisx/nisxcommonnames.hpp"
#include "objectparserfactory.hpp"
#include "datasources/datasourceparsersfactory.hpp"
#include "utils/macsalogger.hpp"
#include "utils/stringutils.hpp"

using macsa::nisx::BarcodeParser;
using macsa::dot::Barcode;
using macsa::utils::MacsaLogger;
using namespace macsa::utils::stringutils;

bool BarcodeParser::_registered = macsa::nisx::ConcreteObjectParserFactory<BarcodeParser>::Register(macsa::nisx::kBarcodeField);

BarcodeParser::BarcodeParser(dot::Object* barcode) :
	ObjectParser(macsa::nisx::kBarcodeField, barcode),
	_barcode{dynamic_cast<Barcode*>(barcode)},
	_font{}
{
	if (!_barcode) {
		std::stringstream message;
		message << "Unable to parse barcode field to a ";
		if (!barcode) {
			message << "nullptr object";
		}
		else {
			message << barcode->GetType().toString() << " object";
		}
		throw (std::invalid_argument(message.str()));
	}
}

bool BarcodeParser::VisitEnter(const tinyxml2::XMLElement& element, const tinyxml2::XMLAttribute* attribute)
{
	std::string eName {ToString(element.Name())};
	if (!parseCommonElements(element, attribute, _barcode)) {
		std::string eValue {ToString(element.GetText())};
		if (eName == kCode) {
			_barcode->SetCode(eValue);
		}
		else if (eName == kFont) {
			FontParser fontParser(_font);
			element.Accept(&fontParser);
		}
		else if (eName == kForeColor) {
			_barcode->SetForegroundColor(parseObjectColor(attribute));
		}
		else if (eName == kBackColor) {
			_barcode->SetBackgroundColor(parseObjectColor(attribute));
		}
		else if (eName == kSymbology) {
			_barcode->SetSymbology(eValue);
		}
		else if (eName == kRatio) {
			_barcode->SetRatio(ToDouble(eValue));
		}
		else if (eName == kDisplayChecksum) {
			_barcode->SetDisplayChecksum(ToBool(eValue));
		}
		else if (eName == kDisplayCode) {
			_barcode->SetShowHumanReadableCode(ToBool(eValue));
		}
		else if (eName == kQrVersion) {
			_barcode->SetQrVersion((uint8_t)ToInt(eValue));
		}
		else if (eName == kQrCorrectionLevel) {
			if (_barcode->IsQrCode()){
				_barcode->SetQrCorrectionLevel(eValue);
			}
			else if (_barcode->GetSymbology() == dot::NBarcodeSymbol::kGS1DataMatrix) {
				if (eValue == "2") { // Patch for support GS1 separator
					_barcode->SetGS1AISeparator(dot::NGS1AISeparator::kGS);
				}
				else {
					_barcode->SetGS1AISeparator(dot::NGS1AISeparator::kFNC1);
				}
			}
		}
		else if (eName == kBearerStyle) {
			_barcode->SetBearerBarStyle(eValue);
		}
		else if (eName == kShavingMode) {
			_barcode->EnableShavingMode(ToBool(eValue));
		}
		else if (eName == kShavingValue) {
			_barcode->SetShavingValue(ToDouble(eValue));
		}
		else if (eName == kNormalized) {
			_barcode->SetKeepAspectRatio(ToBool(eValue));
		}
		else if (eName == kDataSource) {
			if (attribute) {
				std::string attrName {ToString(attribute->Name())};
				if (attrName == kType) {
					std::string attrValue {ToString(attribute->Value())};
					std::unique_ptr<macsa::nisx::DataSourceParser> dataSourceParser{DataSourceParsersFactory::Get(attrValue, _barcode)};
					if (dataSourceParser){
						element.Accept(dataSourceParser.get());
					}
					else {
						ELog() << "Unable to parse datasource of type: \"" << attrValue << "\".";
					}
				}
				else {
					ELog() << "Unable to parse datasource. Missing attribute type.";
				}
			}
			else {
				WLog() << "Missing datasource attribute.";
			}
		}
		else if (eName != _fieldType) {
			std::stringstream trace;
			trace << "Unknown element (line " << element.GetLineNum() << "): " << element.Name();
			if (attribute) {
				trace << "\n\tattribute: " << attribute->Name();
			}
			ILog() << trace.str();
		}
	}
	return (eName == _fieldType);
}

bool BarcodeParser::VisitExit(const tinyxml2::XMLElement& element)
{
	std::string eName {ToString(element.Name())};
	if (eName == kFont) {
		_barcode->SetFont(_font);
	}
	return true;
}
