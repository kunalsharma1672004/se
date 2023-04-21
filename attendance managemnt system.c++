#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <ctime>

using namespace std;

// Function to get current date and time
string currentDateTime() {
    time_t now = time(0);
    struct tm tstruct;
    char buf[80];
    tstruct = *localtime(&now);
    strftime(buf, sizeof(buf), "%Y-%m-%d %X", &tstruct);
    return buf;
}

// Function to check if a file exists
bool fileExists(string fileName) {
    ifstream infile(fileName);
    return infile.good();
}

int main() {
    string fileName = "attendance.txt";
    vector<string> students;
    vector<bool> attendance;

    // Check if attendance file exists
    if (!fileExists(fileName)) {
        // Prompt user to enter the number of students
        int numStudents;
        cout << "Enter the number of students: ";
        cin >> numStudents;
        cin.ignore();

        // Prompt user to enter the names of the students
        for (int i = 0; i < numStudents; i++) {
            cout << "Enter the name of student " << i+1 << ": ";
            string name;
            getline(cin, name);
            students.push_back(name);
            attendance.push_back(false);
        }

        // Create attendance file and write student names
        ofstream outfile(fileName);
        for (int i = 0; i < numStudents; i++) {
            outfile << students[i] << endl;
        }
        outfile.close();
    }
    else {
        // Read student names from attendance file
        ifstream infile(fileName);
        string line;
        while (getline(infile, line)) {
            students.push_back(line);
            attendance.push_back(false);
        }
        infile.close();
    }

    // Display menu and prompt user for choice
    int choice;
    do {
        cout << "\nAttendance Management System\n"
             << "----------------------------\n"
             << "1. Mark attendance\n"
             << "2. View attendance\n"
             << "3. Exit\n"
             << "Enter your choice (1-3): ";
        cin >> choice;
        cin.ignore();

        // Handle user choice
        switch (choice) {
            case 1: {
                // Prompt user for student name and mark attendance
                string name;
                cout << "Enter the name of the student: ";
                getline(cin, name);
                bool found = false;
                for (int i = 0; i < students.size(); i++) {
                    if (students[i] == name) {
                        attendance[i] = true;
                        found = true;
                        break;
                    }
                }
                if (!found) {
                    cout << "Error: Student not found\n";
                }
                else {
                    // Append attendance to attendance file
                    ofstream outfile(fileName, ios_base::app);
                    outfile << currentDateTime() << " - " << name << " - Present\n";
                    outfile.close();
                }
                break;
            }
            case 2: {
                // Read and display attendance from attendance file
                ifstream infile(fileName);
                string line;
                while (getline(infile, line)) {
                    cout << line << endl;
                }
                infile.close();
                break;
            }
            case 3: {
                // Exit program
                cout << "Exiting program...\n";
                break;
            }
            default: {
                cout << "Invalid choice. Try again.\n";
                break;
            }
        }
    } while (choice != 3);

    return
