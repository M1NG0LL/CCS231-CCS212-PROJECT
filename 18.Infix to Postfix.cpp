#include <iostream>
#include <stack>
using namespace std;

bool IsOperator(char c)
{
    return c == '+' || c == '-' || c == '*' || c == '/' || c == '^';
}

int Operator_Priority(char op)
{
    if (op == '+' || op == '-')
        return 1;
    if (op == '*' || op == '/')
        return 2;
    if (op == '^')
        return 3;
    return 0;
}

string Infix_To_Postfix(string infix)
{
    string postfix;
    stack<char> s;

    for (char c : infix)
    {
        if (isalnum(c))
        {
            postfix += c;
        }
        else if (c == '(')
        {
            s.push(c);
        }
        else if (c == ')')
        {
            while (!s.empty() && s.top() != '(')
            {
                if (s.top() != '(' || s.top() != ')')
                    postfix += s.top();
                s.pop();
            }
            if (!s.empty() && s.top() == '(')
            {
                s.pop();
            }
        }
        else if (IsOperator(c))
        {
            while (!s.empty() && Operator_Priority(s.top()) >= Operator_Priority(c))
            {
                postfix += s.top();
                s.pop();
            }
            s.push(c);
        }
    }

    while (!s.empty())
    {
        postfix += s.top();
        s.pop();
    }

    return postfix;
}

int main()
{
    string infix = "a+b*(c^d-e)^(f+g*h)-i";

    cout << "infix expression: " << infix << endl;
    cout << "Postfix expression: " << Infix_To_Postfix(infix) << endl;

    return 0;
}