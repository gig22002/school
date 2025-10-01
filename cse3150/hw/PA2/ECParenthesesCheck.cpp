// Check if the string contains valid parentheses
// The string may include '(', ')', '[', ']' and other characters
// These parentheses must be properly matched e.g. (), [()], [([])]

#include <string>
#include <iostream>
#include <stack>
using namespace std;

bool ECParenthesesCheck(const std::string& strInput)
{
    // Implement the ECParenthesesCheck function here...
 	int i=0;
	stack<char> pStack;
 	while (strInput[i] != '\0'){
		if(strInput[i] == '(' || strInput[i] == '[') { pStack.push(strInput[i]); }
		
		else if(strInput[i] == ')'){
			if(pStack.empty()) { return false; }
			if(pStack.top() != '(') { return false; }
			pStack.pop();
		} else if(strInput[i] == ']'){
			if(pStack.empty()) { return false; }
			if(pStack.top() != '[') { return false; }
			pStack.pop();
		}
		//cout << "strInput[i]: " << strInput[i] << endl;
		//cout << "pStack.top(): " << pStack.top() << endl;

		i++;
	}
	return pStack.empty();

}
