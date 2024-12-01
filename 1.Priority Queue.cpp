#include <iostream>
using namespace std;

struct Node
{
    int data;
    int priority;
    Node *next;
};

class Priority_Queue
{
    Node *head;

public:
    Priority_Queue() : head(nullptr) {} // O(1)

    ~Priority_Queue() // O(N)
    {
        while (head)
        {
            Node *temp = head;
            head = head->next;
            delete temp;
        }
    }

    bool empty() // O(1)
    {
        return head == nullptr;
    }

    void enqueue(int value, int priority) // O(N)
    {
        Node *newNode = new Node{value, priority, nullptr};

        if (empty() || head->priority < priority)
        {
            newNode->next = head;
            head = newNode;
            return;
        }

        Node *temp = head;

        while (temp->next && temp->next->priority >= priority)
        {
            temp = temp->next;
        }

        newNode->next = temp->next;
        temp->next = newNode;
    }

    void dequeue() // O(1)
    {
        if (empty())
        {
            cout << "Queue is empty!" << endl;
            return;
        }

        Node *temp = head;
        head = temp->next;
        delete temp;
    }

    int top() // O(1)
    {
        if (empty())
        {
            cout << "Queue is empty!" << endl;
            return -1;
        }
        return head->data;
    }

    void display() // O(N)
    {
        if (empty())
        {
            cout << "Queue is empty!" << endl;
            return;
        }

        Node *temp = head;

        while (temp)
        {
            cout << "(" << temp->data << "," << temp->priority << ")";
            temp = temp->next;
        }
        cout << endl;
    }
};

int main() // O(N)
{
    Priority_Queue pq;

    pq.enqueue(5, 4);
    pq.enqueue(7, 5);
    pq.enqueue(8, 1);
    pq.enqueue(9, 4);

    cout << "The Top element : " << pq.top() << endl;
    cout << "Queue: " << endl;
    pq.display();

    cout << "Is the queue empty? " << (pq.empty() ? "Yes" : "No") << endl;

    cout << "Dequeuing the top element..." << endl;
    pq.dequeue();
    cout << "Queue after dequeuing: " << endl;
    pq.display();

    return 0;
}

// So the time Complexity of main is O(N)