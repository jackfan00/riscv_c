#ifndef REGBUS_H
#define REGBUS_H

#include "reg.h"

//input
BIT i_regwbus_grt_clked[REGARBIT_NUM];
BIT i_regwbus_cmd_valid[REGARBIT_NUM];
REG32 i_regwbus_cmd_adr[REGARBIT_NUM];
REG32 i_regwbus_cmd_wdata[REGARBIT_NUM];
BIT i_regwbus_cmd_ready[REGARBIT_NUM];

BIT i_rs1bus_grt_clked[REGARBIT_NUM];
BIT i_rs1bus_cmd_valid[REGARBIT_NUM];
BIT i_rs1bus_cmd_ready[REGARBIT_NUM];
REG32 i_rs1bus_cmd_adr[REGARBIT_NUM];
//REG8 i_rs1bus_cmd_rwbyte[REGARBIT_NUM];
BIT i_rs1bus_rsp_ready[REGARBIT_NUM];
BIT i_rs1bus_rsp_err[REGARBIT_NUM];
BIT i_rs2bus_grt_clked[REGARBIT_NUM];
BIT i_rs2bus_cmd_valid[REGARBIT_NUM];
BIT i_rs2bus_cmd_ready[REGARBIT_NUM];
REG32 i_rs2bus_cmd_adr[REGARBIT_NUM];
//REG8 i_rs2bus_cmd_rwbyte[REGARBIT_NUM];
BIT i_rs2bus_rsp_ready[REGARBIT_NUM];
BIT i_rs2bus_rsp_err[REGARBIT_NUM];

//output
BIT i_regwbus_grt[REGARBIT_NUM];
BIT regw_cs;
BIT regw_we;
REG32 regw_wdat;
REG32 regw_adr;
BIT i_rs1bus_grt[REGARBIT_NUM];
BIT i_rs1bus_rsp_valid[REGARBIT_NUM];
REG32 i_rs1bus_rsp_rdata[REGARBIT_NUM];
BIT i_rs2bus_grt[REGARBIT_NUM];
BIT i_rs2bus_rsp_valid[REGARBIT_NUM];
REG32 i_rs2bus_rsp_rdata[REGARBIT_NUM];

#endif // REGBUS_H
