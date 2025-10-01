// Starter code
#include <iostream>

using namespace std;

string ECStringSep(const string &str)
{
  string res;
  // your code goes here
  int i=0;
  while (str[i]!='\0'){
	res=res+str[i++]+',';
  }
  res.pop_back();
  //for(auto i: str)
  
  return res;
}

int main(){
	string s = "xyz";
	string s2 = ECStringSep(s);
	cout << s2 << endl;

	return 0;
}
