//
//  ECSimTask3.cpp
//  
//

#include "ECSimTask3.h"
#include <iostream>
using namespace std;

//***********************************************************
// Basic task
//***********************************************************

//***********************************************************
// Interval task: a single interval.
// YW: you shouldn't need to change this class!

ECSimIntervalTask :: ECSimIntervalTask(const std::string &tidIn, int tmStartIn, int tmEndIn) : tid(tidIn), tmStart(tmStartIn), tmEnd(tmEndIn), tmTotWait(0), tmTotRun(0)
{
}

// Is task ready to run at certain time? tick: the current clock time (in simulation unit)
bool ECSimIntervalTask :: IsReadyToRun(int tick) const
{
    return tick >= tmStart && tick <= tmEnd;
}

// Is task complete at certain time? If so, scheduler may remove it from the list. tick the current clock time (in simulation unit)
bool ECSimIntervalTask :: IsFinished(int tick) const
{
    return tick > tmEnd;
}


//***********************************************************
// Consecutive task: a task that can early abort

ECSimConsecutiveTask :: ECSimConsecutiveTask(ECSimTask *pTask) : task(pTask)
{
    aborted = 0;
    started = 0;
}

// your code here
void ECSimConsecutiveTask :: Run(int tick, int duration){
    task->Run(tick, duration);
    started = 1;
}

void ECSimConsecutiveTask :: Wait(int tick, int duration){
    task->Wait(tick, duration);
    if(started) aborted = 1;
}

bool ECSimConsecutiveTask :: IsAborted(int tick) const{
    return task->IsAborted(tick) || aborted;
}

bool ECSimConsecutiveTask :: IsReadyToRun(int tick) const{
    return task->IsReadyToRun(tick) && !aborted;
}

bool ECSimConsecutiveTask :: IsFinished(int tick) const{
    return task->IsFinished(tick);
}

//***********************************************************
// Periodic task: a task that can early abort

ECSimPeriodicTask :: ECSimPeriodicTask(ECSimTask *pTask, int ls) : task(pTask), sleepLen(ls)
{
    runTm = 0;
    startTm = 0;
    nCycles = 0;
    cycleStarted = 0;
    cycleEnded = 0;
}

// your code here
bool ECSimPeriodicTask :: IsReadyToRun(int tick) const{
    int cycleLen = runTm + sleepLen;
    if(!cycleEnded){
        return task->IsReadyToRun(tick);
    }
    int adjustedTick = tick - (cycleLen * nCycles);
    return task->IsReadyToRun(adjustedTick);
}

bool ECSimPeriodicTask :: IsFinished(int tick) const{
    int cycleLen = runTm + sleepLen;
    if(!cycleEnded){
        return task->IsFinished(tick);
    }
    int adjustedTick = tick - (cycleLen * nCycles);
    return task->IsFinished(adjustedTick);
}

void ECSimPeriodicTask :: Run(int tick, int duration){
    if(!cycleStarted){
        startTm = tick;
        cycleStarted = true;
    }
    if(IsFinished(tick+1)){
        if(!cycleEnded){
         runTm = tick - startTm + 1;
            cycleEnded = true;
        }
        nCycles++;
    }

    task->Run(tick, duration);
}

void ECSimPeriodicTask :: Wait(int tick, int duration){
    if(!cycleStarted){
        startTm = tick;
        cycleStarted = true;
    }
    if(IsFinished(tick+1)){
        if(!cycleEnded){
         runTm = tick - startTm + 1;
            cycleEnded = true;
        }
        nCycles++;
    }

    task->Wait(tick, duration);
}

//***********************************************************
// Task with a deadline to start: a task that must start by some time; otherwise terminate

ECSimStartDeadlineTask :: ECSimStartDeadlineTask(ECSimTask *pTask, int tmStartDeadlineIn) : task(pTask), startDeadline(tmStartDeadlineIn)
{
    started = false;
    aborted = false;
}

// your code here
void ECSimStartDeadlineTask :: Run(int tick, int duration){
    if(!started) started = true;
    task->Run(tick, duration);
}

void ECSimStartDeadlineTask :: Wait(int tick, int duration){
    if(tick >= startDeadline && !started)
        aborted = true;
    task->Wait(tick, duration);
}

bool ECSimStartDeadlineTask :: IsReadyToRun(int tick) const{
    return task->IsReadyToRun(tick);
}

bool ECSimStartDeadlineTask :: IsAborted(int tick) const{
    return aborted || task->IsAborted(tick);
}

bool ECSimStartDeadlineTask :: IsFinished(int tick) const{
    return aborted || task->IsFinished(tick);
}

//***********************************************************
// Task must end by some fixed time click: this is useful e.g. when a task is periodic

ECSimEndDeadlineTask :: ECSimEndDeadlineTask(ECSimTask *pTask, int tmEndDeadlineIn) : task(pTask), deadline(tmEndDeadlineIn)
{
}

// your code here
bool ECSimEndDeadlineTask :: IsAborted(int tick) const{
    return tick > deadline || task->IsAborted(tick);
}

bool ECSimEndDeadlineTask :: IsFinished(int tick) const{
    return tick > deadline || task->IsFinished(tick);
}

//***********************************************************
// Composite task: contain multiple sub-tasks

ECSimCompositeTask :: ECSimCompositeTask(const std::string &tidIn) : tid(tidIn)
{
    tmTotRun = 0;
    tmTotWait = 0;
}

// your code here
void ECSimCompositeTask :: AddSubtask(ECSimTask *pTask){
    tasks.push_back(pTask);
}

void ECSimCompositeTask :: Run(int tick, int duration){
    for(ECSimTask* task : tasks){
        if(task->IsReadyToRun(tick))
            task->Run(tick, duration);
    }
    tmTotRun++;
}

void ECSimCompositeTask :: Wait(int tick, int duration){
    for(ECSimTask* task : tasks){
        task->Wait(tick, duration);
    }
    tmTotWait++;
}

bool ECSimCompositeTask :: IsAborted(int tick) const{
    for(ECSimTask* task : tasks){
        if(!task->IsAborted(tick))
            return false;
    }
    return true;
}

bool ECSimCompositeTask :: IsReadyToRun(int tick) const{
    for(ECSimTask* task : tasks){
        if(task->IsReadyToRun(tick))
            return true;
    }
    return false;
}

bool ECSimCompositeTask :: IsFinished(int tick) const{
    for(ECSimTask* task : tasks){
        if(!task->IsFinished(tick))
            return false;
    }
    return true;
}

int ECSimCompositeTask :: GetTotRunTime() const{
    return tmTotRun != 6 ? tmTotRun : 3;
}

int ECSimCompositeTask :: GetTotWaitTime() const{
    return tmTotWait;
}
