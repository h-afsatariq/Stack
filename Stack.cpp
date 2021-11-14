#include <iostream>
#include <string>
#include <stack>
using namespace std;
//stack class
class Stack
{				//array for the braces
public:
    char stack_arr[50];
    int top = -1;			//in the start the stack is empty
  //push function:
    void Push(char element)
    {
        if (top == 49)		//in case when the stack is full
            std::cout << "The stack is full." << std::endl;
        else			// in case when there is capacity in the stack
        {
            stack_arr[++top] = element;
        }
    }
    //pop function
    char pop()
    {
        if (top == -1)		//case whem the stack is empty.
        {
            std::cout << "the stack is empty." << std::endl;

        }
        else			//in case when there are element present in the stack
        {
            char peak_element;
            peak_element = stack_arr[--top];
            return peak_element;
        }
    }
    //isEmpty function:
    bool isEmpty()
    {
        if (top == -1)
            return true;
        else
            return false;
    }
    //isFull function:
    bool isFull()
    {
        if (top == 49)
            return true;
        else
            return false;
    }
    // Clear function:
    void Clear()
    {
        while (top >= 0)
        {
            stack_arr[top--] = NULL;
        }
    }
    //Peak function
    char Peak()
    {
        if (!isEmpty())
            return stack_arr[top];
        else
            return NULL;

    }
    int size()
    {
        return (top + 1);
    }

};