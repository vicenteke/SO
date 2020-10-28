#include "timer.h"

__BEGIN_API

Timer::Timer(const unsigned int period, const Function * handler) {

    _period = period;
    _handler = handler;

    action.sa_handler = handler;
    sigaction(SIGVTALRM, &action, NULL);

    timer.it_value.tv_sec = 0;
    timer.it_value.tv_usec = _period;
    timer.it_interval.tv_sec = 0;
    timer.it_interval.tv_usec = _period;
    setitimer (ITIMER_VIRTUAL, &timer, NULL);

    // struct itimerval old, timer;
    // timer.it_interval.tv_usec = period;
    // timer.it_interval.tv_sec = 0;
    // timer.it_value.tv_sec = 0;
    // timer.it_value.tv_usec = period;
    // // if (setitimer (ITIMER_REAL, &timer, &old) < 0)
    // setitimer (ITIMER_REAL, &timer, &old);
    //     return 0;
    // else
    //     return old.it_value.tv_sec;
}

void Timer::reset() {

    timer.it_value.tv_sec = 0;
    timer.it_value.tv_usec = _period;
    timer.it_interval.tv_sec = 0;
    timer.it_interval.tv_usec = _period;
    setitimer (ITIMER_VIRTUAL, &timer, NULL);
}

__END_API
