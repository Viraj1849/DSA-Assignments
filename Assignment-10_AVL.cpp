#include <iostream>
#include <string>
#include <queue>
#include <algorithm>
using namespace std;

// Contact details
class Contact {
public:
    int id;
    string name, phone, email;

    Contact(int ident, string fullname, string number, string mail) {
        id = ident;
        name = fullname;
        phone = number;
        email = mail;
    }
};

// Node for AVL tree
class Node {
public:
    Contact* data;
    int h;
    Node* left;
    Node* right;

    Node(Contact* info) {
        data = info;
        h = 1;
        left = right = nullptr;
    }
};

// AVL Tree
class AVL {
public:
    Node* root;
    AVL() { root = nullptr; }

    int height(Node* nodeRef) { return nodeRef ? nodeRef->h : 0; }

    int balance(Node* nodeRef) {
        return nodeRef ? height(nodeRef->left) - height(nodeRef->right) : 0;
    }

    // Right rotation
    Node* rotateRight(Node* mainNode) {
        Node* newRoot = mainNode->left;
        Node* orphan = newRoot->right;

        newRoot->right = mainNode;
        mainNode->left = orphan;

        mainNode->h = 1 + max(height(mainNode->left), height(mainNode->right));
        newRoot->h = 1 + max(height(newRoot->left), height(newRoot->right));

        return newRoot;
    }

    // Left rotation
    Node* rotateLeft(Node* mainNode) {
        Node* newRoot = mainNode->right;
        Node* orphan = newRoot->left;

        newRoot->left = mainNode;
        mainNode->right = orphan;

        mainNode->h = 1 + max(height(mainNode->left), height(mainNode->right));
        newRoot->h = 1 + max(height(newRoot->left), height(newRoot->right));

        return newRoot;
    }

    // Insert contact
    Node* insert(Node* nodePtr, Contact* newContact) {
        if (!nodePtr)
            return new Node(newContact);

        if (newContact->name < nodePtr->data->name)
            nodePtr->left = insert(nodePtr->left, newContact);
        else if (newContact->name > nodePtr->data->name)
            nodePtr->right = insert(nodePtr->right, newContact);
        else {
            cout << "Duplicate contact name not allowed!\n";
            return nodePtr;
        }

        nodePtr->h = 1 + max(height(nodePtr->left), height(nodePtr->right));
        int balFactor = balance(nodePtr);

        // Rebalancing
        if (balFactor > 1 && newContact->name < nodePtr->left->data->name)
            return rotateRight(nodePtr);
        if (balFactor < -1 && newContact->name > nodePtr->right->data->name)
            return rotateLeft(nodePtr);
        if (balFactor > 1 && newContact->name > nodePtr->left->data->name) {
            nodePtr->left = rotateLeft(nodePtr->left);
            return rotateRight(nodePtr);
        }
        if (balFactor < -1 && newContact->name < nodePtr->right->data->name) {
            nodePtr->right = rotateRight(nodePtr->right);
            return rotateLeft(nodePtr);
        }

        return nodePtr;
    }

    // Search by name
    Node* searchByName(Node* current, string searchName) {
        if (!current || current->data->name == searchName)
            return current;
        if (searchName < current->data->name)
            return searchByName(current->left, searchName);
        return searchByName(current->right, searchName);
    }

    // Search by phone
    Node* searchByPhone(Node* current, string targetPhone) {
        if (!current)
            return nullptr;
        if (current->data->phone == targetPhone)
            return current;

        Node* leftResult = searchByPhone(current->left, targetPhone);
        if (leftResult)
            return leftResult;
        return searchByPhone(current->right, targetPhone);
    }

    // Search by email
    Node* searchByEmail(Node* current, string targetEmail) {
        if (!current)
            return nullptr;
        if (current->data->email == targetEmail)
            return current;

        Node* leftResult = searchByEmail(current->left, targetEmail);
        if (leftResult)
            return leftResult;
        return searchByEmail(current->right, targetEmail);
    }

    // Inorder display (alphabetical)
    void inorder(Node* current) {
        if (!current)
            return;
        inorder(current->left);
        cout << "ID: " << current->data->id
             << ", Name: " << current->data->name
             << ", Phone: " << current->data->phone
             << ", Email: " << current->data->email << endl;
        inorder(current->right);
    }

