#include <iostream>
#include <queue>
#include <iomanip> // For formatting the ASCII tree
using namespace std;

struct Node
{
    int data;
    Node *left;
    Node *right;

    Node(int value) : data(value), left(nullptr), right(nullptr) {}
};

class Complete_Binary_Tree
{
    Node *root;

public:
    Complete_Binary_Tree() : root(nullptr) {} // O(1)

    void insert(int value) // O(N)
    {
        if (!root)
        {
            root = new Node(value);
            return;
        }

        queue<Node *> q;

        q.push(root);

        while (!q.empty())
        {
            Node *current = q.front();
            q.pop();

            if (current->left == nullptr)
            {
                current->left = new Node(value);
                break;
            }
            else
                q.push(current->left);

            if (current->right == nullptr)
            {
                current->right = new Node(value);
                break;
            }
            else
                q.push(current->right);
        }
    }

    void Delete(int value) // O(N)
    {
        if (!root)
            return;

        queue<Node *> q;
        q.push(root);

        Node *node_to_delete = nullptr;
        Node *deepNode = nullptr;
        Node *parentOfDeepNode = nullptr;

        while (!q.empty())
        {
            deepNode = q.front();
            q.pop();

            if (deepNode->data == value)
                node_to_delete = deepNode;

            if (deepNode->left)
            {
                parentOfDeepNode = deepNode;
                q.push(deepNode->left);
            }
            if (deepNode->right)
            {
                parentOfDeepNode = deepNode;
                q.push(deepNode->right);
            }
        }

        if (node_to_delete != nullptr)
        {
            node_to_delete->data = deepNode->data;

            if (parentOfDeepNode != nullptr)
            {
                if (parentOfDeepNode->left == deepNode)
                {
                    parentOfDeepNode->left = nullptr;
                }
                else
                {
                    parentOfDeepNode->right = nullptr;
                }
            }

            if (deepNode == root)
            {
                root = nullptr;
            }

            delete deepNode;
        }
    }

    void display() // O(N)
    {
        Print_Tree(root, 0);
    }

    void Print_Tree(Node *node, int space, int level = 6) // O(N)
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

    void levelOrderTraversal() // O(N)
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
};

int main() // O(4)
{
    Complete_Binary_Tree tree;

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

    cout << "Deleting node with value 4...\n";
    tree.Delete(4);
    cout << endl;

    cout << "Full Binary Tree (ASCII Representation) after deletion:\n";
    tree.display();
    cout << endl;
}

// So the time Complexity of main is O(N)