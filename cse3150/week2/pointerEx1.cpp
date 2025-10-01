#include <iostream>
using namespace std;

int main(){
	int* px = new int;
	*px = 20;
	cout << "*px= " << *px << endl; //* operator dereferences, getting the val of the pointer
	cout << "px = " << px << endl; //addr of the pointer
	delete px;

	return 0;
}
