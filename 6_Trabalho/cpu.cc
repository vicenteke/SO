#include "cpu.h"
#include <iostream>

__BEGIN_API

void CPU::Context::save()
{
    //Stores current context in Context::_context
    getcontext(&_context);
}

void CPU::Context::load()
{
    //Loads Context::_context in current context
    setcontext(&_context);
}

CPU::Context::~Context()
{
    //Free allocated memory
    VALGRIND_STACK_DEREGISTER(valcontext);
    operator delete(_stack);
}

void CPU::switch_context(Context *from, Context *to)
{
    //Switches from context 'from' to 'to'
    errno = swapcontext(&(from->_context), &(to->_context));
}

int CPU::finc(volatile int & number) {

    // Atomic implementation for incrementing a number
    // __asm__ ( "xadd %%ebx, %%eax" : "=a"(number) : "a"(number), "b"(1));
    int old = 1;
    asm("lock xadd %0, %2" : "=a"(old) : "a"(old), "m"(number) : "memory");
    return number;
}

int CPU::fdec(volatile int & number) {

    // Atomic implementation for decrementing a number
    // __asm__ ( "xadd %%ebx, %%eax" : "=a"(number) : "a"(number), "b"(-1));
    int old = -1;
    asm("lock xadd %0, %2" : "=a"(old) : "a"(old), "m"(number) : "memory");
    return number;
}

__END_API
