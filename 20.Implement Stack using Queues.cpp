#include <iostream>
#include <queue>
using namespace std;

class stackfromQ
{
private:
    queue<int> q1, q2;

public:
    // Push an element onto the stack
    void push(int x)
    {
        q2.push(x);

        while (!q1.empty())
        {
            q2.push(q1.front());
            q1.pop();
        }
        swap(q1, q2);
    }

    // Remove the top element
    void pop()
    {
        if (q1.empty())
        {
            cout << "Stack is underflow\n";
            return;
        }
        q1.pop();
    }

    // Get the top element
    int top()
    {
        if (q1.empty())
        {
            cout << "Stack is empty\n";
            return -1;
        }
        return q1.front();
    }

    // Check if the stack is empty
    bool empty()
    {
        return q1.empty();
    }

    // Display the elements of the stack
    void display()
    {
        if (q1.empty())
        {
            cout << "Stack is empty\n";
            return;
        }
        queue<int> temp = q1;
        cout << "Stack elements: ";
        while (!temp.empty())
        {
            cout << temp.front() << " ";
            temp.pop();
        }
        cout << "\n";
    }
};

int main()
{
    stackfromQ sfq;
    int choice, value;
    bool running = true;

    sfq.push(21);
    sfq.push(51);
    sfq.push(69);
    sfq.push(7);
    sfq.push(1);
    sfq.push(12);

    while (running)
    {
        cout << "\nMenu:\n";
        cout << "1. Push\n";
        cout << "2. Pop\n";
        cout << "3. Display\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            cout << "Enter the value you want to push: ";
            cin >> value;
            sfq.push(value);
            cout << "Value pushed successfully.\n";
            break;

        case 2:
            cout << "Popping the top element...\n";
            sfq.pop();
            break;

        case 3:
            cout << "Elements in the stack:\n";
            sfq.display();
            break;

        case 4:
            cout << "Exiting...\n";
            running = false;
            break;

        default:
            cout << "Invalid input. Please try again.\n";
        }
    }

    return 0;
}