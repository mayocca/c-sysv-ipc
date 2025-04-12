#include "framework/foundation/init.h"
#include "framework/utils/logging.h"
#include "framework/utils/rand.h"

void framework_init(void)
{
    log0("Initializing framework");

    log0("Initializing random number generator");
    rand_init();

    log0("Framework initialized");
}
