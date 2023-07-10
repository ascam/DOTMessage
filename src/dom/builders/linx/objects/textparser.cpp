#include "textparser.hpp"
#include "fontparser.hpp"
#include "datasources/dataparser.hpp"
#include "dom/components/datasources/userinputdatasource.hpp"
#include "utils/macsalogger.hpp"
#include "utils/stringutils.hpp"

using tinyxml2::XMLElement;
using tinyxml2::XMLAttribute;
using macsa::linx::TextParser;
using macsa::dot::Text;
using macsa::utils::MacsaLogger;
using namespace macsa::utils::stringutils;

static constexpr const char* kText = "Text";
static constexpr uint8_t kVariableFieldsLayer = 1;

TextParser::TextParser(dot::Object *text, LinxParserContext& context) :
	ObjectParser(),
	_context(context),
	_text{dynamic_cast<Text*>(text)},
	_font{},
	_textBoxProperties{},
	_dataParser{}
{
	if (!_text) {
		std::stringstream message;
		message << "Unable to parse text field to a ";
		if (!text) {
			message << "nullptr object";
		}
		else {
			message << text->GetType().toString() << " object";
		}
		throw (std::invalid_argument(message.str()));
	}
	else {
		_text->SetBackgroundColor(_context.GetColorsPalette().at(kTransparent));
		_text->SetForegroundColor(_context.GetColorsPalette().at(kBlack));
	}
}

bool TextParser::VisitEnter(const XMLElement& element, const XMLAttribute* attribute)
{
	std::string eName {ToString(element.Name())};
	if (eName == kField) {
		return true;
	}
	else if (eName == kDisplayed) {
		_text->SetPrintable(ToBool(element.GetText()));
		return false;
	}
	else if (parseCommonElements(element)) {
		return false;
	}
	else if (parseGeometry(element, _geometry)) {
		return false;
	}
	if (eName == kCalcData) {
		_text->SetText(ToString(element.GetText()));
		return false;
	}
	else if (eName == kData) {
		_dataParser = std::unique_ptr<DataParser>(new DataParser(_text, _context));
		element.Accept(_dataParser.get());
		return false;
	}
	else if (eName == kText) {
		FontParser fontParser(_font, _textBoxProperties);
		element.Accept(&fontParser);
		return false;
	}
	else{
		std::stringstream trace;
		trace << "Unknown element (line " << element.GetLineNum() << "): " << element.Name();
		if (attribute) {
			trace << "\n\tattribute: " << attribute->Name();
		}
		WLog() << trace.str();
	}

	return (eName == kField);
}

bool TextParser::VisitExit(const XMLElement& element)
{
	std::string eName {ToString(element.Name())};
	if (eName == kField) {
		_text->SetGeometry(_context.ConvertGeometry(_geometry));
	}
	else if (eName == kData) {
		if (_dataParser.get()) {
			if (_text->IsVariable()) {
				_text->SetLayer(kVariableFieldsLayer);
				std::string calcData = _text->GetText();
				if (_text->GetDatasource()->GetType() == dot::NDataSourceType::kUserInput) {
					auto* userInput = dynamic_cast<dot::UserInputDataSource*>(_text->GetDatasource());
					userInput->SetValue(calcData);
				}
			}
		}
	}
	else if (eName == kText) {
		_text->SetFont(_font);
		_text->SetTextBoxProperties(_textBoxProperties);
	}
	return true;
}
