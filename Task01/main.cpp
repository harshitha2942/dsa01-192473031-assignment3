#include <iostream>
#include <stdexcept>
#include <string>
using namespace std;

class Book {
    string title;
    string author;
    int copies;

    static int validate(int count) {
        if (count < 0) throw invalid_argument("Number of copies cannot be negative");
        return count;
    }

public:
    // Empty record: delegation keeps validation and initialisation in one place.
    Book() : Book("Untitled", "Unknown", 0) {}

    // Donated book: title only.
    explicit Book(const string& t) : Book(t, "Unknown", 1) {}

    // Full-detail book.
    Book(const string& t, const string& a, int c)
        : title(t), author(a), copies(validate(c)) {}

    void print() const {
        cout << "Title: " << title << ", Author: " << author
             << ", Copies: " << copies << '\n';
    }
};

int main() {
    try {
        Book empty;
        Book donated("The Alchemist");
        Book complete("Wings of Fire", "A. P. J. Abdul Kalam", 5);

        cout << "Default object: "; empty.print();
        cout << "Donated object: "; donated.print();
        cout << "Complete object: "; complete.print();

        try {
            Book invalid("Invalid record", "Test", -2);
            invalid.print();
        } catch (const invalid_argument& e) {
            cout << "Rejected invalid book: " << e.what() << '\n';
        }

        // The explicit title constructor prevents implicit conversion:
        // Book implicitBook = "Dune"; // compile-time error because constructor is explicit.
    } catch (const exception& e) {
        cerr << "Error: " << e.what() << '\n';
        return 1;
    }
}
