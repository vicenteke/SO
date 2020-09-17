#include "cpu.h"
#include <iostream>

__BEGIN_API

void CPU::Context::save()
{
    getcontext(&_context);
}

void CPU::Context::load()
{
    setcontext(&_context);
}

CPU::Context::~Context()
{
    //delete _context.uc_stack.ss_sp;
    operator delete(stack);
    //delete _stack; ??
    VALGRIND_STACK_DEREGISTER(valcontext);
}

void CPU::switch_context(Context *from, Context *to)
{
     swapcontext(&(from->_context), &(to->_context));
}

__END_API
