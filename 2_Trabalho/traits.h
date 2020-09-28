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

//declaração da classe Traits
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
    static const bool error = false;   //Use ERR level
    static const bool warning = false; //Use WRN level
    static const bool info = false;    //Use INF level
    static const bool trace = true;    //Use TRC level
};

template<> struct Traits<System> : public Traits<void>
{
    static const bool debugged = true;
};

template<> struct Traits<Context> : public Traits<void>
{
    static const bool debugged = true;
};

template<> struct Traits<Thread> : public Traits<void>
{
    static const bool debugged = false;
};

template<> struct Traits<Main> : public Traits<void>
{
    static const bool debugged = true;
};

__END_API

#endif
