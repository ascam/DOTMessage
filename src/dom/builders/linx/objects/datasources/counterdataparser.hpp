#ifndef MACSA_LINX_COUNTER_PARSER_HPP
#define MACSA_LINX_COUNTER_PARSER_HPP

#include "dom/components/datasources/counterdatasource.hpp"
#include "dom/variableobject.hpp"
#include "tinyxml2.h"

namespace macsa {
	namespace linx {
		class CounterDataParser : public tinyxml2::XMLVisitor
		{
			public:
				CounterDataParser(dot::VariableObject* obj);
				virtual ~CounterDataParser() = default;
				bool VisitEnter( const tinyxml2::XMLElement& element, const tinyxml2::XMLAttribute* firstAttribute) override;
			private:
				dot::VariableObject* _object;
				dot::CounterDataSource* _counter;
		};
	}
}
#endif
