//
//  ECSimTaskScheduler2.cpp
//  
//
//

#include <vector>
#include <iostream>
#include <climits>
using namespace std;

#include "ECSimTaskScheduler2.h"
#include "ECSimTask.h"

//4a) Longest waiting time first
ECSimLWTFTaskScheduler :: ECSimLWTFTaskScheduler()
{
}

ECSimTask * ECSimLWTFTaskScheduler :: ChooseTaskToSchedule(const std::vector<ECSimTask *> &listReadyTasks) const{
    int maxWaitTime = -1;
    ECSimTask* taskToRun = NULL;

    if(listReadyTasks.size() == 0) return taskToRun;

    for(auto task : listReadyTasks){
        if(task->GetTotWaitTime() > maxWaitTime){
            maxWaitTime = task->GetTotWaitTime();
            taskToRun = task;
        }
    }

    return taskToRun;
}

//4b) Shortest actual running time
ECSimSARTTaskScheduler :: ECSimSARTTaskScheduler()
{
}

ECSimTask * ECSimSARTTaskScheduler :: ChooseTaskToSchedule(const std::vector<ECSimTask *> &listReadyTasks) const{
    int minRunTime = INT_MAX;
    ECSimTask* taskToRun = NULL;

    if(listReadyTasks.size() == 0) return taskToRun;

    for(auto task : listReadyTasks){
        if(task->GetTotRunTime() < minRunTime){
            minRunTime = task->GetTotRunTime();
            taskToRun = task;
        }
    }

    return taskToRun;
}

//4c) Highest priority
ECSimPriorityScheduler :: ECSimPriorityScheduler()
{
}

ECSimTask * ECSimPriorityScheduler :: ChooseTaskToSchedule(const std::vector<ECSimTask *> &listReadyTasks) const{
    int minPri = INT_MAX;
    ECSimTask* taskToRun = NULL;

    if(listReadyTasks.size() == 0) return taskToRun;

    for(auto task : listReadyTasks){
        if(task->GetPriority() < minPri){
            minPri = task->GetPriority();
            taskToRun = task;
        }
    }

    return taskToRun;
}

//4d) Round robin
ECSimRoundRobinTaskScheduler :: ECSimRoundRobinTaskScheduler()
{
}

void ECSimRoundRobinTaskScheduler :: AddTask(ECSimTask *pTask) {
    ECSimTaskScheduler :: AddTask(pTask);
    listScheduledTasks[pTask]++;
}

ECSimTask * ECSimRoundRobinTaskScheduler :: ChooseTaskToSchedule(const std::vector<ECSimTask *> &listReadyTasks) const{
    // int minScheduled = INT_MAX;
    // ECSimTask* taskToRun = NULL;

    // if(listReadyTasks.size() == 0) return taskToRun;

    // for(ECSimTask* task : listReadyTasks){
    //     if(listScheduledTasks.at(task) < minScheduled){
    //         minScheduled = listScheduledTasks.at(task);
    //         taskToRun = task;
    //     }
    // }

    // return taskToRun;
    int minRunTime = INT_MAX;
    ECSimTask* taskToRun = NULL;

    if(listReadyTasks.size() == 0) return taskToRun;

    for(auto task : listReadyTasks){
        if(task->GetTotRunTime() < minRunTime){
            minRunTime = task->GetTotRunTime();
            taskToRun = task;
        }
    }

    return taskToRun;
}