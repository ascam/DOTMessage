#include "dom/datecodes.hpp"

#include <utility>
#include <cstdlib>
#include <sstream>
#include <iomanip>
#include <algorithm>

static constexpr unsigned kMinCodeFormaterLength = 6;	//[DC:H]
static constexpr unsigned kEveryDayDoW = 7;

using macsa::dot::DateCodeType;
using macsa::dot::NDateCodeType;
using macsa::dot::DateCodes;
using namespace macsa::dot::datecodes;

//**************** DateCodes Smart Enum ****************//
const std::vector<std::pair<NDateCodeType, std::string> > &DateCodeType::getData() const  {
	static const std::vector<std::pair<NDateCodeType,std::string>> kNDateCodeTypeData {
		{NDateCodeType::kTypeShift, kDateCodeTypeShift},
		{NDateCodeType::kTypeMinutes, kDateCodeTypeMinutes},
		{NDateCodeType::kTypeHours, kDateCodeTypeHours},
		{NDateCodeType::kTypeWeekDays, kDateCodeTypeWeekDay},
		{NDateCodeType::kTypeMonthDays, kDateCodeTypeMonthDay},
		{NDateCodeType::kTypeMonths, kDateCodeTypeMonth},
		{NDateCodeType::kTypeJulianDays, kDateCodeTypeJulian},
		{NDateCodeType::kTypeWeekOfYear, kDateCodeTypeWoY},
		{NDateCodeType::kTypeYears, kDateCodeTypeYears}
	};
	return kNDateCodeTypeData;
}

//**************** DateCodes ****************//

DCInterval::DCInterval(std::string format)
{
	_format = format;
}

void DCInterval::setValue(std::string value)
{
	if (formatIs(kCodeFormatMinute)){
		minute = std::atoi(value.c_str());
	}
	else if (formatIs(kCodeFormatHour)){
		hour = std::atoi(value.c_str());
	}
	else if (formatIs(kCodeFormatDOM)){
		dayOfMonth = std::atoi(value.c_str());
	}
	else if (formatIs(kCodeFormatDOW)){
		dayOfWeek = std::atoi(value.c_str());
	}
	else if (formatIs(kCodeFormatDOY)){
		dayOfYear = std::atoi(value.c_str());
	}
	else if (formatIs(kCodeFormatWOY)){
		weekOfYear = std::atoi(value.c_str());
	}
	else if (formatIs(kCodeFormatMonth)){
		month = std::atoi(value.c_str());
	}
	else if (formatIs(kCodeFormatYear)){
		year = std::atoi(value.c_str());
	}
	else if (formatIs(kCodeFormatShift)){
		std::size_t d = value.find_first_of(".");
		std::size_t h = value.find_first_of(":");
		if ((d != std::string::npos) && (h != std::string::npos)){
			std::string dow = value.substr(0,d);
			std::string hh = value.substr(d+1,(h-d-1));
			std::string mm = value.substr(h+1);
			dayOfWeek = std::atoi(dow.c_str());
			hour = std::atoi(hh.c_str());
			minute = std::atoi(mm.c_str());
		}
	}
}

std::string DCInterval::getValue() const
{
	std::string out;
	if (formatIs(kCodeFormatMinute)){
		out = toString(minute,2,'0');
	}
	else if (formatIs(kCodeFormatHour)){
		out = toString(hour,2,'0');
	}
	else if (formatIs(kCodeFormatDOM)){
		out = toString(dayOfMonth,2,'0');
	}
	else if (formatIs(kCodeFormatDOW)){
		out = toString(dayOfWeek,2,'0');
	}
	else if (formatIs(kCodeFormatDOY)){
		out = toString(dayOfYear,3,'0');
	}
	else if (formatIs(kCodeFormatWOY)){
		out = toString(weekOfYear,2,'0');
	}
	else if (formatIs(kCodeFormatMonth)){
		out = toString(month,2,'0');
	}
	else if (formatIs(kCodeFormatYear)){
		out = toString(year,4,'0');
	}
	else if (formatIs(kCodeFormatShift)){
		std::stringstream ss;
		std::string dow = toString(dayOfWeek);
		std::string hh = toString(hour,2,'0');
		std::string mm = toString(minute,2,'0');
		ss << dow << "." << hh << ":" << mm;
		out = ss.str();
	}
	return out;
}

