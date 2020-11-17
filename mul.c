#include "execu.h"
#include "mul.h"

void mul()
{
    int tmp1, tmp2;
    BIT op1signed;
    BIT op2signed;
    long long mul_opd1, mul_opd2;

    mul_cmd_ready =1;


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
    mul64 = mul_opd1 * mul_opd2;

    if (mul_cmd_valid & mul_cmd_ready){
        mul_enable =1;
    }
    else{
        mul_enable =0;
    }

    if (MUL_RSPVALID_CYCLES==0){
        mul_rsp_valid = mul_enable;
        mulres = mul_low ? mul64 & 0x0ffffffff : (mul64>>32) & 0x0ffffffff ;
    }
    else if (mul_enable_clked & (mul_cycles_clked==MUL_RSPVALID_CYCLES)){
        mul_rsp_valid = 1;
        mulres = mul_low_clked ? mul64_clked & 0x0ffffffff : (mul64_clked>>32) & 0x0ffffffff ;
    }
    else{
        mul_rsp_valid = 0;
    }

    
}