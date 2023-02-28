#include "message/datasources/databasedatasource.hpp"
#include "factories/datasourcefactory.hpp"
#include "message/documentvisitor.hpp"

using macsa::dot::DatabaseDataSource;
using macsa::dot::IDocumentVisitor;

namespace  {
	static const bool DatabaseFactoryRegistered = macsa::dot::ConcreteDataSourceFactory<DatabaseDataSource>::Register(macsa::dot::NDataSourceType::kDataBase);
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