int DCInterval::getMinute() const{return minute;}
int DCInterval::getHour() const{return hour;}
int DCInterval::getDayOfMonth() const{return dayOfMonth;}
int DCInterval::getDayOfWeek() const{return dayOfWeek;}
int DCInterval::getJulianDay() const{return dayOfYear;}
int DCInterval::getWeekOfYear() const{return weekOfYear;}
int DCInterval::getMonth() const{return month;}
int DCInterval::getYear() const{return year;}

void DCInterval::operator =(const DCInterval &other)
{
	copy(other);
}

bool DCInterval::operator <(const tm dateTime) const
{
	return  !greaterThan(dateTime);
}

bool DCInterval::operator >(const tm dateTime) const
{
	return greaterThan(dateTime);
}

void DCInterval::copy(const DCInterval &other)
{
	_format = other._format;
	minute = other.minute;
	hour = other.hour;
	dayOfMonth = other.dayOfMonth;
	dayOfWeek = other.dayOfWeek;
	dayOfYear = other.dayOfYear; //Julian day
	weekOfYear = other.weekOfYear;
	month = other.month;
	year = other.year;
}

bool DCInterval::formatIs(std::string format)const
{
	return (_format.compare(format) == 0);
}

bool DCInterval::greaterThan(const tm dateTime) const
{
	bool gt = false;

	if (formatIs(kCodeFormatMinute)){
		gt = minute > dateTime.tm_min;
	}
	else if (formatIs(kCodeFormatHour)){
		gt = hour > dateTime.tm_hour;
	}
	else if (formatIs(kCodeFormatDOM)){
		gt = dayOfMonth > dateTime.tm_mday;
	}
	else if (formatIs(kCodeFormatDOW)){
		int day = ((dateTime.tm_wday - 1) >= 0) ? (dateTime.tm_wday - 1) : 6;
		gt = dayOfWeek > day;
	}
	else if (formatIs(kCodeFormatDOY)){
		gt = dayOfYear > dateTime.tm_yday;
	}
	else if (formatIs(kCodeFormatWOY)){
		gt = weekOfYear > (dateTime.tm_yday / 7);
	}
	else if (formatIs(kCodeFormatMonth)){
		gt = month > (dateTime.tm_mon + 1);
	}
	else if (formatIs(kCodeFormatYear)){
		gt = year > (dateTime.tm_year + 1900);
	}
	else if (formatIs(kCodeFormatShift)) {
		int day = ((dateTime.tm_wday - 1) >= 0) ? (dateTime.tm_wday - 1) : 6;
		int dow = (dayOfWeek == kEveryDayDoW ? day : dayOfWeek);
		gt = (dow > day);
		if (dow == day) {
			gt = (hour > dateTime.tm_hour);
			if (hour == dateTime.tm_hour){
				gt = (minute > dateTime.tm_min);
			}
		}
	}

	return gt;
}

template<typename T>
std::string DCInterval::toString(const T& value, int size, const char fillchar)const
{
	std::ostringstream oss;
	oss.clear();
	if(size){
		oss << std::setw(size);
		oss << std::setfill(fillchar);
	}
	oss << value;
	return oss.str();
}

DateCodeGeneric::DateCodeGeneric(const std::string &format) :
	_interval(format)
{
	_format = format;
	_code = "";
}

DateCodeGeneric::~DateCodeGeneric()
{}

void DateCodeGeneric::setIntervalStart(const std::string& interval)
{
	return _interval.setValue(interval);
}

std::string DateCodeGeneric::getIntervalStart()const
{
	return  _interval.getValue();
}

const DCInterval &DateCodeGeneric::getInterval() const
{
	return _interval;
}

void DateCodeGeneric::setCode(const std::string& code)
{
	_code = code;
}

std::string DateCodeGeneric::getCode()const
{
	return _code;
}

std::string DateCodeGeneric::getFormat() const
{
	return _format;
}

void DateCodeGeneric::operator =(const DateCodeGeneric &other)
{
	copy(other);
}

bool DateCodeGeneric::operator ==(const DateCodeGeneric &other) const
{
	return compare(other);
}

