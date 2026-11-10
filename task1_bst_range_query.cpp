#include <iostream>
using namespace std;

// BST Node
struct Node 
{
    int data;
    Node* left;
    Node* right;
};

// Create New Node
Node* createNode(int value) 
{
    Node* newNode = new Node;

    newNode->data = value;
    newNode->left = nullptr;
    newNode->right = nullptr;

    return newNode;
}

// Insert into BST
Node* insert(Node* root, int value) 
{
    if (root == nullptr)
        return createNode(value);

    if (value < root->data)
        root->left = insert(root->left, value);

    else if (value > root->data)
        root->right = insert(root->right, value);

    return root;
}

// Inorder Traversal
void inorder(Node* root) 
{
    if (root == nullptr)
        return;

    inorder(root->left);

    cout << root->data << " ";

    inorder(root->right);
}

// Find Minimum
Node* findMin(Node* root) 
{
    while (root->left != nullptr)
        root = root->left;

    return root;
}

// Find Maximum
Node* findMax(Node* root) 
{
    while (root->right != nullptr)
        root = root->right;

    return root;
}

// Find Predecessor and Successor
void findPredecessorSuccessor(Node* root, int key) 
{
    Node* predecessor = nullptr;
    Node* successor = nullptr;

    Node* current = root;

    while (current != nullptr) 
    {
        if (key < current->data) 
        {
            successor = current;
            current = current->left;
        }

        else if (key > current->data) 
        {
            predecessor = current;
            current = current->right;
        }

        else {
            if (current->left != nullptr)
                predecessor = findMax(current->left);

            if (current->right != nullptr)
                successor = findMin(current->right);

            break;
        }
    }

    if (current == nullptr) 
    {
        cout << "Key not found\n";
        return;
    }

    cout << "Predecessor: ";

    if (predecessor != nullptr)
        cout << predecessor->data;
    else
        cout << "None";

    cout << "\nSuccessor: ";

    if (successor != nullptr)
        cout << successor->data;
    else
        cout << "None";

    cout << endl;
}

// Recursive Range Query
void recursiveRangeQuery(Node* root, int low, int high, int& comparisons) 
{
    if (root == nullptr)
        return;

    comparisons++;

    if (root->data < low) 
    {
        recursiveRangeQuery(root->right, low, high, comparisons);
        return;
    }

    comparisons++;

    if (root->data > high) 
    {
        recursiveRangeQuery(root->left, low, high, comparisons);
        return;
    }

    recursiveRangeQuery(root->left, low, high, comparisons);

    cout << root->data << " ";

    recursiveRangeQuery(root->right, low, high, comparisons);
}

// Iterative Range Query
void iterativeRangeQuery(Node* root, int low, int high) 
{
    Node* stack[100];
    int top = -1;

    int comparisons = 0;

    Node* current = root;

    cout << "Iterative Range Query: ";

    while (current != nullptr || top != -1) 
    {
        while (current != nullptr) 
        {
            comparisons++;

            if (current->data < low) {
                current = current->right;
            }

            else {
                comparisons++;

                if (current->data > high) {
                    current = current->left;
                }

                else {

                    stack[++top] = current;
                    current = current->left;
                }
            }
        }

        if (top != -1) 
        {
            current = stack[top--];
            cout << current->data << " ";
            current = current->right;
        }
    }

    cout << "\nComparisons: " << comparisons << endl;
}

// Delete BST
void deleteTree(Node* root) 
{
    if (root == nullptr)
        return;

    deleteTree(root->left);
    deleteTree(root->right);

    delete root;
}

// Main Function
int main() 
{
    Node* root = nullptr;

    int values[] = {50, 30, 70, 20, 40, 60, 80, 35, 45, 65, 85};

    int n = 11;

    // Construct BST
    for (int i = 0; i < n; i++)
        root = insert(root, values[i]);

    cout << "===== BST OPERATIONS =====\n\n";

    // Inorder Traversal
    cout << "Inorder Traversal: ";
    inorder(root);

    cout << "\n\n===== PREDECESSOR AND SUCCESSOR =====\n";

    findPredecessorSuccessor(root, 40);

    cout << "\n===== RANGE QUERY (30 - 70) =====\n";

    int comparisons = 0;

    cout << "Recursive Range Query: ";

    recursiveRangeQuery(root, 30, 70, comparisons);

    cout << "\nComparisons: " << comparisons << endl;

    iterativeRangeQuery(root, 30, 70);

    deleteTree(root);

    return 0;
}