const int MONTH_DAYS[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, ~
31, 30, 31};
// epoch is the first year of the world
const int epoch = 1700;
class Date{
    public:
        //month is zero based
    int year, month, day;
    Date(){}
    Date(int year, int month, int day):year(year), month(month­
1), day(day){}
    bool operator < (const Date &date) const {
        if (year != date.year)
            return year < date.year;
        if (month != date.month)
            return month < date.month;
        return day < date.day;
    }
    friend ostream& operator << (ostream &out, const Date &date)
{
        out << date.month+1 << "/" << date.day << "/" << 
date.year;
        return out;
    }
};
bool isLeap(int year){
    if (year % 400 == 0)
        return true;
    if (year % 100 == 0)
        return false;
    return (year % 4 == 0);
}
int getMonthDays(int year, int month){
    if (month != 1)
        return MONTH_DAYS[month];
    else
        return isLeap(year) ? 29 : 28;
}
//number of leap years between two years
int leapYears(int from, int to){ // [from, to)
    if (from >= to)
        return 0;
    to­­;
    int fours = to / 4 ­ from / 4;
    int hundreds = to / 100 ­ from / 100;
    int fhundreds = to / 400 ­ from / 400;
    if (isLeap(from))
        return fours ­ hundreds + fhundreds + 1;
    return fours ­ hundreds + fhundreds;
}
int dateToDay (Date date){
    int year = date.year;
    int month = date.month;
    int day = date.day;
    int days = (year ­ epoch) * 365;
    days += leapYears(epoch, year);
    for (int i=0 ; i<month ; i++)
        days += getMonthDays(year, i);
    days += day;
    return days;
}
Date dayToDate (int days){
    int year = days / 365;
    year += epoch;
    days %= 365;
    while (days <= leapYears(epoch, year)){
        year­­;
        days += 365;
    }
    days ­= leapYears(epoch, year);
    int month = 0;
    for (; month<12 && days > getMonthDays(year, month);month++)
        days ­= getMonthDays(year, month);
    return Date(year, month+1, days);
}
