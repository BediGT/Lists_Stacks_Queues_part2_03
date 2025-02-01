#include <iostream>
#include <string>
#include "MyStack.h"

bool zad2(Stack<char> stack);

void zad3a(Stack<int> *stack);

void zad3b(Stack<int>& stack);

void zad4(int number);

int zad5(const std::string& expression);

int main()
{
    std::string expression = "-1*(2 + 1 * 6)";
    Stack<char> stackChar;
    stackChar.makeStack(expression); // tylko liczby, operatory (podstawowe 4) i nawiasy, bez liter itp.

    std::cout << "Zad2: Poprawnosc uzycia nawiasow w " << expression << ": " << zad2(stackChar) << "\n";

    Stack<int> stackInt;
    stackInt.push(1);
    stackInt.push(2);
    stackInt.push(3);
    stackInt.push(4);
    stackInt.push(5);
    std::cout << "\n\n";

    std::cout << "Zad3a:\n";
    std::cout << "Przed sortowaniem:\n";
    stackInt.printStack();
    std::cout << "\n\n";
    zad3a(&stackInt);
    std::cout << "Po sortowaniu:\n";
    stackInt.printStack();
    std::cout << "\n\n";

    std::cout << "Zad3b:\n";
    std::cout << "Przed sortowaniem:\n";
    stackInt.printStack();
    std::cout << "\n\n";
    zad3b(stackInt);
    std::cout << "Po sortowaniu:\n";
    stackInt.printStack();
    std::cout << "\n\n";
    
    std::cout << "Zad4: ";
    zad4(13);
    std::cout << "\n\n";

    std::cout << "Zad5: " << expression << " = " << zad5(expression) << "\n";
    std::cout << "\n\n";
}

bool zad2(Stack<char> stack) // funkcja zaczyna sprawdzanie wyrazenia od tylu
{
    char temporary = '+';
    char previous = '+';
    int bracketCounter = 0;
    while (!stack.isEmpty())
    {
        temporary = stack.pop(); // 2+)9(  2(+9)
        bool previousCondition = (previous == '+' || previous == '-' || previous == '*' || previous == '/' || previous == ')'); // pomocniczo jako osobne zmienne zeby bylo czytelniej
        bool temporaryCondition = (temporary == '+' || temporary == '-' || temporary == '*' || temporary == '/' || temporary == '(');

        if (temporary == ')' && !previousCondition)
            return false;

        else if (temporary == '(' && previousCondition)
            return false;

        else if (previous == ')' && temporaryCondition)
            return false;

        else if (previous == '(' && !temporaryCondition)
            return false;


        if (temporary == '(' || temporary == ')')
            bracketCounter++;

        previous = temporary;
    }

    if (bracketCounter % 2 != 0)
        return false;

    return true;
}

void zad3a(Stack<int>* stack)
{
    Stack<int>* temp = new Stack<int>;
    while (!stack->isEmpty())
    {
        temp->push(stack->pop());
    }
    *stack = *temp;
}

void insertAtBottom(Stack<int>& stack, int element)
{
    if (stack.isEmpty())
    {
        stack.push(element);
    }
    else
    {
        int temp = stack.pop();
        insertAtBottom(stack, element);
        stack.push(temp);
    }
}

void zad3b(Stack<int>& stack)
{
    if (!stack.isEmpty())
    {
        int temp = stack.pop();
        zad3b(stack);
        insertAtBottom(stack, temp);
    }
}

void zad4(int number)
{
    std::string toReturn = "";
    Stack<int> stack;
    while (number != 0)
    {
        stack.push(number % 2);
        number /= 2;
    }
    while (!stack.isEmpty())
        std::cout << stack.pop();
    std::cout << "\n";
}

int hierarchy(char op)
{
    if (op == '+' || op == '-')
    {
        return 1;
    }
    else if (op == '*' || op == '/')
    {
        return 2;
    }
    return 0;
}

int calculate(int a, int b, char op)
{
    switch (op)
    {
    case '+': return a + b;
    case '-': return a - b;
    case '*': return a * b;
    case '/': return a / b;
    }
    return 0;
}

int zad5(const std::string& expression)
{
    Stack<int> values;
    values.push(0); // bez tego sam minus w np. -(a+b) nie dziala, do obliczania wartosci msuza byc 2 wartosci
    Stack<char> operands;

    for (int i = 0; i < expression.length(); i++)
    {
        if (expression[i] == ' ')
        {
            continue;
        }

        if (isdigit(expression[i]))
        {
            int value = 0;
            while (i < expression.length() && isdigit(expression[i]))
            {
                value = (value * 10) + (expression[i] - '0');
                i++;
            }
            values.push(value);
            i--;
        }
        else if (expression[i] == '(')
        {
            operands.push(expression[i]);
        }
        else if (expression[i] == ')')
        {
            while (!operands.isEmpty() && operands.peek() != '(')
            {
                int val2 = values.pop();
                int val1 = values.pop();
                char op = operands.pop();
                values.push(calculate(val1, val2, op));
            }
            operands.pop();
        }
        else
        {
            while (!operands.isEmpty() && hierarchy(operands.peek()) >= hierarchy(expression[i]))
            {
                int val2 = values.pop();
                int val1 = values.pop();
                char op = operands.pop();
                values.push(calculate(val1, val2, op));
            }
            operands.push(expression[i]);
        }
    }

    while (!operands.isEmpty())
    {
        int val2 = values.pop();
        int val1 = values.pop();
        char op = operands.pop();
        values.push(calculate(val1, val2, op));
    }

    return values.pop();
}

