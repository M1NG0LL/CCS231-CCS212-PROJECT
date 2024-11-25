#include <iostream>
#include <iomanip> // For formatting the ASCII tree
using namespace std;

struct Node
{
    int data;
    Node *right;

    Node(int value) : data(value), right(nullptr) {}
};

class Degenerate_Binary_Tree
{
    Node *root;

public:
    Degenerate_Binary_Tree() : root(nullptr) {}

    void insert(int value)
    {
        if (!root)
        {
            root = new Node(value);
            return;
        }

        Node *current = root;

        while (current->right)
        {
            current = current->right;
        }

        current->right = new Node(value);
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
    }

    void Inorder(Node *root)
    {
        if (root)
        {
            cout << root->data << " ";
            Inorder(root->right);
        }
    }

    void Preorder(Node *root)
    {
        if (root)
        {
            cout << root->data << " ";
            Preorder(root->right);
        }
    }

    void Postorder(Node *root)
    {
        if (root)
        {
            Postorder(root->right);
            cout << root->data << " ";
        }
    }

    Node *GetRoot()
    {
        return root;
    }
};

int main()
{
    Degenerate_Binary_Tree tree;

    tree.insert(1);
    tree.insert(2);
    tree.insert(3);
    tree.insert(4);
    tree.insert(5);

    cout << "Degenerate Binary Tree (ASCII Representation):\n";
    tree.display();

    cout << "\nIn-order Traversal: ";
    tree.Inorder(tree.GetRoot());
    cout << endl;

    cout << "Pre-order Traversal: ";
    tree.Preorder(tree.GetRoot());
    cout << endl;

    cout << "Post-order Traversal: ";
    tree.Postorder(tree.GetRoot());
    cout << endl;
}