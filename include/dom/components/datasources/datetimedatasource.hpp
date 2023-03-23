#ifndef DOT_MESSAGE_DATE_AND_TIME_DATASOURCE_HPP
#define DOT_MESSAGE_DATE_AND_TIME_DATASOURCE_HPP

#include <string>
#include "dom/components/datasources/datasource.hpp"
#include "dom/rippers/context.hpp"
#include "signal/signal.hpp"

namespace macsa {
	namespace dot {
		class IDocumentVisitor;

		/**
		 * @brief The DateTimeDataSource class. This class allow the objects
		 * to return variable data from a formated date and time.
		 */
		class DateTimeDataSource final : public DataSource
		{
			public:
				DateTimeDataSource();
				virtual ~DateTimeDataSource() = default;

				/**
				 * @brief Accept: Allow the visitor to visit this object.
				 * @param visitor: Visitor object
				 * @return boolean with the result of the visit method
				 * of the visitor object.
				 */
				bool Accept(IDocumentVisitor* visitor) override;

				/**
				 * @brief GetFormat. Getter method for date and time
				 * format.
				 * @return The date and time format used to return
				 * the data
				 */
				std::string GetFormat() const
				{
					return _format;
				}

				/**
				 * @brief SetFormat. Setter method for date and time
				 * format.
				 * @param format: The date and time format.
				 */
				void SetFormat(const std::string& format)
				{
					if (format != _format)	{
						_format = format;
						FormatChanged.Emit();
					}
				}

				/**
				 * @brief DaysOffset. Getter method for the days
				 * offset applied at the current date.
				 * @return the days offset applied at the current date.
				 */
				int GetDaysOffset() const {
					return _daysOffset;
				}

				/**
				 * @brief SetDaysOffset. Setter method for the days
				 * offset to apply at the current date.
				 * @param DaysOffset: the days offset to apply at the
				 * current date.
				 */
				void SetDaysOffset(int offset) {
					if (offset != _daysOffset)	{
						_daysOffset = offset;
						DaysOffsetChanged.Emit();
					}
				}

				/**
				 * @brief GetMonthsOffset. Getter method for the months
				 * offset applied at the current date.
				 * @return the months offset applied at the current date.
				 */
				int GetMonthsOffset() const {
					return _monthsOffset;
				}

				/**
				 * @brief SetMonthsOffset. Setter method for the months
				 * offset to apply at the current date.
				 * @param offset: the months offset to apply at the
				 * current date.
				 */
				void SetMonthsOffset(int offset) {
					if (offset != _monthsOffset)	{
						_monthsOffset = offset;
						MonthOffsetChanged.Emit();
					}
				}

				/**
				 * @brief GetYearsOffset Getter method for the years
				 * offset applied at the current date.
				 * @return the years offset applied at the current date.
				 */
				int GetYearsOffset() const {
					return _yearsOffset;
				}

				/**
				 * @brief SetYearsOffset. Setter method for the years
				 * offset to apply at the current date.
				 * @param offset: the years offset to apply at the
				 * current date.
				 */
				void SetYearsOffset(int offset) {
					if (offset != _yearsOffset)	{
						_yearsOffset = offset;
						YearsOffsetChanged.Emit();
					}
				}

				/**
				 * @brief GetHourDaysStart. Getter method for the hour
				 * which the day starts.
				 * @return the hour were the day changes to the next day.
				 */
				uint GetHourDaysStart() const {
					return _hourDaysStart;
				}

				/**
				 * @brief SetHourDaysStart. Getter method for the hour
				 * which the day starts.
				 * @param hourDayStart: the hour were the day changes to the next day.
				 */
				void SetHourDaysStart(uint hourDayStart) {
					if (hourDayStart != _hourDaysStart)	{
						_hourDaysStart = hourDayStart;
						HourDaysStartChanged.Emit();
					}
				}

				/**
				 * @brief GetData. Get data source updated data result.
				 * @return data source text result data.
				 */
				std::string GetData(Context* context) const override;

			public:
				Signal<> HourDaysStartChanged;
				Signal<> YearsOffsetChanged;
				Signal<> MonthOffsetChanged;
				Signal<> DaysOffsetChanged;
				Signal<> FormatChanged;

			private:
				std::string _format;
				int _daysOffset;
				int _monthsOffset;
				int _yearsOffset;
				uint _hourDaysStart;
		};
	}
}

#endif
