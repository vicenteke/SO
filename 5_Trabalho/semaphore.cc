#include "semaphore.h"

__BEGIN_API

Semaphore::Semaphore (int v) {

    db<Semaphore>(TRC) << "Semaphore() constructor called\n";

    _count = v;
    Ready_Queue _waiting;
}

Semaphore::~Semaphore() {

    db<Semaphore>(TRC) << "~Semaphore() destructor called\n";

    wakeup_all();
}

void Semaphore::p() {

    db<Semaphore>(TRC) << "Semaphore::p() called\n";

    if (_count > 0) fdec(_count);
    else {
        sleep();
    }
}

void Semaphore::v() {

    db<Semaphore>(TRC) << "Semaphore::v() called\n";

    if (_count > 0 || _waiting.size() == 0)
        finc(_count);
    else
        wakeup();
}

// Atomic operations
int Semaphore::finc(volatile int & number) {

    return CPU::finc(number);
}
int Semaphore::fdec(volatile int & number) {

    return CPU::fdec(number);
}

// Thread operations
void Semaphore::sleep() {

    db<Semaphore>(TRC) << "Semaphore::sleep() called\n";

    Thread * exec = Thread::_running;
    _waiting.insert(exec->link());
    exec->sleep();
}

void Semaphore::wakeup() {

    db<Semaphore>(TRC) << "Semaphore::wakeup() called\n";

    Ready_Queue::Element * next_link = _waiting.remove();
    next_link->object()->wakeup();
}

void Semaphore::wakeup_all() {

    db<Semaphore>(TRC) << "Semaphore::wakeup_all() called\n";

    while (_waiting.size() > 0)
        wakeup();
}

__END_API