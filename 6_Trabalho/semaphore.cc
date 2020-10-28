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

    //Comparação atômica para o _count (usar fdec//fint para comparar com o valor antigo)
    if (fdec(_count) == -1)
        sleep();
}

void Semaphore::v() {

    db<Semaphore>(TRC) << "Semaphore::v() called\n";

    //Sempre executar finc, a partir do valor de retorno definir se chama wakeup()
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

    //Não liberar o acesso de _running para outras classes
    //Tratar a fila de espera dentro de um método estático da classe Thread
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

    //liberar todas de uma só vez antes de chamar a yield()
    //Tratar caso onde a Thread é deletada por outra
    while (_waiting.size() > 0)
        wakeup();

    Thread::yield();
}

__END_API
