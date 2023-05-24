#include "textpropertiesparser.hpp"

using macsa::linx::TextPropertiesParser;
using tinyxml2::XMLElement;

namespace {
	std::string str(const char* text) {
		return (text != nullptr ? text : "");
	}
}


static constexpr const char* kElementName = "Text";

TextPropertiesParser::TextPropertiesParser(macsa::dot::Object *object)
{

}

TextPropertiesParser::~TextPropertiesParser()
{

}

bool TextPropertiesParser::VisitEnter(const tinyxml2::XMLElement &element, const tinyxml2::XMLAttribute *firstAttribute)
{

}

