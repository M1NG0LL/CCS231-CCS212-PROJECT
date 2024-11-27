#include <iostream>
#include <vector>
using namespace std;

class Btreenode {
public:
    vector<int> keys;                // Vector to store keys
    vector<Btreenode*> children;     // Pointers to child nodes
    int t;                           // Minimum degree
    bool isaleaf;                    // True if the node is a leaf

    Btreenode(int _t, bool isLeaf) {
        t = _t;
        isaleaf = isLeaf;
    }

    void insertnotfull(int key);
    void splitchild(int i, Btreenode* child);
    void traverse();
    Btreenode* search(int key);
    void Delete(int key);
    int getPredecessor(int idx);
    int getSuccessor(int idx);
    void fill(int idx);
    void borrowFromPrev(int idx);
    void borrowFromNext(int idx);
    void merge(int idx);
};

class Btree {
private:
    Btreenode* root; // Pointer to the root of the tree
    int t;           // Minimum degree

public:
    Btree(int _t) {
        root = nullptr;
        t = _t;
    }
    void Delete(int key);


    void traverse() {
        if (root != nullptr)
            root->traverse();
        cout << "\n";
    }

    Btreenode* search(int key) {
        return (root == nullptr) ? nullptr : root->search(key);
    }

    void insert(int key);


};

void Btreenode::traverse() {
    int i;
    for (i = 0; i < keys.size(); i++) {
        if (!isaleaf)
            children[i]->traverse();
        cout << keys[i] << " ";
    }

    if (!isaleaf)
        children[i]->traverse();
}

Btreenode* Btreenode::search(int key) {
    int i = 0;

    while (i < keys.size() && key > keys[i])
        i++;

    if (i < keys.size() && keys[i] == key)
        return this;

    if (isaleaf)
        return nullptr;

    return children[i]->search(key);
}

void Btreenode::Delete(int key) {
    int idx = 0;
    while (idx < keys.size() && keys[idx] < key)
        idx++;

    // Case 1: The key is in this node
    if (idx < keys.size() && keys[idx] == key) {
        if (isaleaf) {
            // Case 1a: The node is a leaf
            keys.erase(keys.begin() + idx);
        } else {
            // Case 1b: The node is an internal node
            if (children[idx]->keys.size() >= t) {
                // Replace with predecessor
                int pred = getPredecessor(idx);
                keys[idx] = pred;
                children[idx]->Delete(pred);
            } else if (children[idx + 1]->keys.size() >= t) {
                // Replace with successor
                int succ = getSuccessor(idx);
                keys[idx] = succ;
                children[idx + 1]->Delete(succ);
            } else {
                // Merge the child and the key
                merge(idx);
                children[idx]->Delete(key);
            }
        }
    } else {
        // Case 2: The key is not in this node
        if (isaleaf) {
            cout << "Key " << key << " does not exist in the tree.\n";
            return;
        }

        // Check if the key exists in the subtree
        bool isLastChild = (idx == keys.size());
        if (children[idx]->keys.size() < t) {
            fill(idx);
        }

        // Recursive delete in the appropriate child
        if (isLastChild && idx > keys.size())
            children[idx - 1]->Delete(key);
        else
            children[idx]->Delete(key);
    }
}

int Btreenode::getPredecessor(int idx) {
    Btreenode* current = children[idx];
    while (!current->isaleaf)
        current = current->children[current->keys.size()];
    return current->keys.back();
}

int Btreenode::getSuccessor(int idx) {
    Btreenode* current = children[idx + 1];
    while (!current->isaleaf)
        current = current->children[0];
    return current->keys.front();
}

void Btreenode::fill(int idx) {
    if (idx != 0 && children[idx - 1]->keys.size() >= t) {
        borrowFromPrev(idx);
    } else if (idx != keys.size() && children[idx + 1]->keys.size() >= t) {
        borrowFromNext(idx);
    } else {
        if (idx != keys.size())
            merge(idx);
        else
            merge(idx - 1);
    }
}

