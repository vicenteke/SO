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
    _state = FINISHING;
    delete(_context);
}

/*
 * Retorna o ID da thread.
 */
int Thread::id() {
    return _id;
}

/*
 * Daspachante (disptacher) de threads.
 * Executa enquanto houverem threads do usuário.
 * Chama o escalonador para definir a próxima tarefa a ser executada.
 */
void Thread::dispatcher() {

// imprima informação usando o debug em nível TRC
db<Thread>(TRC)<<"Dispatcher called\n";

// enquanto existir thread do usuário:
while (Thread::_ready) {
//     escolha uma próxima thread a ser executada
//     atualiza o status da própria thread dispatacher para READY e reinsire a mesma em _ready
//     atualiza o ponteiro _running para apontar para a próxima thread a ser executada
//     atualiza o estado da próxima thread a ser executada
//     troca o contexto entre as duas threads
//     testa se o estado da próxima thread é FINISHING e caso afirmativo a remova de _ready
}

// muda o estado da thread dispatcher para FINISHING
// remova a thread dispatcher da fila de prontos
// troque o contexto da thread dispatcher para main
}

/*
 * Realiza a inicialização da class Thread.
 * Cria as Threads main e dispatcher.
 */
void Thread::init(void (*main)(void *)) {

//Cria Thread main;
Thread* Main = new Thread(main);

//Cria Thread dispatcher;
Thread::dispatcher();

//Troca o contexto para a Thread main;
Thread::switch_context(this, Main);
}

/*
 * Devolve o processador para a thread dispatcher que irá escolher outra thread pronta
 * para ser executada.
 */
void Thread::yield() {
/*
imprima informação usando o debug em nível TRC
escolha uma próxima thread a ser executada

atualiza a prioridade da tarefa que estava sendo executada (aquela que chamou yield) com o
timestamp atual, a fim de reinserí-la na fila de prontos atualizada (cuide de casos especiais, como
estado ser FINISHING ou Thread main que não devem ter suas prioridades alteradas)

reinsira a thread que estava executando na fila de prontos
atualiza o ponteiro _running
atualiza o estado da próxima thread a ser executada
troque o contexto entre as threads
*/
}

/*
 * Destrutor de uma thread. Realiza todo os procedimentos para manter a consistência da classe.
 */
Thread::~Thread() {
//exit
}

__END_API
