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
    free(_context.uc_stack.ss_sp);
    //delete _stack; ??
}

void CPU::switch_context(Context *from, Context *to)
{
     swapcontext(&(from->_context), &(to->_context));
}

__END_API
