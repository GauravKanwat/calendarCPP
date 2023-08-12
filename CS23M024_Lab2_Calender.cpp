#include <iostream>
#include <vector>
#include <unordered_map>
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
    bool operator==(const Date &d) const
    {
        return dayOfMonth == d.dayOfMonth && month == d.month && year == d.year;
    }
    bool operator!=(const Date &d) const
    {
        return !(*this == d);
    }
};

struct Notes
{
    Date date;
    std::string content;
    Notes() : date(0, 0, 0), content("") {}
    Notes(const Date &d, std::string &c) : date(d), content(c) {}
};
namespace std
{
    template <>
    struct hash<Date>
    {
        size_t operator()(const Date &d) const
        {
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

public:
    unordered_map<Date, string> notes;
    Calendar(const Date &d)
    {
        this->dayOfMonth = d.dayOfMonth;
        this->month = d.month;
        this->year = d.year;
        cout << getDay(d) << " - " << dayOfMonth << "/" << getMonth(d) << "/" << year << endl;
        getNextWeekDay(d);
        getNextHoliday(d);
        char choice;
        cout << "Do you want to add a holiday? (y/n): ";
        cin >> choice;
        while (choice == 'y' || choice == 'Y')
        {
            cout << "Enter holiday date: (dd mm yyyy): ";
            cin >> dayOfMonth >> month >> year;
            Date holiday(month, year, dayOfMonth);
            addHoliday(holiday);

            cout << "Do you want to add another holiday? (y/n): ";
            cin >> choice;
        }
        printHoliday();
        cout << "Do you want to jump to another date? (y/n): ";
        cin >> choice;
        while (choice == 'y' || choice == 'Y')
        {
            cout << "Enter the number of days to add/subtract: ";
            int t;
            cin >> t;
            Date iterate = iterateDates(d, t);
            cout << "Jumped Date: " << iterate.dayOfMonth << "/" << getMonth(iterate) << "/" << getYear(iterate) << endl;

            cout << "Do you wish to jump to another date? (y/n): ";
            cin >> choice;
        }
        cout << "Do you wish to see number of holidays in a month? (y/n): ";
        cin >> choice;
        while (choice == 'y' || choice == 'Y')
        {
            int gMonth, gYear;
            cout << "Enter the desired month and year (mm yyyy): ";
            cin >> gMonth >> gYear;
            if (gMonth < 1 || gMonth > 12 || gYear < 1400 || gYear > 2400)
            {
                cout << "Please enter valid month and year" << endl;
                return;
            }
            Date h(gMonth, gYear, dayOfMonth);
            int numberOfHolidays = getNumberOfHolidays(gMonth, gYear);
            cout << "Number of Holidays in " << getMonth(h) << " " << getYear(h) << ": " << numberOfHolidays << endl;

            cout << "Do you wish to see number of holidays in another month? (y/n): ";
            cin >> choice;
        }

        cout << "Do you wish to know if a date preceded another date? (y/n): ";
        cin >> choice;
        if (choice == 'y' || choice == 'Y')
        {
            int day1, day2, month1, month2, year1, year2;
            cout << "Enter first date (dd mm yyyy): ";
            cin >> day1 >> month1 >> year1;
            cout << "Enter second date (dd mm yyyy): ";
            cin >> day2 >> month2 >> year2;
            Date d1(day1, month1, year1);
            Date d2(day2, month2, year2);
            int isPreced = isPreceded(d1, d2);
            if (isPreced == 1)
                cout << "True" << endl;
            else
                cout << "False" << endl;
        }
        cout << "Do you want to add a note? (y/n): ";
        cin >> choice;
        while (choice == 'y' || choice == 'Y')
        {
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
            cin >> choice;
        }
        cout << "Do you want to remove a note? (y/n): ";
        cin >> choice;
        while (choice == 'y' || choice == 'Y')
        {
            int day, month, year;
            cout << "Enter the date to remove note from (dd mm yyyy): ";
            cin >> day >> month >> year;
            Date remNote(month, year, day);
            cout << "Do you want to remove another note? (y/n): ";
            cin >> choice;

            if (removeNoteFromDate(remNote))
                cout << "Note removed successfully." << endl;
            else
                cout << "Note not found for the given date." << endl;
        }
        cout << "Do you wish to display notes till next n days? (y/n): ";
        cin >> choice;
        if (choice == 'y' || choice == 'Y')
        {
            int n;
            cout << "Enter number of days (n): ";
            cin >> n;
            vector<Notes> givenList = getNotesFromDateTillN(d, n);
            cout << "Notes for the next " << n << " days: " << endl;
            for (const Notes &note : givenList)
            {
                cout << "Date: " << note.date.dayOfMonth << "/" << getMonth(note.date) << "/" << note.date.year << endl;
                cout << "Note: " << note.content << endl;
                cout << "-------------------------------" << endl;
            }
        }
        cout << "Do you wish to calculate number of days between two dates? (y/n): ";
        cin >> choice;
        if (choice == 'y' || choice == 'Y')
        {
            int day1, day2, month1, month2, year1, year2;
            cout << "Enter first date (dd mm yyyy): ";
            cin >> day1 >> month1 >> year1;
            cout << "Enter second date (dd mm yyyy): ";
            cin >> day2 >> month2 >> year2;
            Date d1(month1, year1, day1);
            Date d2(month2, year2, day2);
            int distance = getDistanceBetweenDates(d1, d2);
            cout << "Number of days between the two dates: " << distance << endl;
        }
        cout << "Do you want to print calendar of a month? (y/n): ";
        cin >> choice;
        while (choice == 'y' || choice == 'Y')
        {
            int month, year;
            cout << "Enter month and year (of month) to be printed (mm yyyy): ";
            cin >> month >> year;
            printMonthOfYear(month, year);

            cout << "Do you want to print calendar for some other month? (y/n): ";
            cin >> choice;
        }
    }

    int daysInAMonth(int month, int year)
    {
        int monthDays[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
        if (month == 2 && isLeapYear(year))
            return 29;
        return monthDays[month - 1];
    }
    bool isHoliday(const Date &d)
    {
        for (const Date &holiday : holidays)
        {
            if (holiday.dayOfMonth == d.dayOfMonth && holiday.month == d.month && holiday.year == d.year)
                return true;
        }
        return false;
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
    string getMonth(Date d) {
        string monthChart[12] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sept", "Oct", "Nov", "Dec"};
        return monthChart[d.month - 1];
    }
    int getYear(const Date &d) {
        int year = d.year;
        return year;
    }
    Date getNextWeekDay(const Date &d) {
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

            if (nextHoliday == "Saturday" || nextHoliday == "Sunday")
            {
                cout << "Next Holiday: " << nextHoliday << " - " << nextDayOfMonth << "/" << getMonth(nextDate) << "/" << nextYear << endl;
                return nextDate;
            }
        }
    }
    void addHoliday(Date d)
    {
        int day = d.dayOfMonth;
        int month = d.month;
        int year = d.year;
        if (day < 1 || day > 31 || month < 1 || month > 12 || year < 1400 || year > 2400)
        {
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
    void printHoliday()
    {
        cout << "List of added Holidays: " << endl;
        for (const Date &h : holidays)
        {
            cout << h.dayOfMonth << "/" << h.month << "/" << h.year << endl;
        }
    }
    Date iterateDates(const Date &d, int t)
    {
        int iday = d.dayOfMonth;
        int imonth = d.month;
        int iyear = d.year;

        while (t > 0)
        {
            iday++;
            if (iday > daysInAMonth(imonth, iyear))
            {
                iday = 1;
                imonth++;
                if (imonth > 12)
                {
                    imonth = 1;
                    iyear++;
                }
            }
            t--;
        }
        while (t < 0)
        {
            iday--;
            if (iday < 1)
            {
                imonth--;
                if (imonth < 1)
                {
                    imonth = 12;
                    iyear--;
                }
                iday = daysInAMonth(imonth, iyear);
            }
            t++;
        }
        return Date(imonth, iyear, iday);
    }
    int getNumberOfHolidays(int month, int year)
    {
        int holidaysInAMonth = 0;
        for (int i = 1; i <= daysInAMonth(month, year); i++)
        {
            Date current(month, year, i);
            string dayWeek = getDay(current);
            if (dayWeek == "Saturday" || dayWeek == "Sunday" || isHoliday(current))
            {
                holidaysInAMonth++;
            }
        }
        return holidaysInAMonth;
    }
    bool isPreceded(Date d1, Date d2)
    {
        if (d1.year > d2.year)
            return true;
        else if (d1.year == d2.year && d1.month > d2.month)
            return true;
        else if (d1.year == d2.year && d1.month == d2.month && d1.dayOfMonth > d2.dayOfMonth)
            return true;
        else
            return false;
    }
    void addNoteToDate(Date d, string note)
    {
        int day = d.dayOfMonth;
        int month = d.month;
        int year = d.year;
        notes[d] = note;
        cout << "Note added to " << day << "/" << getMonth(d) << "/" << year << ": " << note << endl;
    }
    bool removeNoteFromDate(Date d)
    {
        auto i = notes.find(d);
        if (i != notes.end())
        {
            notes.erase(i);
            return true;
        }
        else
            return false;
    }
    vector<Notes> getNotesFromDateTillN(Date d, int n)
    {
        vector<Notes> notesInRange;
        for (int i = 0; i < n; i++)
        {
            Date currentDate = iterateDates(d, i);
            auto itrNote = notes.find(currentDate);
            if (itrNote != notes.end())
            {
                Notes note;
                note.date = currentDate;
                note.content = itrNote->second;
                notesInRange.push_back(note);
            }
        }
        return notesInRange;
    }
    int getDistanceBetweenDates(Date d1, Date d2)
    {
        if (d1 == d2)
            return 0;
        if (isPreceded(d1, d2))
            swap(d1, d2);

        int dist = 0;
        while (d1 != d2)
        {
            d1 = iterateDates(d1, 1);
            dist++;
            if (d1 == d2)
                break;
        }
        return dist;
    }
    void printMonthOfYear(int month, int year)
    {
        if (month < 1 || month > 12 || year < 1400 || year > 2400)
        {
            cout << "Please enter valid month and year!" << endl;
            return;
        }
        Date curr(month, year, 1);
        int daysCurrentMonth = daysInAMonth(month, year);
        int startingDay = getStartingDayOfWeek(curr);
        cout << "Calendar for " << getMonth(curr) << " " << year << endl;
        cout << "Su Mo Tu We Th Fr Sa" << endl;
        int currentDay = 1;

        for (int i = 0; i < 6; i++)
        {
            for (int j = 0; j < 7; j++)
            {
                if (i == 0 && j < startingDay)
                {
                    cout << "   ";
                }
                else
                {
                    if (currentDay <= daysCurrentMonth)
                    {
                        printf("%2d ", currentDay);
                        currentDay++;
                    }
                    else
                        cout << "   ";
                }
            }
            cout << endl;
        }
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
    int getStartingDayOfWeek(const Date &d)
    {
        int dayOfMonth = d.dayOfMonth;
        int month = d.month;
        int year = d.year;
        if (month < 3)
        {
            year--;
            month += 12;
        }
        int fDigits = year / 100;
        int lDigits = year % 100;
        int monthNumber[12] = {0, 3, 3, 6, 1, 4, 6, 2, 5, 0, 3, 5};
        int centuryVal = centuryChart(year);
        int dayNumber = (dayOfMonth + 13 * (month + 1) / 5 + lDigits + lDigits / 4 + fDigits / 4 + 5 * fDigits) % 7;
        dayNumber = (dayNumber + 6) % 7;
        return dayNumber;
    }
};

vector<Date> getFreeDates(Calendar c1, Calendar c2, int month, int year)
{
    vector<Date> freeDates;

    int daysInMonth = c1.daysInAMonth(month, year);
    for (int i = 0; i <= daysInMonth; i++)
    {
        Date curr(month, year, i);
        string dayOfWeek = c1.getDay(curr);
        bool isHoliday = (c1.isHoliday(curr) || c2.isHoliday(curr));
        bool meetingc1 = c1.notes.find(curr) != c1.notes.end();
        bool meetingc2 = c2.notes.find(curr) != c2.notes.end();

        if (dayOfWeek != "Saturday" && dayOfWeek != "Sunday" && !isHoliday && !meetingc1 && !meetingc2)
        {
            freeDates.push_back(curr);
        }
    }
    return freeDates;
}

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
    char choice;

    cout << "Do you want to add different users and data? (y/n): ";
    cin >> choice;
    while (choice == 'y' || choice == 'Y')
    {
        // c1 entry
        int day1, month1, year1;
        cout << "Enter date for Calendar 1 (dd mm yyyy): ";
        cin >> day1 >> month1 >> year1;
        Date d1(month1, year1, day1);
        Calendar c1(d1);

        // c2 entry
        int day2, month2, year2;
        cout << "Enter date for Calendar 2 (dd mm yyyy): ";
        cin >> day2 >> month2 >> year2;
        Date d2(month2, year2, day2);
        Calendar c2(d2);

        // free dates entry
        cout << "Enter month and year to find free dates (mm yyyy): ";
        cin >> month >> year;
        vector<Date> freeDate = getFreeDates(c1, c2, month, year);

        // print free dates
        cout << "Free Dates: " << c1.getMonth(d1) << " " << year << ":" << endl;
        for (const Date &date : freeDate)
        {
            if (date.dayOfMonth != 0)
                cout << date.dayOfMonth << "/" << date.month << "/" << date.year << endl;
        }
        
        cout << "Do you want to repeat for different users? (y/n): ";
        cin >> choice;
    }
    return 0;
}