#include <iostream>
#include <queue>
using namespace std;

// Node class represents a single element of the Binary Search Tree
class Node {
public:
    int value;
    Node* leftChild;
    Node* rightChild;

    // Constructor to initialize a node with a given value
    Node(int val) {
        value = val;
        leftChild = rightChild = NULL;
    }
};

// BST class contains all the operations on the Binary Search Tree
class BST {
public:
    Node* rootNode; // The root of the BST

    BST() {
        rootNode = NULL;
    }

    // Insert a new value into the BST
    void insert(int newValue) {
        Node* tempNode = new Node(newValue);

        if (rootNode == NULL) {
            rootNode = tempNode;
            return;
        }

        Node* walker = rootNode;
        Node* prev = NULL;

        while (walker != NULL) {
            prev = walker;
            if (newValue < walker->value)
                walker = walker->leftChild;
            else if (newValue > walker->value)
                walker = walker->rightChild;
            else {
                cout << "Value " << newValue << " already exists in the tree.\n";
                delete tempNode;
                return;
            }
        }

        if (newValue < prev->value)
            prev->leftChild = tempNode;
        else
            prev->rightChild = tempNode;
    }

    // Search for a value in the BST
    void search(int target) {
        Node* explorer = rootNode;

        while (explorer != NULL) {
            if (explorer->value == target) {
                cout << "Value " << target << " is found in the BST.\n";
                return;
            }
            else if (target < explorer->value)
                explorer = explorer->leftChild;
            else
                explorer = explorer->rightChild;
        }

        cout << "Value " << target << " is not found in the BST.\n";
    }

    // Find minimum value from a given node’s subtree
    Node* findMin(Node* refNode) {
        while (refNode && refNode->leftChild != NULL) {
            refNode = refNode->leftChild;
        }
        return refNode;
    }

    // Recursive helper to delete a node
    Node* deleteNodeHelper(Node* rootRef, int targetValue) {
        if (rootRef == NULL)
            return NULL;

        if (targetValue < rootRef->value)
            rootRef->leftChild = deleteNodeHelper(rootRef->leftChild, targetValue);
        else if (targetValue > rootRef->value)
            rootRef->rightChild = deleteNodeHelper(rootRef->rightChild, targetValue);
        else {
            // Node found
            if (rootRef->leftChild == NULL && rootRef->rightChild == NULL) {
                delete rootRef;
                return NULL;
            }
            else if (rootRef->leftChild == NULL) {
                Node* temp = rootRef->rightChild;
                delete rootRef;
                return temp;
            }
            else if (rootRef->rightChild == NULL) {
                Node* temp = rootRef->leftChild;
                delete rootRef;
                return temp;
            }
            else {
                Node* successor = findMin(rootRef->rightChild);
                rootRef->value = successor->value;
                rootRef->rightChild = deleteNodeHelper(rootRef->rightChild, successor->value);
            }
        }
        return rootRef;
    }

    // Delete a value from the BST
    void deleteNode(int num) {
        rootNode = deleteNodeHelper(rootNode, num);
        cout << "Value " << num << " deleted successfully.\n";
    }

    // Inorder traversal
    void inorder(Node* ptr) {
        if (ptr == NULL) return;
        inorder(ptr->leftChild);
        cout << ptr->value << " ";
        inorder(ptr->rightChild);
    }

    // Preorder traversal
    void preorder(Node* ptr) {
        if (ptr == NULL) return;
        cout << ptr->value << " ";
        preorder(ptr->leftChild);
        preorder(ptr->rightChild);
    }

    // Postorder traversal
    void postorder(Node* ptr) {
        if (ptr == NULL) return;
        postorder(ptr->leftChild);
        postorder(ptr->rightChild);
        cout << ptr->value << " ";
    }

    // Display all traversals
    void display() {
        if (rootNode == NULL) {
            cout << "Tree is empty.\n";
            return;
        }
        cout << "Tree Traversals:\n";
        cout << "Inorder: ";
        inorder(rootNode);
        cout << "\nPreorder: ";
        preorder(rootNode);
        cout << "\nPostorder: ";
        postorder(rootNode);
        cout << "\n";
    }

