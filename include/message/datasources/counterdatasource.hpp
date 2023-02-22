#ifndef DOT_MESSAGE_COUNTER_DATASOURCE_HPP
#define DOT_MESSAGE_COUNTER_DATASOURCE_HPP

#include <string>
#include <cstdint>
#include "message/datasources/datasource.hpp"

namespace macsa {
	namespace dot {
		/**
		 * @brief The CounterDataSource class. This class allow the objects
		 * to return variable data
		 */
		class CounterDataSource final : public DataSource
		{
			public:
				CounterDataSource();
				virtual ~CounterDataSource();

				/**
				 * @brief GetData. Getter method to get the inner data
				 * of a data source.
				 * @return The text generated with the inner data of a
				 * data source.
				 */
				std::string GetData() override;

				/**
				 * @brief GetRefreshPolicy. Getter method to get the refresh
				 * policy of a data source.
				 * @return The refresh policy of the data source.
				 */
				RefreshPolicy GetRefreshPolicy() const override {
					return RefreshPolicy::kCounter;
				};

				/**
				 * @brief GetCounterValue. Getter method for the current
				 * source counter value.
				 * @return The current source counter value
				 */
				int GetCounterValue() const {
					return _counter;
				}

				/**
				 * @brief SetCounterValue. Setter method for the current
				 * source counter value.
				 * @param value: source counter value
				 */
				void SetCounterValue(int value) {
					_counter = value;
				}

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
				void SetLeadingZeros(uint32_t zeros) {
					_leadingZeros = zeros;
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
					_minValue = minValue;
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
					_maxValue = maxValue;
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
					_repeatCounter = repeatCounter;
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
					_step = step;
				}

			private:
				int _counter;
				uint32_t _leadingZeros;
				int _minValue;
				int _maxValue;
				int _step;
				uint _repeatCounter;
		};
	}
}

#endif