    // Level order display
    void levelOrder(Node* startNode) {
        if (!startNode)
            return;

        queue<Node*> nodeQueue;
        nodeQueue.push(startNode);

        while (!nodeQueue.empty()) {
            int levelCount = nodeQueue.size();
            for (int i = 0; i < levelCount; i++) {
                Node* active = nodeQueue.front();
                nodeQueue.pop();

                cout << active->data->name << " (" << active->data->phone << ") ";

                if (active->left)
                    nodeQueue.push(active->left);
                if (active->right)
                    nodeQueue.push(active->right);
            }
            cout << endl;
        }
    }

    // Add new contact
    void add(int ident, string fullName, string number, string mail) {
        Contact* freshContact = new Contact(ident, fullName, number, mail);
        root = insert(root, freshContact);
        cout << "Contact added: " << fullName << endl;
    }

    // Update existing contact
    void update() {
        string targetName;
        cout << "Enter name to update: ";
        getline(cin, targetName);

        Node* foundNode = searchByName(root, targetName);
        if (!foundNode) {
            cout << "Contact not found!\n";
            return;
        }

        int newId;
        string newPhone, newEmail;
        cout << "Enter new ID: ";
        cin >> newId;
        cin.ignore();
        cout << "Enter new phone: ";
        getline(cin, newPhone);
        cout << "Enter new email: ";
        getline(cin, newEmail);

        foundNode->data->id = newId;
        foundNode->data->phone = newPhone;
        foundNode->data->email = newEmail;

        cout << "Contact updated successfully!\n";
    }

    // Show all contacts (alphabetical)
    void showAll() {
        cout << "\n--- Contacts (Alphabetical Order) ---\n";
        inorder(root);
        cout << endl;
    }

    // Show tree level order
    void showLevel() {
        cout << "\n--- Contacts (Tree Level Order) ---\n";
        levelOrder(root);
        cout << endl;
    }

    // Search menu
    void searchMenu() {
        int opt;
        cout << "\nSearch by:\n1. Name\n2. Phone\n3. Email\nEnter option: ";
        cin >> opt;
        cin.ignore();

        switch (opt) {
        case 1: {
            string target;
            cout << "Enter name: ";
            getline(cin, target);
            Node* result = searchByName(root, target);
            if (result)
                cout << "Found -> ID: " << result->data->id << ", "
                     << result->data->name << ", " << result->data->phone
                     << ", " << result->data->email << endl;
            else
                cout << "Contact not found!\n";
            break;
        }
        case 2: {
            string target;
            cout << "Enter phone: ";
            getline(cin, target);
            Node* result = searchByPhone(root, target);
            if (result)
                cout << "Found -> ID: " << result->data->id << ", "
                     << result->data->name << ", " << result->data->phone
                     << ", " << result->data->email << endl;
            else
                cout << "Contact not found!\n";
            break;
        }
        case 3: {
            string target;
            cout << "Enter email: ";
            getline(cin, target);
            Node* result = searchByEmail(root, target);
            if (result)
                cout << "Found -> ID: " << result->data->id << ", "
                     << result->data->name << ", " << result->data->phone
                     << ", " << result->data->email << endl;
            else
                cout << "Contact not found!\n";
            break;
        }
        default:
            cout << "Invalid option!\n";
        }
    }
};

// Main Function
int main() {
    AVL book;

    // Initial contacts
    book.add(101, "Rahul Sharma", "9876543210", "rahul@example.com");
    book.add(102, "Priya Patel", "1234567890", "priya@example.com");
    book.add(103, "Aarav Gupta", "8765432109", "aarav@example.com");

    int userChoice;
    do {
        cout << "\nContact Management System\n";
        cout << "1. Add New Contact\n";
        cout << "2. Update Contact\n";
        cout << "3. Search Contact\n";
        cout << "4. Display All Contacts (Alphabetical)\n";
        cout << "5. Display Tree (Level Order)\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        cin >> userChoice;
        cin.ignore();

        switch (userChoice) {
        case 1: {
            int newId;
            string newName, newPhone, newEmail;
            cout << "Enter ID: ";
            cin >> newId;
            cin.ignore();
            cout << "Enter Name: ";
            getline(cin, newName);
            cout << "Enter Phone: ";
            getline(cin, newPhone);
            cout << "Enter Email: ";
            getline(cin, newEmail);
            book.add(newId, newName, newPhone, newEmail);
            break;
        }
        case 2:
            book.update();
            break;
        case 3:
            book.searchMenu();
            break;
        case 4:
            book.showAll();
            break;
        case 5:
            book.showLevel();
            break;
        case 6:
            cout << "Exiting program. Goodbye!\n";
            break;
        default:
            cout << "Invalid choice! Please try again.\n";
        }

    } while (userChoice != 6);

    return 0;
}
