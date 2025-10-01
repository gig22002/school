#include <string>
#include <iostream>

//function that modifies a string `x` so that after the function call, `x` contains only its prefix of **up to five characters**.
void TrimString(std::string &x)
{
  std::string res;
  for(unsigned int i=0; i<5 && i<x.size(); ++i)
  {
    res += x[i];
  }
  x = res;
}

int main(){
	std::string a = "helloworld";
	TrimString(a);
	std::cout << a << std::endl;
	return 0;
}
