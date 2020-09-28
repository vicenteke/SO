#include "thread.h"

__BEGIN_API

//Switches contexts. Returns 0 if OK, otherwise returns -1
int Thread::switch_context(Thread * prev, Thread * next) {
    CPU::switch_context(prev->context(), next->context());
    Thread::_running = next;

    //Debugging implementation. To use it, enable in traits.h
	db<Thread>(TRC) << "errno = " << errno << "\n";
    db<Thread>(INF) << "errno = " << errno << "\n";
    db<Thread>(WRN) << "errno = " << errno << "\n";
    db<Thread>(ERR) << "errno = " << errno << "\n";
    return errno;
}

//Finishes thread
//exit_code ignored by now
void Thread::thread_exit (int exit_code) {
    delete(_context);
}

//Returns thread's ID
int Thread::id() {
    return _id;
}

__END_API
