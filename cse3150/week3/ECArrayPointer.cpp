//
#include <iostream>
using namespace std;

int main()
{
  // allocate an array of char in heap 
  char *px = new char[10];
  // set this array to 'a', 'b' and so on
  // your code here...
  //px[0] = 'a';
  //for(int i=1; i<10; i++){
	//px[i] = px[i-1]+1;
  //}
  *px = 'a';
  for(int i=1; i<10; i++){
	*(px+i) = *(px+i-1)+1;
  }

  // print out
  for(int i=0; i<10; ++i)
  {
    cout << *(px+i);
  }
  cout << endl;

  delete [] px;

  return 0;
}
 
