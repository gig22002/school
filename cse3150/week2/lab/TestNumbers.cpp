#include <iostream>
#include "ECNumbers.h"
#include "ECCalculator.h"
using namespace std;
using namespace ECNumbers;
using namespace ECCalculator;

int main()
{
  // read in an integer n
  // your code here
  int n;
  cin >> n;

  // print out the square of it
  // your code here
  cout << ECSquareN(n) << endl;

  // print out 2n  
  // your code here
  cout << ECDoubleN(n) << endl;

  // print out 4 times of n by invoking ECCalculator's function
  // your code here
  cout << ECFourTimesN(n) << endl;

  return 0;
}
