#include "dom/components/datasources/datetimedatasource.hpp"

#include <sstream>

#include "dom/factories/datasourcefactory.hpp"
#include "dom/documentvisitor.hpp"

using macsa::dot::DateTimeDataSource;
using macsa::dot::IDocumentVisitor;

bool DateTimeDataSource::_registered = macsa::dot::ConcreteDataSourceFactory<DateTimeDataSource>::Register(macsa::dot::NDataSourceType::kDateTime);

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

std::string DateTimeDataSource::GetData(Context* context) const
{
	std::stringstream ss;

	std::time_t result = std::time(nullptr);
	ss << std::asctime(std::localtime(&result));

	return ss.str();
}
