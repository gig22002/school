#include <set>
#include <vector>
#include <iostream>
using namespace std;

int ECSumList(const set<int> &listNums)
{
  // your code goes here ...
  int count=0;
  for (auto i : listNums){
	count += i;
  }
  return count;
}

// Test your code with this main function

int main()
{
  set<int> ss;
  ss.insert(5);
  ss.insert(3);
  ss.insert(3);
  ss.insert(0);
  ss.insert(1);
  int sum = ECSumList(ss);
  cout << "sum: " << sum << endl;
}
