#ifndef RADECALENDAR_CALENDAR_H
#define RADECALENDAR_CALENDAR_H

#include <string>
#include <vector>
#include <array>

using namespace std;

class Time {
private:
    int year = 0, month = 0, day = 0, hour = 0, minute = 0, second = 0;
public:
    Time(int year, int month, int day, int hour, int minute, int second) : year(year), month(month), day(day),
                                                                           hour(hour), minute(minute),
                                                                           second(second) {};

    Time(int year, int month, int day) : year(year), month(month), day(day) {};

    Time() = default;

    void printTime() const;

    void normalize();

    array<int, 6> getTime() const;

    Time operator+(const Time &time) const;
};

class Event {
private:
    bool allDay = false;
    Time dateTimeStart;
    Time dateTimeEnd;
    string uid = "null";
    string summary, description, location;
public:
    Event() = default;

    void generateUID();

    void printEvent(ostream &os);

    void setAllDay(bool option);

    bool getAllday();

    void setDTStart(int year, int month, int day, int hour, int minute, int second);

    void setDTStart(int year, int month, int day);

    string getDTStart(bool allDay = false);

    void setDTEnd(int year, int month, int day, int hour, int minute, int second);

    void setDTEnd(Time duration);

    string getDTEnd(bool allDay = false);

    void setSummary(string summary_input);

    string getSummary() const;

    void setDescription(string description_input);

    string getDescription() const;

    void setLocation(string location_input);

    string getLocation() const;
};

class Calendar {
private:
    vector<Event> events;
    string header = "BEGIN:VCALENDAR\n"
                    "VERSION:2.0\n"
                    "PRODID:-//radelx v1.0//TW";
public:
    Calendar() = default;

    void printHeader(ostream &os);

    void printFooter(ostream &os);

    size_t addEvent(int num);

    size_t removeEvent(int num);

    Event &getEvent(int index);

    size_t getEventSize();

};

#endif //RADECALENDAR_CALENDAR_H
