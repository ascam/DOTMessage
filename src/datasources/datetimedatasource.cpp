#include "message/datasources/datetimedatasource.hpp"
#include "factories/datasourcefactory.hpp"
#include "message/documentvisitor.hpp"

using macsa::dot::DateTimeDataSource;
using macsa::dot::IDocumentVisitor;

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


bool DateTimeDataSource::Accept(IDocumentVisitor* visitor)
{
	if (visitor) {
		return visitor->Visit(*this);
	}
	return false;
}
