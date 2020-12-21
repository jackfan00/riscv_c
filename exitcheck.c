#include "exitcheck.h"
#include "fetch.h"
#include "ext_write_coderam.h"

int exitcheck()
{
    int main_return_event;

    halt_count = downloadper_clked ? 0 : 
                 (fetpc_clked ==pc) ? halt_count_clked+1 : 0;

    main_return_event = (halt_count_clked>=100);
    return(main_return_event);
}