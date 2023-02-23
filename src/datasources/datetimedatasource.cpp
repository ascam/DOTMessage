#include "message/datasources/datetimedatasource.hpp"
#include "factories/datasourcefactory.hpp"
#include "message/documentvisitor.hpp"

using macsa::dot::DateTimeDataSource;
using macsa::dot::IDocumentVisitor;

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


bool DateTimeDataSource::Accept(IDocumentVisitor* visitor)
{
	if (visitor) {
		return visitor->Visit(*this);
	}
	return false;
}


std::string DateTimeDataSource::GetFormat() const
{
	return _format;
}

void DateTimeDataSource::SetFormat(const std::string &format)
{
	_format = format;
}
