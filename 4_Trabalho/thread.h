#ifndef thread_h
#define thread_h

#include "cpu.h"
#include "traits.h"
#include "debug.h"
#include "list.h"
#include <ctime>
#include <chrono>

__BEGIN_API

class Thread
{
protected:
    typedef CPU::Context Context;
public:

    typedef Ordered_List<Thread> Ready_Queue;

    // Thread State
    enum State {
        RUNNING,
        READY,
        FINISHING,
        SUSPENDED
    };

    /*
     * Construtor vazio. Necessário para inicialização, mas sem importância para a execução das Threads.
     */
    Thread() { }

    /*
     * Cria uma Thread passando um ponteiro para a função a ser executada
     * e os parâmetros passados para a função, que podem variar.
     * Cria o contexto da Thread.
     * PS: devido ao template, este método deve ser implementado neste mesmo arquivo .h
     */
    template<typename ... Tn>
    Thread(void (* entry)(Tn ...), Tn ... an);

    /*
     * Retorna a Thread que está em execução.
     */
    static Thread * running() { return _running; }

    /*
     * Método para trocar o contexto entre duas thread, a anterior (prev)
     * e a próxima (next).
     * Deve encapsular a chamada para a troca de contexto realizada pela class CPU.
     * Valor de retorno é negativo se houve erro, ou zero.
     */
    static int switch_context(Thread * prev, Thread * next);

    /*
     * Termina a thread.
     * exit_code é o código de término devolvido pela tarefa (ignorar agora, vai ser usado mais tarde).
     * Quando a thread encerra, o controle deve retornar à main.
     */
    void thread_exit (int exit_code);

    /*
     * Retorna o ID da thread.
     */
    int id();

    /*
     * Daspachante (disptacher) de threads.
     * Executa enquanto houverem threads do usuário.
     * Chama o escalonador para definir a próxima tarefa a ser executada.
     */
    static void dispatcher();

    /*
     * Realiza a inicialização da class Thread.
     * Cria as Threads main e dispatcher.
     */
    static void init(void (*main)(void *));


    /*
     * Devolve o processador para a thread dispatcher que irá escolher outra thread pronta
     * para ser executada.
     */
    static void yield();

    // Suspende a Thread até que resume() seja chamado
    void suspend();

    // Acorda uma Thread que estava suspensa
    void resume();

    // Este método deve suspender a thread em execução até que a thread “alvo” finalize. O inteiro
    // retornado por join() é o argumento recebido por thread_exit(), ou seja, exit_code (novo atributo
    // _exit_code necessário na classe Thread – pergunta: quando o atributo _exit_code deve ser
    // inicializado?). Como tratar a suspensão e o resumo de uma Thread?
    int join();

    /*
     * Destrutor de uma thread. Realiza todo os procedimentos para manter a consistência da classe.
     */
    ~Thread();

    /*
     * Qualquer outro método que você achar necessário para a solução.
     */

    Context * context() const {
        return _context;
    }

    void state(State s) {
        _state = s;
    }

    State state() const {
        return _state;
    }

    Ready_Queue::Element * link() {
        return &_link;
    }

    int exit_code() {
        return _exit_code;
    }

private:
    int _id;
    Context * volatile _context;
    inline static Thread * _running = NULL;

    static Thread _main;
    inline static CPU::Context _main_context;
    static Thread _dispatcher;
    inline static Ready_Queue _ready;
    Ready_Queue::Element _link;
    volatile State _state;

    int _exit_code;
    inline static Ready_Queue _suspended_queue;
    Thread * _suspended;

    inline static int _numberofthreads = 0;
};

template<typename ... Tn>
inline Thread::Thread(void (* entry)(Tn ...), Tn ... an) : _link(this, (std::chrono::duration_cast<std::chrono::microseconds>
        (std::chrono::high_resolution_clock::now().time_since_epoch()).count()))
{
    _id = _numberofthreads;
    _numberofthreads++;
    db<Thread>(TRC) << "Thread " << _id << " created\n";

    _context = new Context(entry, an...);
    _state = READY;
    Thread::_ready.insert(&_link);

    _suspended = NULL;
}

__END_API

#endif
