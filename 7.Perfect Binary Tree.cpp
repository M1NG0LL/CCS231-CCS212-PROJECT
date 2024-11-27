#include <iostream>
#include <queue>
#include <iomanip> // For formatting the ASCII tree
using namespace std;

struct Node
{
    int data;
    Node *right;
    Node *left;

    Node(int value) : data(value), right(nullptr), left(nullptr) {}
};

class Perfect_Binary_Tree
{
    Node *root;

public:
    Perfect_Binary_Tree() : root(nullptr) {}

    void insert(int value)
    {
        if (!root)
        {
            root = new Node(value);
        }

        queue<Node *> q;
        q.push(root);

        while (!q.empty())
        {
            Node *current = q.front();
            q.pop();

            if (!current->left)
                current->left = new Node(value);
            else
                q.push(current->left);
            if (!current->right)
                current->right = new Node(value);
            else
                q.push(current->right);
        }
    }

    void Delete(int value)
    {
        if (!root)
            return;

        queue<Node *> q;
        q.push(root);

        Node *node_to_delete = nullptr;
        Node *deepnode = nullptr;

        while (!q.empty())
        {
            deepnode = q.front();
            q.pop();

            if (deepnode->data == value)
            {
                node_to_delete = deepnode;
            }

            if (deepnode->left)
                q.push(deepnode->left);
            if (deepnode->right)
                q.push(deepnode->right);
        }

        if (node_to_delete != nullptr)
        {
            node_to_delete->data = deepnode->data;

            delete deepnode;
        }
    }

    void levelOrderTraversal()
    {
        if (!root)
            return;

        queue<Node *> q;

        q.push(root);

        cout << "Level-order Traversal: ";

        while (!q.empty())
        {
            Node *current = q.front();
            q.pop();

            cout << current->data << " ";

            if (current->left)
                q.push(current->left);
            if (current->right)
                q.push(current->right);
        }
        cout << endl;
    }

    void display()
    {
        Print_Tree(root, 0);
    }

    void Print_Tree(Node *node, int space, int level = 6)
    {
        if (!node)
            return;

        space += level;

        Print_Tree(node->right, space);

        cout << endl;
        for (int i = level; i < space; i++)
        {
            cout << " ";
        }
        cout << node->data << "\n";

        Print_Tree(node->left, space);
    }

    bool isPerfectUtil(Node *node, int level, int height)
    {
        if (node == nullptr)
            return true;

        if (node->left == nullptr && node->right == nullptr)
        {
            return (level + 1 == height);
        }

        if (node->left == nullptr || node->right == nullptr)
            return false;

        return isPerfectUtil(node->left, level + 1, height) && isPerfectUtil(node->right, level + 1, height);
    }

    bool isPerfect()
    {
        if (!root)
            return true;

        int height = calculateHeight(root);

        return isPerfectUtil(root, 0, height);
    }

    int calculateHeight(Node *node)
    {
        int height = 0;
        while (node != nullptr)
        {
            height++;
            node = node->left;
        }
        return height;
    }

    Node *GetRoot()
    {
        return root;
    }
};

int main()
{
    Perfect_Binary_Tree tree;

    tree.insert(1);
    tree.insert(2);
    tree.insert(3);
    tree.insert(4);
    tree.insert(5);
    tree.insert(6);
    tree.insert(7);

    cout << "Full Binary Tree (ASCII Representation):\n";
    tree.display();

    tree.levelOrderTraversal();

    cout << "Is the tree perfect? " << (tree.isPerfect() ? "Yes" : "No") << endl;

    cout << "Deleting node with value 4...\n";
    tree.Delete(4);
    cout << endl;

    cout << "Full Binary Tree (ASCII Representation) after deletion:\n";
    tree.display();
    cout << endl;

    cout << "Is the tree perfect after deletion? " << (tree.isPerfect() ? "Yes" : "No") << endl;
}