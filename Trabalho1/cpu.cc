#include "cpu.h"
#include <iostream>

__BEGIN_API

template<typename ... Tn>
CPU::Context::Context(void (* func)(Tn ...), Tn ... an) {

    //Setting up _context
    getcontext(&_context);
    _context.uc_link            = 0;
    _context.uc_stack.ss_sp     = malloc(STACK_SIZE);
    _context.uc_stack.ss_size   = STACK_SIZE;
    _context.uc_stack.ss_flags  = 0;

    //Attaching func to _context
    makecontext(&_context, func(an ...));
}

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
    free(_context.uc_stack.ss_sp);
    //delete _stack; ??
}

void CPU::switch_context(Context *from, Context *to)
{
     //swapcontext()
}

__END_API
