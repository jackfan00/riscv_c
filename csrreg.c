#include "csrreg.h"
#include "clint.h"
#include "plic.h"
#include "decode.h"
#include "execu.h"
#include "fetch.h"
#include "memwb.h"

//case1:
// EXT interrupt(which is not precisely exception) affect the memwb stage immediately, it jump to interrupt handler address
// decode/execu/memwb stage flush their current instuction
//case2:
// other interrupt/exception event (which is precisely exception) not affect the memwb stage immediately, 
// decode/execu/memwb stage continue their current instuction, not flush their instrution
// the event propogate to memwb stage, then event is processed and jump to interrupt handler address,
// decode/execu/memwb stage flush their current instuction
// 
void csrreg()
{
    BIT csrreg_wen_mscratch;
    BIT csrreg_wen_mtvec;
    BIT csrreg_wen_mepc;
    BIT csrreg_wen_mie;
    BIT csrreg_wen_mcycle;
    BIT csrreg_wen_mcycleh;
    BIT csrreg_wen_minstret;
    BIT csrreg_wen_minstreth;
    BIT mtvecmode;
    BIT notstall;
    BIT notflush;


    //mtval
    mtval = memwb_load_misaligned | memwb_store_misaligned ? memwb_lsu_misaligned_adr : 
                memwb_dec_ilg ? memwb_IR : mtval_clked;

    //mscratch
    mscratch = csrreg_wen_mscratch ? csrreg_wdata : mscratch_clked;

    //mtvec
    mtvec = csrreg_wen_mtvec ? csrreg_wdata : mtvec_clked;
    mtvecmode = mtvec_clked&0x01;

    //intcause: priroity :external > software > timer
    intcause = mie_meie&EIP_clked ? 11:
               mie_msie&clint_msip_clked ? 3 :
               mie_mtie&clint_mtip_clked ? 7 : 0;

    excepcause = memwb_dec_ilg ? 2:
                memwb_break ? 3:
                memwb_load_misaligned ? 4:
                memwb_store_misaligned ? 6:
                memwb_ecall ? 11: 0;
    //mcause
    mcause = csr_inthappen ? (1<<31)|intcause :
             memwb_excephappen ? excepcause : mcause_clked;

    //mepc
    intpc = mtvecmode ? mtvec_clked+(intcause<<2) : mtvec_clked;
    exceppc = mtvec_clked;
    mepc = csr_inthappen ? intpc :
           memwb_excephappen ? exceppc :
           csrreg_wen_mepc ? csrreg_wdata : mepc_clked;

    //mstatus
    mstatusmie =  (csr_inthappen|memwb_excephappen) ? 0 : 
           memwb_mret ? mstatusmpie_clked : mstatusmie_clked;
    mstatusmpie = (csr_inthappen|memwb_excephappen) ? mstatusmie_clked :
            memwb_mret ? 1 : mstatusmpie_clked;

    //mie
    mie = csrreg_wen_mie ? csrreg_wdata : mie_clked;
    mie_meie = (mie >>11) & 0x01;
    mie_mtie = (mie >>7) & 0x01;
    mie_msie = (mie >>3) & 0x01;

    //mip, read-only
    mip = (EIP_clked<<11) | (clint_mtip_clked<<7) | (clint_msip_clked<<3);

    //interrupt mask
    csr_inthappen = (mie_meie&EIP_clked) | (mie_mtie&clint_mtip_clked) | (mie_msie&clint_msip_clked);

    mcycle =  csrreg_wen_mcycle  ? csrreg_wdata : mcycle_clked+1;
    mcycleh = csrreg_wen_mcycleh ? csrreg_wdata : 
                        (mcycle_clked==0xffffffff) ? mcycleh_clked+1 : mcycleh_clked;
    
    notstall = !(fetch_stall|dec_stall|exe_stall|memwb_stall);
    notflush = !(fetch_flush|dec_flush);

    minstret =  csrreg_wen_minstret  ? csrreg_wdata : 
                notstall & notflush ? minstret_clked+1 : minstret_clked;
    minstreth = csrreg_wen_minstreth ? csrreg_wdata : 
                        (minstret_clked==0xffffffff) ? minstreth_clked+1 : minstreth_clked;

    //
    csrv = csrreg_ren ? csr_rdata : 0;

    switch(csrreg_adr)
    {
        case 0xf11:
            csr_rdata = MVENDORID;
            break;
        case 0xf12:
            csr_rdata = MARCHID;
            break;
        case 0xf13:
            csr_rdata = MIMPID;
            break;
        case 0xf14:
            csr_rdata = MHARTID;
            break;
        case 0x300:
            csr_rdata =  ((0b0<<13)| (0b11<<11)| (0b0<<8)| (mstatusmpie_clked<<7)| (0b0<<4)| (mstatusmie_clked<<3)| 0b0); //mstatus;
            break;
        case 0x301:
            csr_rdata = MISA;
            break;
        //case 0x302:
        //    csr_rdata = medeleg;
        //    break;
        //case 0x303:
        //    csr_rdata = mideleg;
        //    break;
        case 0x304:
            csr_rdata = mie_clked;
            csrreg_wen_mie = csrreg_wen;
            break;
        case 0x305:
            csr_rdata = mtvec_clked;
            csrreg_wen_mtvec = csrreg_wen;
            break;
        //case 0x306:
        //    csr_rdata = mcounteren;
        //    break;
        case 0x340:
            csr_rdata = mscratch_clked;
            csrreg_wen_mscratch = csrreg_wen;
            break;
        case 0x341:
            csr_rdata = mepc_clked;
            csrreg_wen_mepc = csrreg_wen;
            break;
        case 0x342:
            csr_rdata = mcause_clked;
            break;
        case 0x343:
            csr_rdata = mtval_clked;
            break;
        case 0x344:
            csr_rdata = mip;
            break;
        case 0xb00:
            csr_rdata = mcycle_clked;
            csrreg_wen_mcycle = csrreg_wen;
            break;
        case 0xb02:
            csr_rdata = minstret_clked;
            csrreg_wen_minstret = csrreg_wen;
            break;
        case 0xb80:
            csr_rdata = mcycleh_clked;
            csrreg_wen_mcycleh = csrreg_wen;
            break;
        case 0xb82:
            csr_rdata = minstreth_clked;
            csrreg_wen_minstreth = csrreg_wen;
            break;
        case 0x7b0:
         //   csr_rdata = dcsr_clked;
            break;
        case 0x7b1:
         //   csr_rdata = dpc_clked;
            break;
        case 0x7b2:
         //   csr_rdata = dscratch_clked;
            break;
        default:
            csr_rdata =0;
            break;
    }

}