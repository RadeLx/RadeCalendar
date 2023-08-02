#include <utility>
#include "../inc/calendar.h"
#include "iostream"
#include "iomanip"
#include "random"

using namespace std;

size_t Calendar::addEvent(int num) {
    for (int i = 0; i < num; i++) {
        events.emplace_back();
    }
    return getEventSize();
}

size_t Calendar::getEventSize() {
    return events.size();
}

Event &Calendar::getEvent(int index) {
    return events[index];
}

void Calendar::printFooter(ostream &os) {
    os << "END:VCALENDAR" << endl;
}

void Calendar::printHeader(ostream &os) {
    os << header << endl;
}

size_t Calendar::removeEvent(int num) {
    for (int i = 0; i < num; i++) {
        events.pop_back();
    }
    return getEventSize();
}

void Event::printEvent(ostream &os) {
    os << "BEGIN:VEVENT" << endl;
    if (uid == "null")
        generateUID();
    os << "UID:" << uid << endl;
    if(allDay){
        os << "DTSTART;VALUE=DATE:" << getDTStart(allDay) << endl;
        os << "DTEND;VALUE=DATE:" << getDTEnd(allDay) << endl;
    }else{
        os << "DTSTART:" << getDTStart() << endl;
        os << "DTEND:" << getDTEnd() << endl;
    }
    os << "SUMMARY:" << summary << endl;
    os << "DESCRIPTION:" << description << endl;
    os << "LOCATION:" << location << endl;
    os << "SEQUENCE:0" << endl;
    os << "END:VEVENT" << endl;
}


void Event::setDTStart(int year, int month, int day, int hour, int minute, int second) {
    dateTimeStart = Time(year, month, day, hour, minute, second);
}

void Event::setDTStart(int year, int month, int day) {
    dateTimeStart = Time(year, month, day);
    allDay = true;
}

void Event::setDTEnd(int year, int month, int day, int hour, int minute, int second) {
    dateTimeEnd = Time(year, month, day, hour, minute, second);
}

void Event::generateUID() {
    uid = getDTStart();
    uid[8] = '-'; //Change T to '-'
    mt19937 rng = mt19937(random_device()());
    uniform_int_distribution<int> dist(0, 99999999);
    string s = to_string(dist(rng));
    s.insert(s.begin(), 8 - s.length(), '0');
    uid += '-' + s;
}

string Event::getDTStart(bool allDay) {
    stringstream ss;
    array<int, 6> time = dateTimeStart.getTime();
    if(allDay)
        ss << setfill('0') << setw(4) << time[0] << setw(2) << time[1] << setw(2) << time[2];
    else
        ss << setfill('0') << setw(4) << time[0] << setw(2) << time[1] << setw(2) << time[2] << "T" << setw(2) << time[3]
           << setw(2) << time[4] << setw(2) << time[5];
    return ss.str();
}

string Event::getDTEnd(bool allDay) {
    stringstream ss;
    array<int, 6> time = dateTimeEnd.getTime();
    if(allDay)
        ss << setfill('0') << setw(4) << time[0] << setw(2) << time[1] << setw(2) << time[2];
    else
        ss << setfill('0') << setw(4) << time[0] << setw(2) << time[1] << setw(2) << time[2] << "T" << setw(2) << time[3]
           << setw(2) << time[4] << setw(2) << time[5];
    return ss.str();
}

void Event::setSummary(string summary_input) {
    summary = std::move(summary_input);
}

string Event::getSummary() const {
    return summary;
}

void Event::setDescription(string description_input) {
    if (!description_input.empty())
        description = std::move(description_input);
}

string Event::getDescription() const {
    return description;
}

void Event::setLocation(string location_input) {
    if (!location_input.empty())
        location = std::move(location_input);
}

string Event::getLocation() const {
    return location;
}

void Event::setDTEnd(Time duration) {
    dateTimeEnd = dateTimeStart + duration;
}

void Event::setAllDay(bool option) {
     allDay = option;
}

bool Event::getAllday() {
    return allDay;
}

void Time::printTime() const {
    cout << setfill('0') << setw(4) << year << setw(2) << month << setw(2) << day << "T" << setw(2) << hour << setw(2)
         << minute << setw(2) << second << "Z" << endl;
}

array<int, 6> Time::getTime() const {
    return {year, month, day, hour, minute, second};
}

Time Time::operator+(const Time &time) const {
    Time result = *this;
    result.second += time.second;
    result.minute += time.minute;
    result.hour += time.hour;
    result.day += time.day;
    result.month += time.month;
    result.year += time.year;
    result.normalize();
    return result;
}

void Time::normalize() {
    //TODO: Have a lot of bugs.
    second += minute * 60;
    minute = second / 60;
    second %= 60;
    minute += hour * 60;
    hour = minute / 60;
    minute %= 60;
    hour += day * 24;
    day = hour / 24;
    hour %= 24;
    day += month * 30;
    month = day / 30;
    day %= 30;
    month += year * 12;
    year = month / 12;
    month %= 12;
}
