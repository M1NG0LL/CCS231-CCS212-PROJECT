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
    Node *front;
    Node *rear;

public:
    Deque() : front(nullptr), rear(nullptr) {};

    ~Deque()
    {
        while (front)
        {
            Node *temp = front;
            front = front->next;
            delete temp;
        }
    }

    bool empty()
    {
        return front == nullptr || rear == nullptr;
    }

    int getFront()
    {
        if (empty())
        {
            cout << "Deque is empty!" << endl;
            return -1;
        }

        return front->data;
    }

    int getRear()
    {
        if (empty())
        {
            cout << "Deque is empty!" << endl;
            return -1;
        }

        return rear->data;
    }

    void display()
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

    void pushFront(int data)
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

    void popFront()
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

    void pushRear(int data)
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

    void popRear()
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

    void display()
    {
        if (empty())
        {
            cout << "Deque is empty!" << endl;
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
};

int main()
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