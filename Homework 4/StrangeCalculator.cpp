//  StrangeCalculator.cpp
//  CS201 Homework 4: StrangeCalculator
//  May 2021
//  Can Avşar
//  21902111

#include <stdio.h>
#include "StrangeCalculator.h"
#include "Stack.h"
#include <iostream>
using namespace std;


StrangeCalculator::StrangeCalculator()
{
    
}

string infix2prefix(const string exp)
{
    string reversedExp = reverseExp(exp);
    string postFixExp = "";
    int stackTop;
    int item;
    
    Stack aStack;
    
    for (int i = 0; i < reversedExp.length(); i++)
    {
        char ch = reversedExp[i];
        
        switch (ch)
        {
            case '0':
            case '1':
            case '2':
            case '3':
            case '4':
            case '5':
            case '6':
            case '7':
            case '8':
            case '9':
                postFixExp += ch;
                break;
                
            case '(':
                aStack.push(ch);
                break;
                
            case ')':
                aStack.getTop(stackTop);
                while (stackTop != '(')
                {
                    postFixExp += stackTop;
                    aStack.pop();
                    aStack.getTop(stackTop);
                }
                aStack.pop();
                break;
                
            case '+':
            case '-':
            case '*':
            case '/':
                aStack.getTop(stackTop);
                while ((!aStack.isEmpty()) && (stackTop != '(') && (precedence(ch) <= precedence(stackTop)))
                {
                    postFixExp += stackTop;
                    aStack.pop();
                    aStack.getTop(stackTop);
                    
                }
                aStack.push(ch);
                break;
        }
    }
    
    while ((!aStack.isEmpty()))
    {
        aStack.pop(item);
        postFixExp += item;
    }
    
    return reverseExp(postFixExp);
    //return reversedExp;
}

double evaluatePrefix(const string exp)
{
    char ch;
    Stack aStack;
    int operand1, operand2;
    double result;
    result = 0;
    int numOperand1;
    int numOperand2;

    
    for (int i = exp.length()-1; i >= 0; i--)
    {
        ch = exp[i];
        if ((ch >= '0') && (ch <= '9'))
        {
            aStack.push(ch);
        }
        else
        { // ch is an operator named op
            // evaluate and push the result
            aStack.getTop(operand2);
            aStack.pop();
            aStack.getTop(operand1);
            aStack.pop();
            
            numOperand1 = int(operand1) - 48;
            numOperand2 = int(operand2) - 48;

            switch(ch)
            {
                case '+':
                    result = numOperand2 + numOperand1;
                    break;
                case '-':
                    result = numOperand2 - numOperand1;
                    break;
                case '*':
                    result = numOperand2 * numOperand1;
                    break;
                case '/':
                    result = numOperand2 / numOperand1;
                    break;
            }
            
            aStack.push(result+48);
        }
    }
    
    return result;
}

bool isBalancedInfix(const string exp)
{
    
    Stack aStack;
    bool balancedSoFar = true;
    int i = 0;
    
    while ((balancedSoFar) && (i < exp.length()))
    {
        char ch = exp[i];
        ++i;
        
        if (ch == '(')
        {
            aStack.push('(');
        }
        else if (ch == ')')
        {
            if (!aStack.isEmpty())
            {
                aStack.pop();
            }
            else
            {
                balancedSoFar = false;
            }
        }
    }
    
    if (balancedSoFar && aStack.isEmpty())
    {
        return true;
    }
    else
    {
        return false;
    }
}

void evaluateInputPrefixExpression()
{
    char infixInput[100];
    
    cout << "Enter an infix input." << endl;
    
    cin.getline(infixInput, sizeof(infixInput));
    
    string withoutSpaces = removeSpace(infixInput);
    
    cout << withoutSpaces << endl;
    
    if(!isBalancedInfix(withoutSpaces))
    {
        cout << "Input is not balanced" << endl;
        return;
    }
                
    cout << "result of: "<< infixInput <<" is: " << evaluatePrefix(infix2prefix(withoutSpaces)) << endl;
    
}

string reverseExp(const string exp)
{
    Stack reverseStack;
    string reversed = "";
    int ch;
    
    for(int i = 0; i < exp.length(); i++)
    {
        if(exp[i] == '(')
        {
            reverseStack.push(')');
        }
        else if (exp[i] == ')')
        {
            reverseStack.push('(');
        }
        else
        {
            reverseStack.push(exp[i]);
            
        }
    }
    for(int i = 0; i < exp.length(); i++)
    {
        reverseStack.pop(ch);
        reversed = reversed + (char)ch;
    }
    return reversed;
}

int precedence(char op)
{
    if((op == '+') || (op == '-'))
    {
        return 1;
    }
    else if ((op == '*') || (op == '/'))
    {
        return 2;
    }
    else
    {
        return 0;
    }
}

string removeSpace(const string exp)
{
    Stack spaceStack;
    string withoutSpace = "";
    int ch;
    int charCount = 0;
    
    for(int i = exp.length()-1; i >= 0; i--)
    {
        if(exp[i] == ' ')
        {
        }
        else
        {
            spaceStack.push(exp[i]);
            charCount++;
        }

    }
    for(int i = 0; i < charCount; i++)
    {
        spaceStack.pop(ch);
        withoutSpace = withoutSpace + (char)ch;
    }
    return withoutSpace;
}
