#include <iostream>
using namespace std;

class Date {
    public:
    string dayOfWeek;
    int month, dayOfMonth, year;
    
    string findWeekDay(int day, int month, int year) {
        if(month < 3) {
            year--;
            month += 12;
        }
        int firstDigits = year / 100;
        int lastDigits = year % 100;

        string weekChart[7] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
        int monthNumber[12] = {0, 3, 3, 6, 1, 4, 6, 2, 5, 0, 3, 5}; //Zeller's Algorithm 
        int centuryVal = centuryChart(year);
        int dayNumber = (day + 13*(month+1)/5 + lastDigits + lastDigits/4 + firstDigits/4 + 5*firstDigits) % 7;
        dayNumber = (dayNumber+6) % 7;
        if(month == 2 && isLeapYear(year)) {
            dayOfWeek = weekChart[(dayNumber+1)%7];
            return dayOfWeek;
        }
        dayOfWeek = weekChart[dayNumber];
        return dayOfWeek;
    }
    string getMonth(int month) {
        string monthChart[12] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sept", "Oct", "Nov", "Dec"};
        return monthChart[month-1];
    }

    Date(int dayOfMonth, int month, int year) {
        this->month = month;
        this->dayOfMonth = dayOfMonth;
        this->year = year;
        cout << findWeekDay(dayOfMonth, month, year) << " - " << dayOfMonth << "/" << getMonth(month) << "/" << year << endl; 
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

class Calendar {
    private:
    string dayOfWeek;
    int dayOfMonth, month, year;
    public:
    string getDay(Date d) {
        dayOfWeek = d.dayOfWeek;
        return "";
    }
    string getMonth(Date d) {
        month = d.month;
        return "";
    }
    string getYear(Date d) {
        year = d.year;
        return "";
    }
    private:
    string getNextWeekDay(Date d) {
        string weekDays[5] = {"Monday", "Tuesday", "Wednesday", "Thursday", "Friday"};
        string currentDay = d.dayOfWeek;
        int currentDayIdx = -1;
        for(int i=0; i<7; i++) {
            if(weekDays[i] == currentDay) {
                currentDayIdx = i;
                break;
            }
        }
        if(currentDayIdx == -1) {
            cout << "Please enter valid day!" << endl;
            return "!!!!";
        }
        int nextWeekDayIdx = (currentDayIdx+1)%5;
        string nextWeekDay = weekDays[nextWeekDayIdx];
        return nextWeekDay;
    }
    // void dateNextWeekDay(Date d) {
    //     string nextWeekDay = getNextWeekDay(d);
    //     if(!nextWeekDay.empty()) {
    //         int addExtraDays = 1;
    //         if(nextWeekDay == "Tuesday") addExtraDays += 1;
    //         if(nextWeekDay == "Wednesday") addExtraDays += 2;
    //         if(nextWeekDay == "Thursday") addExtraDays += 3;
    //         if(nextWeekDay == "Friday") addExtraDays += 4;
    //         cout << dayOfMonth << "/" << month << "/";
    //     }
    // }
    Date getNextHoliday(Date d) {
        Date nextHolidayDate = d;
        while(isWeekend(nextHolidayDate)) {
        }
    }
    bool isWeekend(Date d) {
        return (d.dayOfWeek == "Saturday" || d.dayOfWeek == "Sunday");
    }
    public:
    Calendar(int dayOfMonth, int month, int year) {
        this->dayOfMonth = dayOfMonth;
        this->month = month;
        this->year = year;
        Date d(dayOfMonth, month, year);
        cout << "Next Weekday is: " << getNextWeekDay(d) << endl;
    }
};

int main() {
    int day, month, year;
    cout << "Enter desired date (dd mm yyyy): ";
    cin >> day >> month >> year;
    if(day < 1 || day > 31) {
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
    // Date d(day, month, year);
    Calendar C(day, month, year);
    return 0;
}