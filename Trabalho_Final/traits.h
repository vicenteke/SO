#ifndef traits_h
#define traits_h

//Não alterar as 3 declarações abaixo

#define __BEGIN_API             namespace SOLUTION {
#define __END_API               }
#define __USING_API            using namespace SOLUTION;

__BEGIN_API

//Classes' declarations
class CPU;
class Context;
class Thread;
class Debug;
class System;
class Main;
class Semaphore;
class Timer;

class List_Element_Rank;
namespace List_Elements {
    template<typename T, typename R>
    class Doubly_Linked_Ordered;
};

class Lists;
template<typename T,
          typename R,
          typename El,
          bool relative>
class Ordered_List;

//Class Traits declaration
template<typename T>
struct Traits {
    static const bool debugged = false;
};

template<> struct Traits<CPU>
{
    static const unsigned int STACK_SIZE = 64000; //Defines stack size
    static const bool debugged = true;
};

//Sets if debugging levels are active
//Each class can disable or enable it for itself through (bool) "debugged"
template<> struct Traits<Debug>: public Traits<void>
{
    static const bool error = true;
    static const bool warning = false;
    static const bool info = true;
    static const bool trace = true;
};

template<> struct Traits<System> : public Traits<void>
{
    static const bool debugged = false;
};

template<> struct Traits<Context> : public Traits<void>
{
    static const bool debugged = false;
};

template<> struct Traits<Thread> : public Traits<void>
{
    static const bool debugged = true;
};

template<> struct Traits<Main> : public Traits<void>
{
    static const bool debugged = false;
};

template<> struct Traits<Lists> : public Traits<void>
{
    static const bool debugged = false;
};

template<typename T, typename R, typename El, bool relative> struct Traits<Ordered_List<T, R, El, relative>> : public Traits<void>
{
    static const bool debugged = false;
};

template<> struct Traits<Semaphore> : public Traits<void>
{
    static const bool debugged = false;
};

template<> struct Traits<Timer> : public Traits<void>
{
    static const bool debugged = false;
    static const bool preemptive = true;
    static const unsigned int QUANTUM = 145000; // in us
};

__END_API

#endif
