//
//  ECSimTask2.cpp
//  
//
//

#include "ECSimTask2.h"
#include <string>
#include <iostream>

//3a) MultiInterval
ECMultiIntervalsTask :: ECMultiIntervalsTask(const std::string &tidIn) : ECSimTask(tidIn)
{
}

bool ECMultiIntervalsTask :: IsReadyToRun(int tick) const
{
    // as long as tick is within the specified intervals, it is ready
    bool ready = 0;
    for (auto _it : listTimes){
        if(tick >= _it[0] && tick <= _it[1]){
            ready = 1;
        }
    }
    return ready;
}

// Is task complete after all intervals?
bool ECMultiIntervalsTask :: IsFinished(int tick) const
{
    return tick > listTimes.back()[1];
}

void ECMultiIntervalsTask :: AddInterval(int a, int b){
    listTimes.push_back({a,b});
}

//3b) HardInterval
ECHardIntervalTask :: ECHardIntervalTask(const std::string &tidIn, int tmStartIn, int tmEndIn) : ECSimTask(tidIn), tmStart(tmStartIn), tmEnd(tmEndIn)
{
}

bool ECHardIntervalTask :: IsReadyToRun(int tick) const
{
    //start strictly at start time
    return tick == tmStart;
}

bool ECHardIntervalTask :: IsFinished(int tick) const
{
    return tick == tmEnd;
}

//3c) ConsecutiveInterval
ECConsecutiveIntervalTask :: ECConsecutiveIntervalTask(const std::string &tidIn, int tmStartIn, int tmEndIn) : ECSimTask(tidIn), tmStart(tmStartIn), tmEnd(tmEndIn)
{
}

void ECConsecutiveIntervalTask :: Run(int tick, int duration){
    ECSimTask :: Run(tick, duration);
    isRunning = 1;
}

void ECConsecutiveIntervalTask :: Wait(int tick, int duration){
    ECSimTask :: Wait(tick, duration);
    if(isRunning) isInterrupted = 1;
}

bool ECConsecutiveIntervalTask :: IsReadyToRun(int tick) const
{
    return tick >= tmStart && tick <= tmEnd && !isInterrupted;
}

bool ECConsecutiveIntervalTask :: IsFinished(int tick) const
{
    return tick > tmEnd || isInterrupted;
}

//3d) PeriodicTask
ECPeriodicTask :: ECPeriodicTask(const std::string &tidIn, int tmStartIn, int runLenIn, int sleepLenIn) : ECSimTask(tidIn), tmStart(tmStartIn), runLen(runLenIn), sleepLen(sleepLenIn)
{
}

bool ECPeriodicTask :: IsReadyToRun(int tick) const
{
    return tick >= tmStart && ((tick - tmStart) % (runLen + sleepLen)) < runLen;
}

bool ECPeriodicTask :: IsFinished(int tick) const
{
    return 0;
}