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
    operator delete(_stack);
    VALGRIND_STACK_DEREGISTER(valcontext);
}

void CPU::switch_context(Context *from, Context *to)
{
    //Switches from context 'from' to 'to'
    errno = swapcontext(&(from->_context), &(to->_context));
}

__END_API