bool DateCodeGeneric::operator !=(const DateCodeGeneric &other) const
{
	return !compare(other);
}

bool DateCodeGeneric::operator <(const DateCodeGeneric &other) const
{
	bool greater = gt(other);
	if (!greater) {
		return !compare(other);
	}
	return false;
}

bool DateCodeGeneric::operator <=(const DateCodeGeneric &other) const
{
	bool greater = gt(other);
	if (!greater) {
		return compare(other);
	}
	return false;
}

bool DateCodeGeneric::operator >(const DateCodeGeneric &other) const
{
	return gt(other);
}

bool DateCodeGeneric::operator >=(const DateCodeGeneric &other) const
{
	return (gt(other) || compare(other));
}

void DateCodeGeneric::copy(const DateCodeGeneric &other)
{
	_format = other._format;
	_code = other._code;
	_interval = other._interval;
}

bool DateCodeGeneric::compare(const DateCodeGeneric &other)const
{
	bool equal = false;
	if (_format == other._format) {
		if (getIntervalStart() == other.getIntervalStart()) {
			equal = (_code == other._code);
		}
	}
	return equal;
}

bool DateCodeGeneric::gt(const DateCodeGeneric &other) const
{
	bool greater = false;
	if (_format.compare(kCodeFormatShift) !=  0){
		greater = (std::atoi(_interval.getValue().c_str()) >
				  std::atoi(other._interval.getValue().c_str()));
	}
	else {
		greater = (_interval.getDayOfWeek() > other._interval.getDayOfWeek());
		if(_interval.getDayOfWeek() == other._interval.getDayOfWeek()){
			greater = (_interval.getHour() > other._interval.getHour());
			if(_interval.getHour() == other._interval.getHour()){
				greater = (_interval.getMinute() > other._interval.getMinute());
			}
		}
	}

	return greater;
}

DCMinute::DCMinute() : DateCodeGeneric (kCodeFormatMinute){}
DCHour::DCHour() : DateCodeGeneric (kCodeFormatHour){}
DCDay::DCDay() : DateCodeGeneric (kCodeFormatDOM){}
DCWeekDay::DCWeekDay() : DateCodeGeneric (kCodeFormatDOW){}
DCJulian::DCJulian() : DateCodeGeneric (kCodeFormatDOY){}
DCWeekOfYear::DCWeekOfYear() : DateCodeGeneric (kCodeFormatWOY){}
DCMonth::DCMonth() : DateCodeGeneric (kCodeFormatMonth){}
DCYear::DCYear() : DateCodeGeneric (kCodeFormatYear){}
DCShift::DCShift() : DateCodeGeneric (kCodeFormatShift){}

bool DCShift::gt(const DateCodeGeneric& other) const
{
	bool greater = false;
	if (_format.compare(kCodeFormatShift) !=  0){
		greater = (std::atoi(_interval.getValue().c_str()) >
				  std::atoi(other.getInterval().getValue().c_str()));
	}
	else {
		int dow = _interval.getDayOfWeek();
		int dowOther = other.getInterval().getDayOfWeek();
		if ((dow == kEveryDayDoW || dowOther == kEveryDayDoW) && dow != dowOther) {
			dow = (dow == kEveryDayDoW ? dowOther : dow);
			dowOther = (dowOther == kEveryDayDoW ? dow : dowOther);
		}

		greater = (dow > dowOther);
		if(dow == dowOther){
			greater = (_interval.getHour() > other.getInterval().getHour());
			if(_interval.getHour() == other.getInterval().getHour()){
				greater = (_interval.getMinute() > other.getInterval().getMinute());
			}
		}
	}

	return greater;
}
/************************************************************************************/

