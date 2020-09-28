#include "system.h"

__BEGIN_API

void System::init() {

    //Disables std::cout to avoid errors
    setvbuf (stdout, 0, _IONBF, 0);
}

__END_API
