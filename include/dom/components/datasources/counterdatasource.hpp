#ifndef DOT_MESSAGE_COUNTER_DATASOURCE_HPP
#define DOT_MESSAGE_COUNTER_DATASOURCE_HPP

#include <string>
#include <cstdint>

#include "dom/components/datasources/datasource.hpp"
#include "dom/rippers/context.hpp"

#include <signal/signal.hpp>

namespace macsa {
	namespace dot {

		class IDocumentVisitor;

		/**
		 * @brief The CounterDataSource class. This class allow the objects
		 * to return variable data
		 */
		class CounterDataSource final : public DataSource
		{
			public:
				CounterDataSource();
				virtual ~CounterDataSource() = default;

				/**
				 * @brief Accept: Allow the visitor to visit this object.
				 * @param visitor: Visitor object
				 * @return boolean with the result of the visit method
				 * of the visitor object.
				 */
				bool Accept(IDocumentVisitor* visitor) override;

				/**
				 * @brief GetLeadingZeros. Getter method for number of
				 * leading zeros
				 * @return Configured leading zeros.
				 */
				uint32_t GetLeadingZeros() const {
					return _leadingZeros;
				}

				/**
				 * @brief SetLeadingZeros. Setter method for number of
				 * leading zeros
				 * @param zeros: number of leading zeros to print.
				 */
				void SetLeadingZeros(uint32_t leadingZeros) {
					if (leadingZeros != _leadingZeros)	{
						_leadingZeros = leadingZeros;
						LeadingZerosChanged.Emit();
					}
				}

				/**
				 * @brief GetMinValue. Getter method for the minimum value
				 * of the printed counter.
				 * @return the minimum value of the printed counter.
				 */
				int GetMinValue() const {
					return _minValue;
				}

				/**
				 * @brief SetMinValue. Setter method for the minimum value
				 * of the printed counter.
				 * @param minValue: the minimum value to print.
				 */
				void SetMinValue(int minValue) {
					if (minValue != _minValue)	{
						_minValue = minValue;
						MinValueChanged.Emit();
					}
				}

				/**
				 * @brief GetMaxValue. Getter method for the maximum value
				 * of the printed counter.
				 * @return the maximum value of the printed counter.
				 */
				int GetMaxValue() const {
					return _maxValue;
				}

				/**
				 * @brief SetMaxValue. Setter method for the maximum value
				 * of the printed counter.
				 * @param maxValue: the maximum value to print.
				 */
				void SetMaxValue(int maxValue) {
					if (maxValue != _maxValue)	{
						_maxValue = maxValue;
						MaxValueChanged.Emit();
					}
				}

				/**
				 * @brief GetRepeatCounter. Getter method for repeat counter.
				 * @return how many times the counter will be the same
				 * before jump to the next value.
				 */
				uint GetRepeatCounter() const {
					return _repeatCounter;
				}

				/**
				 * @brief SetRepeatCounter. Setter method for repeat counter.
				 * @param repeatCounter: how many times the counter will be the same
				 * before jump to the next value.
				 */
				void SetRepeatCounter(uint repeatCounter) {
					if (repeatCounter != _repeatCounter)	{
						_repeatCounter = repeatCounter;
						RepeatCounterChanged.Emit();
					}
				}

				/**
				 * @brief GetStep. Getter method for counter's step.
				 * @return how many counts will jump in a step.
				 */
				int GetStep() const {
					return _step;
				}

				/**
				 * @brief SetStep. Setter method for counter's step.
				 * @param step: how many counts will jump in a step.
				 */
				void SetStep(int step) {
					if (_step != step)	{
						_step = step;
						StepChanged.Emit();
					}
				}

				/**
				 * @brief GetData. Get data source updated data result.
				 * @return data source text result data.
				 */
				std::string GetData(Context* context) const;

			public:
				Signal<> StepChanged;
				Signal<> RepeatCounterChanged;
				Signal<> MaxValueChanged;
				Signal<> MinValueChanged;
				Signal<> LeadingZerosChanged;
				Signal<> CounterValueChanged;

			private:
				uint32_t _leadingZeros;
				int _minValue;
				int _maxValue;
				int _step;
				uint _repeatCounter;
		};
	}
}

#endif
