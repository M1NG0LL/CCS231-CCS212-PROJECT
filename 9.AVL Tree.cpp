#include<iostream>
using namespace std;

struct Tree 
{
char C;
Tree *left,*right;
int length;
};

int max(int a,int b)
{
return (a>b)? a:b;
}

Tree *minnode(Tree* node)
{
    Tree* current=node;
    while(current->left!=nullptr)
    {
        current= current->left;
    }
    return current;
}

int hieght(Tree* node)
{
    if(!node)return 0;
    return node->length;
}

Tree *createnode(char thing)
{
Tree *node = new(Tree);
node->C=thing;
node->left=nullptr;
node->right=nullptr;
node->length=1;
return(node);
}

Tree *rotateright(Tree* R)
{
cout<<"rotate right on node"<<R->C<<endl;
Tree *temp1=R->left;
Tree *temp2=R->right;
temp1->right=R;
R->left=temp2;
R->length=max(hieght(R->left),hieght(R->right))+1;
temp1->length=max(hieght(temp1->left),hieght(temp1->right))+1;
return temp1;
}

Tree *rotateleft(Tree* L)
{
cout<<"rotate left on node"<<L->C<<endl;
Tree *temp1=L->right;
Tree *temp2=L->left;
temp1->left=L;
L->right=temp2;
L->length=max(hieght(L->left),hieght(L->right))+1;
temp1->length=max(hieght(temp1->left),hieght(temp1->right))+1;
return temp1;
}

int checkbalance(Tree *balance)
{
    if(balance==nullptr)return 0;
    return hieght(balance->left)-hieght(balance->right);
}

Tree *insert(Tree* root,char data)
{
    if(!root)return createnode(data);//check if root is null or not

if(data<root->C)
root->left=insert(root->left,data);
else if(data>root->C)root->right=insert(root->right,data);

root->length=1+(hieght(root->left)>hieght(root->right)? 
hieght(root->left):hieght(root->right));
int bal=checkbalance(root);

if(bal>1 && checkbalance(root->left)>=0)
return rotateright(root);//check if node is heavy left and rotate right

if(bal>1 && checkbalance(root->right)<0)
{
    root->left=rotateleft(root->left);
    return rotateleft(root);//preform a left right rotate
}

if(bal<-1 && checkbalance(root->right)<=0)
return rotateleft(root);

if(bal<-1 && checkbalance(root->right)>0)
{
    root->right=rotateright(root->right);
    return rotateright(root);
}
return root;
}


Tree* delet(Tree* root, char data) {
    if (!root) return root;

    if (data < root->C)
        root->left = delet(root->left, data);
    else if (data > root->C)
        root->right = delet(root->right, data);
    else {
        if (root->left == NULL) {
            Tree* temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            Tree* temp = root->left;
            free(root);
            return temp;
        }

        Tree* temp = minnode(root->right);
        root->C = temp->C;
        root->right = delet(root->right, temp->C);
    }

    if (root == NULL) return root;

    root->length = 1 + (hieght(root->left) > hieght(root->right) ? hieght(root->left) : hieght(root->right));
    int balance = checkbalance(root);

    if (balance > 1 && checkbalance(root->left) >= 0)
        return rotateright(root);

    if (balance > 1 && checkbalance(root->left) < 0) {
        root->left = rotateleft(root->left);
        return rotateright(root);
    }

    if (balance < -1 && checkbalance(root->right) <= 0)
        return rotateleft(root);

    if (balance < -1 && checkbalance(root->right) > 0) {
        root->right = rotateright(root->right);
        return rotateleft(root);
    }

    return root;
}

void inorder(Tree* root)
{
if(root != nullptr)
{
    inorder(root->left);
    cout<<root->C<<" ";
    inorder(root->right);
}
}
int main() {
    Tree* root = nullptr;
    int x;
    bool B = true;
    char Letters[] = {'C', 'B', 'E', 'A', 'D', 'H', 'G', 'F'};
    int n = sizeof(Letters) / sizeof(Letters[0]);

    // Insert initial nodes
    for (int i = 0; i < n; i++) {
        root = insert(root, Letters[i]);  // Ensure root is updated
    }
inorder(root);
    // Menu for user input
    while (B) {
        cout << "Enter 1 to insert\nEnter 2 to delete\nEnter 3 to display\nEnter 4 to exit\n";
        cin >> x;
        switch (x) {
            case 1: {
                char letter;
                cout << "Enter the Letter you want to add: ";
                cin >> letter;
                root = insert(root, letter);  // Update root
                cout << "After insertion (Inorder): ";
                inorder(root);
                cout << endl;
                break;
            }
case 2: {
    char letter;
    cout << "Enter the Letter you want to delete: ";
    cin >> letter;
    root = delet(root, letter);  // Call the delete function and update root
    cout << "After deletion (Inorder): ";
    inorder(root);
    cout << endl;
    break;
}
            case 3:
                if (root == nullptr) {
                    cout << "The tree is empty." << endl;
                } else {
                    cout << "Inorder traversal: ";
                    inorder(root);
                    cout << endl;
                }
                break;
            case 4:
                B = false;
                break;
            default:
                cout << "Invalid input" << endl;
                break;
        }
    }

    return 0;
}
