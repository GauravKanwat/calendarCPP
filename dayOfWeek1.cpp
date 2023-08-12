#include <iostream>
#include <vector>
#include<unordered_map>
#include <functional>

using namespace std;
class Date
{
public:
    string dayOfWeek;
    int month, dayOfMonth, year;
    Date(int month, int year, int dayOfMonth)
    {
        this->dayOfMonth = dayOfMonth;
        this->month = month;
        this->year = year;
    }
    bool operator==(const Date& d) const{
        return dayOfMonth == d.dayOfMonth && month == d.month && year == d.year;
    }
};
namespace std {
    template<>
    struct hash<Date> {
        size_t operator()(const Date& d) const {
            return hash<int>()(d.year) ^ hash<int>()(d.month) ^ hash<int>()(d.dayOfMonth);
        }
    };
}
class Calendar
{
private:
    string dayOfWeek;
    int month, dayOfMonth, year;
    vector<Date> holidays;
    unordered_map<Date, string> notes;

public:
    Calendar(const Date &d)
    {
        this->dayOfMonth = d.dayOfMonth;
        this->month = d.month;
        this->year = d.year;
        cout << getDay(d) << " - " << dayOfMonth << "/" << getMonth(d) << "/" << year << endl;
        getNextWeekDay(d);
        getNextHoliday(d);
        char choice1;
        cout << "Do you want to add a holiday? (y/n): ";
        cin >> choice1;
        while(choice1 == 'y' || choice1 == 'Y') {
            cout << "Enter holiday date: (dd mm yyyy): ";
            cin >> dayOfMonth >> month >> year;
            Date holiday(month, year, dayOfMonth);
            addHoliday(holiday);

            cout << "Do you want to add another holiday? (y/n): ";
            cin >> choice1;
        }
        printHoliday();
        char choice2;
        cout << "Do you want to jump to another date? (y/n): ";
        cin >> choice2;
        if(choice2 == 'y' || choice2 == 'Y') {
            cout << "Enter the number of days to add/subtract: ";
            int t;
            cin >> t;
            Date iterate = iterateDates(d, t);
            cout << "Jumped Date: " << iterate.dayOfMonth << "/" << getMonth(iterate) << "/" << getYear(iterate) << endl;
        }
        int gMonth, gYear;
        cout << "Enter the desired month and year (mm yyyy): ";
        cin >> gMonth >> gYear;
        if(gMonth < 1 || gMonth > 12 || gYear < 1400 || gYear > 2400) {
            cout << "Please enter valid month and year" << endl;
            return;
        }
        Date h(gMonth, gYear, dayOfMonth);
        int numberOfHolidays = getNumberOfHolidays(gMonth, gYear);
        cout << "Number of Holidays in " << getMonth(h) << " " << getYear(h) << ": " << numberOfHolidays << endl;

        cout << "Do you wish to know if a date is preceded another date? (y/n): ";
        char choice3;
        cin >> choice3;
        if(choice3 == 'y' || choice3 == 'Y') {
            int day1, day2, month1, month2, year1, year2;
            cout << "Enter first date (dd mm yyyy): ";
            cin >> day1 >> month1 >> year1;
            cout << "Enter second date (dd mm yyyy): ";
            cin >> day2 >> month2 >> year2;
            Date d1(day1, month1, year1);
            Date d2(day2, month2, year2);
            int isPreced = isPreceded(d1, d2);
            if(isPreced == 1) cout << "True";
            else cout << "False";
        }
        char choice4;
        cout << "Do you want to add a note? (y/n): ";
        cin >> choice4;
        while(choice4 == 'y' || choice4 == 'Y') {
            int day, month, year;
            cout << "Enter the date to add note to (dd mm yyyy): ";
            cin >> day >> month >> year;
            Date noteDate(month, year, day);
            cout << "Enter the note: ";
            cin.ignore();
            string note;
            getline(cin, note);
            addNoteToDate(noteDate, note);
            cout << "Do you want to add another note? (y/n): ";
            cin >> choice4;
        }
        char choice5;
        cout << "Do you want to remove a note? (y/n): ";
        cin >> choice5;
        while(choice5 == 'y' || choice5 == 'Y') {
            int day, month, year;
            cout << "Enter the date to remove note from (dd mm yyyy): ";
            cin >> day >> month >> year;
            Date remNote(month, year, day);
            cout << "Do you want to remove another note? (y/n): ";
            cin >> choice5;

            if(removeNoteFromDate(remNote)) cout << "Note removed successfully." << endl;
            else cout << "Note not found for the given date." << endl;
        }
    }
    string getDay(const Date &d)
    {
        int dayOfMonth = d.dayOfMonth;
        int month = d.month;
        int year = d.year;
        if (month < 3)
        {
            year--;
            month += 12;
        }
        int firstDigits = year / 100;
        int lastDigits = year % 100;

        string weekChart[7] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
        int monthNumber[12] = {0, 3, 3, 6, 1, 4, 6, 2, 5, 0, 3, 5}; // Zeller's Algorithm
        int centuryVal = centuryChart(year);
        int dayNumber = (dayOfMonth + 13 * (month + 1) / 5 + lastDigits + lastDigits / 4 + firstDigits / 4 + 5 * firstDigits) % 7;
        dayNumber = (dayNumber + 6) % 7;
        if (month == 2 && isLeapYear(year))
        {
            dayOfWeek = weekChart[(dayNumber + 1) % 7];
            return dayOfWeek;
        }
        dayOfWeek = weekChart[dayNumber];
        return dayOfWeek;
    }
    string getMonth(Date d)
    {
        string monthChart[12] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sept", "Oct", "Nov", "Dec"};
        return monthChart[d.month - 1];
    }
    int getYear(const Date &d) {
        int year = d.year;
        return year;
    }
    Date getNextWeekDay(const Date &d)
    {
        int nextDayOfMonth = d.dayOfMonth + 1;
        int nextMonth = d.month;
        int nextYear = d.year;
        if (nextDayOfMonth > daysInAMonth(nextMonth, nextYear))
        {
            nextDayOfMonth = 1;
            nextMonth += 1;
            if (nextMonth > 12)
            {
                nextMonth = 1;
                nextYear += 1;
            }
        }
        Date nextDate(nextMonth, nextYear, nextDayOfMonth);
        string nextWeekDay = getDay(nextDate);

        while (nextWeekDay == "Saturday" || nextWeekDay == "Sunday")
        {
            nextDayOfMonth += 1;
            if (nextDayOfMonth > daysInAMonth(nextMonth, nextYear))
            {
                nextMonth += 1;
                nextDayOfMonth = 1;
                if (nextMonth > 12)
                {
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
    Date getNextHoliday(const Date &d)
    {
        int nextDayOfMonth = d.dayOfMonth;
        int nextMonth = d.month;
        int nextYear = d.year;
        while (true)
        {
            nextDayOfMonth++;
            if (nextDayOfMonth > daysInAMonth(nextMonth, nextYear))
            {
                nextDayOfMonth = 1;
                nextMonth++;
                if (nextMonth > 12)
                {
                    nextMonth = 1;
                    nextYear++;
                }
            }
            Date nextDate(nextMonth, nextYear, nextDayOfMonth);
            string nextHoliday = getDay(nextDate);

            if(nextHoliday == "Saturday" || nextHoliday == "Sunday") {
                cout << "Next Holiday: " << nextHoliday << " - " << nextDayOfMonth << "/" << getMonth(nextDate) << "/" << nextYear << endl;
                return nextDate;
            }
        }
    }
    void addHoliday(Date d) {
        int day = d.dayOfMonth;
        int month = d.month;
        int year = d.year;
        if(day < 1 || day > 31 || month < 1 || month > 12 || year < 1400 || year > 2400) {
            cout << "Please enter a valid Date (dd mm yyyy)!" << endl;
            return;
        }
        this->dayOfMonth = day;
        this->month = month;
        this->year = year;
        
        Date holiday(month, year, day);
        holidays.push_back(holiday);
        cout << "Holiday added at: " << day << "/" << getMonth(holiday) << "/" << getYear(holiday) << endl;
    }
    void printHoliday() {
        cout << "List of added Holidays: " << endl;
        for(const Date& h : holidays) {
            cout << h.dayOfMonth << "/" << h.month << "/" << h.year << endl;
        }
    }
    Date iterateDates(const Date& d, int t) {
        int iday = d.dayOfMonth;
        int imonth = d.month;
        int iyear = d.year;

        while(t > 0) {
            iday++;
            if(iday > daysInAMonth(imonth, iyear)) {
                iday = 1;
                imonth++;
                if(imonth > 12) {
                    imonth = 1;
                    iyear++;
                }
            }
            t--;
        }

        while(t < 0) {
            iday--;
            if(iday < 1) {
                imonth--;
                if(imonth < 1) {
                    imonth = 12;
                    iyear--;
                }
                iday = daysInAMonth(imonth, iyear);
            }
            t++;
        }
        return Date(imonth, iyear, iday); 
    }
    int getNumberOfHolidays(int month, int year) {
        int holidaysInAMonth = 0;
        for(int i=0; i<daysInAMonth(month, year); i++) {
            Date current(month, year, i);
            string dayWeek = getDay(current);
            if(dayWeek == "Saturday" || dayWeek == "Sunday" || isHoliday(current)) {
                holidaysInAMonth++;
            }
        }
        return holidaysInAMonth;
    }
    bool isPreceded(Date d1, Date d2) {
        if(d1.year < d2.year)
            return true;
        else if(d1.year == d2.year && d1.month < d2.month)
            return true;
        else if(d1.year == d2.year && d1.month == d2.month && d1.dayOfMonth < d2.dayOfMonth)
            return true;
        else return false;
    }
    void addNoteToDate(Date d, string note) {
        int day = d.dayOfMonth;
        int month = d.month;
        int year = d.year;
        notes[d] = note;
        cout << "Note added to " << day << "/" << getMonth(d) << "/" << year << ": " << note << endl;
    }
    bool removeNoteFromDate(Date d) {
        auto i = notes.find(d);
        if(i != notes.end()) {
            notes.erase(i);
            return true;
        }
        else return false;
    }

private:
    bool isLeapYear(int year)
    {
        return (year % 4 == 0 && year % 100 != 0 || year % 400 == 0);
    }
    int centuryChart(int year)
    {
        if (year > 1400 && year < 1499)
            return 2;
        if (year > 1500 && year < 1599)
            return 0;
        if (year > 1600 && year < 1699)
            return 6;
        if (year > 1700 && year < 1799)
            return 4;
        if (year > 1800 && year < 1899)
            return 2;
        if (year > 1900 && year < 1999)
            return 0;
        if (year > 2000 && year < 2099)
            return 6;
        if (year > 2100 && year < 2199)
            return 4;
        if (year > 2200 && year < 2299)
            return 2;
        if (year > 2300 && year < 2399)
            return 0;
        else
            return -1;
    }
    int daysInAMonth(int month, int year)
    {
        int monthDays[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
        if (month == 2 && isLeapYear(year))
            return 29;
        return monthDays[month - 1];
    }
    bool isHoliday(const Date& d) {
        for(const Date& holiday : holidays) {
            if(holiday.dayOfMonth == d.dayOfMonth && holiday.month == d.month && holiday.year == d.year)
                return true;
            }
        return false;
    }
};

int main()
{
    int dayOfMonth, month, year;
    cout << "Enter desired date (dd mm yyyy): ";
    cin >> dayOfMonth >> month >> year;
    if (dayOfMonth < 1 || dayOfMonth > 31)
    {
        cout << "Please enter valid day!" << endl;
        return 1;
    }
    if (month < 1 || month > 12)
    {
        cout << "Please enter valid month!" << endl;
        return 1;
    }
    if (year < 1400 || year > 2400)
    {
        cout << "Please enter year in range (1400 - 2400)!" << endl;
        return 1;
    }
    Date date(month, year, dayOfMonth);
    Calendar cal(date);
}