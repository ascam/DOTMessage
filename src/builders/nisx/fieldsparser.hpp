#ifndef MACSA_NISX_FIELDS_PARSER_HPP
#define MACSA_NISX_FIELDS_PARSER_HPP

#include <map>
#include "dom/document.hpp"
#include "tinyxml2.h"

namespace macsa {
	namespace nisx {
		class FieldsParser : public tinyxml2::XMLVisitor
		{
			public:
				FieldsParser(dot::Document& doc);
				virtual ~FieldsParser();

				bool VisitEnter(const tinyxml2::XMLElement& element, const tinyxml2::XMLAttribute* firstAttribute) override;
				bool VisitExit(const tinyxml2::XMLElement& element) override;

			private:
				dot::Document& _dom;

				static const std::map<std::string,macsa::dot::NObjectType>& GetObjectsMap();
		};
	}
}

#endif
