#include "divrem.h"
#include "execu.h"

void divrem_clked()
{
    divisor_signed_clked = diven_p ? divisor_signed : divisor_signed_clked;
    dividend_signed_clked = diven_p ? dividend_signed : dividend_signed_clked;
    dividend_undivsigned_clked = diven_p ? dividend_undivsigned : dividend_undivsigned_clked;
    dividend_clked = diven_p ? dividend : dividend_clked;
    divisor_undivsigned_clked = diven_p ? divisor_undivsigned : divisor_undivsigned_clked;
    divorrem_clked = diven_p ? divorrem : divorrem_clked;
    divremcnt_clked = diven_p ? inik : 
                      diven_clked ? divremcnt_clked + 1 : 0;
    minued_clked =  diven_p ? iniminued : 
                    diven_clked ? nxt_minued : minued_clked;
    //
    q_clked = diven_p ? 0 : 
                diven_clked ? nxt_q : q_clked;
    quo_undivsigned_clked = div_end_p ? nxt_q : quo_undivsigned_clked;
    rem_undivsigned_clked = div_end_p ? nxtrem : rem_undivsigned_clked;
    div_end_p_clked = div_end_p ? 1 :
                      div_rsp_valid & div_rsp_ready ? 0 : div_end_p_clked ;
    div0_clked =  diven_p ? div0 : 
                  div_rsp_valid & div_rsp_ready ? 0 : div0_clked;
    ovflow_clked =  diven_p ? ovflow : 
                  div_rsp_valid & div_rsp_ready ? 0 : ovflow_clked;

    //must put at last line, to match hardware behavoir
    diven_clked = diven_p ? 1 : 
                  div_end_p ? 0 : diven_clked;

    divregidx_clked = divregidx;              
    divrden_clked = divrden;              

}