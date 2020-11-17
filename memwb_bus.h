#ifndef MEMWB_BUS_H
#define MEMWB_BUS_H

#include "reg.h"

BIT i_memwb_bus_cmd_valid[WBARBIT_NUM];
BIT i_memwb_bus_cmd_ready[WBARBIT_NUM];
BIT i_memwb_bus_rsp_valid[WBARBIT_NUM];
BIT i_memwb_bus_rsp_ready[WBARBIT_NUM];
REG8 i_memwb_bus_cmd_adr[WBARBIT_NUM];
REG32 i_memwb_bus_cmd_wdata[WBARBIT_NUM];
REG32 i_memwb_bus_rsp_rdata[WBARBIT_NUM];
BIT i_memwb_bus_grt_clked[WBARBIT_NUM];
BIT i_memwb_bus_grt[WBARBIT_NUM];

BIT o_memwb_bus_cmd_valid;
BIT o_memwb_bus_cmd_ready;
REG8 o_memwb_bus_cmd_adr;
REG32 o_memwb_bus_cmd_wdata;
REG8 o_memwb_bus_cmd_id;

//memwb_bus arbitor priority
#define DIVBUSID 0  //1st priority
#define LSUBUSID 1
#define MULBUSID 2
#define EXEBUSID 3

#endif  //MEMWB_BUS_H