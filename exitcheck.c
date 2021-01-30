#include "exitcheck.h"
#include "fetch.h"
#include "memwb.h"
#include "ext_write_coderam.h"

int exitcheck()
{
    int main_return_event;

    halt_count = downloadper_clked ? 0 : 
                 (fetpc_clked ==pc) | fetch_stall ? halt_count_clked+1 : 0;

    main_return_event = (halt_count_clked>=100) | memwb_excephappen;
    return(main_return_event);
}