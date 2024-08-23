#include <iostream>
using namespace std;

int main() {
    int numCourses;
    float grade, creditHours, totalGradePoints = 0.0, totalCreditHours = 0.0, CGPA, normalizedCGPA;

    cout << "Enter the number of courses: ";
    cin >> numCourses;

    // Validate number of courses
    if (numCourses <= 0) {
        cout << "Invalid number of courses!" << endl;
        return 1;
    }

    for(int i = 0; i < numCourses; i++) {
        cout << "Enter grade point for course " << i + 1 << " (1 to 16): ";
        cin >> grade;

        // Validate grade input
        if (grade < 1 || grade > 16) {
            cout << "Invalid grade point! Grade point should be between 1 and 16." << endl;
            return 1;
        }

        cout << "Enter credit hours for course " << i + 1 << " (1 to 4): ";
        cin >> creditHours;

        // Validate credit hours input
        if (creditHours < 1 || creditHours > 4) {
            cout << "Invalid credit hours! Credit hours should be between 1 and 4." << endl;
            return 1;
        }

        totalGradePoints += grade * creditHours;
        totalCreditHours += creditHours;

        // Debugging output
        cout << "Current Total Grade Points: " << totalGradePoints << endl;
        cout << "Current Total Credit Hours: " << totalCreditHours << endl;
    }

    if (totalCreditHours == 0) {
        cout << "Total credit hours cannot be zero!" << endl;
        return 1;
    }

    CGPA = totalGradePoints / totalCreditHours;

    // Normalize CGPA to a 4-point scale
    normalizedCGPA = (CGPA / 16.0) * 4.0;

    cout << "Your CGPA on a 4-point scale is: " << normalizedCGPA << endl;

    return 0;
}
