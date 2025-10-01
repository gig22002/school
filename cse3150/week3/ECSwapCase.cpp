// Starter code
#include <string>
#include <iostream>

std::string ECSwapCase(std::string str)
{
  // your code here...
  for(auto &a:str){
	if (a >= 'a' && a <= 'z') { a+= 'A'-'a'; }
	else if (a >= 'A' && a <= 'Z') { a+= 'a'-'A'; }
  }
  return str;
}

int main(){
	std::cout << ECSwapCase("Hello") << std::endl;

	return 0;
}
