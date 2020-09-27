////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2011, Computer Graphics Group RWTH Aachen University         //
// All rights reserved.                                                       //
////////////////////////////////////////////////////////////////////////////////

#ifndef ACGL_UTILS_PERFORMANCETIMER_HH
#define ACGL_UTILS_PERFORMANCETIMER_HH

/*
 * Three Timers are defined here: SystemTimer, ProcessTimer and ThreadTimer.
 * They can be used to do basic time measurements with high accuracy.
 *
 * SystemTimer is based on the time since 1.1.1970.
 * ProcessTime is based on the runtime of the process/application.
 * ThreadTime  is based on the time the thread has run in which it is called.
 *
 * Just use it like:
 *
 * ProcessTime t; // automatic reset
 * slowFunction();
 * log() << "function took " << t.getTimeInSecondsD() << " seconds, ";
 * t.reset();
 * fastFunction();
 * log() << "other function took " << t.getTimeInNanoseconds() << " nanoseconds";
 */

#include <ACGL/ACGL.hh>
#include <iostream>

#include <ctime>

namespace ACGL{
namespace Utils{

template < clockid_t TIMER_TYPE >
class PerformanceTimer
{
public:

    PerformanceTimer() { restart(); }

    // set the mStartTime to the current time:
    inline void restart() { timespec t; clock_gettime( TIMER_TYPE, &t); mStartTime = timespecTo64( t ); }

    // returns the CPU/Process/Thread time in nanosecounds, a 64 bit unsigned int will overflow after
    // 584 years...
    inline uint64_t getTimeInNanoseconds() { timespec t; clock_gettime( TIMER_TYPE, &t); return timespecTo64(t); }

    // 32 bit unsigned int with seconds will overflow after 136 years
    inline uint32_t getTimeInSeconds()  { timespec t; clock_gettime( TIMER_TYPE, &t); return t.tv_sec; }
    inline double   getTimeInSecondsD() { timespec t; clock_gettime( TIMER_TYPE, &t); return timespecToDouble(t); }

    // get time diff since last reset:
    inline uint64_t getTimeDiffInNanoseconds() { return getTimeInNanoseconds() - mStartTime; }

    // 32 bit unsigned int with seconds will overflow after 136 years
    inline uint32_t getTimeDiffInSeconds()  { return getTimeInSeconds()  - (mStartTime/1000000000); }
    inline double   getTimeDiffInSecondsD() { return getTimeInSecondsD() - (mStartTime/1000000000.0); }

    // get the system dependent resolution of the timing in nanoseconds
    inline uint64_t getTimerResolutionInNanoseconds() { timespec t; clock_getres( TIMER_TYPE, &t); return timespecTo64(t); }

private:
    inline uint64_t timespecTo64( const timespec &_time ) const {
        return ( _time.tv_sec*1000000000 + _time.tv_nsec );
    }

    inline uint64_t timespecToDouble( const timespec &_time ) const {
        return ( _time.tv_sec + _time.tv_nsec/1000000000.0 );
    }

    uint64_t mStartTime;

};

// systemwide clock which holds the time since 1.1.1970:
typedef PerformanceTimer< ((clockid_t)CLOCK_REALTIME) >           SystemTimer;
typedef PerformanceTimer< ((clockid_t)CLOCK_PROCESS_CPUTIME_ID) > ProcessTimer;
typedef PerformanceTimer< ((clockid_t)CLOCK_THREAD_CPUTIME_ID) >  ThreadTimer;

} // Utils
} // ACGL

#endif // ACGL_UTILS_PERFORMANCETIMER_HH
