#include <iostream>
#include <string>
using namespace std;

class Event {
    string name;
    int rows;
    int seatsPerRow;
    char** seats;
    int booked;

public:
    Event(const string& eventName, int r, int s)
        : name(eventName), rows(r > 0 ? r : 0),
          seatsPerRow(s > 0 ? s : 0), seats(nullptr), booked(0) {
        if (rows > 0 && seatsPerRow > 0) {
            seats = new char*[rows]{};
            try {
                for (int i = 0; i < rows; ++i) {
                    seats[i] = new char[seatsPerRow];
                    for (int j = 0; j < seatsPerRow; ++j) seats[i][j] = 'O';
                }
            } catch (...) {
                for (int i = 0; i < rows; ++i) delete[] seats[i];
                delete[] seats;
                throw;
            }
        }
        cout << "Created event: " << name << " (" << rows << " x "
             << seatsPerRow << ")\n";
    }

    Event(const Event&) = delete;
    Event& operator=(const Event&) = delete;

    bool book(int r, int s) {
        if (!valid(r, s) || seats[r][s] == 'X') return false;
        seats[r][s] = 'X'; ++booked; return true;
    }
    bool cancel(int r, int s) {
        if (!valid(r, s) || seats[r][s] == 'O') return false;
        seats[r][s] = 'O'; --booked; return true;
    }
    void show() const {
        cout << name << " booked seats: " << booked << '\n';
    }
    ~Event() {
        for (int i = 0; i < rows; ++i) delete[] seats[i];
        delete[] seats;
        cout << "Closed event: " << name << ", final bookings: " << booked << '\n';
    }

private:
    bool valid(int r, int s) const {
        return r >= 0 && r < rows && s >= 0 && s < seatsPerRow;
    }
};

int main() {
    Event morning("Morning Show", 2, 3); // stack object
    morning.book(0, 1);
    morning.book(1, 2);
    morning.cancel(0, 1);
    morning.show();

    Event* evening = new Event("Evening Show", 1, 2); // heap object
    evening->book(0, 0);
    evening->show();
    delete evening; // required to invoke destructor and release memory

    {
        Event workshop("Workshop", 1, 1); // block-scope object
        workshop.book(0, 0);
        workshop.show();
    } // destroyed at block exit

    Event empty("Zero Row Event", 0, 10);
    empty.show();
}
