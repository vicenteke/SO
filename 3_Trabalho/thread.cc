#include "thread.h"

__BEGIN_API

//Inicializa atributos static
Thread Thread::_main;
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
 * Retorna o ID da thread.
 */
int Thread::id() {
    return _id;
}

/*
* Realiza a inicialização da class Thread.
* Cria as Threads main e dispatcher.
*/
void Thread::init(void (*main)(void *)) {

    db<Thread>(TRC) << "Thread::init called\n";

    new (&_dispatcher) Thread(Thread::dispatcher);

    //Cria Thread main;
    std::string main_name = "main";
    new (&_main) Thread((void (*) (char*))main, (char*) main_name.data());


    //Troca o contexto para a Thread main;
    Thread::_running = &_main;
    _main.state(RUNNING);
    Thread::_ready.remove(_main.link()->object());
    CPU::switch_context(&_main_context, _main.context());
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
    while (Thread::_ready.size() > 0) {

        // escolha uma próxima thread a ser executada
        Ready_Queue::Element * next_link = Thread::_ready.remove();
        Thread * next = next_link->object();

        //next é uma thread do usuário? (!= Main e dispatcher)
        bool main_removed = false;
        while ((next->id() == Thread::_main.id() || next->id() == Thread::_dispatcher.id())) {
            db<Thread>(INF) << "next is not user thread (" << next->id() << "), but there are still some. Recalculating.\n";

            next_link = Thread::_ready.remove();
            next = next_link->object();

            main_removed = true;
        }

        // atualiza o status da própria thread dispatacher para READY e reinsire a mesma em _ready
        Thread::_dispatcher.state(READY);
        Thread::_ready.insert(Thread::_dispatcher.link());

        if (main_removed)
            Thread::_ready.insert(Thread::_main.link());

        // atualiza o ponteiro _running para apontar para a próxima thread a ser executada
        Thread::_running = next;

        // atualiza o estado da próxima thread a ser executada
        next->state(RUNNING);

        db<Thread>(INF) << "Dispatcher: next is Thread " << next->id() << "\n";

        // troca o contexto entre as duas threads
        Thread::switch_context(&Thread::_dispatcher, next);

        // testa se o estado da próxima thread é FINISHING e caso afirmativo a remova de _ready
        if(next->state() == FINISHING)  {
            Thread::_ready.remove(next_link->object());
        }
    }

    db<Thread>(TRC)<<"Dispatcher finishing\n";

    // muda o estado da thread dispatcher para FINISHING
    Thread::_dispatcher.state(FINISHING);

    // remova a thread dispatcher da fila de prontos
    Thread::_ready.remove(Thread::_dispatcher.link()->object());

    // troque o contexto da thread dispatcher para main
    Thread::switch_context(&Thread::_dispatcher, &Thread::_main);
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

    // escolhe dispatcher como proxima a ser executada
    Ready_Queue::Element * next_link = Thread::_ready.remove(Thread::_dispatcher.link()->object());
    Thread * next = next_link->object();

    db<Thread>(INF) << "Yield: next is Thread " << next->id() << "\n";

    if (exec != &Thread::_main && exec->state() != FINISHING) {

        // Atualiza prioridade da thread
        exec->link()->rank(std::chrono::duration_cast<std::chrono::microseconds>
                (std::chrono::high_resolution_clock::now().time_since_epoch()).count());

        exec->state(READY);

        // reinsira a thread que estava executando na fila de prontos
        Thread::_ready.insert(exec->link());
    }

    // atualiza o ponteiro _running para apontar para a próxima thread a ser executada
    Thread::_running = next;

    // atualiza o estado da próxima thread a ser executada
    next->state(RUNNING);

    // troca o contexto entre as duas threads
    Thread::switch_context(exec, &Thread::_dispatcher);
}

/*
* Termina a thread.
* exit_code é o código de término devolvido pela tarefa (ignorar agora, vai ser usado mais tarde).
* Quando a thread encerra, o controle deve retornar à main.
*/
void Thread::thread_exit (int exit_code) {
    db<Thread>(TRC) << "thread_exit called for Thread " << this->id() << "\n";

    _state = FINISHING;
    Thread::_ready.remove(this->link()->object());

    Thread::_running = &Thread::_dispatcher;
    Thread::_dispatcher.state(RUNNING);
    Thread::_ready.remove(Thread::_dispatcher.link()->object());
    Thread::switch_context(this, &Thread::_dispatcher);

    // yield();
}

/*
 * Destrutor de uma thread. Realiza todo os procedimentos para manter a consistência da classe.
 */
Thread::~Thread() {
    db<Thread>(TRC) << "~Thread() for Thread " << this->id() << "\n";

    delete(_context);
}

__END_API
