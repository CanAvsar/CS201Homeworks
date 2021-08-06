//  Stack.cpp
//  CS201 Homework 4: StrangeCalculator
//  May 2021
//  Can Avşar
//  21902111

#include <stdio.h>
#include "Stack.h"


Stack::Stack():topPtr(NULL)
{
    
}

Stack::Stack(const Stack& aStack)
{
    
    if (aStack.topPtr == NULL)
    {
        topPtr = NULL;  // original stack is empty
    }
    
    else
    {
        // copy first node
        topPtr = new StackNode;
        topPtr->item = aStack.topPtr->item;
        
        // copy rest of stack
        StackNode *newPtr = topPtr;
        for (StackNode *origPtr = aStack.topPtr->next; origPtr != NULL; origPtr = origPtr->next)
        {
            newPtr->next = new StackNode;
            newPtr = newPtr->next;
            newPtr->item = origPtr->item;
        }
        
        newPtr->next = NULL;
    }
}

Stack::~Stack()
{
    // pop until stack is empty
    while (!isEmpty())
    {
        pop();
    }
}

bool Stack::isEmpty() const
{
    return topPtr == NULL;
    
}

bool Stack::push(StackItemType newItem)
{
    // create a new node
    StackNode *newPtr = new StackNode;
    
    // set data portion  of new node
    newPtr->item = newItem;
    
    // insert the new node
    newPtr->next = topPtr;
    topPtr = newPtr;
    
    return true;
    
}

bool Stack::pop()
{
    if (isEmpty())
    {
        return false;
    }
    
    else
    {
        StackNode *temp = topPtr;
        topPtr = topPtr->next;
        
        temp->next = NULL;
        delete temp;
        return true;
    }
    
}
bool Stack::pop(StackItemType& stackTop)
{
    if (isEmpty())
    {
        return false;
    }
    else
    {
        stackTop = topPtr->item;
        StackNode *temp = topPtr;
        topPtr = topPtr->next;
        
        temp->next = NULL;
        delete temp;
        return true;
    }
}

bool Stack::getTop(StackItemType& stackTop) const
{
    if (isEmpty())
    {
        return false;
    }
    else
    {
        stackTop = topPtr->item;
        return true;
    }
}
