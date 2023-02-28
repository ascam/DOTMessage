#ifndef MACSA_NISX_OBJECT_COUNTER_DATASOURCE_PARSER_HPP
#define MACSA_NISX_OBJECT_COUNTER_DATASOURCE_PARSER_HPP

#include "datasourceparser.hpp"
#include "dom/datasources/counterdatasource.hpp"

namespace macsa {
	namespace nisx {
		class CounterParser: public DataSourceParser
		{
			public:
				CounterParser(dot::VariableObject* object);
				virtual ~CounterParser() = default;

				bool VisitEnter( const tinyxml2::XMLElement& element, const tinyxml2::XMLAttribute* firstAttribute) override;

			private:
				dot::CounterDataSource* _counter;
		};
	}
}

#endif
