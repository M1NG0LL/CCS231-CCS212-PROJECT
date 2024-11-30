#include <iostream>
using namespace std;

enum Color
{
    RED,
    BLACK
};

struct Node
{
    int data;
    Color color;
    Node *left, *right, *parent;

    Node(int value) : data(value), color(RED), left(nullptr), right(nullptr), parent(nullptr) {}
};

class Red_Black_Tree
{
    Node *root, *TNULL;

protected:
    void initializeTNULL()
    {
        TNULL = new Node(0);
        TNULL->color = BLACK;
        TNULL->left = nullptr;
        TNULL->right = nullptr;
    }

    void LeftRotation(Node *x)
    {
        Node *y = x->left;
        x->right = y->left;

        if (y->left != TNULL)
        {
            y->left->parent = x;
        }

        y->parent = x->parent;
        if (x->parent == nullptr)
        {
            root = y;
        }
        else if (x == x->parent->left)
        {
            x->parent->left = y;
        }
        else
        {
            x->parent->right = y;
        }

        y->left = x;
        x->parent = y;
    }
    /*
        We wanna to maintain the Red-Black Tree balance after insertion or deletion.

        We the right child of the node being rotated moves up to become the parent of the subtree,
        while the original node moves down to become the left child of this new parent.
        This operation also involves updating pointers to ensure all child and parent relationships are correctly maintained,
        thereby rebalancing the tree to preserve its properties and ensure efficient operations such as search, insert, and delete
    */

    void RightRotation(Node *x)
    {
        Node *y = x->right;
        x->left = y->right;

        if (y->right != TNULL)
        {
            y->right->parent = x;
        }

        y->parent = x->parent;
        if (x->parent == nullptr)
        {
            root = y;
        }
        else if (x == x->parent->right)
        {
            x->parent->right = y;
        }
        else
        {
            x->parent->left = y;
        }

        y->right = x;
        x->parent = y;
    }
    // Same as leftRotation but changing directions

    void insertfix(Node *k)
    {
        Node *u;

        while (k->parent->color == BLACK)
        {
            if (k->parent == k->parent->parent->left)
            {
                u = k->parent->parent->right;

                if (u->color == RED)
                {
                    u->color = BLACK;
                    k->parent->color = BLACK;
                    k->parent->parent->color = RED;
                    k = k->parent->parent;
                }
                else
                {
                    if (k == k->parent->right)
                    {
                        k = k->parent;
                        LeftRotation(k);
                    }

                    k->parent->color = BLACK;
                    k->parent->parent->color = RED;
                    RightRotation(k->parent->parent);
                }
            }
            else
            {
                u = k->parent->parent->left;

                if (u->color == RED)
                {
                    u->color = BLACK;
                    k->parent->color = BLACK;
                    k->parent->parent->color = RED;
                    k = k->parent->parent;
                }
                else
                {
                    if (k == k->parent->left)
                    {
                        k = k->parent;
                        RightRotation(k);
                    }

                    k->parent->color = BLACK;
                    k->parent->parent->color = RED;
                    LeftRotation(k->parent->parent);
                }
            }

            if (k == root)
                break;
        }
        root->color = BLACK;
    }
    /*
        After insertion, the tree may violate Red-Black Tree properties. Fixing ensures:
            1- The root is always BLACK.
            2- No two consecutive RED nodes exist.

        The fix process involves identifying and resolving violations by adjusting the colors of nodes and rotating subtrees when necessary.
         If the parent of the newly inserted node is red, the violation is detected.
          Depending on the color of the node's uncle (the parent's sibling),
           the fix could involve simply recoloring nodes if the uncle is red or performing rotations if the uncle is black.
    */

    void DeleteFix(Node *x)
    {
        Node *s;

        while (x != root && x->color == BLACK)
        {
            if (x == x->parent->left)
            {
                s = x->parent->right;

                if (s->color == RED)
                {
                    s->color = BLACK;
                    x->parent->color = RED;
                    LeftRotation(x->parent);
                    s = x->parent->right;
                }

                if (s->left->color == BLACK && s->right->color == BLACK)
                {
                    s->color = RED;
                    x = x->parent;
                }
                else
                {
                    if (s->right->color == BLACK)
                    {
                        s->left->color = BLACK;
                        s->color = RED;
                        RightRotation(s);
                        s = x->parent->right;
                    }

                    s->color = x->parent->color;
                    x->parent->color = BLACK;
                    s->right->color = BLACK;
                    LeftRotation(x->parent);
                    x = root;
                }
            }
            else
            {
                s = x->parent->left;

                if (s->color == RED)
                {
                    s->color = BLACK;
                    x->parent->color = RED;
                    RightRotation(x->parent);
                    s = x->parent->left;
                }

                if (s->right->color == BLACK && s->left->color == BLACK)
                {
                    s->color = RED;
                    x = x->parent;
                }
                else
                {
                    if (s->left->color == BLACK)
                    {
                        s->right->color = BLACK;
                        s->color = RED;
                        LeftRotation(s);
                        s = x->parent->left;
                    }

                    s->color = x->parent->color;
                    x->parent->color = BLACK;
                    s->left->color = BLACK;
                    RightRotation(x->parent);
                    x = root;
                }
            }
        }
        x->color = BLACK;
    }
    /*
        Fixing deletions in a red-black tree is a critical process to maintain the tree's balanced properties after a node removal.

        When a node is deleted, it can potentially violate the red-black tree properties,
         such as maintaining equal black height in all paths from the root to the leaves and ensuring no two consecutive red nodes appear.
          The fix deletion process starts by identifying the type of node being removed—either a leaf node or an internal node with one or two children.
           If the node is black, its removal could disrupt the black height,
            leading to an imbalance. The process involves a series of steps,
             including node recoloring and tree rotations, to restore the balance.
              These operations ensure that every path from the root to the leaves retains the same number of black nodes and the red-black tree properties are upheld.
               The process continues up the tree, checking and correcting any violations until the entire tree maintains its balanced state,
                ensuring efficient performance for future operations.
    */

