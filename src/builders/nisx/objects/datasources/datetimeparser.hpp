#ifndef MACSA_NISX_OBJECT_DATETIME_DATASOURCE_PARSER_HPP
#define MACSA_NISX_OBJECT_DATETIME_DATASOURCE_PARSER_HPP

#include "datasourceparser.hpp"
#include "dom/datasources/datetimedatasource.hpp"

namespace macsa {
	namespace nisx {
		class DateTimeParser: public DataSourceParser
		{
			public:
				DateTimeParser(dot::VariableObject* object);
				virtual ~DateTimeParser();

				bool VisitEnter( const tinyxml2::XMLElement& element, const tinyxml2::XMLAttribute* firstAttribute) override;

			private:
				dot::DateTimeDataSource* _datetime;
		};
	}
}

#endif
