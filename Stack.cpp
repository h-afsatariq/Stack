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


// function for conversion of infin to postfix
string infixTOpostfix(string infix)
{
	string postfix, top, character;//defining variables

	int stack_size;

	Stack mystack;//making object of the stack.
	int lenght = infix.length();//taking the lenght of the input infix expression.
	for (int pos = 0; pos < lenght; pos++)//using for loop to triverse over the whole infix expression.
	{
		character = infix[pos];//taking each element of the infix one by one.
		if (isdigit(infix[pos]))//checking whether the current infix element is digit or not.
		{
			postfix = postfix + infix[pos];
		}
		else if ((character == "+") || (character == "-") || (character == "*")
			|| (character == "/") || (character == "^")
			|| (character == "(") || (character == ")"))//checking whether the current infix element is operator or not.
		{

			if (mystack.isEmpty())//checking if the stack is empty.
			{
				postfix = postfix + " ";
				mystack.Push(infix[pos]);//if the stack is empty then just push the element in the stack.
				top = mystack.Peak();//taking the value of top element of the stack in top variable.
			}



			else if (!mystack.isEmpty())//here if the stack is not empty condition is checked.

			{
				postfix = postfix + " ";//for creating space between the numbers and the operator.
				top = mystack.Peak();
				if (top == "(")//if the top variable have ( then just push the next element in the stack
				{
					mystack.Push(infix[pos]);
					top = mystack.Peak();//updating top variable.
				}


				else if (((character == "+") || (character == "-"))
					&& ((top == "+") || (top == "-") || (top == "*")
						|| (top == "/") || (top == "^")))//checking if the already present top is of equal or high priority as that of + and-.
				{
					postfix = postfix + top;
					mystack.pop();
					mystack.Push(infix[pos]);

				}

				else if (((character == "/") || (character == "*"))
					&& ((top == "*") || (top == "/") || (top == "^")))//checking if the already present top is of equal or high priority as that of * and/.
				{
					postfix = postfix + top;
					mystack.pop();
					mystack.Push(infix[pos]);
				}
				else if ((character == "^") && ((top == "^")))//checking if top has the equal priority element as that of ^.
				{
					postfix = postfix + top;
					mystack.pop();
					mystack.Push(infix[pos]);
				}
				else
					if (((character == "/") || (character == "*")
						|| (character == "^")) && ((top == "+") || (top == "-")))//in this case high priorty comes over the low priorty.
					{
						mystack.Push(infix[pos]);
					}
					else if ((character == "^")
						&& ((top == "+") || (top == "-") || (top == "*")
							|| (top == "/")))//in this case high priorty comes over the low priorty.
					{
						mystack.Push(infix[pos]);
					}

					else if ((character == "("))
					{
						mystack.Push(infix[pos]);
					}
					else if ((character == ")"))//if the closing bracket comes then we will pop all the operators present in the stack until we get a opening bracket.
					{

						while (top != "(")
						{
							postfix = postfix + top;
							mystack.pop();
							top = mystack.Peak();
						}
						mystack.pop();//removing the opening bracket from the stack.

					}

			}
		}

	}
	if (!mystack.isEmpty())// when the infix expression finishes but the stack is not empty so we pop all the operators.
	{
		stack_size = mystack.size();
		for (int loop = 0; loop < stack_size; ++loop)
		{
			postfix = postfix + " " + mystack.Peak();
			mystack.pop();
		}
	}
	return postfix;//final postfix expression is returned.
}

//evaluation of postfix
int  Eval_Postfix(string postfix)
{

	string element, num1;//defining variables.
	int num2, num3, length;
	int ans;
	stack < double >eval_stack;//making a stack object that holds the double values.
	length = postfix.length();
	for (int loop = 0; loop < length; loop++)//for loop for triversing over whole postfix expression.
	{
		element = postfix[loop];
		if (isdigit(postfix[loop]))//checking whether the current element of postfix is digit or not.
		{
			num1 = num1 + element;//num1 will have a compelet number
		}
		else if ((element == " ") && (isdigit(postfix[loop - 1])))//if the space comes in the postfix and its previous element was digit then a num compelets.
		{
			num2 = stoi(num1);//converting string into integer.
			eval_stack.push(num2);
			num1 = "";//doing this so that next number can be saved in it.
		}
		else if (element == "+")//if the operator is sum then pop the two recent elements from the stack and perform addition and push the answer back in the stack.
		{
			num3 = eval_stack.top();
			eval_stack.pop();
			num2 = eval_stack.top();
			eval_stack.pop();
			ans = num2 + num3;
			eval_stack.push(ans);
		}
		else if (element == "-")//if the operator is subtraction then pop the two recent elements from the stack and perform subtraction and push the answer back in the stack.
		{
			num3 = eval_stack.top();
			eval_stack.pop();
			num2 = eval_stack.top();
			eval_stack.pop();
			ans = num2 - num3;
			eval_stack.push(ans);
		}
		else if (element == "*")//if the operator is multiplication then pop the two recent elements from the stack and perform multiplication and push the answer back in the stack.
		{
			num3 = eval_stack.top();
			eval_stack.pop();
			num2 = eval_stack.top();
			eval_stack.pop();
			ans = num2 * num3;
			eval_stack.push(ans);
		}
		else if (element == "/")//if the operator is division then pop the two recent elements from the stack and perform divide and push the answer back in the stack.
		{
			num3 = eval_stack.top();
			eval_stack.pop();
			num2 = eval_stack.top();
			eval_stack.pop();
			ans = num2 / num3;
			eval_stack.push(ans);
		}
		else if (element == "^")//if the power is sum then pop the two recent elements from the stack and perform power operation and push the answer back in the stack.
		{
			num3 = eval_stack.top();
			eval_stack.pop();
			num2 = eval_stack.top();
			eval_stack.pop();
			ans = num2 ^ num3;
			eval_stack.push(ans);
		}


	}

	if (eval_stack.size() == 1) {
		return eval_stack.top();
	}
	else {
		std::cout << "The entered expression is wrong." << std::endl;


	}


}


int
main()
{
	string resultant_pf, infix;
	cout << "Enter your infix expression here:";
	getline(cin, infix);
	resultant_pf = infixTOpostfix(infix);
	cout << "The postfix expression is : ";
	std::cout << resultant_pf << std::endl;
	cout << "The evaluation of postfix gives the answer as : ";
	std::cout << Eval_Postfix(resultant_pf) << std::endl;

	return 0;
}