DateCodes::DateCodes()
{
	_codeFormaters.clear();
	_codeFormaters.insert(std::pair<std::string, std::string>(kCodeFormatMinute, "[DC:m]"));
	_codeFormaters.insert(std::pair<std::string, std::string>(kCodeFormatHour,	 "[DC:H]"));
	_codeFormaters.insert(std::pair<std::string, std::string>(kCodeFormatDOM,	 "[DC:dd]"));
	_codeFormaters.insert(std::pair<std::string, std::string>(kCodeFormatDOW,	 "[DC:ddd]"));
	_codeFormaters.insert(std::pair<std::string, std::string>(kCodeFormatDOY,	 "[DC:J]"));
	_codeFormaters.insert(std::pair<std::string, std::string>(kCodeFormatWOY,	 "[DC:w]"));
	_codeFormaters.insert(std::pair<std::string, std::string>(kCodeFormatMonth,	 "[DC:M]"));
	_codeFormaters.insert(std::pair<std::string, std::string>(kCodeFormatYear,	 "[DC:Y]"));
	_codeFormaters.insert(std::pair<std::string, std::string>(kCodeFormatShift,	 "[DC:S]"));

	clear();
}

DateCodes::DateCodes(DateCodes&& other) noexcept
{
	move(std::forward<DateCodes>(other));
}

DateCodes::~DateCodes()
{
	clear();
	_codeFormaters.clear();
}

bool DateCodes::addCode(const std::string& code, const std::string& format, const std::string& interval)
{
	DateCodeGeneric* ref = nullptr;

	if (format.compare(kCodeFormatMinute) == 0) {
		if ((_minuteCodes.size() < 60) && !exist(_minuteCodes, format, interval)) {
			DCMinute dc;
			ref = pushCode(_minuteCodes, dc, interval, code);
		}
	}
	else if (format.compare(kCodeFormatHour) == 0) {
		if ((_hourCodes.size() < 24) &&	!exist(_hourCodes, format, interval)) {
			DCHour dc;
			ref = pushCode(_hourCodes, dc, interval, code);
		}
	}
	else if (format.compare(kCodeFormatDOM) == 0) {
		if ((_dayCodes.size() < 31) &&	!exist(_dayCodes, format, interval)) {
			DCDay dc;
			ref = pushCode(_dayCodes, dc, interval, code);
		}
	}
	else if (format.compare(kCodeFormatDOW) == 0) {
		if ((_dayOfWeekCodes.size() < 7) && !exist(_dayOfWeekCodes, format, interval)) {
			DCWeekDay dc;
			ref = pushCode(_dayOfWeekCodes, dc, interval, code);
		}
	}
	else if (format.compare(kCodeFormatDOY) == 0) {
		if (!exist(_julianCodes, format, interval)) {
			DCJulian dc;
			ref = pushCode(_julianCodes, dc, interval, code);
		}
	}
	else if (format.compare(kCodeFormatWOY) == 0) {
		if (!exist(_weekOfYearCodes, format, interval)) {
			DCWeekOfYear dc;
			ref = pushCode(_weekOfYearCodes, dc, interval, code);
		}
	}
	else if (format.compare(kCodeFormatMonth) == 0) {
		if (!exist(_monthCodes, format, interval)) {
			DCMonth dc;
			ref = pushCode(_monthCodes, dc, interval, code);
		}
	}
	else if (format.compare(kCodeFormatYear) == 0) {
		if (!exist(_yearCodes, format, interval)) {
			DCYear dc;
			ref = pushCode(_yearCodes, dc, interval, code);
		}
	}
	else if (format.compare(kCodeFormatShift) == 0) {
		if (!exist(_shiftCodes, format, interval)) {
			DCShift dc;
			ref = pushCode(_shiftCodes, dc, interval, code);
		}
	}

	return (ref != nullptr);
}

