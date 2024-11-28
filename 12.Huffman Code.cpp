#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>
using namespace std;

struct Node
{
    char ch;
    int freq;
    Node *left, *right;
    Node(char c, int f) : ch(c), freq(f), left(nullptr), right(nullptr) {}
};

struct comp
{
    bool operator()(Node *a, Node *b)
    {
        return a->freq > b->freq;
    }
};

void buildhufftree(Node *root, const string &code, unordered_map<char, string> &huffmancode)
{
    if (!root)
        return;

    if (!root->left && !root->right)
    {
        huffmancode[root->ch] = code;
    }

    buildhufftree(root->left, code + "0", huffmancode);
    buildhufftree(root->right, code + "1", huffmancode);
}

void huffmancodeing(const string &text)
{
    unordered_map<char, int> freq;
    for (char ch : text)
    {
        freq[ch]++;
    }

    priority_queue<Node *, vector<Node *>, comp> pq;
    for (auto &pair : freq)
    {
        pq.push(new Node(pair.first, pair.second));
    }

    while (pq.size() > 1)
    {
        Node *left = pq.top();
        pq.pop();
        Node *right = pq.top();
        pq.pop();

        Node *newNode = new Node('\0', left->freq + right->freq);
        newNode->left = left;
        newNode->right = right;
        pq.push(newNode);
    }
    Node *root = pq.top();

    unordered_map<char, string> huffmancode;
    buildhufftree(root, "", huffmancode);

    cout << "huffmancode:\n";
    for (auto &pair : huffmancode)
    {
        cout << pair.first << ":" << pair.second << endl;
    }
    string encoded = "";
    for (char ch : text)
    {
        encoded += huffmancode[ch];
    }
    cout << "encoded string" << encoded << endl;
}

int main()
{
    string text = "hello world";
    cout << text << endl;
    huffmancodeing(text);
    return 0;
}
