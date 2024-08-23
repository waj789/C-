#include <iostream>
#include <fstream>
#include <string>

using namespace std;

void registerUser() {
    string username, password;
    ofstream userFile;

    cout << "Enter username: ";
    cin >> username;
    cout << "Enter password: ";
    cin >> password;

    userFile.open(username + ".txt"); // Create a file with the username
    if (userFile.is_open()) {
        userFile << password; // Store the password in the file
        userFile.close();
        cout << "Registration successful!" << endl;
    } else {
        cout << "Error in creating file!" << endl;
    }
}

void loginUser() {
    string username, password, storedPassword;
    ifstream userFile;

    cout << "Enter username: ";
    cin >> username;
    cout << "Enter password: ";
    cin >> password;

    userFile.open(username + ".txt"); // Open the file with the username
    if (userFile.is_open()) {
        getline(userFile, storedPassword); // Read the stored password
        userFile.close();
        if (storedPassword == password) {
            cout << "Login successful!" << endl;
        } else {
            cout << "Incorrect password!" << endl;
        }
    } else {
        cout << "Username does not exist!" << endl;
    }
}

int main() {
    int choice;
    cout << "1. Register" << endl;
    cout << "2. Login" << endl;
    cout << "Enter your choice: ";
    cin >> choice;

    switch (choice) {
        case 1:
            registerUser();
            break;
        case 2:
            loginUser();
            break;
        default:
            cout << "Invalid choice!" << endl;
    }

    return 0;
}
