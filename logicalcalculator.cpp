#include <iostream>
#include <string>
#include <unordered_map>
#include <stack>

using namespace std;

bool getPropositionValue(const string& proposition)
{
    char response;
    cout << "Is " << proposition << " true? (y/n): ";
    cin >> response;
    cin.ignore(); // Clear any remaining characters in the buffer
    return (response == 'y' || response == 'Y');
}

bool applyLogicalOperation(bool prop1, bool prop2, char operation)
{
    switch (operation)
    {
    case 'A':
        return prop1 && prop2;
    case 'O':
        return prop1 || prop2;
    case 'N':
        return !prop1;
    case 'I':
        return (!prop1) || prop2;
    case 'B':
        return prop1 == prop2;
    default:
        cout << "Invalid operation code. Please choose A, O, N, I, or B." << endl;
        return false;
    }
}

bool evaluateExpression(const string& expression, const unordered_map<char, bool>& propValues)
{
    stack<bool> s;

    for (size_t i = 0; i < expression.size(); i++)
    {
        char c = expression[i];
        if (isalpha(c) && propValues.find(c) != propValues.end())
        {
            s.push(propValues.at(c));
        }
        else if (c == '!')
        {
            bool operand = s.top();
            s.pop();
            s.push(!operand);
        }
        else if (c == '&' && i + 1 < expression.size() && expression[i + 1] == '&')
        {
            bool operand2 = s.top();
            s.pop();
            bool operand1 = s.top();
            s.pop();
            s.push(operand1 && operand2);
            i++; // Skip the next character
        }
        else if (c == '|' && i + 1 < expression.size() && expression[i + 1] == '|')
        {
            bool operand2 = s.top();
            s.pop();
            bool operand1 = s.top();
            s.pop();
            s.push(operand1 || operand2);
            i++; // Skip the next character
        }
        else if (c == '>' && i + 1 < expression.size() && expression[i + 1] == '=')
        {
            bool operand2 = s.top();
            s.pop();
            bool operand1 = s.top();
            s.pop();
            s.push((!operand1) || operand2);
            i++; // Skip the next character
        }
        else if (c == '=' && i + 1 < expression.size() && expression[i + 1] == '=')
        {
            bool operand2 = s.top();
            s.pop();
            bool operand1 = s.top();
            s.pop();
            s.push(operand1 == operand2);
            i++; // Skip the next character
        }
    }

    return s.top();
}

int main()
{
    cout << "Choose an option:" << endl;
    cout << "1. Calculate propositions using logical operators\n";
    cout << "2. Input a logical expression and evaluate\n";
    cout << "Enter your choice (1 or 2): ";

    int choice;
    cin >> choice;

    if (choice == 1)
    {
        // Existing proposition calculation code
        string proposition1, proposition2;
        char operationCode;

        // Get user input for propositions
        cout << "Enter the first proposition: ";
        cin >> proposition1;
        cout << "Enter the second proposition: ";
        cin >> proposition2;

        // Get user input for logical operation
        cout << "Choose a logical operation:" << endl;
        cout << "A - AND\n";
        cout << "O - OR\n";
        cout << "N - NOT\n";
        cout << "I - IMPLIES\n";
        cout << "B - BICONDITIONAL\n";
        cout << "Enter the operation code (A, O, N, I, or B): ";
        cin >> operationCode;

        // Get values for the propositions
        bool value1 = getPropositionValue(proposition1);
        bool value2 = getPropositionValue(proposition2);

        // Apply the logical operation
        bool result = applyLogicalOperation(value1, value2, operationCode);

        // Output the result
        cout << "The result is: " << (result ? "TRUE" : "FALSE") << endl;
    }
    else if (choice == 2)
    {
        // New logical expression evaluation code
        string expression;
        unordered_map<char, bool> propValues;

        // Get user input for logical expression
        cout << "Enter the logical expression: ";
        cin.ignore(); // Ignore the newline character left in the buffer
        getline(cin, expression);

        // Get user input for proposition values
        for (char c : expression)
        {
            if (isalpha(c) && propValues.find(c) == propValues.end())
            {
                bool value = getPropositionValue(string(1, c));
                propValues[c] = value;
            }
        }

        // Evaluate the expression
        bool result = evaluateExpression(expression, propValues);

        // Output the result
        cout << "The result is: " << (result ? "TRUE" : "FALSE") << endl;
    }
    else
    {
        cout << "Invalid choice. Please choose 1 or 2." << endl;
    }

    return 0;
}
