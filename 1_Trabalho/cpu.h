#ifndef cpu_h
#define cpu_h

#include <ucontext.h>
#include <iostream>
#include "traits.h"
#include <valgrind/valgrind.h>


__BEGIN_API

class CPU
{
    public:

        class Context
        {
        private:
            static const unsigned int STACK_SIZE = Traits<CPU>::STACK_SIZE;
        public:
            Context() { _stack = 0; }

            template<typename ... Tn>
            Context(void (* func)(Tn ...), Tn ... an) {

                void *stack;
                //Setting up _context
                getcontext(&_context);

                stack = malloc(STACK_SIZE);

                valcontext = VALGRIND_STACK_REGISTER(stack, ((uint8_t*)stack) + STACK_SIZE);

                _context.uc_link            = 0;
                //_context.uc_stack.ss_sp     = new char [STACK_SIZE]; //Can we use 'new' and 'delete'?
                _context.uc_stack.ss_sp     = stack; //Can we use 'new' and 'delete'?
                _stack = (char*) _context.uc_stack.ss_sp;
                _context.uc_stack.ss_size   = STACK_SIZE;
                _context.uc_stack.ss_flags  = 0;

                //Attaching func to _context
                makecontext(&(_context), (void (*) (void))func, sizeof...(an), an ...);
            }

            ~Context();

            void save();
            void load();

        private:
            char *_stack;
        public:
            ucontext_t _context;
            int valcontext;
        };

    public:

        static void switch_context(Context *from, Context *to);

};

__END_API

#endif
