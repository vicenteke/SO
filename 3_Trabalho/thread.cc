#include "thread.h"

__BEGIN_API

Thread Thread::_dispatcher;

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
    //Thread::_ready.remove(link());
    delete(_context);
    Thread::yield();
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
    while (Thread::_ready.size() > 2) {
        // escolha uma próxima thread a ser executada
        Ready_Queue::Element * next_link = Thread::_ready.remove();
        Thread * next = next_link->object();

        // atualiza o status da própria thread dispatacher para READY e reinsire a mesma em _ready
        Thread::_dispatcher.state(READY);
        Thread::_ready.insert(Thread::_dispatcher.link());

        // atualiza o ponteiro _running para apontar para a próxima thread a ser executada
        Thread::_running = next;

        // atualiza o estado da próxima thread a ser executada
        next->state(RUNNING);

        // troca o contexto entre as duas threads
        Thread::switch_context(&Thread::_dispatcher, next);

        // testa se o estado da próxima thread é FINISHING e caso afirmativo a remova de _ready
        if(next->state() == FINISHING)  {
            Thread::_ready.remove(next_link);
        }
    }

    db<Thread>(TRC)<<"Dispatcher saying bye\n";
    // muda o estado da thread dispatcher para FINISHING
    Thread::_dispatcher.state(FINISHING);

    // remova a thread dispatcher da fila de prontos
    Thread::_ready.remove(Thread::_dispatcher.link());

    // troque o contexto da thread dispatcher para main
    Thread::switch_context(&Thread::_dispatcher, Thread::_main);
}

/*
 * Realiza a inicialização da class Thread.
 * Cria as Threads main e dispatcher.
 */
void Thread::init(void (*main)(void *)) {

    //Cria Thread main;
    std::string main_name = "main";
    Thread* Main = new Thread((void (*) (char*))main, (char*) main_name.data());

    //Cria Thread dispatcher;
    Thread * dispatcher_pointer = new Thread(Thread::dispatcher);
    Thread::_dispatcher = *dispatcher_pointer;

    //Thread::_dispatcher.context()->load();

    //Troca o contexto para a Thread main;
    // CPU::Context * cont = new CPU::Context();
    // cont->save();
    // CPU::switch_context(cont, Main->context());
    // db<Thread>(TRC)<<"Thread::init 1\n";
    Main->context()->load();
}

/*
 * Devolve o processador para a thread dispatcher que irá escolher outra thread pronta
 * para ser executada.
 */
void Thread::yield() {

    // imprima informação usando o debug em nível TRC
    db<Thread>(TRC)<<"Thread::yield called\n";

    //Pointeiro para thread em execucao
    Thread * exec = _running;

    // escolha uma próxima thread a ser executada
    Ready_Queue::Element * next_link = Thread::_ready.remove();
    Thread * next = next_link->object();

    // atualiza a prioridade da tarefa que estava sendo executada (aquela que chamou yield) com o
    // timestamp atual, a fim de reinserí-la na fila de prontos atualizada (cuide de casos especiais, como
    // estado ser FINISHING ou Thread main que não devem ter suas prioridades alteradas)
    if (exec != Thread::_main) {

        if (exec->state() != FINISHING) {
            exec->link()->rank(std::chrono::duration_cast<std::chrono::microseconds>
                    (std::chrono::high_resolution_clock::now().time_since_epoch()).count());

            // reinsira a thread que estava executando na fila de prontos
            Thread::_ready.insert(exec->link());

        } else {
            //Remove thread de _ready
            Thread::_ready.remove(exec->link());
        }

    }

    // atualiza o ponteiro _running para apontar para a próxima thread a ser executada
    Thread::_running = next;

    // atualiza o estado da próxima thread a ser executada
    next->state(RUNNING);

    // troca o contexto entre as duas threads
    Thread::switch_context(exec, next);

}

/*
 * Destrutor de uma thread. Realiza todo os procedimentos para manter a consistência da classe.
 */
Thread::~Thread() {
    thread_exit(0);
}

__END_API
