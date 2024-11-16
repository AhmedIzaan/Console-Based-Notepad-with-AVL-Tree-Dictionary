#include <ncurses.h>
#include <iostream>
#include <string>
#include <fstream>
using namespace std;

class listNode
{
public:
    char data;
    listNode *next;

    listNode(char d) : data(d), next(nullptr) {}
};

class LinkedList
{
public:
    listNode *head;
    LinkedList() : head(nullptr) {}

    void append(char data)
    {
        listNode *newNode = new listNode(data);
        if (!head)
        {
            head = newNode;
            return;
        }
        listNode *temp = head;
        while (temp->next)
        {
            temp = temp->next;
        }
        temp->next = newNode;
    }

    void deleteAtEnd()
    {
        if (!head)
            return;
        if (!head->next)
        {
            delete head;
            head = nullptr;
            return;
        }
        listNode *temp = head;
        while (temp->next->next)
        {
            temp = temp->next;
        }
        delete temp->next;
        temp->next = nullptr;
    }

    void display(int startRow)
    {

        int row = startRow;
        int col = 0;
        listNode *temp = head;
        while (temp)
        {
            mvaddch(row, col++, temp->data);
            if (col >= COLS) // If reached end of the row, go to the next line
            {
                row++;
                col = 0;
            }
            temp = temp->next;
        }

        refresh(); // Refresh the screen to display the updates
    }

    ~LinkedList()
    {
        while (head)
        {
            listNode *temp = head;
            head = head->next;
            delete temp;
        }
    }
};

class queueNode
{
public:
    char data;
    queueNode *next;

    queueNode(char d) : data(d), next(nullptr) {}
};

class Queue
{
public:
    queueNode *front;
    queueNode *rear;
    Queue() : front(nullptr), rear(nullptr) {}

    void enqueue(char data)
    {
        queueNode *newNode = new queueNode(data);
        if (!rear)
        {
            front = rear = newNode;
            return;
        }
        rear->next = newNode;
        rear = newNode;
    }

    void dequeue()
    {
        if (!front)
            return;
        queueNode *temp = front;
        front = front->next;
        if (!front)
            rear = nullptr;
        delete temp;
    }
    void deleteAtEnd()
    {
        if (!front)
            return;
        if (!front->next)
        {
            delete front;
            front = rear = nullptr;
            return;
        }
        queueNode *temp = front;
        while (temp->next->next)
        {
            temp = temp->next;
        }
        delete temp->next;
        temp->next = nullptr;
        rear = temp;
    }

    bool isEmpty() const { return front == nullptr; }

    char getFront() const { return front ? front->data : '\0'; }

    string dequeueAll()
    {
        string word;
        while (!isEmpty())
        {
            word += getFront();
            dequeue();
        }
        return word;
    }

    ~Queue()
    {
        while (front)
        {
            queueNode *temp = front;
            front = front->next;
            delete temp;
        }
    }
};

class TreeNode
{
public:
    string value;
    TreeNode *left;
    TreeNode *right;

    TreeNode(string v) : value(v), left(nullptr), right(nullptr) {}
};

class AVLTree
{
public:
    TreeNode *root;

    AVLTree() : root(nullptr) {}

    int height(TreeNode *r) const
    {
        return r ? max(height(r->left), height(r->right)) + 1 : -1;
    }

    int getBalanceFactor(TreeNode *n) const
    {
        return n ? height(n->left) - height(n->right) : 0;
    }

    TreeNode *rightRotate(TreeNode *y)
    {
        TreeNode *x = y->left;
        TreeNode *T2 = x->right;
        x->right = y;
        y->left = T2;
        return x;
    }

    TreeNode *leftRotate(TreeNode *y)
    {
        TreeNode *x = y->right;
        TreeNode *T2 = x->left;
        x->left = y;
        y->right = T2;
        return x;
    }

    TreeNode *insert(TreeNode *node, const string &value)
    {
        if (!node)
            return new TreeNode(value);
        if (value < node->value)
            node->left = insert(node->left, value);
        else if (value > node->value)
            node->right = insert(node->right, value);
        else
            return node;

        int bf = getBalanceFactor(node);

        if (bf > 1 && value < node->left->value)
            return rightRotate(node);
        if (bf < -1 && value > node->right->value)
            return leftRotate(node);
        if (bf > 1 && value > node->left->value)
        {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }
        if (bf < -1 && value < node->right->value)
        {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }
        return node;
    }

    void insertValue(const string &value)
    {
        root = insert(root, value);
    }

    bool searchValue(TreeNode *node, const string &value) const
    {
        if (!node)
            return false;
        if (node->value == value)
            return true;
        return value < node->value ? searchValue(node->left, value) : searchValue(node->right, value);
    }

