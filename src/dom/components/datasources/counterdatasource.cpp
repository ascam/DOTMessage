#include "dom/components/datasources/counterdatasource.hpp"
#include <cmath>
#include "dom/documentvisitor.hpp"
#include "dom/factories/datasourcefactory.hpp"

using macsa::dot::CounterDataSource;
using macsa::dot::IDocumentVisitor;

bool CounterDataSource::_registered = macsa::dot::ConcreteDataSourceFactory<CounterDataSource>::Register(macsa::dot::NDataSourceType::kCounter);

CounterDataSource::CounterDataSource(const dot::Object& obj) :
	DataSource(NDataSourceType::kCounter, obj),
	_leadingZeros{},
	_minValue{},
	_maxValue{},
	_step{},
	_repeatCounter{}
{}

bool CounterDataSource::Accept(IDocumentVisitor* visitor)
{
	if (visitor) {
		return visitor->Visit(*this);
	}
	return false;
}

std::string CounterDataSource::GetData(Context* context) const
{
	std::string returnValue;

	if (context != nullptr)	{
		std::string counterStr{};
		int min = std::min(_minValue, _maxValue);
		int max = std::max(_minValue, _maxValue);
		int counter = context->counter;

		// Rep control
		if (_repeatCounter > 0) {
			unsigned int timesRepeated = _repeatCounter + 1;
			counter = (counter - counter % timesRepeated) / timesRepeated;
		}

		// Range control
		if ((max > 0) || (_step < 0 && min < 0))
		{
			unsigned int range = 1 + (max - min);
			int nsteps = static_cast<int>(ceil((range*1.0)/_step));
			if (_step < 0) {
				nsteps = static_cast<int>(floor((range*1.0)/_step));
			}
			if (!nsteps) {
				nsteps = 1;
			}
			int modulus = (nsteps + (counter % nsteps)) % nsteps;
			counter = min + modulus * _step;
		}
		else {
			counter = min + counter * _step;
		}

		// Format control
		if (_leadingZeros) {
			std::stringstream ss;
			std::string sign{};
			if (counter < 0) {
				sign = "-";
				counter *= -1;
			}
			ss << sign << std::setw(_leadingZeros) << std::setfill('0') << counter;
			counterStr = ss.str();
		}
		else {
			counterStr = std::to_string(counter);
		}

		returnValue = std::move(counterStr);
	}

	return returnValue;
}
