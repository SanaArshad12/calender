#include <iostream>
#include <iomanip>
#include <windows.h> // For Windows-specific color functions
using namespace std;

// Function to set text color (Windows-specific)
void setColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

// Function to reset text color to default
void resetColor() {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7); // 7 is default color
}

// Function to check if a year is a leap year
bool isLeapYear(int year) {
    return (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0));
}

// Function to get the number of days in a month
int getDaysInMonth(int month, int year) {
    if (month == 2) {
        return isLeapYear(year) ? 29 : 28;
    } else if (month == 4 || month == 6 || month == 9 || month == 11) {
        return 30;
    } else {
        return 31;
    }
}

// Function to get the day of the week for the first day of the month
int getDayOfWeek(int month, int year) {
    if (month < 3) {
        month += 12;
        year -= 1;
    }
    int k = year % 100;
    int j = year / 100;
    int day = 1 + (13 * (month + 1)) / 5 + k + (k / 4) + (j / 4) + 5 * j;
    return day % 7;
}

// Function to print a single month's calendar
void printMonthCalendar(int month, int year) {
    string months[] = {"January", "February", "March", "April", "May", "June", 
                       "July", "August", "September", "October", "November", "December"};
    
    int daysInMonth = getDaysInMonth(month, year);
    int dayOfWeek = getDayOfWeek(month, year);

    // Print the header
    setColor(14); // Yellow for header
    cout << "\n-------------------------------------" << endl;
    cout << "           " << months[month - 1] << " " << year << endl;
    cout << "-------------------------------------" << endl;
    resetColor();

    setColor(11); // Cyan for days of the week
    cout << " Sun  Mon  Tue  Wed  Thu  Fri  Sat" << endl;
    resetColor();

    // Print the calendar
    for (int i = 0; i < dayOfWeek; ++i) {
        cout << "     ";
    }

    for (int day = 1; day <= daysInMonth; ++day) {
        if ((day + dayOfWeek - 1) % 7 == 0 || day == 1) {
            setColor(10); // Green for Sundays and the first day
        } else {
            setColor(7); // Default color for other days
        }
        printf("%4d ", day);
        if ((day + dayOfWeek) % 7 == 0 || day == daysInMonth) {
            cout << endl;
        }
    }
    resetColor();
}

// Function to print the entire year's calendar
void printYearCalendar(int year) {
    for (int month = 1; month <= 12; ++month) {
        printMonthCalendar(month, year);
        cout << endl;
    }
}

// Main menu function
void displayMenu() {
    setColor(13); // Magenta for menu
    cout << "-------------------------------------" << endl;
    cout << "       ADVANCED CALENDAR GENERATOR   " << endl;
    cout << "-------------------------------------" << endl;
    cout << "1. View a specific month" << endl;
    cout << "2. View the entire year" << endl;
    cout << "3. Exit" << endl;
    cout << "-------------------------------------" << endl;
    resetColor();
    cout << "Enter your choice: ";
}

int main() {
    int choice, month, year;

    while (true) {
        displayMenu();
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter month (1-12): ";
                cin >> month;
                if (month < 1 || month > 12) {
                    setColor(12); // Red for error
                    cout << "Invalid month! Please enter a month between 1 and 12." << endl;
                    resetColor();
                    break;
                }
                cout << "Enter year: ";
                cin >> year;
                printMonthCalendar(month, year);
                break;

            case 2:
                cout << "Enter year: ";
                cin >> year;
                printYearCalendar(year);
                break;

            case 3:
                setColor(14); // Yellow for exit message
                cout << "Exiting the program. Goodbye!" << endl;
                resetColor();
                return 0;

            default:
                setColor(12); // Red for invalid choice
                cout << "Invalid choice! Please select a valid option." << endl;
                resetColor();
                break;
        }

        cout << "\nPress Enter to continue...";
        cin.ignore();
        cin.get();
    }

    return 0;
}