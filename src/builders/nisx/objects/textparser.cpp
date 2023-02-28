#include "textparser.hpp"
#include "fontparser.hpp"
#include "builders/nisx/nisxcommonnames.hpp"
#include "objectparserfactory.hpp"
#include "utils/macsalogger.hpp"
#include "utils/stringutils.hpp"
#include "datasources/datasourceparsersfactory.hpp"

using macsa::nisx::TextParser;
using macsa::nisx::TextAdjustParser;
using macsa::dot::Text;
using macsa::utils::MacsaLogger;
using tinyxml2::XMLElement;
using tinyxml2::XMLAttribute;
using namespace macsa::utils::stringutils;

namespace macsa {
	namespace nisx {
		namespace  {
			static const bool FactoryRegistered = ConcreteObjectParserFactory<TextParser>::Register(macsa::nisx::kTextField);

			std::string str(const char* text) {
				return (text != nullptr ? text : "");
			}
		}
	}
}

TextParser::TextParser(dot::Object *text) :
	ObjectParser(macsa::nisx::kTextField, text),
	_text{dynamic_cast<Text*>(text)},
	_font{}
{
	if (!text || !_text) {
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
}

TextParser::~TextParser()
{}

bool TextParser::VisitEnter(const XMLElement& element, const XMLAttribute* attribute)
{
	std::string eName {str(element.Name())};
	if (!parseCommonElements(element, attribute, _text)) {
		if (eName == kText) {
			std::string eValue {str(element.GetText())};
			_text->SetText(eValue);
		}
		else if (eName == kFont) {
			FontParser fontParser(_font);
			element.Accept(&fontParser);
		}
		else if (eName == kForeColor) {
			_text->SetForegroundColor(parseObjectColor(attribute).GetName());
		}
		else if (eName == kBackColor) {
			_text->SetBackgroundColor(parseObjectColor(attribute).GetName());
		}
		else if (eName == kAdjust) {
			TextAdjustParser textBoxParser(_text);
			element.Accept(&textBoxParser);
		}
		else if (eName == kDataSource) {
			if (attribute) {
				std::string attrName {str(attribute->Name())};
				if (attrName == kType) {
					std::string attrValue {str(attribute->Value())};
					auto* dataSourceParser = DataSourceParsersFactory::Get(attrValue, _text);
					if (dataSourceParser){
						element.Accept(dataSourceParser);
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

bool TextParser::VisitExit(const XMLElement& element)
{
	std::string eName {str(element.Name())};
	if (eName == kFont) {
		_text->SetFont(_font);
	}
	return true;
}



TextAdjustParser::TextAdjustParser(Text *text) :
	_text{text},
	_elementName{kAdjust}
{}

TextAdjustParser::~TextAdjustParser()
{}

bool TextAdjustParser::VisitEnter(const XMLElement &element, const XMLAttribute *firstAttribute)
{
	std::string eName {str(element.Name())};
	std::string eValue {str(element.GetText())};

	if (eName == kHorizontal) {
		dot::HorizontalAlignment alignment{eValue};
		_boxProperties.SetHorizontalAlignment(alignment);
	}
	else if (eName == kVertical) {
		dot::VerticalAlignment alignment{eValue};
		_boxProperties.SetVerticalAlignment(alignment);
	}
	else if (eName == kFitToBox) {
		_boxProperties.SetBoxAdjustment(dot::NTextBoxAdjustment::kFitToBox);
		return true; // Continue parsing
	}
	else if (eName == kParagraph) {
		_boxProperties.SetBoxAdjustment(dot::NTextBoxAdjustment::kParagraph);
		return true; // Continue parsing
	}
	else if (eName == kMaxCharsLine) {
		_boxProperties.SetMaxCharsLine(static_cast<uint32_t>(ToInt(eValue)));
	}
	else if (eName == kAutoincrement) {
		bool autoinc = ToBool(eValue);
		_boxProperties.SetClipText(!autoinc);
	}
	else if (eName == kInterLine) {
		_boxProperties.SetLineSpacing(static_cast<double>(ToDouble(eValue)));
	}

	return (eName == _elementName);
}

bool TextAdjustParser::VisitExit(const tinyxml2::XMLElement &element)
{
	std::string eName {str(element.Name())};
	if (eName == _elementName) {
		_text->SetTextBoxProperties(_boxProperties);
	}
	return true;
}
