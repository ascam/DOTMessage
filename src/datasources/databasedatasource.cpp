#include "message/datasources/databasedatasource.hpp"
#include "factories/datasourcefactory.hpp"

using macsa::dot::DatabaseDataSource;
using macsa::dot::RefreshPolicy;

namespace macsa {
	namespace dot {
		namespace  {
			static const bool DatabaseFactoryRegistered = ConcreteDataSourceFactory<DatabaseDataSource>::Register(NDataSourceType::kDataBase);
		}
	}
}

macsa::dot::DatabaseDataSource::DatabaseDataSource() :
	DataSource(NDataSourceType::kDataBase),
	_fieldName{},
	_defaultValue{}
{}

std::string DatabaseDataSource::GetData()
{
	return _defaultValue;
}

macsa::dot::RefreshPolicy DatabaseDataSource::GetRefreshPolicy() const
{
	return RefreshPolicy::kNone;
}