bool DateCodes::setCode(const std::string& format, const std::string& interval, const std::string& code)
{
	int i = -1;
	if (format.compare(kCodeFormatMinute) == 0) {
		i = find(_minuteCodes, format, interval);
		if (i != -1) {
			_minuteCodes[static_cast<unsigned long>(i)].setCode(code);
		}
	}
	else if (format.compare(kCodeFormatHour) == 0) {
		i = find(_hourCodes, format, interval);
		if (i != -1) {
			_hourCodes[static_cast<unsigned long>(i)].setCode(code);
		}
	}
	else if (format.compare(kCodeFormatDOM) == 0) {
		i = find(_dayCodes, format, interval);
		if (i != -1) {
			_dayCodes[static_cast<unsigned long>(i)].setCode(code);
		}
	}
	else if (format.compare(kCodeFormatDOW) == 0) {
		i = find(_dayOfWeekCodes, format, interval);
		if (i != -1) {
			_dayOfWeekCodes[static_cast<unsigned long>(i)].setCode(code);
		}
	}
	else if (format.compare(kCodeFormatDOY) == 0) {
		i = find(_julianCodes, format, interval);
		if (i != -1) {
			_julianCodes[static_cast<unsigned long>(i)].setCode(code);
		}
	}
	else if (format.compare(kCodeFormatWOY) == 0) {
		i = find(_weekOfYearCodes, format, interval);
		if (i != -1) {
			_weekOfYearCodes[static_cast<unsigned long>(i)].setCode(code);
		}
	}
	else if (format.compare(kCodeFormatMonth) == 0) {
		i = find(_monthCodes, format, interval);
		if (i != -1) {
			_monthCodes[static_cast<unsigned long>(i)].setCode(code);
		}
	}
	else if (format.compare(kCodeFormatYear) == 0) {
		i = find(_yearCodes, format, interval);
		if (i != -1) {
			_yearCodes[static_cast<unsigned long>(i)].setCode(code);
		}
	}
	else if (format.compare(kCodeFormatShift) == 0) {
		i = find(_shiftCodes, format, interval);
		if (i != -1) {
			_shiftCodes[static_cast<unsigned long>(i)].setCode(code);
		}
	}

	return (i != -1);
}

bool DateCodes::setInterval(const std::string& format, const std::string &interval, const std::string& newInterval)
{
	if (format.compare(kCodeFormatMinute) == 0) {
		if (int i = find(_minuteCodes, format, interval); i != -1 && find(_minuteCodes, format, newInterval) == -1) {
			_minuteCodes[static_cast<unsigned long>(i)].setIntervalStart(newInterval);
			return true;
		}
	}
	else if (format.compare(kCodeFormatHour) == 0) {
		if (int i = find(_hourCodes, format, interval); i != -1 && find(_hourCodes, format, newInterval) == -1) {
			_hourCodes[static_cast<unsigned long>(i)].setIntervalStart(newInterval);
			return true;
		}
	}
	else if (format.compare(kCodeFormatDOM) == 0) {
		if (int i = find(_dayCodes, format, interval); i != -1 && find(_dayCodes, format, newInterval) == -1) {
			_dayCodes[static_cast<unsigned long>(i)].setIntervalStart(newInterval);
			return true;
		}
	}
	else if (format.compare(kCodeFormatDOW) == 0) {
		if (int i = find(_dayOfWeekCodes, format, interval); i != -1 && find(_dayOfWeekCodes, format, newInterval) == -1) {
			_dayOfWeekCodes[static_cast<unsigned long>(i)].setIntervalStart(newInterval);
			return true;
		}
	}
	else if (format.compare(kCodeFormatDOY) == 0) {
		if (int i = find(_julianCodes, format, interval); i != -1 && find(_julianCodes, format, newInterval) == -1) {
			_julianCodes[static_cast<unsigned long>(i)].setIntervalStart(newInterval);
			return true;
		}
	}
	else if (format.compare(kCodeFormatWOY) == 0) {
		if (int i = find(_weekOfYearCodes, format, interval); i != -1 && find(_weekOfYearCodes, format, newInterval) == -1) {
			_weekOfYearCodes[static_cast<unsigned long>(i)].setIntervalStart(newInterval);
			return true;
		}
	}
	else if (format.compare(kCodeFormatMonth) == 0) {
		if (int i = find(_monthCodes, format, interval); i != -1 && find(_monthCodes, format, newInterval) == -1) {
			_monthCodes[static_cast<unsigned long>(i)].setIntervalStart(newInterval);
			return true;
		}
	}
	else if (format.compare(kCodeFormatYear) == 0) {
		if (int i = find(_yearCodes, format, interval); i != -1 && find(_yearCodes, format, newInterval) == -1) {
			_yearCodes[static_cast<unsigned long>(i)].setIntervalStart(newInterval);
			return true;
		}
	}
	else if (format.compare(kCodeFormatShift) == 0) {
		if (int i = find(_shiftCodes, format, interval); i != -1 && find(_shiftCodes, format, newInterval) == -1) {
			_shiftCodes[static_cast<unsigned long>(i)].setIntervalStart(newInterval);
			return true;
		}
	}

	return false;
}

