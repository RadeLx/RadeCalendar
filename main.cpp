#include "inc/calendar.h"
#include "inc/ansi2unicode.h"
#include "iostream"
#include "sstream"

using namespace std;

int main() {

    const string userName = "nxrad";
    const int default_year = 2023, default_month = 7, default_second = 0;

    stringstream output;
    int month, day;
    Calendar calendar;
    calendar.printHeader(output);
    int hour = 0, minute = 1;
    for (int i = 0; true; i++) {
        calendar.addEvent(1);
        cout << "Enter date (m d)" << endl;
        cin >> month >> day;
        if (month + day == 0) {
            calendar.removeEvent(1);
            break;
        }
        string dtStart, summary, description, location;
        cout << "When does the event start?" << endl;

        cin.ignore(99, '\n');
        getline(cin, dtStart);
        if(dtStart.empty()){
            //All day event
            calendar.getEvent(i).setAllDay(true);
            calendar.getEvent(i).setDTStart(default_year, month, day);
            cout << "How many days is the event?" << endl;
            int days;
            cin >> days;
            calendar.getEvent(i).setDTEnd(Time(0, 0, days));
        }else{
            stringstream ss(dtStart);
            ss >> hour >> minute;
            calendar.getEvent(i).setDTStart(default_year, month, day, hour, minute, default_second);
            cout << "How long is the event?" << endl;
            cin >> minute;
            if (minute)
                calendar.getEvent(i).setDTEnd(Time(0, 0, 0, 0, minute, 0));
            else {
                cout << "When does the event end?" << endl;
                cin >> hour >> minute;
                calendar.getEvent(i).setDTEnd(default_year, month, day, hour, minute, default_second);
            }
        }
        cout << "What is the event summary?" << endl;
        cin.ignore(99, '\n');
        getline(cin, summary);
        calendar.getEvent(i).setSummary(summary);

        cout << "What is the event description?" << endl;
        getline(cin, description);
        calendar.getEvent(i).setDescription(description);

        cout << "Where is the event?" << endl;
        getline(cin, location);
        calendar.getEvent(i).setLocation(location);

        calendar.getEvent(i).printEvent(output);
    }
    calendar.printFooter(output);
    string temp = output.str();
    ansi2unicode::saveAsUTF8((string) "calendar.ics", temp, userName);
}
