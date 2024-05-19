        else if (c == '&' && i + 1 < expression.size() && expression[i + 1] == '&')
        {
            bool operand2 = s.top();
            s.pop();
            bool operand1 = s.top();
            s.pop();
            s.push(operand1 && operand2);
            i++; // Skip the next character
        }