#include "execu.h"
#include "mul.h"
#include "decode.h"

//same pipe as execu
void mul()
{
    int tmp1, tmp2;
    BIT op1signed;
    BIT op2signed;
    BIT mul_busy;
    long long mul_opd1, mul_opd2;



    tmp1 = (int) mul_cmd_opd1;
    tmp2 = (int) mul_cmd_opd2;

    switch(mul_cmd_opmode){
        case 1: //mul
        mul_low = 1;
        mul_opd1 = mul_cmd_opd1;
        mul_opd2 = mul_cmd_opd2;
        break;
        case 2:  //mulh
        mul_low = 0;
        mul_opd1 = tmp1;
        mul_opd2 = tmp2;
        break;
        case 4: //mulhsu
        mul_low = 0;
        mul_opd1 = tmp1;
        mul_opd2 = mul_cmd_opd2;
        break;
        case 8:  //mulhu
        mul_low = 0;
        mul_opd1 = mul_cmd_opd1;
        mul_opd2 = mul_cmd_opd2;
        break;
    }

    //mul_busy = (mul_enable_clked & (!mul_rsp_valid))  | (mul_rsp_valid & (!mul_rsp_ready));
    //mul_cmd_ready = !mul_busy;
    //same as sram, because need fixed 1 cycle to read
    mul_cmd_ready = (!mul_rsp_valid) | (mul_rsp_valid & mul_rsp_ready);

    if (mul_cmd_valid & mul_cmd_ready){
        mul_enable = !dec_mulh_fuse_clked; //1;
        mul64 = mul_opd1 * mul_opd2;
    }
    else{
        mul_enable =0;
        mul64 =mul64_clked;
    }

    // not support MUL_RSPVALID_CYCLES==0
    //if (MUL_RSPVALID_CYCLES==0){
    //    mul_rsp_valid = 1;
    //    mulres = dec_mulh_fuse_clked ? mul64_clked & 0x0ffffffff : 
    //             mul_low ? mul64 & 0x0ffffffff : (mul64>>32) & 0x0ffffffff ;
    //}
    //else 

    mulregidx = mul_cmd_valid & mul_cmd_ready ? mul_cmd_regidx : mulregidx_clked;
    mulrden   = mul_cmd_valid & mul_cmd_ready ? mul_cmd_rden   : mulrden_clked;

    mul_fused = mul_cmd_valid & mul_cmd_ready ? dec_mulh_fuse_clked : 
                mul_rsp_valid & mul_rsp_ready ? 0 : 
                                                mul_fused_clked;

    if (mul_fused_clked){
        mul_rsp_valid = 1;
        mulres = mul64_clked & 0x0ffffffff;
        mul_rsp_regidx = mulregidx_clked;
        mul_rsp_rden   = mulrden_clked;
    }
    else if (mul_enable_clked & (mul_cycles_clked>=MUL_RSPVALID_CYCLES)){
        mul_rsp_valid = 1;
        mulres = mul_low_clked ? mul64_clked & 0x0ffffffff : (mul64_clked>>32) & 0x0ffffffff ;
        mul_rsp_regidx = mulregidx_clked;
        mul_rsp_rden   = mulrden_clked;
    }
    else{
        mulres =0;  //not necessary, just for easy debug
        mul_rsp_valid = 0;
        mul_rsp_regidx = 0;
        mul_rsp_rden   = 0;
    }
    mul_rsp_read = mul_rsp_valid;
    mul_rsp_rdata = mulres;

    
}