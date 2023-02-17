#include "message/datasources/datetimedatasource.hpp"
#include "factories/datasourcefactory.hpp"

using macsa::dot::DateTimeDataSource;
using macsa::dot::RefreshPolicy;

namespace macsa {
	namespace dot {
		namespace  {
			static const bool DateTimeFactoryRegistered = ConcreteDataSourceFactory<DateTimeDataSource>::Register(NDataSourceType::kDateTime);
		}
	}
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

void DateTimeDataSource::SetFormat(const std::string &format)
{
	_format = format;
}
