#ifndef DOT_MESSAGE_DATE_AND_TIME_DATASOURCE_HPP
#define DOT_MESSAGE_DATE_AND_TIME_DATASOURCE_HPP

#include <string>

#include "dom/components/datasources/datasource.hpp"
#include "dom/components/datasources/datetimesource.hpp"
#include "dom/components/datasources/offsettime.hpp"
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
				DateTimeDataSource(const dot::Object& obj);
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
				std::string GetFormat() const;

				/**
				 * @brief SetFormat. Setter method for date and time
				 * format.
				 * @param format: The date and time format.
				 */
				void SetFormat(const std::string& format);

				/**
				 * @brief DaysOffset. Getter method for the days
				 * offset applied at the current date.
				 * @return the days offset applied at the current date.
				 */
				int GetDaysOffset() const {
					return _time.GetOffsetDays();
				}

				/**
				 * @brief SetDaysOffset. Setter method for the days
				 * offset to apply at the current date.
				 * @param DaysOffset: the days offset to apply at the
				 * current date.
				 */
				void SetDaysOffset(int daysOffset) {
					if (daysOffset != _time.GetOffsetDays())	{
						_time.SetOffsetDays(daysOffset);
						DaysOffsetChanged.Emit();
					}
				}

				/**
				 * @brief GetMonthsOffset. Getter method for the months
				 * offset applied at the current date.
				 * @return the months offset applied at the current date.
				 */
				int GetMonthsOffset() const {
					return _time.GetOffsetMonths();
				}

				/**
				 * @brief SetMonthsOffset. Setter method for the months
				 * offset to apply at the current date.
				 * @param offset: the months offset to apply at the
				 * current date.
				 */
				void SetMonthsOffset(int monthsOffset) {
					if (monthsOffset != _time.GetOffsetMonths())	{
						_time.SetOffsetMonths(monthsOffset);
						MonthOffsetChanged.Emit();
					}
				}

				/**
				 * @brief GetYearsOffset Getter method for the years
				 * offset applied at the current date.
				 * @return the years offset applied at the current date.
				 */
				int GetYearsOffset() const {
					return  _time.GetOffsetYears();
				}

				/**
				 * @brief SetYearsOffset. Setter method for the years
				 * offset to apply at the current date.
				 * @param offset: the years offset to apply at the
				 * current date.
				 */
				void SetYearsOffset(int yearsOffset) {
					if (yearsOffset != _time.GetOffsetYears())	{
						_time.SetOffsetYears(yearsOffset);
						YearsOffsetChanged.Emit();
					}
				}

				/**
				 * @brief GetHourDaysStart. Getter method for the hour
				 * which the day starts.
				 * @return the hour were the day changes to the next day.
				 */
				int GetHourDaysStart() const {
					return _time.GetHourDaysStart();
				}

				/**
				 * @brief SetHourDaysStart. Getter method for the hour
				 * which the day starts.
				 * @param hourDayStart: the hour were the day changes to the next day.
				 */
				void SetHourDaysStart(int hourDayStart) {
					if (hourDayStart != _time.GetHourDaysStart())	{
						_time.SetHourDaysStart(hourDayStart);
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
				static bool _registered;
				mutable OffsetTime _time;
				std::vector<std::unique_ptr<datetime::DateTimeSource>> _dateTimeSources;
		};
	}
}

#endif
