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

                //Setting up _context
                getcontext(&_context);
                _context.uc_link            = 0;
                _context.uc_stack.ss_sp     = operator new(STACK_SIZE);

                //Command necessary to avoid Valgrind's misinterpretation of context changing operations
                valcontext = VALGRIND_STACK_REGISTER(_context.uc_stack.ss_sp, ((uint8_t*)_context.uc_stack.ss_sp) + STACK_SIZE);

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
            int valcontext; //Necessary to avoid Valgrind's misinterpretation of context changing
        };

    public:
        static void switch_context(Context *from, Context *to);

};

__END_API

#endif