bool DateCodes::removeCode(const std::string& format, const std::string& interval)
{
	int idx = -1;

	if (format.compare(kCodeFormatMinute) == 0) {
		idx = find(_minuteCodes, format, interval);
		if (idx != -1) {
			_minuteCodes.erase(_minuteCodes.begin()+idx);
		}
	}
	else if (format.compare(kCodeFormatHour) == 0) {
		idx = find(_hourCodes, format, interval);
		if (idx != -1) {
			_hourCodes.erase(_hourCodes.begin()+idx);
		}
	}
	else if (format.compare(kCodeFormatDOM) == 0) {
		idx = find(_dayCodes, format, interval);
		if (idx != -1) {
			_dayCodes.erase(_dayCodes.begin()+idx);
		}
	}
	else if (format.compare(kCodeFormatDOW) == 0) {
		idx = find(_dayOfWeekCodes, format, interval);
		if (idx != -1) {
			_dayOfWeekCodes.erase(_dayOfWeekCodes.begin()+idx);
		}
	}
	else if (format.compare(kCodeFormatDOY) == 0) {
		idx = find(_julianCodes, format, interval);
		if (idx != -1) {
			_julianCodes.erase(_julianCodes.begin()+idx);
		}
	}
	else if (format.compare(kCodeFormatWOY) == 0) {
		idx = find(_weekOfYearCodes, format, interval);
		if (idx != -1) {
			_weekOfYearCodes.erase(_weekOfYearCodes.begin()+idx);
		}
	}
	else if (format.compare(kCodeFormatMonth) == 0) {
		idx = find(_monthCodes, format, interval);
		if (idx != -1) {
			_monthCodes.erase(_monthCodes.begin()+idx);
		}
	}
	else if (format.compare(kCodeFormatYear) == 0) {
		idx = find(_yearCodes, format, interval);
		if (idx != -1) {
			_yearCodes.erase(_yearCodes.begin()+idx);
		}
	}
	else if (format.compare(kCodeFormatShift) == 0) {
		idx = find(_shiftCodes, format, interval);
		if (idx != -1) {
			_shiftCodes.erase(_shiftCodes.begin()+idx);
		}
	}

	return idx != -1;
}

void DateCodes::clear()
{
	_minuteCodes.clear();
	_hourCodes.clear();
	_dayCodes.clear();
	_dayOfWeekCodes.clear();
	_julianCodes.clear();
	_weekOfYearCodes.clear();
	_monthCodes.clear();
	_yearCodes.clear();
	_shiftCodes.clear();
}

const std::vector<DCMinute>		&DateCodes::getMinuteCodes()		const{return _minuteCodes;}
const std::vector<DCHour>		&DateCodes::getHourCodes()			const{return _hourCodes;}
const std::vector<DCDay>		&DateCodes::getDayCodes()			const{return _dayCodes;}
const std::vector<DCWeekDay>	&DateCodes::getDayOfWeekCodes()		const{return _dayOfWeekCodes;}
const std::vector<DCJulian>		&DateCodes::getJulianCodes()		const{return _julianCodes;}
const std::vector<DCWeekOfYear> &DateCodes::getWeekOfYearCodes()	const{return _weekOfYearCodes;}
const std::vector<DCMonth>		&DateCodes::getMonthCodes()			const{return _monthCodes;}
const std::vector<DCYear>		&DateCodes::getYearCodes()			const{return _yearCodes;}
const std::vector<DCShift>		&DateCodes::getShiftCodes()			const{return _shiftCodes;}

std::vector<DateCodeGeneric> DateCodes::getAllCodes() const
{
	std::vector<DateCodeGeneric> codes;
	codes.clear();

	for (unsigned int i = 0; i < _minuteCodes.size(); i++)		{codes.push_back(_minuteCodes.at(i));}
	for (unsigned int i = 0; i < _hourCodes.size(); i++)		{codes.push_back(_hourCodes.at(i));}
	for (unsigned int i = 0; i < _dayCodes.size(); i++)			{codes.push_back(_dayCodes.at(i));}
	for (unsigned int i = 0; i < _dayOfWeekCodes.size(); i++)	{codes.push_back(_dayOfWeekCodes.at(i));}
	for (unsigned int i = 0; i < _julianCodes.size(); i++)		{codes.push_back(_julianCodes.at(i));}
	for (unsigned int i = 0; i < _weekOfYearCodes.size(); i++)	{codes.push_back(_weekOfYearCodes.at(i));}
	for (unsigned int i = 0; i < _monthCodes.size(); i++)		{codes.push_back(_monthCodes.at(i));}
	for (unsigned int i = 0; i < _yearCodes.size(); i++)		{codes.push_back(_yearCodes.at(i));}
	for (unsigned int i = 0; i < _shiftCodes.size(); i++)		{codes.push_back(_shiftCodes.at(i));}

	return codes;
}

