#include "message/datasources/datetimedatasource.hpp"
#include "factories/datasourcefactory.hpp"

using macsa::dot::DateTimeDataSource;
using macsa::dot::RefreshPolicy;

namespace  {
	static const bool DateTimeFactoryRegistered = macsa::dot::ConcreteDataSourceFactory<DateTimeDataSource>::Register(macsa::dot::NDataSourceType::kDateTime);
}

DateTimeDataSource::DateTimeDataSource() :
	DataSource(NDataSourceType::kDateTime),
	_format{},
	_daysOffset{},
	_monthsOffset{},
	_yearsOffset{},
	_hourDaysStart{}
{}

std::string DateTimeDataSource::GetData()
{
	return _format;
}

macsa::dot::RefreshPolicy DateTimeDataSource::GetRefreshPolicy() const
{
	return RefreshPolicy::kNone;
}
