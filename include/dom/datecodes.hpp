#ifndef DOT_MESSAGE_DATECODES_HPP
#define DOT_MESSAGE_DATECODES_HPP

#include <string>
#include <vector>
#include <map>
#include <ctime>

#include "utils/smartenum.hpp"

static constexpr const char* kCodeFormatMinute = "m";
static constexpr const char* kCodeFormatHour   = "H";
static constexpr const char* kCodeFormatDOM    = "d";
static constexpr const char* kCodeFormatDOW    = "ddd";
static constexpr const char* kCodeFormatDOY    = "J";
static constexpr const char* kCodeFormatWOY    = "w";
static constexpr const char* kCodeFormatMonth	 = "M";
static constexpr const char* kCodeFormatYear   = "Y";
static constexpr const char* kCodeFormatShift	 = "S";

static constexpr const char* kDateCodeTypeShift    = "Shift";
static constexpr const char* kDateCodeTypeMinutes  = "Minutes";
static constexpr const char* kDateCodeTypeHours    = "Hours";
static constexpr const char* kDateCodeTypeWeekDay  = "Week_Days";
static constexpr const char* kDateCodeTypeMonthDay = "Month_Days";
static constexpr const char* kDateCodeTypeMonth    = "Months";
static constexpr const char* kDateCodeTypeJulian   = "Julian_Days";
static constexpr const char* kDateCodeTypeWoY      = "Weeks_Of_Year";
static constexpr const char* kDateCodeTypeYears    = "Years";


namespace macsa {
	namespace dot {

		enum class NDateCodeType{
			kTypeShift = 0,
			kTypeMinutes,
			kTypeHours,
			kTypeWeekDays,
			kTypeMonthDays,
			kTypeMonths,
			kTypeJulianDays,
			kTypeWeekOfYear,
			kTypeYears
		};

		class DateCodeType final : public utils::SmartEnum<NDateCodeType>
		{
			public:
				DateCodeType(NDateCodeType type = NDateCodeType::kTypeShift) :
					SmartEnum<NDateCodeType>(type)
				{}

				const DateCodeType& operator = (const std::string& val) {
					fromString(val);
					return *this;
				}

				const std::vector<std::pair<NDateCodeType, std::string>>& getData() const override;
		};

		namespace datecodes {
			class DCInterval{
				public:
					DCInterval(std::string format);
					void setValue(std::string value);
					std::string getValue()const;
					int getMinute()const;
					int getHour()const;
					int getDayOfMonth()const;
					int getDayOfWeek()const;
					int getJulianDay()const; //Julian day
					int getWeekOfYear()const;
					int getMonth()const;
					int getYear()const;

					void operator = (const DCInterval& other);
					bool operator < (const tm dateTime) const;
					bool operator > (const tm dateTime) const;

					inline std::string getFormat()const {return _format; } //temporal patch (remove after mcomms migration)

				private:
					std::string _format;
					int minute;
					int hour;
					int dayOfMonth;
					int dayOfWeek;
					int dayOfYear; //Julian day
					int weekOfYear;
					int month;
					int year;

					void copy (const DCInterval& other);
					bool formatIs(std::string format)const;
					bool greaterThan(const tm dateTime)const;
					template<typename T>
					std::string toString(const T& value, int size = 0, const char fillchar = ' ')const;
			};

			class DateCodeGeneric
			{
				public:
					DateCodeGeneric(const std::string& format);
					virtual ~DateCodeGeneric();
					virtual void setIntervalStart(const std::string& interval);
					virtual std::string getIntervalStart()const;
					virtual const DCInterval &getInterval()const;
					virtual void setCode(const std::string& code);
					virtual std::string getCode()const;
					virtual std::string getFormat()const;

					void operator = (const DateCodeGeneric& other);
					bool operator == (const DateCodeGeneric& other) const;
					bool operator != (const DateCodeGeneric& other) const;
					bool operator < (const DateCodeGeneric& other) const;
					bool operator <= (const DateCodeGeneric& other) const;
					bool operator > (const DateCodeGeneric& other) const;
					bool operator >= (const DateCodeGeneric& other) const;

				protected:
					std::string _format;
					std::string _code;
					DCInterval _interval;

					virtual void copy(const DateCodeGeneric& other);
					virtual bool compare(const DateCodeGeneric& other)const;
					virtual bool gt(const DateCodeGeneric& other)const;
			};

