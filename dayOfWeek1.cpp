#include<iostream>
using namespace std;

class Date {
    public:
    string dayOfWeek;
    int month, dayOfMonth, year;
    Date(int month, int year, int dayOfMonth) {
        this->dayOfMonth = dayOfMonth;
        this->month = month;
        this->year = year;
    }
};

class Calendar {
    private:
    string dayOfWeek;
    int month, dayOfMonth, year;
    public:
    Calendar(const Date& d) {
        this->dayOfMonth = d.dayOfMonth;
        this->month = d.month;
        this->year = d.year;
        cout << getDay(d) << " - " << dayOfMonth << "/" << getMonth(d) << "/" << year << endl;
        getNextWeekDay(d);
    }
    string getDay(const Date& d) {
        if(month < 3) {
            year--;
            month += 12;
        }
        int firstDigits = year / 100;
        int lastDigits = year % 100;

        string weekChart[7] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
        int monthNumber[12] = {0, 3, 3, 6, 1, 4, 6, 2, 5, 0, 3, 5}; //Zeller's Algorithm 
        int centuryVal = centuryChart(year);
        int dayNumber = (dayOfMonth + 13*(month+1)/5 + lastDigits + lastDigits/4 + firstDigits/4 + 5*firstDigits) % 7;
        dayNumber = (dayNumber+6) % 7;
        if(month == 2 && isLeapYear(year)) {
            dayOfWeek = weekChart[(dayNumber+1)%7];
            return dayOfWeek;
        }
        dayOfWeek = weekChart[dayNumber];
        return dayOfWeek;
    }
    string getMonth(Date d) {
        string monthChart[12] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sept", "Oct", "Nov", "Dec"};
        return monthChart[month-1];
    }
    Date getNextWeekDay(const Date& d) {
        int nextDayOfMonth = d.dayOfMonth + 1;
        int nextMonth = d.month;
        int nextYear = d.year;

        if(nextDayOfMonth > daysInAMonth(nextMonth, nextYear)) {
            nextDayOfMonth = 1;
            nextMonth += 1;
            if(nextMonth > 12) {
                nextMonth = 1;
                nextYear += 1;
            }
        }
        Date nextDate(nextMonth, nextYear, nextDayOfMonth);
        string nextWeekDay = getDay(nextDate);

        while(nextWeekDay == "Saturday" || nextWeekDay == "Sunday") {
            nextDayOfMonth += 1;
            if(nextDayOfMonth > daysInAMonth(nextMonth, nextYear)) {
                nextMonth += 1;
                nextDayOfMonth = 1;
                if(nextMonth > 12) {
                    nextMonth = 1;
                    nextYear += 1;
                }
            }
        nextDate = Date(nextMonth, nextYear, nextDayOfMonth);
        nextWeekDay = getDay(nextDate);
        }
        cout << "Next Weekday: " << nextWeekDay << " - " << nextDayOfMonth << "/" << getMonth(nextDate) << "/" << nextYear << endl;
        return nextDate;
    }
    private:
    bool isLeapYear(int year) {
        return (year % 4 == 0 && year % 100 != 0 || year % 400 == 0);
    }
    int centuryChart(int year) {
        if(year > 1400 && year < 1499) return 2;
        if(year > 1500 && year < 1599) return 0;
        if(year > 1600 && year < 1699) return 6;
        if(year > 1700 && year < 1799) return 4;
        if(year > 1800 && year < 1899) return 2;
        if(year > 1900 && year < 1999) return 0;
        if(year > 2000 && year < 2099) return 6;
        if(year > 2100 && year < 2199) return 4;
        if(year > 2200 && year < 2299) return 2;
        if(year > 2300 && year < 2399) return 0;
        else return -1;
    }
    int daysInAMonth(int month, int year) {
        int monthDays[12] = {31,28,31,30,31,30,31,31,30,31,30,31};
        if(month == 2 && isLeapYear(year))
            return 29;
        return monthDays[month - 1];
    }
};

int main() {
    int dayOfMonth, month, year;
    cout << "Enter desired date (dd mm yyyy): ";
    cin >> dayOfMonth >> month >> year;
    if(dayOfMonth < 1 || dayOfMonth > 31) {
        cout << "Please enter valid day!" << endl;
        return 1;
    }
    if(month < 1 || month > 12) {
        cout << "Please enter valid month!" << endl;
        return 1;
    }
    if(year < 1400 || year > 2400) {
        cout << "Please enter year in range (1400 - 2400)!" << endl;
        return 1;
    }
    Date date(month, year, dayOfMonth);
    Calendar cal(date);
}