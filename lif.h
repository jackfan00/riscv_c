#ifndef LIF_H
#define LIF_H
void lif_clked();

#include "reg.h"

//REG8 lifrdidx_clked[LIFSIZE];
//BIT lifvalid_clked[LIFSIZE];
//REG8 lifcmdcnt_clked;
//REG8 lifid_clked[LIFSIZE];
//BIT lifbuffull;

REG8 lif_divrdidx_clked;
REG8 lif_loadrdidx_clked;
BIT lif_loadfull_clked;

//
REG8 lif_divrdidx;
REG8 lif_loadrdidx;
BIT lif_loadfull;

#endif //LIF_H