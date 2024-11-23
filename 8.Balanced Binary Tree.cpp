#include <iostream>
using namespace std;

struct TreeNode {
    int data;
    TreeNode* left;
    TreeNode* right;

    TreeNode(int value) {
        data = value;
        left = nullptr;
        right = nullptr;
    }
};

TreeNode* createNewNode(int data) {
    return new TreeNode(data);
}

TreeNode* search(TreeNode* node, int target) {
    if (node == nullptr) {
        return nullptr;
    } else if (node->data == target) {
        return node;
    } else if (target < node->data) {
        return search(node->left, target);
    } else {
        return search(node->right, target);
    }
}

TreeNode* insert(TreeNode* root, int value) {
    if (root == nullptr) {
        return createNewNode(value);
    }
    if (value < root->data) {
        root->left = insert(root->left, value);
    } else if (value > root->data) {
        root->right = insert(root->right, value);
    }
    return root;
}

TreeNode* findMin(TreeNode* node) {
    // Finds the node with the minimum value in a BST
    while (node->left != nullptr) {
        node = node->left;
    }
    return node;
}

TreeNode* deleteNode(TreeNode* root, int key) {
    if (root == nullptr) {
        return root; // Base case: key not found
    }

    if (key < root->data) {
        // Key is smaller than root's data, so go to the left subtree
        root->left = deleteNode(root->left, key);
    } else if (key > root->data) {
        // Key is greater than root's data, so go to the right subtree
        root->right = deleteNode(root->right, key);
    } else {
        // Found the node to be deleted

        // Case 1: Node has no child (leaf node)
        if (root->left == nullptr && root->right == nullptr) {
            delete root;
            return nullptr;
        }

        // Case 2: Node has one child
        if (root->left == nullptr) {
            TreeNode* temp = root->right;
            delete root;
            return temp;
        } else if (root->right == nullptr) {
            TreeNode* temp = root->left;
            delete root;
            return temp;
        }

        // Case 3: Node has two children
        // Find the inorder successor (smallest in the right subtree)
        TreeNode* temp = findMin(root->right);
        // Copy the inorder successor's value to this node
        root->data = temp->data;
        // Delete the inorder successor
        root->right = deleteNode(root->right, temp->data);
    }

    return root;
}



void postorder(TreeNode* root) {
    if (root == nullptr)
        return;
    postorder(root->left);
    postorder(root->right);
    cout << root->data << ",";
}

void preorder(TreeNode* root) {
    if (root == nullptr)
        return;
    cout << root->data << ",";
    preorder(root->left);
    preorder(root->right);
}

void inorder(TreeNode* root) {
    if (root == nullptr)
        return;
    inorder(root->left);
    cout << root->data << ",";
    inorder(root->right);
}

int main() {
    int x, y;bool b=true;
    TreeNode* root = createNewNode(13);
    TreeNode* Node7 = createNewNode(7);
    TreeNode* Node15 = createNewNode(15);
    TreeNode* Node3 = createNewNode(3);
    TreeNode* Node8 = createNewNode(8);
    TreeNode* Node14 = createNewNode(14);
    TreeNode* Node19 = createNewNode(19);
    TreeNode* Node18 = createNewNode(18);

    root->left = Node7;
    root->right = Node15;

    Node7->left = Node3;
    Node7->right = Node8;

    Node15->left = Node14;
    Node15->right = Node19;

    Node19->left = Node18;

    cout << "Postorder traversal: ";
    postorder(root);
    cout << "\nPreorder traversal: ";
    preorder(root);
    cout << "\nInorder traversal: ";
    inorder(root);


while(b){
    cout << "\nEnter 1 to search, 2 to insert\n3 to delete\n 4 to exit\n";
    cin >> x;
    switch (x) {
    case 1:
        cout << "Enter the number you want to search for: ";
        cin >> y;
        if (TreeNode* result = search(root, y)) {
            cout << "Value found: " << result->data;
        } else {
            cout << "Value not found";
        }
        break;
    case 2:
        cout << "Enter the number to insert: ";
        cin >> y;
        root = insert(root, y);
        cout << "Inorder after insertion: ";
        inorder(root);
        break;
    case 3:
         cout << "Enter the number to delete: ";
        cin >> y;
        root = deleteNode(root, y);
        cout << "Inorder after deletion: ";
        inorder(root);
        break;

        case 4:b=false;
        break;
    default:
        cout << "Invalid option";
        break;
    }
}
    return 0;
}
