#include <iostream>
using namespace std;

struct Contact {
    char fullName[50];
    char phoneNumber[20];
};

int main() {
    int totalContacts;
    cout << "Enter the number of contacts: ";
    cin >> totalContacts;

    Contact contactsList[100];

    // Clear the newline character after reading totalContacts
    cin.ignore();

    // Input contacts
    for (int idx = 0; idx < totalContacts; ++idx) {
        cout << "Name: ";
        cin.getline(contactsList[idx].fullName, 50);
        cout << "Number: ";
        cin.getline(contactsList[idx].phoneNumber, 20);
    }

    char searchName[50];
    cout << "Enter name to search: ";
    cin.getline(searchName, 50);

    // Search for contact
    bool isFound = false;
    for (int idx = 0; idx < totalContacts; ++idx) {
        int k = 0;
        bool isMatch = true;
        while (contactsList[idx].fullName[k] != '\0' || searchName[k] != '\0') {
            if (contactsList[idx].fullName[k] != searchName[k]) {
                isMatch = false;
                break;
            }
            k++;
        }
        if (isMatch) {
            cout << "Found: " << contactsList[idx].fullName << " - " << contactsList[idx].phoneNumber << endl;
            isFound = true;
            break;
        }
    }

    if (!isFound) {
        cout << "Contact Not Found" << endl;
    }
}
