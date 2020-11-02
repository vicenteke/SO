#include "semaphore.h"

__BEGIN_API

Semaphore::Semaphore (int v) {

    db<Semaphore>(TRC) << "Semaphore() constructor called\n";

    _count = v;
}

Semaphore::~Semaphore() {

    db<Semaphore>(TRC) << "~Semaphore() destructor called\n";

    wakeup_all();
}

void Semaphore::p() {

    db<Semaphore>(TRC) << "Semaphore::p() called\n";

    if (fdec(_count) == -1)
        sleep();
}

void Semaphore::v() {

    db<Semaphore>(TRC) << "Semaphore::v() called\n";

    if (finc(_count) == 1)
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

    finc(_count);
    Thread::sleep(_waiting);
}

void Semaphore::wakeup() {

    db<Semaphore>(TRC) << "Semaphore::wakeup() called\n";

    fdec(_count);
    if (!Thread::wakeup(_waiting))
        finc(_count);
}

void Semaphore::wakeup_all() {

    db<Semaphore>(TRC) << "Semaphore::wakeup_all() called\n";

    Thread::wakeup_all(_waiting);

}

__END_API
