#ifndef MACSA_NISX_OBJECT_COMPOSITE_DATASOURCE_PARSER_HPP
#define MACSA_NISX_OBJECT_COMPOSITE_DATASOURCE_PARSER_HPP

#include "datasourceparser.hpp"
#include "dom/components/datasources/compositedatasource.hpp"

namespace macsa {
	namespace nisx {
		class CompositeParser: public DataSourceParser
		{
			public:
				CompositeParser(dot::VariableObject* object);
				virtual ~CompositeParser() = default;

				bool VisitEnter( const tinyxml2::XMLElement& element, const tinyxml2::XMLAttribute* firstAttribute) override;

			private:
				dot::CompositeDataSource* _composite;
		};
	}
}

#endif
