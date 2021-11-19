// Stanislav Alpatiev stal5991@student.su.se
// Labb3, Datum.cpp – definitioner av icke-triviala medlemsfunktioner

#include <iostream>
#include <string>
#include "Datum.h"

// Initialisera statisk medlem
// (första elementet används inte i denna lösning!)
const std::array<unsigned int, 13> Datum::ANT_DAGAR_PER_MAANAD = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
const std::array<std::string, 12> Datum::MONTH_NAMES =
    {"January", "February", "March", "April", "May", "Jun", "July",
     "August", "September", "October", "November", "December"};

//Default constructor
Datum::Datum()
{
    set_date(2000, 1, 1);
}

// Konstruktor
Datum::Datum(int year, int month, int day)
{
    set_date(year, month, day);
}

void Datum::set_date(int yy, int mm, int dd)
{
    if (yy < 2000 || yy > 2100)
    {
        std::invalid_argument("Året måste vara mellan >= 2000 och <= 2100");
    }
    if (mm < 1 || mm > 12)
    {
        std::invalid_argument("Månaden måste vara >= 1 och <= 12");
    }

    bool isLeapYear = is_skott_aar(yy);
    int maxDaysInMonth = ANT_DAGAR_PER_MAANAD[mm];

    if (isLeapYear == true && mm == 2)
    {
        maxDaysInMonth = 29;
    }
    if (dd < 1 || dd > maxDaysInMonth)
    {
        std::invalid_argument("Dagen stämmer inte med år och månad");
    }
    // Glöm inte att kontrollera inmatade värden, annars "exception"
    year = yy;
    month = mm;
    day = dd;
}

// Denna medlemsfunktion är tänkt att lägga till 1 dag till befintligt datum.
// Om sista dagen i månaden, så byt månad.
//     Om skottår, så ta hänsyn till att februari(månad 2) har 29 dagar.
// Om sista dagen på året, så byt år.
void Datum::step_one_day()
{
    // Dagen är inte sista dagen i månaden!
    if (!end_of_month(day))
        ++day;
    else if (month < 12)
    {
        ++month;
        day = 1;
    }
    else
    {
        ++year;
        month = 1;
        day = 1;
    }
}

// Returnera true om yy(year) är skottår!
bool Datum::is_skott_aar(int yy)
{
    if (yy % 400 == 0 ||
        (yy % 100 != 0 && yy % 4 == 0))
        return true;
    else
        return false;
}

// Är det sista dagen (dd) i månaden?
bool Datum::end_of_month(int dd) const
{
    if (month == 2 && is_skott_aar(year))
        return dd == 29;
    else
        return dd == ANT_DAGAR_PER_MAANAD[month];
}

const bool Datum::operator==(const Datum &other)
{
    if (year != other.year || month != other.month || day != other.day)
    {
        return false;
    }
    else
    {
        return true;
    }
}

const bool Datum::operator!=(const Datum &other)
{
    if (year != other.year || month != other.month || day != other.day)
    {
        return true;
    }
    else
    {
        return false;
    }
}

const bool Datum::operator<(const Datum &other)
{
    if (year < other.year)
    {
        return true;
    }
    else if (year > other.year)
    {
        return false;
    }
    else if (month < other.month)
    {
        return true;
    }
    else if (month > other.month)
    {
        return false;
    }
    else if (day < other.day)
    {
        return true;
    }
    else
    {
        return false;
    }
}

const bool Datum::operator>(const Datum &other)
{
    if (year < other.year)
    {
        return false;
    }
    else if (year > other.year)
    {
        return true;
    }
    else if (month < other.month)
    {
        return false;
    }
    else if (month > other.month)
    {
        return true;
    }
    else if (day <= other.day)
    {
        return false;
    }
    else
    {
        return true;
    }
}

const bool Datum::operator<=(const Datum &other)
{
    if (year < other.year)
    {
        return true;
    }
    else if (year > other.year)
    {
        return false;
    }
    else if (month < other.month)
    {
        return true;
    }
    else if (month > other.month)
    {
        return false;
    }
    else if (day <= other.day)
    {
        return true;
    }
    else
    {
        return false;
    }
}

const bool Datum::operator>=(const Datum &other)
{
    if (year >= other.year)
    {
        return true;
    }
    else if (year < other.year)
    {
        return false;
    }
    else if (month >= other.month)
    {
        return true;
    }
    else if (month < other.month)
    {
        return false;
    }
    else if (day < other.day)
    {
        return false;
    }
    else
    {
        return true;
    }
}

const Datum Datum::operator++()
{
    step_one_day();
    return *this;
}

const Datum Datum::operator++(int dd)
{
    step_one_day();
    return *this;
}

const Datum Datum::operator+(int dd) const
{
    Datum date = *this;
    for (int i = 0; i < dd; i++)
    {
        date.step_one_day();
    }
    return date;
}

const Datum Datum::operator+=(int dd)
{
    for (int i = 0; i < dd; i++)
    {
        step_one_day();
    }
    return *this;
}

// operator<<
std::ostream &
operator<<(std::ostream &os, const Datum &date)
{
    // OBS. Glöm inte att modifiera vad som skrivs ut!
    os << date.day << '-' << date.MONTH_NAMES[date.month - 1] << '-' << date.year;
    return os;
}
