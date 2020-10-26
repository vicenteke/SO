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
    if (!next_link) db<Thread> (ERR) << "Error in Thread::yield(): next_link is null\n";
    Thread * next = next_link->object();

    db<Thread>(INF) << "Yield: next is Thread " << next->id() << "\n";

    if (exec->state() != FINISHING && exec->state() != SUSPENDED && exec->state() != WAITING) {

        if (exec != &Thread::_main) {
            // Atualiza prioridade da thread
            exec->link()->rank(std::chrono::duration_cast<std::chrono::microseconds>
                    (std::chrono::high_resolution_clock::now().time_since_epoch()).count());
        }

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

// Suspende a Thread até que resume() seja chamado
void Thread::suspend() {

    db<Thread>(TRC)<<"Thread::suspend() called for " << id() << "\n";

    _ready.remove(this->link()->object());
    this->state(SUSPENDED);
    _suspended_queue.insert(this->link());
    yield();
}

// Acorda uma Thread que estava suspensa
void Thread::resume() {

    db<Thread>(TRC)<<"Thread::resume() called for " << id() << "\n";

    _suspended_queue.remove(this->link()->object());
    state(READY);
    _ready.insert(link());
    yield();
}

// Este método deve suspender a thread em execução até que a thread “alvo” finalize
int Thread::join() {

    db<Thread>(TRC)<<"Thread " << _running->id() << " joining " << id() << "\n";

    _suspended = _running;
    _suspended->suspend();
    return _exit_code;
}


/*
* Termina a thread.
* exit_code é o código de término devolvido pela tarefa (ignorar agora, vai ser usado mais tarde).
* Quando a thread encerra, o controle deve retornar à main.
*/
void Thread::thread_exit (int exit_code) {

    db<Thread>(TRC) << "thread_exit called for Thread " << this->id() << "\n";

    _exit_code = exit_code;

    _state = FINISHING;
    Thread::_ready.remove(this->link()->object());

    // Resumes all suspended threads
    if (_suspended != NULL) {
        _suspended->resume();
        _suspended = NULL;
    }

    if (_ready.size() == 0 && _suspended_queue.size() > 0) {
        while (_suspended_queue.size() > 0) {
            Ready_Queue::Element * next_link = _suspended_queue.remove();
            next_link->object()->resume();
        }
    }

    yield();
}

/*
 * Destrutor de uma thread. Realiza todo os procedimentos para manter a consistência da classe.
 */
Thread::~Thread() {
    db<Thread>(TRC) << "~Thread() for Thread " << this->id() << "\n";

    delete(_context);
}

void Thread::sleep() {

    db<Thread>(TRC) << "Thread::sleep() called for thread " << this->id() << "\n";

    state(WAITING);
    _ready.remove(this->link()->object());
    yield();
}

void Thread::wakeup() {

    db<Thread>(TRC) << "Thread::wakeup() called for thread " << this->id() << "\n";

    state(READY);
    _ready.insert(this->link());
    yield();
}

__END_API
