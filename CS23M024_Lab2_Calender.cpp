#include <iostream>
using namespace std;

class Calender {
    private:
    string Day, Month;
    int Year;
    public:
    string getDay(Date d) {
        if(d.dayOfWeek == 1) return "Monday";
        if(d.dayOfWeek == 2) return "Tuesday";
        if(d.dayOfWeek == 3) return "Wednesday";
        if(d.dayOfWeek == 4) return "Thursday";
        if(d.dayOfWeek == 5) return "Friday";
        if(d.dayOfWeek == 6) return "Saturday";
        if(d.dayOfWeek == 7) return "Sunday";
    }

    string getMonth(Date d) {
        if(d.month == 1) return "January";
        if(d.month == 2) return "February";
        if(d.month == 3) return "March";
        if(d.month == 4) return "April";
        if(d.month == 5) return "May";
        if(d.month == 6) return "June";
        if(d.month == 7) return "July";
        if(d.month == 8) return "August";
        if(d.month == 9) return "September";
        if(d.month == 10) return "October";
        if(d.month == 11) return "November";
        if(d.month == 12) return "December";
    }

    string getYear(Date d) {
        return d.year;
    }
    // enum weekDays {Monday = 1, Tuesday, Wednesday, Thursday, Friday, Saturday};
    // weekDays day;
    // day = Monday;
    // cout << "Day: " << day;
};

int noOfOddDays(int dayOfMonth, int month) {
    int oddDays = 0;
    if(month == 1)  oddDays = 3;
    if(month == 2)  oddDays = 3;
    if(month == 3)  oddDays = 6;
    if(month == 4)  oddDays = 1;
    if(month == 5)  oddDays = 4;
    if(month == 6)  oddDays = 6;
    if(month == 7)  oddDays = 2;
    if(month == 8)  oddDays = 5;
    if(month == 9)  oddDays = 0;
    if(month == 10)  oddDays = 3;
    if(month == 11)  oddDays = 5;
    if(month == 12)  oddDays = 1;
    return (oddDays + month) % 7;
}

class Date{
    // 01 Jan 2023 was Sunday
    public:
    string dayOfWeek;
    Calender C;
    // dayOfWeek = C.getDay();
    int month, dayOfMonth, year;

    public:
    Date(int dayOfMonth, int month, int year) {
        int oddDays = noOfOddDays(dayOfMonth, month);
        // dayOfWeek = C.getDay(oddDays);
    }
};

int main() {
    int date;
    // cin >> date;
    Date(7, 8, 2023);
    Calender::getDay(7);
}