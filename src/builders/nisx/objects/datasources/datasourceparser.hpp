#ifndef MACSA_NISX_OBJECT_DATASOURCE_PARSER_HPP
#define MACSA_NISX_OBJECT_DATASOURCE_PARSER_HPP

#include "dom/variableobject.hpp"
#include "tinyxml2.h"

namespace macsa {
	namespace nisx {
		class DataSourceParser : public tinyxml2::XMLVisitor
		{
			public:
				DataSourceParser(dot::VariableObject* object) :
				_object{object}
				{}
				virtual ~DataSourceParser() = default;

			protected:
				dot::VariableObject* _object;
		};
	}
}

#endif
