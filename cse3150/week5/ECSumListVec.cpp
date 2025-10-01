#include <vector>
#include <iostream>
using namespace std;

// return the sum of the numbers
int ECSumList(const vector<int> &listNums)
{
  // your code goes here ...
  int count=0;
  //for(int i=0; i<listNums.size(); i++){
//	count += listNum[i];
  //}
  for(auto i : listNums){
	  count += i;
  }
 
  return count;
  
}

// Test your code with this main function

int main()
{
  vector<int> vec;
  vec.push_back(2);
  vec.push_back(3);
  vec.push_back(3);
  vec.push_back(0);
  vec.push_back(1);
  int sum = ECSumList(vec);
  cout << "sum: " << sum << endl;
}