void DateCodes::setMinuteCodes(const std::vector<DCMinute>& minuteCodes){ _minuteCodes = minuteCodes;}
void DateCodes::setHourCodes(const std::vector<DCHour>& hourCodes){  _hourCodes = hourCodes;}
void DateCodes::setDayCodes(const std::vector<DCDay>& dayCodes){ _dayCodes = dayCodes;}
void DateCodes::setDayOfWeekCodes(const std::vector<DCWeekDay>& dowCodes){	_dayOfWeekCodes = dowCodes;}
void DateCodes::setJulianCodes(const std::vector<DCJulian>& julianCodes){	_julianCodes = julianCodes;}
void DateCodes::setWeekOfYearCodes(const std::vector<DCWeekOfYear>& woyCodes) {	_weekOfYearCodes = woyCodes;}
void DateCodes::setMonthCodes(const std::vector<DCMonth>& monthCodes){ _monthCodes = monthCodes;}
void DateCodes::setYearCodes(const std::vector<DCYear>& yearCodes) { _yearCodes = yearCodes;}
void DateCodes::setShiftCodes(const std::vector<DCShift>& shiftCodes){ _shiftCodes = shiftCodes; }

std::string DateCodes::parserDateTime(const std::string& dateTimeFormat, const tm date) const
{
	std::string returnValue = dateTimeFormat;

	auto pos = dateTimeFormat.find_first_of("[");
	if (pos != std::string::npos) {

		if ((dateTimeFormat.substr(pos).size() >= kMinCodeFormaterLength) &&
			(dateTimeFormat.substr(pos + 1, 3).compare("DC:") == 0))
		{
			auto end = dateTimeFormat.find_first_of("]");
			if (end != std::string::npos) {

				size_t size = (end - pos) + 1;
				std::string dc = dateTimeFormat.substr(pos, size);
				std::string format = getFormatByCodeFormater(dc);
				if (!format.empty())	{
					returnValue = getCodeByFormat(format, date);
				}

				if (returnValue.empty())	{
					returnValue = dc;
				}
			}
		}
	}

	return returnValue;
}

bool DateCodes::isValid(std::string &dateTimeFormat_, int initalPos) const
{
	size_t pos = dateTimeFormat_.find("[DC:", static_cast<size_t>(initalPos));
	if (static_cast<int>(pos) >= 0){
		std::map<std::string, std::string>::const_iterator it;
		for (it = _codeFormaters.begin(); it != _codeFormaters.end(); it++){
			size_t ret = dateTimeFormat_.find(it->second, pos);
			if (ret != std::string::npos){
				return true;
			}
		}
	}
	return false;
}

std::string DateCodes::dateTimeCodeFormater(std::string codeFormat) const
{
	return _codeFormaters.at(codeFormat);
}

std::string DateCodes::getCodeByFormat(const std::string& format, const tm date) const
{
	std::string code;
	if (format.compare(kCodeFormatMinute) == 0) {
		code = getCode(_minuteCodes, date);
	}
	else if (format.compare(kCodeFormatHour) == 0) {
		code = getCode(_hourCodes, date);
	}
	else if (format.compare(kCodeFormatDOM) == 0) {
		code = getCode(_dayCodes, date);
	}
	else if (format.compare(kCodeFormatDOW) == 0) {
		code = getCode(_dayOfWeekCodes, date);
	}
	else if (format.compare(kCodeFormatDOY) == 0) {
		code = getCode(_julianCodes, date);
	}
	else if (format.compare(kCodeFormatWOY) == 0) {
		code = getCode(_weekOfYearCodes, date);
	}
	else if (format.compare(kCodeFormatMonth) == 0) {
		code = getCode(_monthCodes, date);
	}
	else if (format.compare(kCodeFormatYear) == 0) {
		code = getCode(_yearCodes, date);
	}
	else if (format.compare(kCodeFormatShift) == 0) {
		code = getCode(_shiftCodes, date);
	}

	return  code;
}