void Btreenode::borrowFromPrev(int idx) {
    Btreenode* child = children[idx];
    Btreenode* sibling = children[idx - 1];

    child->keys.insert(child->keys.begin(), keys[idx - 1]);
    if (!child->isaleaf)
        child->children.insert(child->children.begin(), sibling->children.back());

    keys[idx - 1] = sibling->keys.back();
    sibling->keys.pop_back();
    if (!sibling->isaleaf)
        sibling->children.pop_back();
}

void Btreenode::borrowFromNext(int idx) {
    Btreenode* child = children[idx];
    Btreenode* sibling = children[idx + 1];

    child->keys.push_back(keys[idx]);
    if (!child->isaleaf)
        child->children.push_back(sibling->children[0]);

    keys[idx] = sibling->keys[0];
    sibling->keys.erase(sibling->keys.begin());
    if (!sibling->isaleaf)
        sibling->children.erase(sibling->children.begin());
}

void Btreenode::merge(int idx) {
    Btreenode* child = children[idx];
    Btreenode* sibling = children[idx + 1];

    child->keys.push_back(keys[idx]);

    for (int i = 0; i < sibling->keys.size(); ++i)
        child->keys.push_back(sibling->keys[i]);

    if (!child->isaleaf) {
        for (int i = 0; i < sibling->children.size(); ++i)
            child->children.push_back(sibling->children[i]);
    }

    keys.erase(keys.begin() + idx);
    children.erase(children.begin() + idx + 1);

    delete sibling;
}

void Btree::Delete(int key) {
    if (!root) {
        cout << "Tree is empty.\n";
        return;
    }

    root->Delete(key);

    if (root->keys.size() == 0) {
        Btreenode* temp = root;
        if (root->isaleaf)
            root = nullptr;
        else
            root = root->children[0];

        delete temp;
    }
}


void Btree::insert(int key) {
    if (root == nullptr) {
        root = new Btreenode(t, true);
        root->keys.push_back(key);
    } else {
        if (root->keys.size() == 2 * t - 1) {
            Btreenode* newroot = new Btreenode(t, false);
            newroot->children.push_back(root);
            newroot->splitchild(0, root);

            int i = (newroot->keys[0] < key) ? 1 : 0;
            newroot->children[i]->insertnotfull(key);

            root = newroot;
        } else {
            root->insertnotfull(key);
        }
    }
}

void Btreenode::insertnotfull(int key) {
    int i = keys.size() - 1;

    if (isaleaf) {
        keys.push_back(0);
        while (i >= 0 && keys[i] > key) {
            keys[i + 1] = keys[i];
            i--;
        }
        keys[i + 1] = key;
    } else {
        while (i >= 0 && keys[i] > key)
            i--;

        if (children[i + 1]->keys.size() == 2 * t - 1) {
            splitchild(i + 1, children[i + 1]);
            if (keys[i + 1] < key)
                i++;
        }
        children[i + 1]->insertnotfull(key);
    }
}

void Btreenode::splitchild(int i, Btreenode* child) {
    Btreenode* newnode = new Btreenode(child->t, child->isaleaf);

    for (int j = 0; j < t - 1; j++)
        newnode->keys.push_back(child->keys[j + t]);

    if (!child->isaleaf) {
        for (int j = 0; j < t; j++)
            newnode->children.push_back(child->children[j + t]);
    }

    child->keys.resize(t - 1);
    child->children.resize(t);

    children.insert(children.begin() + i + 1, newnode);
    keys.insert(keys.begin() + i, child->keys[t - 1]);
}

int main() {
 Btree tree(3);
tree.insert(10);
tree.insert(20);
tree.insert(5);
tree.insert(6);
tree.insert(12);
tree.insert(30);
tree.insert(7);
tree.insert(17);
cout<<"the travesrse:\n";
tree.traverse();
int key=6;
if(tree.search(key)!=nullptr)   
cout<<"key:"<<key<<"found in tree\n";
else
{
    cout<<"key:"<<key<<"not found in tree\n";
}
tree.Delete(5);
cout <<"traverseal after deleting 5\n";
tree.traverse();
 return 0;
}
