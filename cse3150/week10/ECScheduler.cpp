// implement a task scheduler based on the Singleton pattern
#include "ECScheduler.h"

class ECScheduler
{
public:
  static ECScheduler& Instance(); 

  void StartTask(int id);
  void StopTask(int id);
  int GetNumRunTasks() const;
  
private:

};
