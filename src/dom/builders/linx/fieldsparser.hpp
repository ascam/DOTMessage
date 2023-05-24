#ifndef MACSA_LINX_FIELD_PARSER_HPP
#define MACSA_LINX_FIELD_PARSER_HPP

#include <map>
#include "message/document.hpp"
#include "tinyxml2.h"

namespace macsa {
	namespace linx {
		class FieldParser : public tinyxml2::XMLVisitor
		{
			public:
				FieldParser(dot::Document& doc);
				virtual ~FieldParser();

				bool VisitEnter(const tinyxml2::XMLElement& element, const tinyxml2::XMLAttribute* firstAttribute) override;
				bool VisitExit(const tinyxml2::XMLElement& element) override;

			private:
				dot::Document& _dom;

				static const std::map<std::string,macsa::dot::NObjectType>& GetObjectsMap();
		};
	}
}

#endif
