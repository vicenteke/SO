#include "main_class.h"

__BEGIN_API

Thread *Main::ThreadMain = 0;
Thread *Main::ping = 0;
Thread *Main::pong = 0;
CPU::Context *Main::mainContext;

//Static Declarations
Thread * Thread::_running = NULL;

__END_API
