// implement a task scheduler based on the Singleton pattern
#include <set>

class ECScheduler
{
public:
  static ECScheduler& Instance(){
    if(!pInstance){
	pInstance = new ECScheduler;
    }
    return *pInstance;
  } 

  void StartTask(int id){ setIDs.insert(id); }
  void StopTask(int id){ setIDs.erase(id); }
  int GetNumRunTasks() const { return setIDs.size(); }
  
private:
  ECScheduler() {}
  ~ECScheduler() {}
  static ECScheduler *pInstance;
  std::set<int> setIDs;
};

ECScheduler *ECscheduler::pInstance = nullptr;
