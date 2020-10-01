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
    db<Thread>(TRC) << "Thread::switch_context called\n";
    db<Thread>(INF) << "From Thread " << prev->id() << " to " << next->id() << "\n";

    Thread::_running = next;
    next->state(RUNNING);
    CPU::switch_context(prev->context(), next->context());
    return errno;
}

/*
 * Termina a thread.
 * exit_code é o código de término devolvido pela tarefa (ignorar agora, vai ser usado mais tarde).
 * Quando a thread encerra, o controle deve retornar à main.
 */
void Thread::thread_exit (int exit_code) {
    db<Thread>(TRC) << "thread_exit called for Thread " << this->id() << "\n";

    _state = FINISHING;
    Thread::_ready.remove(link());
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
    db<Thread>(TRC) << "Dispatcher called\n";

    // enquanto existir thread do usuário:
    while (Thread::_ready.size() > 2) {
        // escolha uma próxima thread a ser executada
        Ready_Queue::Element * next_link = Thread::_ready.remove();
        Thread * next = next_link->object();

        //next é uma thread do usuário? (!= Main e dispatcher)

        //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
        int i = 0;
        while ((next->id() == Thread::_main->id() || next->id() == Thread::_dispatcher.id()) && Thread::_ready.size() > 2 && i++ < 5) {
            db<Thread>(INF) << "next is not user thread, but there are still some. Recalculating.\n";

            Ready_Queue::Element * buffer = next_link;

            next_link = Thread::_ready.remove();
            next = next_link->object();

            if (i < 4)
            Thread::_ready.insert(buffer);
        }

        // atualiza o status da própria thread dispatacher para READY e reinsire a mesma em _ready
        Thread::_dispatcher.state(READY);
        Thread::_ready.insert(Thread::_dispatcher.link());

        // atualiza o ponteiro _running para apontar para a próxima thread a ser executada
        Thread::_running = next;

        // atualiza o estado da próxima thread a ser executada
        next->state(RUNNING);

        db<Thread>(INF) << "Dispatcher: next is Thread " << next->id() << "\n";

        // troca o contexto entre as duas threads
        Thread::switch_context(&Thread::_dispatcher, next);

        // testa se o estado da próxima thread é FINISHING e caso afirmativo a remova de _ready
        if(next->state() == FINISHING)  {
            Thread::_ready.remove(next_link);
        }
    }

    db<Thread>(TRC)<<"Dispatcher finishing\n";
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

    db<Thread>(TRC) << "Thread::init called\n";

    //Cria Thread main;
    std::string main_name = "main";
    Thread* Main = new Thread((void (*) (char*))main, (char*) main_name.data());
    Thread::_main = Main;
    Thread::_main_context = *Main->context();

    //Cria Thread dispatcher;
    Thread * dispatcher_pointer = new Thread(&Thread::dispatcher);
    Thread::_dispatcher = *dispatcher_pointer;

    //Troca o contexto para a Thread main;
    // Thread::switch_context(&Thread::_dispatcher, Main);
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
    //next = dispatcher
    Ready_Queue::Element * next_link = Thread::_ready.remove(Thread::_dispatcher.link());
    Thread * next = next_link->object();

    // atualiza a prioridade da tarefa que estava sendo executada (aquela que chamou yield) com o
    // timestamp atual, a fim de reinserí-la na fila de prontos atualizada (cuide de casos especiais, como
    // estado ser FINISHING ou Thread main que não devem ter suas prioridades alteradas)

    db<Thread>(INF) << "Yield: next is Thread " << next->id() << "\n";

    if (exec->id() != Thread::_main->id()) {

        if (exec->state() != FINISHING) {
            Thread::_ready.remove(exec->link());

            exec->link()->rank(std::chrono::duration_cast<std::chrono::microseconds>
                    (std::chrono::high_resolution_clock::now().time_since_epoch()).count());

            // reinsira a thread que estava executando na fila de prontos
            Thread::_ready.insert(exec->link());

        } else {
            //Remove thread de _ready
            Thread::_ready.remove(exec->link());
        }

    // } else {
    //     Thread::_ready.insert(exec->link());
    }

    // atualiza o ponteiro _running para apontar para a próxima thread a ser executada
    Thread::_running = next;

    // atualiza o estado da próxima thread a ser executada
    next->state(RUNNING);

    // troca o contexto entre as duas threads
    Thread::switch_context(exec, &Thread::_dispatcher);

}

/*
 * Destrutor de uma thread. Realiza todo os procedimentos para manter a consistência da classe.
 */
Thread::~Thread() {
    db<Thread>(TRC) << "~Thread() for Thread " << this->id() << "\n";
    thread_exit(0);
}

__END_API
