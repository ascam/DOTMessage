#include "message/datasources/databasedatasource.hpp"
#include "factories/datasourcefactory.hpp"
#include "message/documentvisitor.hpp"

using macsa::dot::DatabaseDataSource;
using macsa::dot::IDocumentVisitor;

namespace macsa {
	namespace dot {
		namespace  {
			static const bool DatabaseFactoryRegistered = ConcreteDataSourceFactory<DatabaseDataSource>::Register(NDataSourceType::kDataBase);
		}
	}
}

DatabaseDataSource::DatabaseDataSource() :
	DataSource(NDataSourceType::kDataBase),
	_fieldName{},
	_defaultValue{}
{}

bool DatabaseDataSource::Accept(IDocumentVisitor* visitor)
{
	if (visitor) {
		return visitor->Visit(*this);
	}
	return false;
}
