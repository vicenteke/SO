#include "timer.h"

__BEGIN_API

Timer::Timer(const unsigned int period, const Function * handler) {

    _period = period;
    _handler = handler;

    // Sets "handler" as handler for signal SIGALRM
    action.sa_handler = handler;
    sigaction(SIGALRM, &action, NULL);

    // Configures alarm timer
    timer.it_value.tv_sec = 0;
    timer.it_value.tv_usec = _period;
    timer.it_interval.tv_sec = 0;
    timer.it_interval.tv_usec = _period;
    setitimer (ITIMER_REAL, &timer, NULL);
}

void Timer::reset() {

    // Restarts timer counting
    timer.it_value.tv_sec = 0;
    timer.it_value.tv_usec = _period;
    timer.it_interval.tv_sec = 0;
    timer.it_interval.tv_usec = _period;
    setitimer (ITIMER_REAL, &timer, NULL);
}

__END_API
