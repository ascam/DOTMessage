#include "imageparser.hpp"
#include "builders/nisx/nisxcommonnames.hpp"
#include "objectparserfactory.hpp"
#include "utils/macsalogger.hpp"
#include "utils/stringutils.hpp"
#include "utils/base64.h"

using macsa::nisx::ImageParser;
using macsa::dot::Image;
using macsa::utils::MacsaLogger;
using namespace macsa::utils::stringutils;

static constexpr const char* kTopLeft = "TopLeft";
static constexpr const char* kMiddleLeft = "MiddleLeft";
static constexpr const char* kBottomLeft = "BottomLeft";
static constexpr const char* kTopCenter = "TopCenter";
static constexpr const char* kMiddleCenter = "MiddleCenter";
static constexpr const char* kBottomCenter = "BottomCenter";
static constexpr const char* kTopRight = "TopRight";
static constexpr const char* kMiddleRight = "MiddleRight";
static constexpr const char* kBottomRight = "BottomRight";


namespace macsa {
	namespace nisx {
		namespace  {
			static const bool FactoryRegistered = ConcreteObjectParserFactory<ImageParser>::Register(macsa::nisx::kImageField);

			std::string str(const char* text) {
				return (text != nullptr ? text : "");
			}
		}
	}
}

ImageParser::ImageParser(dot::Object *image) :
	ObjectParser(macsa::nisx::kImageField, image),
	_image{dynamic_cast<Image*>(image)}
{
	if (!image || !_image) {
		std::stringstream message;
		message << "Unable to parse image field to a ";
		if (!image) {
			message << "nullptr object";
		}
		else {
			message << image->GetType().toString() << " object";
		}
		throw (std::invalid_argument(message.str()));
	}
}

ImageParser::~ImageParser()
{}

//    <IMAGE>{BASE64}</IMAGE>

bool ImageParser::VisitEnter(const tinyxml2::XMLElement& element, const tinyxml2::XMLAttribute* attribute)
{
	std::string eName {str(element.Name())};
	if (!parseCommonElements(element, attribute, _image)) {
		if (eName == kAdjust) {
			if (attribute) {
				std::string attrName {str(attribute->Name())};
				if (attrName == kType){
					std::string attrValue {str(attribute->Value())};
					_image->SetBoxAdjustment(attrValue);
				}
				else {
					WLog() << "Invalid image adjusting type attribute";
				}
			}
			else {
				WLog() << "Missing image adjusting type attribute";
			}
		}
		else if (eName == kAlignment) {
			if (attribute) {
				std::string attrName {str(attribute->Name())};
				if (attrName == kAttrValue){
					parseAlignment(str(attribute->Value()));
				}
				else {
					WLog() << "Invalid image alignment attribute";
				}
			}
			else {
				WLog() << "Missing image alignment attribute";
			}
		}
		else if (eName == kAlgorithm) {
			_image->SetAlgorithm(str(element.GetText()));
		}
		else if (eName == kPath) {
			_image->SetFilepath(str(element.GetText()));
		}
		else if (eName == kTopThreshold) {
			_image->SetTopThreshold(ToInt(str(element.GetText())));
		}
		else if (eName == kDownThreshold) {
			_image->SetDownThreshold(ToInt(str(element.GetText())));
		}
		else if (eName == kImage) {
			_image->SetData(imageContentFromString(element.GetText()));
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


void ImageParser::parseAlignment(const std::string &adjust)
{
	if (adjust == kTopLeft) {
		_image->SetVerticalAlignment(dot::NVerticalAlignment::kTop);
		_image->SetHorizontalAlignment(dot::NHorizontalAlignment::kLeft);
	}
	else if (adjust == kMiddleLeft) {
		_image->SetVerticalAlignment(dot::NVerticalAlignment::kMiddle);
		_image->SetHorizontalAlignment(dot::NHorizontalAlignment::kLeft);
	}
	else if (adjust == kBottomLeft) {
		_image->SetVerticalAlignment(dot::NVerticalAlignment::kBottom);
		_image->SetHorizontalAlignment(dot::NHorizontalAlignment::kLeft);
	}
	else if (adjust == kTopCenter) {
		_image->SetVerticalAlignment(dot::NVerticalAlignment::kTop);
		_image->SetHorizontalAlignment(dot::NHorizontalAlignment::kCenter);

	}
	else if (adjust == kMiddleCenter) {
		_image->SetVerticalAlignment(dot::NVerticalAlignment::kMiddle);
		_image->SetHorizontalAlignment(dot::NHorizontalAlignment::kCenter);
	}
	else if (adjust == kBottomCenter) {
		_image->SetVerticalAlignment(dot::NVerticalAlignment::kBottom);
		_image->SetHorizontalAlignment(dot::NHorizontalAlignment::kCenter);
	}
	else if (adjust == kTopRight) {
		_image->SetVerticalAlignment(dot::NVerticalAlignment::kTop);
		_image->SetHorizontalAlignment(dot::NHorizontalAlignment::kRight);
	}
	else if (adjust == kMiddleRight) {
		_image->SetVerticalAlignment(dot::NVerticalAlignment::kMiddle);
		_image->SetHorizontalAlignment(dot::NHorizontalAlignment::kRight);
	}
	else if (adjust == kBottomRight) {
		_image->SetVerticalAlignment(dot::NVerticalAlignment::kBottom);
		_image->SetHorizontalAlignment(dot::NHorizontalAlignment::kRight);
	}
	else {
		WLog() << "Unknown image alignment: \"" << adjust << "\"";
	}
}

std::vector<uint8_t> ImageParser::imageContentFromString(const char *data) const
{
	std::vector<uint8_t> content;
	if (data != nullptr) {
		int decodedLen = Base64decode_len(data);
		char* decodedData = new char[decodedLen + 1];
		decodedLen = Base64decode(decodedData, data);
		for (int i = 0; i < decodedLen; i++) {
			content.push_back(static_cast<uint8_t>(*(decodedData + i)));
		}
//		content.push_back('\0');
		delete[]  decodedData;
	}
	return content;
}