    void transplant(Node *u, Node *v)
    {
        if (u->parent == nullptr)
        {
            root = v;
        }
        else if (u == u->parent->left)
        {
            u->parent->left = v;
        }
        else
        {
            u->parent->right = v;
        }
        v->parent = u->parent;
    }

    Node *minimum(Node *node)
    {
        while (node->left != TNULL)
        {
            node = node->left;
        }
        return node;
    }

    void Print_Tree(Node *node, int space, int level = 6)
    {
        if (node == TNULL)
            return;

        space += level;

        Print_Tree(node->right, space);

        cout << endl;
        for (int i = level; i < space; i++)
        {
            cout << " ";
        }
        cout << node->data << "(" << (node->color == RED ? "R" : "B") << ")\n";

        Print_Tree(node->left, space);
    }

    void inOrderHelper(Node *node)
    {
        if (node == TNULL)
            return;

        inOrderHelper(node->left);

        cout << node->data << "(" << (node->color == RED ? "R" : "B") << ") ";

        inOrderHelper(node->right);
    }

public:
    Red_Black_Tree()
    {
        initializeTNULL();
        root = TNULL;
    }

    void insert(int value)
    {
        Node *node = new Node(value);
        node->parent = nullptr;
        node->left = TNULL;
        node->right = TNULL;

        Node *y = nullptr;
        Node *x = root;

        while (x != TNULL)
        {
            y = x;

            if (node->data < x->data)
            {
                x = x->left;
            }
            else
            {
                x = x->right;
            }
        }

        node->parent = y;

        if (y == nullptr)
        {
            root = node;
        }
        else if (node->data < y->data)
        {
            y->left = node;
        }
        else
        {
            y->right = node;
        }

        if (node->parent == nullptr)
        {
            node->color = BLACK;
            return;
        }

        if (node->parent->parent == nullptr)
        {
            return;
        }

        insertfix(node);
    }
    /*
        Inserting a node into a red-black tree is a nuanced process designed to maintain the tree's balanced structure.

        ...
    */

    void Delete(int key)
    {
        Node *z = root;
        Node *x, *y;

        while (z != TNULL)
        {
            if (z->data == key)
                break;
            if (key < z->data)
                z = z->left;
            else
                z = z->right;
        }

        if (z == TNULL)
        {
            cout << "Key not found in the tree." << endl;
            return;
        }

        y = z;
        Color yOriginalColor = y->color;

        if (z->left == TNULL)
        {
            x = z->right;
            transplant(z, z->right);
        }
        else if (z->right == TNULL)
        {
            x = z->left;
            transplant(z, z->left);
        }
        else
        {
            y = minimum(z->right);
            yOriginalColor = y->color;
            x = y->right;
            if (y->parent == z)
            {
                x->parent = y;
            }
            else
            {
                transplant(y, y->right);
                y->right = z->right;
                y->right->parent = y;
            }
            transplant(z, y);
            y->left = z->left;
            y->left->parent = y;
            y->color = z->color;
        }
        delete z;

        if (yOriginalColor == BLACK)
        {
            DeleteFix(x);
        }
    }
    /*
        Deleting a node from a red-black tree is a complex process aimed at maintaining the tree's balanced structure.

        When a node is removed, it can potentially violate the red-black properties,
         such as maintaining equal black height in all paths from the root to the leaves and ensuring no two consecutive red nodes appear.
          The deletion process begins with a standard binary search tree deletion,
           which includes finding the node to be removed and replacing it with its successor if it has two children.
            After removal, if the deleted node or the node that replaced it is black, this can cause a violation of the red-black properties.
             To fix this, the tree undergoes a series of adjustments, which may involve recoloring nodes and performing rotations to ensure the properties are preserved.
              These steps include cases like when the sibling of the deleted node is red, or when the sibling is black and has black children, among others.
               The goal is to restore the tree's balance while ensuring that the red-black properties are maintained,
                which is crucial for the tree to provide efficient performance for subsequent operations.
                 This meticulous process ensures the red-black tree remains balanced, preserving its ability to perform insertions, deletions, and searches efficiently.
    */

    void display()
    {
        Print_Tree(root, 0);
    }

    void inOrder()
    {
        cout << "In-order traversal: ";
        inOrderHelper(root);
        cout << endl;
    }
};

int main()
{
    Red_Black_Tree rbt;

    rbt.insert(10);
    rbt.insert(20);
    rbt.insert(30);
    rbt.insert(15);
    rbt.insert(25);

    rbt.inOrder();

    cout << "Red-Black Tree after insertion:" << endl;
    rbt.display();

    rbt.Delete(20);

    cout << "\nRed-Black Tree after deletion:" << endl;
    rbt.display();

    return 0;
}