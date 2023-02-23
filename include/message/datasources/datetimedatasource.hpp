#ifndef DOT_MESSAGE_DATE_AND_TIME_DATASOURCE_HPP
#define DOT_MESSAGE_DATE_AND_TIME_DATASOURCE_HPP

#include <string>
#include "message/datasources/datasource.hpp"
#include "vector"

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
					return _daysOffset;
				}
				/**
				 * @brief SetDaysOffset. Setter method for the days
				 * offset to apply at the current date.
				 * @param DaysOffset: the days offset to apply at the
				 * current date.
				 */
				void SetDaysOffset(int offset) {
					_daysOffset = offset;
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
					_monthsOffset = offset;
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
					_yearsOffset = offset;
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
					_hourDaysStart = hourDayStart;
				}

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
