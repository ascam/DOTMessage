#include "dom/components/datasources/databasedatasource.hpp"
#include "dom/documentvisitor.hpp"
#include "dom/factories/datasourcefactory.hpp"

using macsa::dot::DatabaseDataSource;
using macsa::dot::IDocumentVisitor;

bool DatabaseDataSource::_registered = macsa::dot::ConcreteDataSourceFactory<DatabaseDataSource>::Register(macsa::dot::NDataSourceType::kDataBase);

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
