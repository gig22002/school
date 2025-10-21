#include <iostream>
using namespace std;

// base class
class ECLife
{
public:
  void Die() {}
  virtual int Type() { return 0; }
};

// derived class
class ECCat : public ECLife
{
public:
  void Mew() { }
  int Type() { return 1; }
};

// derived class 2
class ECDog : public ECLife
{
public:
  void Bark() { }
  int Type() { return 2; }
};

// test code
int main()
{
  ECLife *pl1 = new ECCat;
  ECLife *pl2 = new ECDog;
  ECLife *pl3 = new ECCat;

  // How to tell what kind of life it is?
  // How to tell if say pl1 and pl2 point to the same kind of life?
  cout << pl1->Type() << endl;
  cout << (pl1->Type() == pl2->Type()) << endl;


  delete pl1;
  delete pl2;
  delete pl3; 
}

