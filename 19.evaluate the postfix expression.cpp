#include <iostream>
#include <stack>
#include <cmath>
#include <stdexcept>
using namespace std;

bool IsOperator(char c)
{
    return c == '+' || c == '-' || c == '*' || c == '/' || c == '^';
}

double Calc(double num1, double num2, char op)
{
    switch (op)
    {
    case '+':
        return num1 + num2;
    case '-':
        return num1 - num2;
    case '*':
        return num1 * num2;
    case '/':
        if (num2 == 0)
        {
            throw invalid_argument("Division by zero!");
        }
        return num1 / num2;
    case '^':
        return pow(num1, num2);
    default:
        throw invalid_argument("Invalid operator!");
    }
}

double Evaluate_Postfix(string postfix)
{
    stack<double> s;
    int i = 0, len = postfix.size();

    while (i < len)
    {
        if (isdigit(postfix[i]))
        {
            double num = 0;
            while (i < len && isdigit(postfix[i]))
            {
                num = num * 10 + (postfix[i] - '0');
                i++;
            }

            s.push(num);
        }
        else if (IsOperator(postfix[i]))
        {
            if (s.size() < 2)
            {
                throw invalid_argument("Insufficient operands for the operator.");
            }

            double Second_Num = s.top();
            s.pop();
            double First_Num = s.top();
            s.pop();

            double result = Calc(First_Num, Second_Num, postfix[i]);
            s.push(result);
            i++;
        }
        else if (postfix[i] == ' ')
        {
            i++;
        }
        else
        {
            throw invalid_argument("Invalid character in the postfix expression.");
        }
    }

    if (s.size() != 1)
    {
        throw invalid_argument("Invalid postfix expression.");
    }

    return s.top();
}

int main()
{
    string postfix_single = "6 2 3 + - 3 8 2 / + *";
    string postfix_multi = "56 34 + 23 12 - * 2 /";

    cout << "Postfix expression (single-digit): " << postfix_single << endl;
    try
    {
        cout << "Value: " << Evaluate_Postfix(postfix_single) << endl;
    }
    catch (const exception &e)
    {
        cout << "Error: " << e.what() << endl;
    }

    cout << "Postfix expression (multi-digit): " << postfix_multi << endl;
    try
    {
        cout << "Value: " << Evaluate_Postfix(postfix_multi) << endl;
    }
    catch (const exception &e)
    {
        cout << "Error: " << e.what() << endl;
    }

    return 0;
}