			class DCMinute : public DateCodeGeneric{
				public:
					DCMinute();
			};
			class DCHour : public DateCodeGeneric {
				public:
					DCHour();
			};
			class DCDay : public DateCodeGeneric {
				public:
					DCDay();
			};
			class DCWeekDay : public DateCodeGeneric {
				public:
					DCWeekDay();
			};
			class DCJulian : public DateCodeGeneric {
				public:
					DCJulian();
			};
			class DCWeekOfYear : public DateCodeGeneric {
				public:
					DCWeekOfYear();
			};
			class DCMonth : public DateCodeGeneric {
				public:
					DCMonth();
			};
			class DCYear : public DateCodeGeneric {
				public:
					DCYear();
			};
			class DCShift : public DateCodeGeneric {
				public:
					DCShift();
				protected:
					bool gt(const DateCodeGeneric &other) const override;
			};
		}

		class DateCodes
		{
			public:
				DateCodes();
				DateCodes(const DateCodes&) = default;
				DateCodes(DateCodes&& other) noexcept;
				virtual ~DateCodes();

				bool addCode(const std::string& code, const std::string& format, const std::string& interval);
				bool setCode(const std::string& format, const std::string &interval, const std::string& code);
				bool setInterval(const std::string& format, const std::string &interval, const std::string& newInterval);
				bool removeCode(const std::string& format, const std::string& interval);
				void clear();

				const std::vector<datecodes::DCHour>& getHourCodes() const;
				const std::vector<datecodes::DCDay>& getDayCodes() const;
				const std::vector<datecodes::DCWeekDay>& getDayOfWeekCodes() const;
				const std::vector<datecodes::DCJulian>& getJulianCodes() const;
				const std::vector<datecodes::DCWeekOfYear>& getWeekOfYearCodes() const;
				const std::vector<datecodes::DCMonth>& getMonthCodes() const;
				const std::vector<datecodes::DCYear>& getYearCodes() const;
				const std::vector<datecodes::DCShift>& getShiftCodes() const;
				std::vector<datecodes::DateCodeGeneric> getAllCodes() const;
				void setMinuteCodes(const std::vector<datecodes::DCMinute>& minuteCodes);
				const std::vector<datecodes::DCMinute>& getMinuteCodes() const;
				void setHourCodes(const std::vector<datecodes::DCHour>& hourCodes);
				void setDayCodes(const std::vector<datecodes::DCDay>& dayCodes);
				void setDayOfWeekCodes(const std::vector<datecodes::DCWeekDay>& dowCodes);
				void setJulianCodes(const std::vector<datecodes::DCJulian>& julianCodes);
				void setWeekOfYearCodes(const std::vector<datecodes::DCWeekOfYear>& woyCodes);
				void setMonthCodes(const std::vector<datecodes::DCMonth>& monthCodes);
				void setYearCodes(const std::vector<datecodes::DCYear>& yearCodes);
				void setShiftCodes(const std::vector<datecodes::DCShift>& shiftCodes);


				std::string parserDateTime(const std::string& dateTimeFormat, const std::tm date) const;
				bool isValid(std::string &dateTimeFormat_, int initialPos = 0) const;
				std::string dateTimeCodeFormater(std::string codeFormat) const;
				std::string getCodeByFormat(const std::string &format, const tm date) const;

				void operator = (const DateCodes& other);
				void operator = (DateCodes&& other) noexcept;
				bool operator == (const DateCodes& other) const;
				bool operator != (const DateCodes& other) const;


			protected:
				std::vector<datecodes::DCMinute>		_minuteCodes;
				std::vector<datecodes::DCHour>		_hourCodes;
				std::vector<datecodes::DCDay>		_dayCodes;
				std::vector<datecodes::DCWeekDay>	_dayOfWeekCodes;
				std::vector<datecodes::DCJulian>		_julianCodes;
				std::vector<datecodes::DCWeekOfYear>	_weekOfYearCodes;
				std::vector<datecodes::DCMonth>		_monthCodes;
				std::vector<datecodes::DCYear>		_yearCodes;
				std::vector<datecodes::DCShift>		_shiftCodes;
				std::map<std::string, std::string>	_codeFormaters;

				std::string getFormatByCodeFormater(const std::string& formater) const;

				bool equal(const DateCodes& other) const;
				void copy(const DateCodes& other);
				void move(DateCodes&& other) noexcept;

				template<class T>
				int find(const std::vector<T>& data, std::string format, std::string interval) const;
				template<class T>
				bool exist(const std::vector<T>& data, std::string format, std::string interval) const;
				template<class T>
				void sort(std::vector<T>& data) const;
				template<class T>
				std::string getCode(const std::vector<T>& data, const tm dateTime) const;
				template<class T>
				datecodes::DateCodeGeneric* pushCode(std::vector<T> &data, T &dc, const std::string& interval, const std::string& code);
		};
	}
}

#endif
