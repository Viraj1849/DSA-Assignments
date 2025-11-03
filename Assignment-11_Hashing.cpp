#include <iostream>
#include <vector>
#include <list>
#include <string>
using namespace std;

// CLASS: Student
class Student {
public:
    int id;
    string name;
    int age;
    string branch;

    // Default Constructor
    Student() {
        id = -1;
        name = "";
        age = 0;
        branch = "";
    }

    // Parameterized Constructor
    Student(int stuId, string stuName, int stuAge, string stuBranch) {
        id = stuId;
        name = stuName;
        age = stuAge;
        branch = stuBranch;
    }

    // Display Function
    void display() {
        cout << "ID: " << id
             << ", Name: " << name
             << ", Age: " << age
             << ", Branch: " << branch << "\n";
    }
};

// CLASS: Hash Table for Student Records
class StudentHashTable {
public:
    vector<list<Student>> table; // Hash table using chaining
    int totalRecords;
    const double LOAD_FACTOR = 0.7;

    // Constructor
    StudentHashTable(int initialSize = 11) {
        table.resize(initialSize);
        totalRecords = 0;
    }

    // Hash Function
    int hashFunction(int keyValue) {
        return keyValue % table.size();
    }

    // Rehash Function
    void rehash() {
        int expandedSize = table.size() * 2;
        vector<list<Student>> updatedTable(expandedSize);

        for (int idx = 0; idx < (int)table.size(); idx++) {
            list<Student>& oldBucket = table[idx];
            for (Student record : oldBucket) {
                int newPos = record.id % expandedSize;
                updatedTable[newPos].push_back(record);
            }
        }

        table.swap(updatedTable);
        cout << "\n[Rehash completed — New table size: " << expandedSize << "]\n";
    }

    // Insert or Update Record
    void insert(Student newRecord) {
        int pos = hashFunction(newRecord.id);
        bool wasUpdated = false;
        list<Student>& currentBucket = table[pos];
        list<Student> revisedBucket;

        // Check if record already exists
        for (Student existing : currentBucket) {
            if (existing.id == newRecord.id) {
                revisedBucket.push_back(newRecord); // Replace existing record
                wasUpdated = true;
            } else {
                revisedBucket.push_back(existing);
            }
        }

        if (!wasUpdated) {
            revisedBucket.push_back(newRecord);
            totalRecords++;
            cout << "\nStudent added successfully.\n";
        } else {
            cout << "\nRecord with ID " << newRecord.id << " updated successfully.\n";
        }

        currentBucket = revisedBucket; // Replace old bucket

        double currentLoad = (double)totalRecords / table.size();
        if (currentLoad > LOAD_FACTOR) {
            rehash();
        }
    }

    // Search Record
    bool search(int targetId, Student& foundRecord) {
        int pos = hashFunction(targetId);
        list<Student>& currentBucket = table[pos];

        for (Student record : currentBucket) {
            if (record.id == targetId) {
                foundRecord = record;
                return true;
            }
        }
        return false;
    }

    // Delete Record
    bool remove(int targetId) {
        int pos = hashFunction(targetId);
        list<Student>& currentBucket = table[pos];
        list<Student> revisedBucket;
        bool recordFound = false;

        for (Student record : currentBucket) {
            if (record.id != targetId) {
                revisedBucket.push_back(record);
            } else {
                recordFound = true;
                totalRecords--;
            }
        }

        currentBucket = revisedBucket;

        if (recordFound) {
            cout << "\nRecord deleted successfully.\n";
            return true;
        }
        return false;
    }

    // Display All Records
    void displayAll() {
        cout << "\n----- All Student Records -----\n";
        for (int idx = 0; idx < (int)table.size(); idx++) {
            cout << "Bucket " << idx << ": ";
            if (table[idx].empty()) {
                cout << "(empty)\n";
                continue;
            }
            cout << "\n";
            for (Student record : table[idx]) {
                record.display();
            }
        }
        cout << "-------------------------------\n";
        cout << "Total Records: " << totalRecords << "\n\n";
    }
};

// MAIN FUNCTION
int main() {
    StudentHashTable studentSystem(11);
    int menuChoice;

    do {
        cout << "\nSTUDENT INFORMATION SYSTEM\n";
        cout << "1. Add / Update Student\n";
        cout << "2. Search Student by ID\n";
        cout << "3. Delete Student by ID\n";
        cout << "4. Display All Students\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> menuChoice;

        switch (menuChoice) {
        case 1: {
            int stuId, stuAge;
            string stuName, stuBranch;

            cout << "Enter Student ID: ";
            cin >> stuId;
            cin.ignore();

            cout << "Enter Name: ";
            getline(cin, stuName);

            cout << "Enter Age: ";
            cin >> stuAge;
            cin.ignore();

            cout << "Enter Branch: ";
            getline(cin, stuBranch);

            Student newStudent(stuId, stuName, stuAge, stuBranch);
            studentSystem.insert(newStudent);
            break;
        }
        case 2: {
            int searchId;
            cout << "Enter Student ID to search: ";
            cin >> searchId;
            Student foundStudent;
            if (studentSystem.search(searchId, foundStudent)) {
                cout << "\nRecord found:\n";
                foundStudent.display();
            } else {
                cout << "\nRecord not found!\n";
            }
            break;
        }
        case 3: {
            int deleteId;
            cout << "Enter Student ID to delete: ";
            cin >> deleteId;
            if (!studentSystem.remove(deleteId))
                cout << "\nRecord not found!\n";
            break;
        }
        case 4:
            studentSystem.displayAll();
            break;
        case 5:
            cout << "\nExiting program...\n";
            break;
        default:
            cout << "\nInvalid choice. Please try again.\n";
            break;
        }

    } while (menuChoice != 5);

    return 0;
}