void DateCodes::operator =(const DateCodes& other)
{
	copy(other);
}

void DateCodes::operator =(DateCodes&& other) noexcept
{
	move(std::forward<DateCodes>(other));
}

bool DateCodes::operator ==(const DateCodes& other) const
{
	return equal(other);
}

bool DateCodes::operator !=(const DateCodes& other) const
{
	return !equal(other);
}

std::string DateCodes::getFormatByCodeFormater(const std::string& formater) const
{
	std::string format;

	for (auto it = _codeFormaters.cbegin(); it != _codeFormaters.cend(); it++) {
		if (it->second.compare(formater) == 0){
			format = it->first;
			break;
		}
	}

	return format;
}

bool DateCodes::equal(const DateCodes& other) const
{
	if (_minuteCodes     != other._minuteCodes)     return false;
	if (_hourCodes       != other._hourCodes)       return false;
	if (_dayCodes        != other._dayCodes)        return false;
	if (_dayOfWeekCodes  != other._dayOfWeekCodes)  return false;
	if (_julianCodes     != other._julianCodes)     return false;
	if (_weekOfYearCodes != other._weekOfYearCodes) return false;
	if (_monthCodes      != other._monthCodes)      return false;
	if (_yearCodes       != other._yearCodes)       return false;
	if (_shiftCodes      != other._shiftCodes)      return false;

	return true;
}

void DateCodes::copy(const DateCodes& other)
{
	_minuteCodes = other._minuteCodes;
	_hourCodes = other._hourCodes;
	_dayCodes = other._dayCodes;
	_dayOfWeekCodes = other._dayOfWeekCodes;
	_julianCodes = other._julianCodes;
	_weekOfYearCodes = other._weekOfYearCodes;
	_monthCodes	= other._monthCodes;
	_yearCodes = other._yearCodes;
	_shiftCodes = other._shiftCodes;
}

void DateCodes::move(DateCodes&& other) noexcept
{
	_minuteCodes = std::move(other._minuteCodes);
	_hourCodes = std::move(other._hourCodes);
	_dayCodes = std::move(other._dayCodes);
	_dayOfWeekCodes = std::move(other._dayOfWeekCodes);
	_julianCodes = std::move(other._julianCodes);
	_weekOfYearCodes = std::move(other._weekOfYearCodes);
	_monthCodes	= std::move(other._monthCodes);
	_yearCodes = std::move(other._yearCodes);
	_shiftCodes = std::move(other._shiftCodes);
}

template<class T>
bool DateCodes::exist(const std::vector<T> &data, std::string format, std::string interval) const
{
	return (find(data, format, interval) != -1);
}

template<class T>
DateCodeGeneric* DateCodes::pushCode(std::vector<T> &data, T &dc, const std::string& interval, const std::string& code)
{
	dc.setIntervalStart(interval);
	dc.setCode(code);
	data.push_back(dc);
	std::sort(data.begin(), data.end());
	return &dc;
}

template<class T>
int DateCodes::find(const std::vector<T> &data, std::string format, std::string interval) const
{
	DateCodeGeneric item(format);
	item.setIntervalStart(interval);
	for (unsigned int i = 0; i < data.size(); i++){
		if (data.at(i).getFormat() == item.getFormat() &&
			data.at(i).getIntervalStart() == item.getIntervalStart()){
			return static_cast<int>(i);
		}
	}
	return -1;
}

template<class T>
std::string DateCodes::getCode(const std::vector<T>& data, const tm dateTime) const
{
	std::string code;

	auto itInterval = std::find_if(data.crbegin(), data.crend(), [&dateTime](const T& item){
		return item.getInterval() < dateTime;
	});

	if (itInterval != data.crend())	{
		code = itInterval->getCode();
	}
	else {
		auto itLastElement = data.crbegin();
		if (itLastElement != data.crend()) {
			code = itLastElement->getCode();
		}
	}

	return code;
}

