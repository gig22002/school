#include <iostream>
using namespace std;

int main(){

	int x = 0;
	int* ptr1 = &x;
	int *ptr2 = &x;
	cout << "*ptr1 & *ptr2: " << *ptr1 << " " << *ptr2 << endl;
	cout << "ptr1 & ptr2: " << ptr1 << " " << ptr2 << endl;
}
