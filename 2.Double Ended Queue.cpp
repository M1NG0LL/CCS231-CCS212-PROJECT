#include <iostream>
using namespace std;

struct Node
{
    int data;
    Node *next;
    Node *prev;
};

class Deque
{
    /*
    How we wanna the deque to appear:

    front -> [15 | prev: nullptr | next: 10] <-> [10 | prev: 15 | next: 9] <-> [9 | prev: 10 | next: 30] <-> [30 | prev: 9 | next: nullptr] <- rear

    */
    Node *front;
    Node *rear;

public:
    Deque() : front(nullptr), rear(nullptr) {}; // O(1)

    ~Deque() // O(N)
    {
        while (front)
        {
            Node *temp = front;
            front = front->next;
            delete temp;
        }
    }

    bool empty() // O(1)
    {
        return front == nullptr || rear == nullptr;
    }

    int getFront() // O(1)
    {
        if (empty())
        {
            cout << "Deque is empty!" << endl;
            return -1;
        }

        return front->data;
    }

    int getRear() // O(1)
    {
        if (empty())
        {
            cout << "Deque is empty!" << endl;
            return -1;
        }

        return rear->data;
    }

    void display() // O(N)
    {
        if (empty())
        {
            cout << "Deque is empty!\n";
            return;
        }

        Node *temp = front;
        cout << "Deque elements: ";
        while (temp)
        {
            cout << temp->data << " ";
            temp = temp->next;
        }

        cout << endl;
    }

    void pushFront(int data) // O(1)
    {
        Node *newNode = new Node{data, nullptr, nullptr};

        if (empty())
        {
            front = rear = newNode;
        }
        else
        {
            newNode->next = front;
            front->prev = newNode;
            front = newNode;
        }
    }

    void popFront() // O(1)
    {
        if (empty())
        {
            cout << "Deque is empty!" << endl;
            return;
        }

        Node *temp = front;

        front = front->prev;

        if (front)
        {
            front->prev = nullptr; // if the front != nullptr, wpdate the prev only
        }
        else
        {
            rear = nullptr; // if the dq became empty, we will change the value of rear
        }

        delete temp;
    }

    void pushRear(int data) // O(1)
    {
        Node *newNode = new Node{data, nullptr, nullptr};

        if (empty())
        {
            front = rear = newNode;
        }
        else
        {
            newNode->prev = rear;
            rear->next = newNode;
            rear = newNode;
        }
    }

    void popRear() // O(1)
    {
        if (empty())
        {
            cout << "Deque is empty!" << endl;
            return;
        }

        Node *temp = rear;

        front = front->prev;

        if (rear)
        {
            rear->prev = nullptr;
        }
        else
        {
            front = nullptr;
        }

        delete temp;
    }
};

int main() // O(N)
{
    Deque dq;

    dq.pushFront(10);
    dq.pushRear(9);
    dq.pushFront(15);
    dq.pushRear(30);

    cout << "Deque after pushing elements :" << endl;
    dq.display();

    cout << "Front element: " << dq.getFront() << endl;
    cout << "Rear element: " << dq.getRear() << endl;

    dq.popFront();
    cout << "Deque after popping front:\n";
    dq.display();

    dq.popRear();
    cout << "Deque after popping rear:\n";
    dq.display();

    return 0;
}

// So the time Complexity of main is O(N)