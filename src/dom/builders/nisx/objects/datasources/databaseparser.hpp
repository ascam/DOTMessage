#ifndef MACSA_NISX_OBJECT_DATABASE_DATASOURCE_PARSER_HPP
#define MACSA_NISX_OBJECT_DATABASE_DATASOURCE_PARSER_HPP

#include "datasourceparser.hpp"
#include "dom/components/datasources/databasedatasource.hpp"

namespace macsa {
	namespace nisx {
		class DatabaseParser: public DataSourceParser
		{
			public:
				DatabaseParser(dot::VariableObject* object);
				virtual ~DatabaseParser() = default;

				bool VisitEnter( const tinyxml2::XMLElement& element, const tinyxml2::XMLAttribute* firstAttribute) override;

				static bool GetRegistered()
				{
					return _registered;
				}

			private:
				dot::DatabaseDataSource* _database;
				static bool _registered;
		};
	}
}

#endif
