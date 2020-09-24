#include "thread.h"

__BEGIN_API

/*
 * Método para trocar o contexto entre duas thread, a anterior (prev)
 * e a próxima (next).
 * Deve encapsular a chamada para a troca de contexto realizada pela class CPU.
 * Valor de retorno é negativo se houve erro, ou zero.
 */
int Thread::switch_context(Thread * prev, Thread * next) {
    CPU::switch_context(prev->context(), next->context());
    Thread::_running = next;
    return errno;
}

/*
 * Termina a thread.
 * exit_code é o código de término devolvido pela tarefa (ignorar agora, vai ser usado mais tarde).
 * Quando a thread encerra, o controle deve retornar à main.
 */
void Thread::thread_exit (int exit_code) {
    delete(_context);
}

/*
 * Retorna o ID da thread.
 */
int Thread::id() {
    return _id;
}

/*
 * Qualquer outro método que você achar necessário para a solução.
 */

__END_API