    bool search(const string &value) const
    {
        return searchValue(root, value);
    }
};

void loadDictionary(AVLTree &dictionary, const string &filename)
{
    ifstream file(filename);
    string word;
    while (file >> word)
        dictionary.insertValue(word);
}

string substituteLetters(AVLTree &dictionary, const string &word)
{
    string modifiedWord;
    for (size_t i = 0; i < word.length(); ++i)
    {
        modifiedWord = word;
        for (char ch = 'a'; ch <= 'z'; ++ch)
        {
            if (word[i] != ch)
            {
                modifiedWord[i] = ch;
                if (dictionary.search(modifiedWord))
                {
                    return modifiedWord;
                }
            }
        }
    }
    return "";
}

string omitLetters(AVLTree &dictionary, const string &word)
{
    string modifiedWord;
    for (size_t i = 0; i < word.length(); ++i)
    {
        modifiedWord = word.substr(0, i) + word.substr(i + 1);
        if (dictionary.search(modifiedWord))
        {
            return modifiedWord;
        }
    }
    return "";
}

string insertLetters(AVLTree &dictionary, const string &word)
{
    string modifiedWord;
    for (size_t i = 0; i <= word.length(); ++i)
    {
        for (char ch = 'a'; ch <= 'z'; ++ch)
        {
            modifiedWord = word.substr(0, i) + ch + word.substr(i);
            if (dictionary.search(modifiedWord))
            {
                return modifiedWord;
            }
        }
    }
    return "";
}

string reverseLetters(AVLTree &dictionary, const string &word)
{
    string modifiedWord;
    for (size_t i = 0; i < word.length() - 1; ++i)
    {
        modifiedWord = word;
        swap(modifiedWord[i], modifiedWord[i + 1]);
        if (dictionary.search(modifiedWord))
        {
            return modifiedWord;
        }
    }
    return "";
}

void suggestCorrections(AVLTree &dictionary, const string &word)
{
    string suggestion;
    int suggestionRow = 3;

    for (int row = suggestionRow; row < LINES; ++row)
    {
        move(row, 0);
        clrtoeol();
    }

    suggestion = substituteLetters(dictionary, word);
    if (!suggestion.empty())
    {
        mvprintw(suggestionRow++, 0, "Did you mean (substitution): %s?", suggestion.c_str());
    }

    suggestion = omitLetters(dictionary, word);
    if (!suggestion.empty())
    {
        mvprintw(suggestionRow++, 0, "Did you mean (omission): %s?", suggestion.c_str());
    }

    suggestion = insertLetters(dictionary, word);
    if (!suggestion.empty())
    {
        mvprintw(suggestionRow++, 0, "Did you mean (insertion): %s?", suggestion.c_str());
    }

    suggestion = reverseLetters(dictionary, word);
    if (!suggestion.empty())
    {
        mvprintw(suggestionRow++, 0, "Did you mean (reversal): %s?", suggestion.c_str());
    }

    if (suggestionRow == 3)
    {
        mvprintw(suggestionRow++, 0, "No suggestions found.");
    }

    refresh();
}

void spellCheckWord(AVLTree &dictionary, Queue &wordQueue)
{
    string word = wordQueue.dequeueAll();
    move(1, 0);
    clrtoeol();

    mvprintw(1, 0, "Checking word: %s", word.c_str());

    if (dictionary.search(word))
    {
        mvprintw(1, 0, "Word is correct: %s", word.c_str());
    }

    else
    {

        suggestCorrections(dictionary, word);
    }

    refresh();
}

int main()
{
    initscr();
    noecho();
    cbreak();
    keypad(stdscr, TRUE);

    AVLTree dictionary;
    loadDictionary(dictionary, "dictionary.txt");

    LinkedList text;
    Queue wordQueue;
    char ch;

    mvprintw(0, 0, "Notepad - Press ESC to exit");

    while (true)
    {
        ch = getch();
        if (ch == 27)
            break;
        else if (ch == 7)
        {

            text.deleteAtEnd();

            if (!wordQueue.isEmpty())
                wordQueue.deleteAtEnd();

            for (int row = 2; row < LINES; ++row)
            {
                move(row, 0);
                clrtoeol();
            }

            text.display(2);
            refresh();
        }

        else if (ch == ' ')
        {
            refresh();
            text.append(' ');
            spellCheckWord(dictionary, wordQueue);
        }
        else
        {
            text.append(ch);
            wordQueue.enqueue(ch);
        }

        mvprintw(0, 0, "Notepad - Press ESC to exit");
        text.display(2);
        refresh();
    }

    endwin();
    return 0;
}
