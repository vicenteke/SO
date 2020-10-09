#include "system.h"
#include "thread.h"

__BEGIN_API

void System::init(void (*main)(void *)) {

    setvbuf (stdout, 0, _IONBF, 0);
    Thread::init(main);
}

__END_API
