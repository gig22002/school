// Code for modeling a university's various units: department, office,
// college, etc
#include <vector>

// Generic interface. 
class ECUnit
{
public:
	double GetBudget() const { return 1; }
};

// Department
class ECDepartment : public ECUnit
{
public:
	ECDepartment(int b) : budget(b) {} 
	double GetBudget() const { return budget; }

private:
	int budget;
};

// Office
class ECOffice : public ECUnit
{
public:
  ECOffice(int b) : budget(b) {}
  double GetBudget() const { return budget; }

private:
  int budget;
};

// Composite
class ECCompositeUnit : public ECUnit
{
public:
  ECCompositeUnit() {}
  ~ECCompositeUnit(){
	for (auto v : listUnits) delete v;
  }
  
  
  double GetBudget() const 
  { 
	double sum=0.0;
	for (auto x : listUnits){
		sum += x->GetBudget();
	}
	return sum;
  }
  void AddChild(ECUnit *pUnit)
  {
	listUnits.push_back(pUnit);
  }

private:
  // your code here
  std::vector<ECUnit*> listUnits;
};

