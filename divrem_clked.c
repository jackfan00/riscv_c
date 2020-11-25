#include "divrem.h"

void divrem_clked()
{
    dividend_clked = diven_p ? dividend : dividend_clked;
    divisor_clked = diven_p ? divisor : divisor_clked;
    divorrem_clked = diven_p ? divorrem : divorrem_clked;
    divremcnt_clked = diven_p ? inik : 
                      diven_clked ? divremcnt_clked + 1 : 0;
    diven_clked = diven_p ? 1 : 
                  div_end_p ? 0 : diven_clked;
    //
    q_clked = nxt_q;
    quo_clked = div_end_p ? nxt_q : quo_clked;
    rem_clked = div_end_p ? nxtrem : rem_clked;
    div_end_p_clked = div_end_p ? 1 :
                      div_rsp_ready ? 0 : div_end_p_clked ;
}