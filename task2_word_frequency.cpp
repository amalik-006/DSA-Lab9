#include <iostream>
using namespace std;

// BST Node
struct Node 
{
    char word[50];
    int frequency;
    Node* left;
    Node* right;
};

// Convert uppercase to lowercase
char toLower(char ch) 
{
    if (ch >= 'A' && ch <= 'Z')
        return ch + 32;

    return ch;
}

// Compare two words alphabetically
int compareWords(char word1[], char word2[]) 
{
    int i = 0;

    while (word1[i] != '\0' && word2[i] != '\0') 
    {
        if (word1[i] < word2[i])
            return -1;

        if (word1[i] > word2[i])
            return 1;

        i++;
    }

    if (word1[i] == '\0' && word2[i] == '\0')
        return 0;

    if (word1[i] == '\0')
        return -1;

    return 1;
}

// Create New Node
Node* createNode(char word[]) 
{
    Node* newNode = new Node;

    int i = 0;

    while (word[i] != '\0') 
    {        
        newNode->word[i] = word[i];
        i++;
    }

    newNode->word[i] = '\0';

    newNode->frequency = 1;
    newNode->left = nullptr;
    newNode->right = nullptr;

    return newNode;
}

// Insert Word into BST
Node* insert(Node* root, char word[], int& uniqueWords) 
{
    if (root == nullptr) 
    {
        uniqueWords++;
        return createNode(word);
    }

    int result = compareWords(word, root->word);

    if (result < 0)
        root->left = insert(root->left, word, uniqueWords);

    else if (result > 0)
        root->right = insert(root->right, word, uniqueWords);

    else
        root->frequency++;

    return root;
}

// Display Words Alphabetically
void displayAlphabetical(Node* root) 
{
    if (root == nullptr)
        return;

    displayAlphabetical(root->left);

    cout << root->word << " : " << root->frequency << endl;

    displayAlphabetical(root->right);
}

// Count Nodes
int countNodes(Node* root) 
{
    if (root == nullptr)
        return 0;

    return 1 + countNodes(root->left) + countNodes(root->right);
}

// Store BST Nodes in Array
void storeNodes(Node* root, Node* arr[], int& index) 
{
    if (root == nullptr)
        return;

    storeNodes(root->left, arr, index);

    arr[index++] = root;

    storeNodes(root->right, arr, index);
}

// Display Words by Frequency
void displayByFrequency(Node* root) 
{
    int n = countNodes(root);

    Node* arr[100];

    int index = 0;

    storeNodes(root, arr, index);

    // Selection Sort (Descending Frequency)
    for (int i = 0; i < n - 1; i++) 
    {
        int maxIndex = i;

        for (int j = i + 1; j < n; j++) 
        {
            if (arr[j]->frequency > arr[maxIndex]->frequency)
                maxIndex = j;

            else if (arr[j]->frequency == arr[maxIndex]->frequency &&
                     compareWords(arr[j]->word, arr[maxIndex]->word) < 0)
                maxIndex = j;
        }

        Node* temp = arr[i];
        arr[i] = arr[maxIndex];
        arr[maxIndex] = temp;
    }

    for (int i = 0; i < n; i++) 
    {
        cout << arr[i]->word << " : "
             << arr[i]->frequency << endl;
    }
}

// Find Highest Frequency
int findMaximumFrequency(Node* root) 
{
    if (root == nullptr)
        return 0;

    int maxLeft = findMaximumFrequency(root->left);
    int maxRight = findMaximumFrequency(root->right);

    int maximum = root->frequency;

    if (maxLeft > maximum)
        maximum = maxLeft;

    if (maxRight > maximum)
        maximum = maxRight;

    return maximum;
}

// Display Most Frequent Word
void displayMostFrequent(Node* root, int maximum) 
{
    if (root == nullptr)
        return;

    displayMostFrequent(root->left, maximum);

    if (root->frequency == maximum)
        cout << root->word << " : " << root->frequency << endl;

    displayMostFrequent(root->right, maximum);
}

// Check Alphabet
bool isLetter(char ch) 
{
    return (ch >= 'A' && ch <= 'Z') ||
           (ch >= 'a' && ch <= 'z');
}

// Convert Paragraph into Words and Insert
void processParagraph(Node*& root, char paragraph[], int& totalWords, int& uniqueWords) 
{
    char word[50];

    int i = 0;
    int j = 0;

    while (true) 
    {
        char ch = paragraph[i];

        if (isLetter(ch)) {
            word[j] = toLower(ch);
            j++;
        }

        else if (j > 0) {
            word[j] = '\0';
            root = insert(root, word, uniqueWords);
            
            totalWords++;
            j = 0;
        }

        if (ch == '\0')
            break;

        i++;
    }
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

    char paragraph[] = "The quick brown fox jumps over the lazy dog. The fox is quick and smart.";

    int totalWords = 0;
    int uniqueWords = 0;

    // Process Paragraph
    processParagraph(root, paragraph, totalWords, uniqueWords);

    cout << "===== WORD FREQUENCY INDEXING USING BST =====\n";

    // Alphabetical Display
    cout << "\n===== ALPHABETICAL ORDER =====\n";

    displayAlphabetical(root);

    // Frequency Display
    cout << "\n===== SORTED BY FREQUENCY =====\n";

    displayByFrequency(root);

    // Most Frequent Word
    cout << "\n===== MOST FREQUENT WORD(S) =====\n";

    int maximum = findMaximumFrequency(root);

    displayMostFrequent(root, maximum);

    // Summary
    cout << "\n===== SUMMARY =====\n";

    cout << "Total Unique Words: " << uniqueWords << endl;

    cout << "Total Word Count: " << totalWords << endl;

    deleteTree(root);

    return 0;
}