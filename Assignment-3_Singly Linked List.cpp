#include <iostream>
using namespace std;

struct PatientNode {
    int id;
    string name;
    int age;
    PatientNode* next;
};

PatientNode* CreateNewPatient(int patientId, string patientName, int patientAge) {
    PatientNode* newNode = new PatientNode;
    newNode->id = patientId;
    newNode->name = patientName;
    newNode->age = patientAge;
    newNode->next = nullptr;

    return newNode;
}

PatientNode* AppendPatient(PatientNode* headPtr, int patientId, string patientName, int patientAge) {
    PatientNode* nodeToAdd = CreateNewPatient(patientId, patientName, patientAge);
    if (headPtr == nullptr) {
        return nodeToAdd;
    }
    PatientNode* current = headPtr;
    while (current->next != nullptr) {
        current = current->next;
    }
    current->next = nodeToAdd;

    return headPtr;
}

PatientNode* RemovePatientFromFront(PatientNode* headPtr) {
    if (headPtr == nullptr) {
        cout << "Queue is empty.\n";
        return nullptr;
    }
    PatientNode* tempNode = headPtr;
    headPtr = headPtr->next;
    cout << "Patient examined and removed: " << tempNode->name << "\n";
    delete tempNode;

    return headPtr;
}

PatientNode* PromotePatient(PatientNode* headPtr, int patientId) {
    if (!headPtr || !headPtr->next) {
        return headPtr;
    }

    PatientNode* prev = nullptr;
    PatientNode* current = headPtr;

    while (current->next && current->next->id != patientId) {
        prev = current;
        current = current->next;
    }

    if (!(current->next) || current->next->id != patientId) {
        cout << "Patient not found or already at front!\n";
        return headPtr;
    }

    PatientNode* patientToMove = current->next;
    current->next = patientToMove->next;

    patientToMove->next = headPtr;
    headPtr = patientToMove;

    cout << "Patient " << patientToMove->name << " moved to front of queue!\n";

    return headPtr;
}

void ShowQueue(PatientNode* headPtr) {
    if (!headPtr) {
        cout << "Queue empty!\n";
        return;
    }

    PatientNode* tempPtr = headPtr;
    cout << "Current Patient Queue:\n";

    while (tempPtr) {
        cout << "[ID:" << tempPtr->id << " | Name:" << tempPtr->name << " | Age:" << tempPtr->age << "] -> ";
        tempPtr = tempPtr->next;
    }
    cout << "END\n";
}

PatientNode* FindPatient(PatientNode* headPtr, int patientId) {
    PatientNode* tempPtr = headPtr;

    while (tempPtr) {
        if (tempPtr->id == patientId) {
            cout << "Found patient: " << tempPtr->name << " (age " << tempPtr->age << ")\n";
            return tempPtr;
        }
        tempPtr = tempPtr->next;
    }
    cout << "Patient ID " << patientId << " not found.\n";

    return nullptr;
}

void ModifyPatient(PatientNode* headPtr, int patientId) {
    PatientNode* targetPatient = FindPatient(headPtr, patientId);
    if (!targetPatient) {
        return;
    }
    cout << "Enter new name (current: " << targetPatient->name << "): ";
    cin >> targetPatient->name;
    cout << "Enter new age (current: " << targetPatient->age << "): ";
    cin >> targetPatient->age;
    cout << endl;
    cout << "Patient info updated." << endl;
}

int main() {
    PatientNode* patientQueue = nullptr;

    int userChoice, patientId, patientAge;
    string patientName;

    while (true) {
        cout << "\n----- Menu -----\n";
        cout << "1. Add patient\n";
        cout << "2. Remove patient (doctor examines)\n";
        cout << "3. Move patient up (priority)\n";
        cout << "4. Display queue\n";
        cout << "5. Search patient\n";
        cout << "6. Update patient\n";
        cout << "0. Exit\n";
        cout << "Enter choice: ";
        cin >> userChoice;

        switch (userChoice) {
            case 1:
                cout << "Patient ID: ";
                cin >> patientId;
                cout << "Name: ";
                cin >> patientName;
                cout << "Age: ";
                cin >> patientAge;

                patientQueue = AppendPatient(patientQueue, patientId, patientName, patientAge);
                break;
            case 2:
                patientQueue = RemovePatientFromFront(patientQueue);
                break;
            case 3:
                cout << "Enter patient ID to move up: ";
                cin >> patientId;
                patientQueue = PromotePatient(patientQueue, patientId);
                break;
            case 4:
                ShowQueue(patientQueue);
                break;
            case 5:
                cout << "Enter patient ID to search: ";
                cin >> patientId;
                FindPatient(patientQueue, patientId);
                break;
            case 6:
                cout << "Enter patient ID to update: ";
                cin >> patientId;
                ModifyPatient(patientQueue, patientId);
                break;
            case 0:
                cout << "Exiting...\n";
                return 0;
            default:
                cout << "Invalid choice!\n";
        }
    }
}
