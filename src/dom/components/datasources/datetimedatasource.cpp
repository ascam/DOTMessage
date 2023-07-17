#include "dom/components/datasources/datetimedatasource.hpp"

#include <sstream>

#include "dom/factories/datasourcefactory.hpp"
#include "dom/documentvisitor.hpp"
#include "dom/components/datasources/datetime/datetimesourcefactory.hpp"

using macsa::dot::DateTimeDataSource;
using macsa::dot::IDocumentVisitor;
using macsa::dot::datetime::DateTimeSourceFactory;

bool DateTimeDataSource::_registered = macsa::dot::ConcreteDataSourceFactory<DateTimeDataSource>::Register(macsa::dot::NDataSourceType::kDateTime);

DateTimeDataSource::DateTimeDataSource(const dot::Object& obj) :
	DataSource(NDataSourceType::kDateTime, obj)
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
	context->time = _time();

	std::stringstream ss;
	for (const auto& dateTimeSource : _dateTimeSources) {
		if (dateTimeSource) {
			ss << dateTimeSource->GetData(context);
		}
	}

	return ss.str();
}

macsa::dot::RefreshPolicy DateTimeDataSource::GetRefreshPolicy() const
{
	RefreshPolicy refreshPolicy = dot::RefreshPolicy::kNone;
	for (const auto& dateTimeSource : _dateTimeSources) {
		if (dateTimeSource) {
			refreshPolicy |= dateTimeSource->GetRefreshPolicy();
		}
	}
	return refreshPolicy;
}

std::string DateTimeDataSource::GetFormat() const
{
	std::stringstream ss;
	for (const auto& dateTimeSource  : _dateTimeSources) {
		if (dateTimeSource) {
			ss << dateTimeSource->GetFormat();
		}
	}

	return ss.str();
}

void DateTimeDataSource::SetFormat(const std::string& format)
{
	if (!format.empty()){
		if (!_dateTimeSources.empty()) {
			_dateTimeSources.clear();
		}

		DateTimeSourceFactory dateTimeFactoryParser;
		_dateTimeSources = dateTimeFactoryParser.parseFormatRegex(format);

		FormatChanged.Emit();
	}
}
