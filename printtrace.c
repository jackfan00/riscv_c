//
//This file is generated by program dumpvcd/dumpvcd.exe, dont modify it
//
#include <stdio.h>
#include "reg.h"
#include "fetch.h"
#include "decode.h"
#include "execu.h"
#include "memwb.h"
#include "regbus.h"
#include "codebus.h"
#include "databus.h"
#include "memwb_bus.h"
#include "mul.h"
#include "divrem.h"
#include "lif.h"
#include "dumpvars.h"
#include "rv16torv32.h"
#include "peri_write_coderam.h"

void printtrace(FILE * fp){
fprintfb(fp,"08b<<<\n",code_rspid_fifo[0]);
fprintfb(fp,"08b<<!\n",code_rspid_fifo[1]);
fprintfb(fp,"08b<<@\n",data_rspid_fifo[0]);
fprintfb(fp,"08b<<#\n",data_rspid_fifo[1]);
fprintfb(fp,"32b<<$\n",clockcnt);
fprintfb(fp,"32b<<>\n",regsarray[0]);
fprintfb(fp,"32b<<^\n",regsarray[1]);
fprintfb(fp,"32b<<&\n",regsarray[2]);
fprintfb(fp,"32b<<*\n",regsarray[3]);
fprintfb(fp,"32b<<|\n",regsarray[4]);
fprintfb(fp,"32b<!<\n",regsarray[5]);
fprintfb(fp,"32b<!!\n",regsarray[6]);
fprintfb(fp,"32b<!@\n",regsarray[7]);
fprintfb(fp,"32b<!#\n",regsarray[8]);
fprintfb(fp,"32b<!$\n",regsarray[9]);
fprintfb(fp,"32b<!>\n",regsarray[10]);
fprintfb(fp,"32b<!^\n",regsarray[11]);
fprintfb(fp,"32b<!&\n",regsarray[12]);
fprintfb(fp,"32b<!*\n",regsarray[13]);
fprintfb(fp,"32b<!|\n",regsarray[14]);
fprintfb(fp,"32b<@<\n",regsarray[15]);
fprintfb(fp,"32b<@!\n",regsarray[16]);
fprintfb(fp,"32b<@@\n",regsarray[17]);
fprintfb(fp,"32b<@#\n",regsarray[18]);
fprintfb(fp,"32b<@$\n",regsarray[19]);
fprintfb(fp,"32b<@>\n",regsarray[20]);
fprintfb(fp,"32b<@^\n",regsarray[21]);
fprintfb(fp,"32b<@&\n",regsarray[22]);
fprintfb(fp,"32b<@*\n",regsarray[23]);
fprintfb(fp,"32b<@|\n",regsarray[24]);
fprintfb(fp,"32b<#<\n",regsarray[25]);
fprintfb(fp,"32b<#!\n",regsarray[26]);
fprintfb(fp,"32b<#@\n",regsarray[27]);
fprintfb(fp,"32b<##\n",regsarray[28]);
fprintfb(fp,"32b<#$\n",regsarray[29]);
fprintfb(fp,"32b<#>\n",regsarray[30]);
fprintfb(fp,"32b<#^\n",regsarray[31]);
fprintfb(fp,"32b<#&\n",ras_stack[0]);
fprintfb(fp,"32b<#*\n",ras_stack[1]);
fprintfb(fp,"32b<#|\n",ras_stack[2]);
fprintfb(fp,"32b<$<\n",ras_stack[3]);
fprintfb(fp,"32b<$!\n",ras_stack[4]);
fprintfb(fp,"32b<$@\n",ras_stack[5]);
fprintfb(fp,"32b<$#\n",ras_stack[6]);
fprintfb(fp,"32b<$$\n",ras_stack[7]);
fprintfb(fp,"08b<$>\n",ras_sp);
fprintf(fp,"%d<$^\n",fetch_stall);
fprintf(fp,"%d<$&\n",ifu2mem_rsp_valid);
fprintfb(fp,"32b<$*\n",ifu2mem_rsp_rdata);
fprintfb(fp,"16b<$|\n",memIR_hi16_clked);
fprintf(fp,"%d<><\n",fetch_flush);
fprintfb(fp,"32b<>!\n",fetchIR_clked);
fprintfb(fp,"32b<>@\n",fetpc_clked);
fprintfb(fp,"32b<>#\n",flush_pc);
fprintf(fp,"%d<>$\n",ifu2mem_cmd_ready);
fprintfb(fp,"32b<>>\n",rs1v);
fprintf(fp,"%d<>^\n",branchjmp_hipart_clked);
fprintf(fp,"%d<>&\n",new_midnxtpc_part2_fg_clked);
fprintf(fp,"%d<>*\n",fet_rs1en_ack);
fprintfb(fp,"32b<>|\n",fet_rs1v);
fprintf(fp,"%d<^<\n",fet_predict_jmp_clked);
fprintf(fp,"%d<^!\n",fet_ir16_clked);
fprintf(fp,"%d<^@\n",firstinst_clked);
fprintfb(fp,"08b<^#\n",remain_ir16s_clked);
fprintfb(fp,"32b<^$\n",ifu2mem_cmd_adr_clked);
fprintf(fp,"%d<^>\n",ifu2mem_rsp_ready);
fprintfb(fp,"16b<^^\n",memIR_hi16);
fprintfb(fp,"32b<^&\n",fetchIR);
fprintfb(fp,"32b<^*\n",pc);
fprintf(fp,"%d<^|\n",ifu2mem_cmd_valid);
fprintf(fp,"%d<&<\n",ifu2mem_cmd_read);
fprintfb(fp,"32b<&!\n",ifu2mem_cmd_adr);
fprintfb(fp,"08b<&@\n",ifu2mem_cmd_rwbyte);
fprintf(fp,"%d<&#\n",branchjmp);
fprintf(fp,"%d<&$\n",predict_en);
fprintf(fp,"%d<&>\n",fet_predict_jmp);
fprintfb(fp,"32b<&^\n",branchjmp_pc);
fprintf(fp,"%d<&&\n",fet_rs1en);
fprintfb(fp,"08b<&*\n",fet_rs1idx);
fprintfb(fp,"08b<&|\n",fet_rdidx);
fprintf(fp,"%d<*<\n",branchjmp_hipart);
fprintf(fp,"%d<*!\n",new_midnxtpc_part2_fg);
fprintf(fp,"%d<*@\n",fet_ras_pop);
fprintf(fp,"%d<*#\n",fet_ir16);
fprintfb(fp,"08b<*$\n",remain_ir16s);
fprintfb(fp,"32b<*>\n",memIR);
fprintfb(fp,"32b<*^\n",memIR32);
fprintfb(fp,"16b<*&\n",memIR16);
fprintfb(fp,"08b<**\n",irlsb10);
fprintfb(fp,"08b<*|\n",iroffset);
fprintfb(fp,"32b<|<\n",nxtpc);
fprintfb(fp,"32b<|!\n",dec_rs2v_clked);
fprintfb(fp,"32b<|@\n",rs1v);
fprintfb(fp,"32b<|#\n",rs2v);
fprintf(fp,"%d<|$\n",  rs1en_ack);
fprintf(fp,"%d<|>\n",  rs2en_ack);
fprintfb(fp,"32b<|^\n",decpc_clked);
fprintfb(fp,"32b<|&\n",dec_alu_opd1_clked);
fprintfb(fp,"32b<|*\n",dec_alu_opd2_clked);
fprintfb(fp,"08b<||\n", dec_rs1idx_clked);
fprintfb(fp,"08b!<<\n", dec_rs2idx_clked);
fprintfb(fp,"08b!<!\n", dec_rdidx_clked );
fprintf(fp,"%d!<@\n",  dec_rs1en_clked );
fprintf(fp,"%d!<#\n",  dec_rs2en_clked );
fprintf(fp,"%d!<$\n",  dec_rden_clked  );
fprintf(fp,"%d!<>\n",  dec_aluop_sub_clked);
fprintf(fp,"%d!<^\n",  dec_aluop_add_clked);
fprintf(fp,"%d!<&\n",  dec_aluop_sll_clked);
fprintf(fp,"%d!<*\n",  dec_aluop_slt_clked);
fprintf(fp,"%d!<|\n",  dec_aluop_sltu_clked);
fprintf(fp,"%d!!<\n",  dec_aluop_xor_clked);
fprintf(fp,"%d!!!\n",  dec_aluop_sra_clked);
fprintf(fp,"%d!!@\n",  dec_aluop_srl_clked);
fprintf(fp,"%d!!#\n",  dec_aluop_or_clked);
fprintf(fp,"%d!!$\n",  dec_aluop_and_clked);
fprintf(fp,"%d!!>\n",  dec_dec_ilg_clked);
fprintf(fp,"%d!!^\n",  dec_aluopimm_clked);
fprintf(fp,"%d!!&\n",  dec_aluop_clked);
fprintf(fp,"%d!!*\n",  dec_aluload_clked);
fprintf(fp,"%d!!|\n",  dec_alustore_clked);
fprintf(fp,"%d!@<\n",  dec_alujal_clked);
fprintf(fp,"%d!@!\n",  dec_alujalr_clked);
fprintf(fp,"%d!@@\n",  dec_alului_clked);
fprintf(fp,"%d!@#\n",  dec_aluauipc_clked);
fprintf(fp,"%d!@$\n",  dec_alubranch_clked);
fprintf(fp,"%d!@>\n",  dec_alumiscmem_clked);
fprintf(fp,"%d!@^\n",  dec_alusystem_clked);
fprintf(fp,"%d!@&\n",  dec_aluop_beq_clked);
fprintf(fp,"%d!@*\n",  dec_aluop_bne_clked);
fprintf(fp,"%d!@|\n",  dec_aluop_blt_clked);
fprintf(fp,"%d!#<\n",  dec_aluop_bge_clked);
fprintf(fp,"%d!#!\n",  dec_aluop_bltu_clked);
fprintf(fp,"%d!#@\n",  dec_aluop_bgeu_clked);
fprintf(fp,"%d!##\n",  dec_aluop_lb_clked);
fprintf(fp,"%d!#$\n",  dec_aluop_lh_clked);
fprintf(fp,"%d!#>\n",  dec_aluop_lw_clked);
fprintf(fp,"%d!#^\n",  dec_aluop_lbu_clked);
fprintf(fp,"%d!#&\n",  dec_aluop_lhu_clked);
fprintf(fp,"%d!#*\n",  dec_aluop_sb_clked);
fprintf(fp,"%d!#|\n",  dec_aluop_sh_clked);
fprintf(fp,"%d!$<\n",  dec_aluop_sw_clked);
fprintf(fp,"%d!$!\n",  dec_aluop_mul_clked);
fprintf(fp,"%d!$@\n",  dec_aluop_mulh_clked);
fprintf(fp,"%d!$#\n",  dec_aluop_mulhsu_clked);
fprintf(fp,"%d!$$\n",  dec_aluop_mulhu_clked);
fprintf(fp,"%d!$>\n",  dec_aluop_div_clked);
fprintf(fp,"%d!$^\n",  dec_aluop_divu_clked);
fprintf(fp,"%d!$&\n",  dec_aluop_rem_clked);
fprintf(fp,"%d!$*\n",  dec_aluop_remu_clked);
fprintf(fp,"%d!$|\n",  dec_ras_push_clked);
fprintf(fp,"%d!><\n",  dec_predict_jmp_clked);
fprintfb(fp,"32b!>!\n",cti_pc_clked);
fprintf(fp,"%d!>@\n",dec_jalr_pdict_fail_clked);
fprintf(fp,"%d!>#\n",dec_mulh_fuse_clked);
fprintfb(fp,"32b!>$\n",real_rs1v);
fprintfb(fp,"32b!>>\n",real_rs2v);
fprintfb(fp,"08b!>^\n",depfifo_wadr_clked);
fprintfb(fp,"32b!>&\n",alu_opd1);
fprintfb(fp,"32b!>*\n",alu_opd2);
fprintfb(fp,"08b!>|\n",rs1idx);
fprintfb(fp,"08b!^<\n",rs2idx);
fprintfb(fp,"08b!^!\n",rdidx);
fprintf(fp,"%d!^@\n",rs1en);
fprintf(fp,"%d!^#\n",rs2en);
fprintf(fp,"%d!^$\n",rden);
fprintf(fp,"%d!^>\n",aluop_sub);
fprintf(fp,"%d!^^\n",aluop_add);
fprintf(fp,"%d!^&\n",aluop_sll);
fprintf(fp,"%d!^*\n",aluop_slt);
fprintf(fp,"%d!^|\n",aluop_sltu);
fprintf(fp,"%d!&<\n",aluop_xor);
fprintf(fp,"%d!&!\n",aluop_sra);
fprintf(fp,"%d!&@\n",aluop_srl);
fprintf(fp,"%d!&#\n",aluop_or);
fprintf(fp,"%d!&$\n",aluop_and);
fprintf(fp,"%d!&>\n",dec_ilg);
fprintf(fp,"%d!&^\n",aluopimm);
fprintf(fp,"%d!&&\n",aluop);
fprintf(fp,"%d!&*\n",aluload);
fprintf(fp,"%d!&|\n",alustore);
fprintf(fp,"%d!*<\n",alujal);
fprintf(fp,"%d!*!\n",alujalr);
fprintf(fp,"%d!*@\n",alului);
fprintf(fp,"%d!*#\n",aluauipc);
fprintf(fp,"%d!*$\n",alubranch);
fprintf(fp,"%d!*>\n",alumiscmem);
fprintf(fp,"%d!*^\n",alusystem);
fprintf(fp,"%d!*&\n",aluop_beq);
fprintf(fp,"%d!**\n",aluop_bne);
fprintf(fp,"%d!*|\n",aluop_blt);
fprintf(fp,"%d!|<\n",aluop_bge);
fprintf(fp,"%d!|!\n",aluop_bltu);
fprintf(fp,"%d!|@\n",aluop_bgeu);
fprintf(fp,"%d!|#\n",aluop_lb);
fprintf(fp,"%d!|$\n",aluop_lh);
fprintf(fp,"%d!|>\n",aluop_lw);
fprintf(fp,"%d!|^\n",aluop_lbu);
fprintf(fp,"%d!|&\n",aluop_lhu);
fprintf(fp,"%d!|*\n",aluop_sb);
fprintf(fp,"%d!||\n",aluop_sh);
fprintf(fp,"%d@<<\n",aluop_sw);
fprintf(fp,"%d@<!\n",aluop_mul);
fprintf(fp,"%d@<@\n",aluop_mulh);
fprintf(fp,"%d@<#\n",aluop_mulhsu);
fprintf(fp,"%d@<$\n",aluop_mulhu);
fprintf(fp,"%d@<>\n",aluop_div);
fprintf(fp,"%d@<^\n",aluop_divu);
fprintf(fp,"%d@<&\n",aluop_rem);
fprintf(fp,"%d@<*\n",aluop_remu);
fprintf(fp,"%d@<|\n",dec_lif_cmd);
fprintfb(fp,"08b@!<\n",dec_lif_id);
fprintf(fp,"%d@!!\n",dec_stall);
fprintf(fp,"%d@!@\n",dec_ras_push);
fprintfb(fp,"32b@!#\n",cti_pc);
fprintf(fp,"%d@!$\n",dec_jalr_pdict_fail);
fprintf(fp,"%d@!>\n",dec_mulh_fuse);
fprintf(fp,"%d@!^\n",dec_raw_exe_rs1);
fprintf(fp,"%d@!&\n",dec_raw_exe_rs2);
fprintf(fp,"%d@!*\n",dec_rwaw_lif_rs1);
fprintf(fp,"%d@!|\n",dec_rwaw_lif_rs2);
fprintf(fp,"%d@@<\n",dec_rwaw_lif_rd);
fprintf(fp,"%d@@!\n",dec_raw_memwb_rs1);
fprintf(fp,"%d@@@\n",dec_raw_memwb_rs2);
fprintf(fp,"%d@@#\n",exe_res_valid_clked);
fprintfb(fp,"32b@@$\n",exe_res_clked      );
fprintf(fp,"%d@@>\n",exe_rden_clked      );
fprintfb(fp,"08b@@^\n",exe_rdidx_clked     );
fprintf(fp,"%d@@&\n",exe_aluload_clked);
fprintf(fp,"%d@@*\n",exe_lh_clked);
fprintf(fp,"%d@@|\n",exe_lhu_clked);
fprintf(fp,"%d@#<\n",exe_lb_clked);
fprintf(fp,"%d@#!\n",exe_lbu_clked);
fprintf(fp,"%d@#@\n",exe_lw_clked);
fprintf(fp,"%d@##\n",exe_dec_ilg_clked);
fprintf(fp,"%d@#$\n",lsu2mem_rsp_valid);
fprintf(fp,"%d@#>\n",lsu2mem_rsp_ready);
fprintf(fp,"%d@#^\n",lsu2mem_rsp_err);
fprintfb(fp,"32b@#&\n",lsu2mem_rsp_rdata);
fprintf(fp,"%d@#*\n",exe_mulh_fuse_clked);
fprintf(fp,"%d@#|\n",exe_res_valid);
fprintfb(fp,"32b@$<\n",exe_res           );
fprintf(fp,"%d@$!\n",exe_stall);
fprintf(fp,"%d@$@\n",lsu_misaligned);
fprintf(fp,"%d@$#\n",lsu2mem_cmd_valid);
fprintf(fp,"%d@$$\n",lsu2mem_cmd_ready);
fprintf(fp,"%d@$>\n",lsu2mem_cmd_read);
fprintfb(fp,"32b@$^\n",lsu2mem_cmd_adr);
fprintfb(fp,"32b@$&\n",lsu2mem_cmd_wdata);
fprintfb(fp,"08b@$*\n",lsu2mem_cmd_rwbyte);
fprintf(fp,"%d@$|\n",exe_branch_pdict_fail);
fprintf(fp,"%d@><\n",exe_rden);
fprintfb(fp,"32b@>!\n",exe_branch_pdict_fail_pc);
fprintf(fp,"%d@>@\n",exe_jalr_pdict_fail);
fprintfb(fp,"32b@>#\n",exe_jalr_pc);
fprintf(fp,"%d@>$\n",mul_cmd_valid);
fprintfb(fp,"32b@>>\n",mul_cmd_opd1);
fprintfb(fp,"32b@>^\n",mul_cmd_opd2);
fprintfb(fp,"08b@>&\n",mul_cmd_opmode);
fprintf(fp,"%d@>*\n",div_cmd_valid);
fprintfb(fp,"32b@>|\n",div_cmd_opd1);
fprintfb(fp,"32b@^<\n",div_cmd_opd2);
fprintfb(fp,"08b@^!\n",div_cmd_opmode);
fprintf(fp,"%d@^@\n",div_cmd_ready);
fprintf(fp,"%d@^#\n",exe_branch_taken);
fprintf(fp,"%d@^$\n",lsu_stall);
fprintf(fp,"%d@^>\n",mul_stall);
fprintf(fp,"%d@^^\n",div_stall);
fprintfb(fp,"32b@^&\n",memwb_wdata);
fprintfb(fp,"08b@^*\n",memwb_idx);
fprintf(fp,"%d@^|\n",memwb_valid);
fprintf(fp,"%d@&<\n",memwb_ready);
fprintf(fp,"%d@&!\n",memwb_stall);
fprintf(fp,"%d@&@\n",lsu2mem_rsp_valid);
fprintf(fp,"%d@&#\n",lsu2mem_rsp_ready);
fprintfb(fp,"32b@&$\n",lsu2mem_rsp_rdata);
fprintfb(fp,"08b@&>\n",lsu2mem_rsp_adr);
fprintf(fp,"%d@&^\n",mul_rsp_valid);
fprintf(fp,"%d@&&\n",mul_rsp_ready);
fprintfb(fp,"08b@&*\n",mul_rsp_adr);
fprintfb(fp,"08b@&|\n",memwb_id);
fprintf(fp,"%d@*<\n",i_regwbus_grt_clked[0]);
fprintf(fp,"%d@*!\n",i_regwbus_grt_clked[1]);
fprintf(fp,"%d@*@\n",i_regwbus_cmd_valid[0]);
fprintf(fp,"%d@*#\n",i_regwbus_cmd_valid[1]);
fprintfb(fp,"08b@*$\n",i_regwbus_cmd_id[0]);
fprintfb(fp,"08b@*>\n",i_regwbus_cmd_id[1]);
fprintfb(fp,"32b@*^\n",i_regwbus_cmd_adr[0]);
fprintfb(fp,"32b@*&\n",i_regwbus_cmd_adr[1]);
fprintfb(fp,"32b@**\n",i_regwbus_cmd_wdata[0]);
fprintfb(fp,"32b@*|\n",i_regwbus_cmd_wdata[1]);
fprintf(fp,"%d@|<\n",i_regwbus_cmd_ready[0]);
fprintf(fp,"%d@|!\n",i_regwbus_cmd_ready[1]);
fprintf(fp,"%d@|@\n",i_rs1bus_grt_clked[0]);
fprintf(fp,"%d@|#\n",i_rs1bus_grt_clked[1]);
fprintf(fp,"%d@|$\n",i_rs1bus_cmd_valid[0]);
fprintf(fp,"%d@|>\n",i_rs1bus_cmd_valid[1]);
fprintf(fp,"%d@|^\n",i_rs1bus_cmd_ready[0]);
fprintf(fp,"%d@|&\n",i_rs1bus_cmd_ready[1]);
fprintfb(fp,"32b@|*\n",i_rs1bus_cmd_adr[0]);
fprintfb(fp,"32b@||\n",i_rs1bus_cmd_adr[1]);
fprintf(fp,"%d#<<\n",i_rs1bus_rsp_ready[0]);
fprintf(fp,"%d#<!\n",i_rs1bus_rsp_ready[1]);
fprintf(fp,"%d#<@\n",i_rs1bus_rsp_err[0]);
fprintf(fp,"%d#<#\n",i_rs1bus_rsp_err[1]);
fprintf(fp,"%d#<$\n",i_rs2bus_grt_clked[0]);
fprintf(fp,"%d#<>\n",i_rs2bus_grt_clked[1]);
fprintf(fp,"%d#<^\n",i_rs2bus_cmd_valid[0]);
fprintf(fp,"%d#<&\n",i_rs2bus_cmd_valid[1]);
fprintf(fp,"%d#<*\n",i_rs2bus_cmd_ready[0]);
fprintf(fp,"%d#<|\n",i_rs2bus_cmd_ready[1]);
fprintfb(fp,"32b#!<\n",i_rs2bus_cmd_adr[0]);
fprintfb(fp,"32b#!!\n",i_rs2bus_cmd_adr[1]);
fprintf(fp,"%d#!@\n",i_rs2bus_rsp_ready[0]);
fprintf(fp,"%d#!#\n",i_rs2bus_rsp_ready[1]);
fprintf(fp,"%d#!$\n",i_rs2bus_rsp_err[0]);
fprintf(fp,"%d#!>\n",i_rs2bus_rsp_err[1]);
fprintf(fp,"%d#!^\n",i_regwbus_grt[0]);
fprintf(fp,"%d#!&\n",i_regwbus_grt[1]);
fprintf(fp,"%d#!*\n",regw_cs);
fprintf(fp,"%d#!|\n",regw_we);
fprintfb(fp,"32b#@<\n",regw_wdat);
fprintfb(fp,"32b#@!\n",regw_adr);
fprintfb(fp,"08b#@@\n",regw_id);
fprintf(fp,"%d#@#\n",i_rs1bus_grt[0]);
fprintf(fp,"%d#@$\n",i_rs1bus_grt[1]);
fprintf(fp,"%d#@>\n",i_rs1bus_rsp_valid[0]);
fprintf(fp,"%d#@^\n",i_rs1bus_rsp_valid[1]);
fprintfb(fp,"32b#@&\n",i_rs1bus_rsp_rdata[0]);
fprintfb(fp,"32b#@*\n",i_rs1bus_rsp_rdata[1]);
fprintf(fp,"%d#@|\n",i_rs2bus_grt[0]);
fprintf(fp,"%d##<\n",i_rs2bus_grt[1]);
fprintf(fp,"%d##!\n",i_rs2bus_rsp_valid[0]);
fprintf(fp,"%d##@\n",i_rs2bus_rsp_valid[1]);
fprintfb(fp,"32b###\n",i_rs2bus_rsp_rdata[0]);
fprintfb(fp,"32b##$\n",i_rs2bus_rsp_rdata[1]);
fprintf(fp,"%d##>\n",i_codebus_grt_clked[0]);
fprintf(fp,"%d##^\n",i_codebus_grt_clked[1]);
fprintf(fp,"%d##&\n",i_codebus_grt_clked[2]);
fprintf(fp,"%d##*\n",i_codebus_grt_clked[3]);
fprintf(fp,"%d##|\n",i_codebus_cmd_valid[0]);
fprintf(fp,"%d#$<\n",i_codebus_cmd_valid[1]);
fprintf(fp,"%d#$!\n",i_codebus_cmd_valid[2]);
fprintf(fp,"%d#$@\n",i_codebus_cmd_valid[3]);
fprintf(fp,"%d#$#\n",i_codebus_cmd_read[0]);
fprintf(fp,"%d#$$\n",i_codebus_cmd_read[1]);
fprintf(fp,"%d#$>\n",i_codebus_cmd_read[2]);
fprintf(fp,"%d#$^\n",i_codebus_cmd_read[3]);
fprintfb(fp,"32b#$&\n",i_codebus_cmd_adr[0]);
fprintfb(fp,"32b#$*\n",i_codebus_cmd_adr[1]);
fprintfb(fp,"32b#$|\n",i_codebus_cmd_adr[2]);
fprintfb(fp,"32b#><\n",i_codebus_cmd_adr[3]);
fprintfb(fp,"32b#>!\n",i_codebus_cmd_wdata[0]);
fprintfb(fp,"32b#>@\n",i_codebus_cmd_wdata[1]);
fprintfb(fp,"32b#>#\n",i_codebus_cmd_wdata[2]);
fprintfb(fp,"32b#>$\n",i_codebus_cmd_wdata[3]);
fprintfb(fp,"08b#>>\n",i_codebus_cmd_rwbyte[0]);
fprintfb(fp,"08b#>^\n",i_codebus_cmd_rwbyte[1]);
fprintfb(fp,"08b#>&\n",i_codebus_cmd_rwbyte[2]);
fprintfb(fp,"08b#>*\n",i_codebus_cmd_rwbyte[3]);
fprintf(fp,"%d#>|\n",o_codebus_cmd_ready);
fprintf(fp,"%d#^<\n",code_rspid_fifo_full_clked);
fprintf(fp,"%d#^!\n",code_rspid_fifo_empty_clked);
fprintfb(fp,"08b#^@\n",r_code_rspid);
fprintf(fp,"%d#^#\n",o_codebus_rsp_valid);
fprintf(fp,"%d#^$\n",o_codebus_rsp_err);
fprintfb(fp,"32b#^>\n",o_codebus_rsp_rdata);
fprintf(fp,"%d#^^\n",i_codebus_rsp_ready[0]);
fprintf(fp,"%d#^&\n",i_codebus_rsp_ready[1]);
fprintf(fp,"%d#^*\n",i_codebus_rsp_ready[2]);
fprintf(fp,"%d#^|\n",i_codebus_rsp_ready[3]);
fprintfb(fp,"32b#&<\n",code_rspid_fifo_wadr_clked);
fprintfb(fp,"32b#&!\n",code_rspid_fifo_radr_clked);
fprintfb(fp,"32b#&@\n",coderam_rdat);
fprintf(fp,"%d#&#\n",coderam_cs_clked);
fprintf(fp,"%d#&$\n",coderam_we_clked);
fprintf(fp,"%d#&>\n",i_codebus_grt[0]);
fprintf(fp,"%d#&^\n",i_codebus_grt[1]);
fprintf(fp,"%d#&&\n",i_codebus_grt[2]);
fprintf(fp,"%d#&*\n",i_codebus_grt[3]);
fprintf(fp,"%d#&|\n",o_codebus_cmd_valid);
fprintf(fp,"%d#*<\n",o_codebus_cmd_read);
fprintfb(fp,"32b#*!\n",o_codebus_cmd_adr);
fprintfb(fp,"32b#*@\n",o_codebus_cmd_wdata);
fprintfb(fp,"08b#*#\n",o_codebus_cmd_rwbyte);
fprintf(fp,"%d#*$\n",i_codebus_cmd_ready[0]);
fprintf(fp,"%d#*>\n",i_codebus_cmd_ready[1]);
fprintf(fp,"%d#*^\n",i_codebus_cmd_ready[2]);
fprintf(fp,"%d#*&\n",i_codebus_cmd_ready[3]);
fprintf(fp,"%d#**\n",code_rspid_fifo_wen);
fprintf(fp,"%d#*|\n",code_rspid_fifo_ren);
fprintf(fp,"%d#|<\n",i_codebus_rsp_valid[0]);
fprintf(fp,"%d#|!\n",i_codebus_rsp_valid[1]);
fprintf(fp,"%d#|@\n",i_codebus_rsp_valid[2]);
fprintf(fp,"%d#|#\n",i_codebus_rsp_valid[3]);
fprintf(fp,"%d#|$\n",i_codebus_rsp_err[0]);
fprintf(fp,"%d#|>\n",i_codebus_rsp_err[1]);
fprintf(fp,"%d#|^\n",i_codebus_rsp_err[2]);
fprintf(fp,"%d#|&\n",i_codebus_rsp_err[3]);
fprintfb(fp,"32b#|*\n",i_codebus_rsp_rdata[0]);
fprintfb(fp,"32b#||\n",i_codebus_rsp_rdata[1]);
fprintfb(fp,"32b$<<\n",i_codebus_rsp_rdata[2]);
fprintfb(fp,"32b$<!\n",i_codebus_rsp_rdata[3]);
fprintf(fp,"%d$<@\n",o_codebus_rsp_ready);
fprintfb(fp,"08b$<#\n",w_code_rspid);
fprintfb(fp,"32b$<$\n",code_rspid_fifo_wadr);
fprintfb(fp,"32b$<>\n",code_rspid_fifo_radr);
fprintfb(fp,"32b$<^\n",coderam_adr);
fprintf(fp,"%d$<&\n",coderam_cs);
fprintfb(fp,"32b$<*\n",coderam_wdat);
fprintf(fp,"%d$<|\n",coderam_we);
fprintfb(fp,"08b$!<\n",coderam_bmask);
fprintf(fp,"%d$!!\n",coderam_wrsp_per_clked);
fprintf(fp,"%d$!@\n",coderam_rrsp_per_clked);
fprintf(fp,"%d$!#\n",coderam_wrsp_valid);
fprintf(fp,"%d$!$\n",coderam_rrsp_valid);
fprintfb(fp,"08b$!>\n",coderam_cmdready_cycles_clked);
fprintfb(fp,"08b$!^\n",coderam_rspvalid_cycles_clked);
fprintf(fp,"%d$!&\n",i_databus_grt_clked[0]);
fprintf(fp,"%d$!*\n",i_databus_grt_clked[1]);
fprintf(fp,"%d$!|\n",i_databus_grt_clked[2]);
fprintf(fp,"%d$@<\n",i_databus_grt_clked[3]);
fprintf(fp,"%d$@!\n",i_databus_cmd_valid[0]);
fprintf(fp,"%d$@@\n",i_databus_cmd_valid[1]);
fprintf(fp,"%d$@#\n",i_databus_cmd_valid[2]);
fprintf(fp,"%d$@$\n",i_databus_cmd_valid[3]);
fprintf(fp,"%d$@>\n",i_databus_cmd_read[0]);
fprintf(fp,"%d$@^\n",i_databus_cmd_read[1]);
fprintf(fp,"%d$@&\n",i_databus_cmd_read[2]);
fprintf(fp,"%d$@*\n",i_databus_cmd_read[3]);
fprintfb(fp,"32b$@|\n",i_databus_cmd_adr[0]);
fprintfb(fp,"32b$#<\n",i_databus_cmd_adr[1]);
fprintfb(fp,"32b$#!\n",i_databus_cmd_adr[2]);
fprintfb(fp,"32b$#@\n",i_databus_cmd_adr[3]);
fprintfb(fp,"32b$##\n",i_databus_cmd_wdata[0]);
fprintfb(fp,"32b$#$\n",i_databus_cmd_wdata[1]);
fprintfb(fp,"32b$#>\n",i_databus_cmd_wdata[2]);
fprintfb(fp,"32b$#^\n",i_databus_cmd_wdata[3]);
fprintfb(fp,"08b$#&\n",i_databus_cmd_rwbyte[0]);
fprintfb(fp,"08b$#*\n",i_databus_cmd_rwbyte[1]);
fprintfb(fp,"08b$#|\n",i_databus_cmd_rwbyte[2]);
fprintfb(fp,"08b$$<\n",i_databus_cmd_rwbyte[3]);
fprintf(fp,"%d$$!\n",o_databus_cmd_ready);
fprintf(fp,"%d$$@\n",data_rspid_fifo_full_clked);
fprintf(fp,"%d$$#\n",data_rspid_fifo_empty_clked);
fprintfb(fp,"08b$$$\n",r_data_rspid);
fprintf(fp,"%d$$>\n",o_databus_rsp_valid);
fprintf(fp,"%d$$^\n",o_databus_rsp_err);
fprintfb(fp,"32b$$&\n",o_databus_rsp_rdata);
fprintf(fp,"%d$$*\n",i_databus_rsp_ready[0]);
fprintf(fp,"%d$$|\n",i_databus_rsp_ready[1]);
fprintf(fp,"%d$><\n",i_databus_rsp_ready[2]);
fprintf(fp,"%d$>!\n",i_databus_rsp_ready[3]);
fprintfb(fp,"32b$>@\n",data_rspid_fifo_wadr_clked);
fprintfb(fp,"32b$>#\n",data_rspid_fifo_radr_clked);
fprintfb(fp,"32b$>$\n",dataram_rdat);
fprintf(fp,"%d$>>\n",dataram_cs_clked);
fprintf(fp,"%d$>^\n",dataram_we_clked);
fprintf(fp,"%d$>&\n",dataram_wrsp_per_clked);
fprintf(fp,"%d$>*\n",dataram_rrsp_per_clked);
fprintf(fp,"%d$>|\n",i_databus_grt[0]);
fprintf(fp,"%d$^<\n",i_databus_grt[1]);
fprintf(fp,"%d$^!\n",i_databus_grt[2]);
fprintf(fp,"%d$^@\n",i_databus_grt[3]);
fprintf(fp,"%d$^#\n",o_databus_cmd_valid);
fprintf(fp,"%d$^$\n",o_databus_cmd_read);
fprintfb(fp,"32b$^>\n",o_databus_cmd_adr);
fprintfb(fp,"32b$^^\n",o_databus_cmd_wdata);
fprintfb(fp,"08b$^&\n",o_databus_cmd_rwbyte);
fprintf(fp,"%d$^*\n",i_databus_cmd_ready[0]);
fprintf(fp,"%d$^|\n",i_databus_cmd_ready[1]);
fprintf(fp,"%d$&<\n",i_databus_cmd_ready[2]);
fprintf(fp,"%d$&!\n",i_databus_cmd_ready[3]);
fprintf(fp,"%d$&@\n",data_rspid_fifo_wen);
fprintf(fp,"%d$&#\n",data_rspid_fifo_ren);
fprintf(fp,"%d$&$\n",i_databus_rsp_valid[0]);
fprintf(fp,"%d$&>\n",i_databus_rsp_valid[1]);
fprintf(fp,"%d$&^\n",i_databus_rsp_valid[2]);
fprintf(fp,"%d$&&\n",i_databus_rsp_valid[3]);
fprintf(fp,"%d$&*\n",i_databus_rsp_err[0]);
fprintf(fp,"%d$&|\n",i_databus_rsp_err[1]);
fprintf(fp,"%d$*<\n",i_databus_rsp_err[2]);
fprintf(fp,"%d$*!\n",i_databus_rsp_err[3]);
fprintfb(fp,"32b$*@\n",i_databus_rsp_rdata[0]);
fprintfb(fp,"32b$*#\n",i_databus_rsp_rdata[1]);
fprintfb(fp,"32b$*$\n",i_databus_rsp_rdata[2]);
fprintfb(fp,"32b$*>\n",i_databus_rsp_rdata[3]);
fprintf(fp,"%d$*^\n",o_databus_rsp_ready);
fprintfb(fp,"08b$*&\n",w_data_rspid);
fprintfb(fp,"32b$**\n",data_rspid_fifo_wadr);
fprintfb(fp,"32b$*|\n",data_rspid_fifo_radr);
fprintfb(fp,"32b$|<\n",dataram_adr);
fprintf(fp,"%d$|!\n",dataram_cs);
fprintfb(fp,"32b$|@\n",dataram_wdat);
fprintf(fp,"%d$|#\n",dataram_we);
fprintfb(fp,"08b$|$\n",dataram_bmask);
fprintf(fp,"%d$|>\n",dataram_wrsp_valid);
fprintf(fp,"%d$|^\n",dataram_rrsp_valid);
fprintfb(fp,"08b$|&\n",dataram_rspvalid_cycles_clked);
fprintfb(fp,"08b$|*\n",dataram_cmdready_cycles_clked);
fprintf(fp,"%d$||\n",i_memwb_bus_cmd_valid[0]);
fprintf(fp,"%d><<\n",i_memwb_bus_cmd_valid[1]);
fprintf(fp,"%d><!\n",i_memwb_bus_cmd_valid[2]);
fprintf(fp,"%d><@\n",i_memwb_bus_cmd_valid[3]);
fprintf(fp,"%d><#\n",i_memwb_bus_cmd_ready[0]);
fprintf(fp,"%d><$\n",i_memwb_bus_cmd_ready[1]);
fprintf(fp,"%d><>\n",i_memwb_bus_cmd_ready[2]);
fprintf(fp,"%d><^\n",i_memwb_bus_cmd_ready[3]);
fprintf(fp,"%d><&\n",i_memwb_bus_rsp_valid[0]);
fprintf(fp,"%d><*\n",i_memwb_bus_rsp_valid[1]);
fprintf(fp,"%d><|\n",i_memwb_bus_rsp_valid[2]);
fprintf(fp,"%d>!<\n",i_memwb_bus_rsp_valid[3]);
fprintf(fp,"%d>!!\n",i_memwb_bus_rsp_ready[0]);
fprintf(fp,"%d>!@\n",i_memwb_bus_rsp_ready[1]);
fprintf(fp,"%d>!#\n",i_memwb_bus_rsp_ready[2]);
fprintf(fp,"%d>!$\n",i_memwb_bus_rsp_ready[3]);
fprintfb(fp,"08b>!>\n",i_memwb_bus_cmd_adr[0]);
fprintfb(fp,"08b>!^\n",i_memwb_bus_cmd_adr[1]);
fprintfb(fp,"08b>!&\n",i_memwb_bus_cmd_adr[2]);
fprintfb(fp,"08b>!*\n",i_memwb_bus_cmd_adr[3]);
fprintfb(fp,"32b>!|\n",i_memwb_bus_cmd_wdata[0]);
fprintfb(fp,"32b>@<\n",i_memwb_bus_cmd_wdata[1]);
fprintfb(fp,"32b>@!\n",i_memwb_bus_cmd_wdata[2]);
fprintfb(fp,"32b>@@\n",i_memwb_bus_cmd_wdata[3]);
fprintfb(fp,"32b>@#\n",i_memwb_bus_rsp_rdata[0]);
fprintfb(fp,"32b>@$\n",i_memwb_bus_rsp_rdata[1]);
fprintfb(fp,"32b>@>\n",i_memwb_bus_rsp_rdata[2]);
fprintfb(fp,"32b>@^\n",i_memwb_bus_rsp_rdata[3]);
fprintf(fp,"%d>@&\n",i_memwb_bus_grt_clked[0]);
fprintf(fp,"%d>@*\n",i_memwb_bus_grt_clked[1]);
fprintf(fp,"%d>@|\n",i_memwb_bus_grt_clked[2]);
fprintf(fp,"%d>#<\n",i_memwb_bus_grt_clked[3]);
fprintf(fp,"%d>#!\n",i_memwb_bus_grt[0]);
fprintf(fp,"%d>#@\n",i_memwb_bus_grt[1]);
fprintf(fp,"%d>##\n",i_memwb_bus_grt[2]);
fprintf(fp,"%d>#$\n",i_memwb_bus_grt[3]);
fprintf(fp,"%d>#>\n",o_memwb_bus_cmd_valid);
fprintf(fp,"%d>#^\n",o_memwb_bus_cmd_ready);
fprintfb(fp,"08b>#&\n",o_memwb_bus_cmd_adr);
fprintfb(fp,"32b>#*\n",o_memwb_bus_cmd_wdata);
fprintfb(fp,"08b>#|\n",o_memwb_bus_cmd_id);
fprintf(fp,"%d>$<\n",mul_enable_clked);
fprintfb(fp,"08b>$!\n",mul_cycles_clked);
fprintf(fp,"%d>$@\n",mul_low_clked);
fprintf(fp,"%d>$#\n",mul_rsp_ready);
fprintf(fp,"%d>$$\n",mul_cmd_ready);
fprintf(fp,"%d>$>\n",mul_rsp_valid);
fprintf(fp,"%d>$^\n",mul_enable);
fprintfb(fp,"32b>$&\n",mulres);
fprintf(fp,"%d>$*\n",mul_low);
fprintfb(fp,"32b>$|\n",divrem_opd1);
fprintfb(fp,"32b>><\n",divrem_opd2);
fprintf(fp,"%d>>!\n",div0_clked);
fprintf(fp,"%d>>@\n",ovflow_clked);
fprintfb(fp,"32b>>#\n",quo_undivsigned_clked);
fprintfb(fp,"32b>>$\n",rem_undivsigned_clked);
fprintf(fp,"%d>>>\n",div_end_p_clked);
fprintfb(fp,"32b>>^\n",divisor_undivsigned_clked);
fprintfb(fp,"32b>>&\n",dividend_undivsigned_clked);
fprintf(fp,"%d>>*\n",divorrem_clked);
fprintfb(fp,"08b>>|\n",divremcnt_clked);
fprintfb(fp,"32b>^<\n",minued_clked);
fprintf(fp,"%d>^!\n",diven_clked);
fprintfb(fp,"32b>^@\n",q_clked);
fprintf(fp,"%d>^#\n",divisor_signed_clked);
fprintf(fp,"%d>^$\n",dividend_signed_clked);
fprintfb(fp,"32b>^>\n",dividend_clked);
fprintfb(fp,"08b>^^\n",inik);
fprintf(fp,"%d>^&\n",diven_p);
fprintf(fp,"%d>^*\n",div_end_p);
fprintfb(fp,"32b>^|\n",nxtrem);
fprintfb(fp,"32b>&<\n",nxt_q);
fprintfb(fp,"32b>&!\n",iniminued);
fprintfb(fp,"32b>&@\n",divisor_undivsigned);
fprintfb(fp,"32b>&#\n",dividend_undivsigned);
fprintf(fp,"%d>&$\n",divsigned);
fprintf(fp,"%d>&>\n",div0);
fprintf(fp,"%d>&^\n",ovflow);
fprintf(fp,"%d>&&\n",div_rsp_valid);
fprintf(fp,"%d>&*\n",div_rsp_ready);
fprintfb(fp,"32b>&|\n",div_rsp_rdata);
fprintf(fp,"%d>*<\n",divorrem);
fprintf(fp,"%d>*!\n",divisor_signed);
fprintf(fp,"%d>*@\n",dividend_signed);
fprintfb(fp,"32b>*#\n",dividend);
fprintfb(fp,"32b>*$\n",nxt_minued);
fprintf(fp,"%d>*>\n",qbit);
fprintfb(fp,"32b>*^\n",newminued);
fprintfb(fp,"32b>*&\n",remsigned);
fprintfb(fp,"32b>**\n",quosigned);
fprintfb(fp,"32b>*|\n",remres);
fprintfb(fp,"32b>|<\n",quores);
fprintfb(fp,"08b>|!\n",lifrdidx_clked[0]);
fprintfb(fp,"08b>|@\n",lifrdidx_clked[1]);
fprintfb(fp,"08b>|#\n",lifrdidx_clked[2]);
fprintfb(fp,"08b>|$\n",lifrdidx_clked[3]);
fprintfb(fp,"08b>|>\n",lifrdidx_clked[4]);
fprintfb(fp,"08b>|^\n",lifrdidx_clked[5]);
fprintfb(fp,"08b>|&\n",lifrdidx_clked[6]);
fprintfb(fp,"08b>|*\n",lifrdidx_clked[7]);
fprintf(fp,"%d>||\n",lifvalid_clked[0]);
fprintf(fp,"%d^<<\n",lifvalid_clked[1]);
fprintf(fp,"%d^<!\n",lifvalid_clked[2]);
fprintf(fp,"%d^<@\n",lifvalid_clked[3]);
fprintf(fp,"%d^<#\n",lifvalid_clked[4]);
fprintf(fp,"%d^<$\n",lifvalid_clked[5]);
fprintf(fp,"%d^<>\n",lifvalid_clked[6]);
fprintf(fp,"%d^<^\n",lifvalid_clked[7]);
fprintf(fp,"%d^<&\n",CADDI4SPN );
fprintf(fp,"%d^<*\n",CLW       );
fprintf(fp,"%d^<|\n",CSW       );
fprintf(fp,"%d^!<\n",CNOP      );
fprintf(fp,"%d^!!\n",CADDI     );
fprintf(fp,"%d^!@\n",CJAL      );
fprintf(fp,"%d^!#\n",CLI       );
fprintf(fp,"%d^!$\n",CADDI16SP );
fprintf(fp,"%d^!>\n",CLUI      );
fprintf(fp,"%d^!^\n",CSRLI     );
fprintf(fp,"%d^!&\n",CSRAI     );
fprintf(fp,"%d^!*\n",CANDI     );
fprintf(fp,"%d^!|\n",CSUB      );
fprintf(fp,"%d^@<\n",CXOR      );
fprintf(fp,"%d^@!\n",COR       );
fprintf(fp,"%d^@@\n",CAND      );
fprintf(fp,"%d^@#\n",CJ        );
fprintf(fp,"%d^@$\n",CBEQZ     );
fprintf(fp,"%d^@>\n",CBNEZ     );
fprintf(fp,"%d^@^\n",CSLLI     );
fprintf(fp,"%d^@&\n",CLWSP     );
fprintf(fp,"%d^@*\n",CJR       );
fprintf(fp,"%d^@|\n",CMV       );
fprintf(fp,"%d^#<\n",CBREAK    );
fprintf(fp,"%d^#!\n",CJALR     );
fprintf(fp,"%d^#@\n",CADD      );
fprintf(fp,"%d^##\n",CSWSP     );
fprintfb(fp,"16b^#$\n",rv16     );
fprintfb(fp,"32b^#>\n",rv32     );
fprintfb(fp,"32b^#^\n",c0_instr );
fprintfb(fp,"32b^#&\n",c1_instr );
fprintfb(fp,"32b^#*\n",c2_instr );
fprintf(fp,"%d^#|\n",peri_cmd_ready);
fprintf(fp,"%d^$<\n",randomcycle_clked);
fprintf(fp,"%d^$!\n",downloadper_clked);
fprintfb(fp,"32b^$@\n",codeindex_clked);
fprintfb(fp,"32b^$#\n",download_codesize);
fprintf(fp,"%d^$$\n",downloadstart);
fprintf(fp,"%d^$>\n",downloadcomplete);
fprintf(fp,"%d^$^\n",peri_cmd_valid);
fprintf(fp,"%d^$&\n",peri_cmd_read);
fprintfb(fp,"32b^$*\n",peri_cmd_addr);
fprintfb(fp,"32b^$|\n",peri_cmd_wdata);
}
