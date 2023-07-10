#ifndef MACSA_LINX_OBJECT_PARSER_HPP
#define MACSA_LINX_OBJECT_PARSER_HPP

#include "dom/components/geometry.hpp"
#include "tinyxml2.h"
#include <string>

//Common
static constexpr const char* kField = "Field";
static constexpr const char* kFldType = "FldType";
static constexpr const char* kCLSID = "CLSID";
static constexpr const char* kDisplayed = "Displayed";
static constexpr const char* kLn = "Ln";
static constexpr const char* kCalcData = "CalcData";
static constexpr const char* kLoggedField = "LoggedField";
static constexpr const char* kData = "Data";

namespace macsa {
	namespace linx {
		class ObjectParser : public tinyxml2::XMLVisitor
		{
			public:
				ObjectParser();
				virtual ~ObjectParser() = default;

			protected:
				bool parseCommonElements(const tinyxml2::XMLElement& element) const;
				bool parseGeometry(const tinyxml2::XMLElement& element, dot::Geometry& geometry) const;
		};
	}
}

#endif
