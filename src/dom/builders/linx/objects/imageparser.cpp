#include "imageparser.hpp"

#include "utils/macsalogger.hpp"
#include "utils/stringutils.hpp"

using namespace macsa::linx;
using namespace macsa::dot;
using namespace macsa::utils::stringutils;
using macsa::utils::MacsaLogger;

static constexpr const char* kGraphic = "Graphic";
static constexpr const char* kImagesDir = "/images/";
static constexpr const char* kBackSlash = "\\";
static constexpr const char* kSlash = "/";

ImageParser::ImageParser(Object* image, LinxParserContext &context):
	_image{dynamic_cast<Image*>(image)},
	_context{context}
{
	if (!_image || !image) {
		std::stringstream message;
		message << "Unable to parse text field to a ";
		if (!image) {
			message << "nullptr object";
		}
		else {
			message << image->GetType().toString() << " object";
		}
		throw (std::invalid_argument(message.str()));
	}
}

bool ImageParser::VisitEnter(const tinyxml2::XMLElement &element, const tinyxml2::XMLAttribute *attribute)
{
	std::string eName {ToString(element.Name())};
	std::string eValue {ToString(element.GetText())};
	DLog() << eName << " : " << eValue;

	if (eName == kField){
		return true;
	}
	else if (eName == kFldType){
		return true;
	}
	else if (eName == kCLSID){
		return false;
	}
	else if (parseGeometry(element, _geometry)) {
		return false;
	}
	else if (eName == kLn){
		return false;
	}
	else if (eName == kLoggedField){
		return false;
	}
	if (eName == kCalcData) {
		size_t pos = eValue.find_last_of(kBackSlash);
		if (pos == std::string::npos) {
			pos = eValue.find_last_of(kSlash);
		}
		pos++;

		eValue.replace(0, pos, kImagesDir);
		_image->SetFilepath(eValue);
		return true;
	}
	else if (eName == kData){
		return false;
	}
	else if (eName == kGraphic){
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

bool ImageParser::VisitExit(const tinyxml2::XMLElement &element)
{
	std::string eName {ToString(element.Name())};
	if (eName == kField){
		_image->SetGeometry(_context.ConvertGeometry(_geometry));
	}
	return true;
}