    // Compute depth (height) of the tree
    int depth(Node* nodeRef) {
        if (nodeRef == NULL) return 0;
        int lDepth = depth(nodeRef->leftChild);
        int rDepth = depth(nodeRef->rightChild);
        return 1 + max(lDepth, rDepth);
    }

    void showDepth() {
        cout << "Depth of tree: " << depth(rootNode) << endl;
    }

    // Create a mirror of the BST (left <-> right)
    Node* mirror(Node* n) {
        if (n == NULL) return NULL;
        Node* mirrored = new Node(n->value);
        mirrored->leftChild = mirror(n->rightChild);
        mirrored->rightChild = mirror(n->leftChild);
        return mirrored;
    }

    void showMirror() {
        Node* mirroredRoot = mirror(rootNode);
        cout << "Mirror Tree (Inorder): ";
        inorder(mirroredRoot);
        cout << "\n";
    }

    // Copy the tree into a new structure
    Node* copyTree(Node* oldRoot) {
        if (oldRoot == NULL) return NULL;
        Node* duplicate = new Node(oldRoot->value);
        duplicate->leftChild = copyTree(oldRoot->leftChild);
        duplicate->rightChild = copyTree(oldRoot->rightChild);
        return duplicate;
    }

    void copyAndShow() {
        Node* copiedRoot = copyTree(rootNode);
        cout << "Copied Tree (Inorder): ";
        inorder(copiedRoot);
        cout << "\n";
    }

    // Display each parent and its children
    void showParentChild() {
        if (rootNode == NULL) return;
        queue<Node*> nodeQueue;
        nodeQueue.push(rootNode);

        while (!nodeQueue.empty()) {
            Node* cur = nodeQueue.front();
            nodeQueue.pop();

            cout << "Parent: " << cur->value << " -> ";
            if (cur->leftChild)
                cout << "Left Child: " << cur->leftChild->value << " ";
            if (cur->rightChild)
                cout << "Right Child: " << cur->rightChild->value;
            cout << "\n";

            if (cur->leftChild) nodeQueue.push(cur->leftChild);
            if (cur->rightChild) nodeQueue.push(cur->rightChild);
        }
    }

    // Display only leaf nodes
    void displayLeafNodes(Node* curNode) {
        if (curNode == NULL) return;
        if (curNode->leftChild == NULL && curNode->rightChild == NULL)
            cout << curNode->value << " ";
        displayLeafNodes(curNode->leftChild);
        displayLeafNodes(curNode->rightChild);
    }

    void showLeafNodes() {
        cout << "Leaf Nodes: ";
        displayLeafNodes(rootNode);
        cout << "\n";
    }

    // Display the tree level by level
    void showLevelWise() {
        if (rootNode == NULL) return;
        queue<Node*> q;
        q.push(rootNode);
        cout << "Level-wise Display:\n";

        while (!q.empty()) {
            int count = q.size();
            while (count--) {
                Node* temp = q.front();
                q.pop();
                cout << temp->value << " ";

                if (temp->leftChild) q.push(temp->leftChild);
                if (temp->rightChild) q.push(temp->rightChild);
            }
            cout << "\n";
        }
    }
};

// Main function for menu-driven BST operations
int main() {
    BST bst;
    int choice, data;

    do {
        cout << "\nBinary Search Tree Menu\n";
        cout << "1. Insert\n2. Delete\n3. Search\n4. Display Traversals\n5. Depth\n";
        cout << "6. Mirror Image\n7. Copy Tree\n8. Show Parent & Child\n";
        cout << "9. Show Leaf Nodes\n10. Level-wise Display\n11. Exit\n";

        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter value to insert: ";
                cin >> data;
                bst.insert(data);
                cout << data << " inserted successfully.\n";
                break;
            case 2:
                cout << "Enter value to delete: ";
                cin >> data;
                bst.deleteNode(data);
                break;
            case 3:
                cout << "Enter value to search: ";
                cin >> data;
                bst.search(data);
                break;
            case 4:
                bst.display();
                break;
            case 5:
                bst.showDepth();
                break;
            case 6:
                bst.showMirror();
                break;
            case 7:
                bst.copyAndShow();
                break;
            case 8:
                bst.showParentChild();
                break;
            case 9:
                bst.showLeafNodes();
                break;
            case 10:
                bst.showLevelWise();
                break;
            case 11:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice! Try again.\n";
        }

    } while (choice != 11);

    return 0;
}
