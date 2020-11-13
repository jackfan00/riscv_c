#ifndef DECODE_H
#define DECODE_H

#include "reg.h"

//input
REG32 dec_rs2v_clked;
REG32 rs1v;
REG32 rs2v;
BIT   rs1en_ack;
BIT   rs2en_ack;
REG32 decpc_clked;
REG32 dec_alu_opd1_clked;
REG32 dec_alu_opd2_clked;
REG8  dec_rs1idx_clked;
REG8  dec_rs2idx_clked;
REG8  dec_rdidx_clked ;
BIT   dec_rs1en_clked ;
BIT   dec_rs2en_clked ;
BIT   dec_rden_clked  ;
BIT   dec_aluop_sub_clked;
BIT   dec_aluop_add_clked;
BIT   dec_aluop_sll_clked;
BIT   dec_aluop_slt_clked;
BIT   dec_aluop_sltu_clked;
BIT   dec_aluop_xor_clked;
BIT   dec_aluop_sra_clked;
BIT   dec_aluop_srl_clked;
BIT   dec_aluop_or_clked;
BIT   dec_aluop_and_clked;
BIT   dec_dec_ilg_clked;
BIT   dec_aluopimm_clked;
BIT   dec_aluop_clked;
BIT   dec_aluload_clked;
BIT   dec_alustore_clked;
BIT   dec_alujal_clked;
BIT   dec_alujalr_clked;
BIT   dec_alului_clked;
BIT   dec_aluauipc_clked;
BIT   dec_alubranch_clked;
BIT   dec_alumiscmem_clked;
BIT   dec_alusystem_clked;
BIT   dec_aluop_beq_clked;
BIT   dec_aluop_bne_clked;
BIT   dec_aluop_blt_clked;
BIT   dec_aluop_bge_clked;
BIT   dec_aluop_bltu_clked;
BIT   dec_aluop_bgeu_clked;
BIT   dec_aluop_lb_clked;
BIT   dec_aluop_lh_clked;
BIT   dec_aluop_lw_clked;
BIT   dec_aluop_lbu_clked;
BIT   dec_aluop_lhu_clked;
BIT   dec_aluop_sb_clked;
BIT   dec_aluop_sh_clked;
BIT   dec_aluop_sw_clked;

//output
REG32 real_rs1v;
REG32 real_rs2v;
REG8 depfifo_wadr_clked;
REG32 alu_opd1;
REG32 alu_opd2;
REG8 rs1idx;
REG8 rs2idx;
REG8 rdidx;
BIT rs1en;
BIT rs2en;
BIT rden;
BIT aluop_sub;
BIT aluop_add;
BIT aluop_sll;
BIT aluop_slt;
BIT aluop_sltu;
BIT aluop_xor;
BIT aluop_sra;
BIT aluop_srl;
BIT aluop_or;
BIT aluop_and;
BIT dec_ilg;
BIT aluopimm;
BIT aluop;
BIT aluload;
BIT alustore;
BIT alujal;
BIT alujalr;
BIT alului;
BIT aluauipc;
BIT alubranch;
BIT alumiscmem;
BIT alusystem;
BIT aluop_beq;
BIT aluop_bne;
BIT aluop_blt;
BIT aluop_bge;
BIT aluop_bltu;
BIT aluop_bgeu;
BIT aluop_lb;
BIT aluop_lh;
BIT aluop_lw;
BIT aluop_lbu;
BIT aluop_lhu;
BIT aluop_sb;
BIT aluop_sh;
BIT aluop_sw;
BIT dec_stall;


#endif // DECODE_H
