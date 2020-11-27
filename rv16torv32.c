#include "rv16torv32.h"

REG32 slicebits(REG32 a, int up, int dn)
{
    REG32 tmp;
    //ex: rv16[4:2]
    //step1: rv16[4:0]
    tmp = (a<<(31-up));
    tmp = (tmp>>(31-up));
    //step2: rv16[4:2]
    tmp = (tmp>>dn);
    return(tmp);
}

REG32 rv16torv32(REG16 in16)
{
    REG8 c0_rdprime;
    REG8 c0_rs2prime;
    REG8 c0_rs1prime;
    REG8 c0_uimm;
    REG8 c0_uimm62;
    REG8 c0_nzuimm;

    REG8 c1_rs2prime;
    REG8 c1_rs1prime;
    REG8 c1_rdprime;
    REG8 c1_rs1;
    REG8 c1_rd;
    REG8 c1_nzimm;
    REG16 c1_jalimm;
    REG16 c1_jalimm111;
    REG8 c1_imm;
    REG16 c1_addi16sp_nzimm;
    REG16 c1_addi16sp_nzimm94;
    REG8 c1_lui_nzuimm;
    REG8 c1_shamt;
    REG16 c1_bxx_offset;
    REG16 c1_bxx_offset81;

    REG8 hlp10;
    REG8 hlp65;
    REG8 hlp1110;
    REG8 hlp1210;
    REG8 hlp1513;

    REG8 c2_shamt;
    REG8 c2_lw_offset;
    REG8 c2_lw_offset72;
    REG8 c2_rs1;
    REG8 c2_rd;
    REG8 c2_rs2;
    REG8 c2_sw_offset;
    REG8 c2_sw_offset72;

    rv16 = in16;

    c0_rdprime = slicebits(rv16,4,2);
    c0_rs2prime = c0_rdprime;
    c0_rs1prime = slicebits(rv16,9,7);
    c0_uimm = (slicebits(rv16,5,5)<<4) | (slicebits(rv16,12,10)<<1) | slicebits(rv16,6,6);
    c0_uimm62 = (c0_uimm<<2);
    c0_nzuimm = (slicebits(rv16,10,7)<<4) | (slicebits(rv16,12,11)<<2) | (slicebits(rv16,5,5)<<1) | slicebits(rv16,6,6);

    CADDI4SPN = (slicebits(rv16,1,0)==0b0) && (slicebits(rv16,15,13)==0b0) && (slicebits(rv16,12,5)!=0b0);
    CLW       = (slicebits(rv16,1,0)==0b0) && (slicebits(rv16,15,13)==0b010);
    CSW       = (slicebits(rv16,1,0)==0b0) && (slicebits(rv16,15,13)==0b110);

    c0_instr =  ((CADDI4SPN ? 0xffffffff : 0) & ((0b0<<30)|(c0_nzuimm<<22)|(0b0<<20)|(0x2<<15)|(0b0<<12)|(0b01<<10)|(c0_rdprime<<7)|0x13)) |  // addi rd', x2, nzuimm[9:2]
                ((CLW       ? 0xffffffff : 0) & ((0b0<<27)|(c0_uimm<<22)|(0b0<<20)|(0b01<<18),(c0_rs1prime<<15)|(0b010<<12)|(0b01<<10)|(c0_rdprime<<7)|0x03)) |  //lw rd', offset[6:2](rs1')
                ((CSW       ? 0xffffffff : 0) & ((0b0<<27)|(slicebits(c0_uimm62,6,5)<<25)|(0b01<<23)|(c0_rs2prime<<20)|(0b01<<18)|(c0_rs1prime<<15)|(0b010<<12),(slicebits(c0_uimm62,4,2)<<9)|(0b0<<7)|0x23)) ;  // sw, rs2', offset[6:2](rs1')

    c1_rs2prime = c0_rdprime;
    c1_rs1prime = c0_rs1prime;
    c1_rdprime = c0_rs1prime;
    c1_rs1 = slicebits(rv16,11,7);
    c1_rd = c1_rs1;
    c1_nzimm = (slicebits(rv16,12,12)<<5)|slicebits(rv16,6,2);
    c1_jalimm = (slicebits(rv16,12,12)<<10)|(slicebits(rv16,8,8)<<9)|(slicebits(rv16,10,9)<<7)|(slicebits(rv16,6,6)<<6)|
                (slicebits(rv16,7,7)<<5)|(slicebits(rv16,2,2)<<4)|(slicebits(rv16,11,11)<<3)|slicebits(rv16,5,3);
    c1_jalimm111 = (c1_jalimm<<1);            
    c1_imm = c1_nzimm;
    c1_addi16sp_nzimm = (slicebits(rv16,12,12)<<5)|(slicebits(rv16,4,3)<<3)|(slicebits(rv16,5,5)<<2)|
                        (slicebits(rv16,2,2)<<1)|slicebits(rv16,6,6);
    c1_addi16sp_nzimm94 = (c1_addi16sp_nzimm<<4);                    
    c1_lui_nzuimm =  c1_nzimm;      
    c1_shamt = c1_nzimm;
    c1_bxx_offset = (slicebits(rv16,12,12)<<7)|(slicebits(rv16,6,5)<<5)|(slicebits(rv16,2,2)<<4)|
                    (slicebits(rv16,11,10)<<2)|slicebits(rv16,4,3);
    c1_bxx_offset81 = (c1_bxx_offset<<1);                

    hlp10 = slicebits(rv16,1,0);
    hlp65 = slicebits(rv16,6,5);
    hlp1110 = slicebits(rv16,11,10);
    hlp1210 = slicebits(rv16,12,10);
    hlp1513 = slicebits(rv16,15,13);

    CNOP      = (slicebits(rv16,15,0)==0x1);       
    CADDI     = (hlp10==0b1) && (hlp1513==0x0) && (c1_nzimm!=0b0) && (c1_rd!=0b0);
    CJAL      = (hlp10==0b1) && (hlp1513==0b001) ;
    CLI       = (hlp10==0b1) && (hlp1513==0b010) && (c1_rd!=0b0);
    CADDI16SP = (hlp10==0b1) && (hlp1513==0b011) && (c1_addi16sp_nzimm!=0b0) && (c1_rd==0x2) ;
    CLUI      = (hlp10==0b1) && (hlp1513==0b011) && (c1_lui_nzuimm!=0b0) && (c1_rd!=0x2) && (c1_rd!=0x0) ;
    CSRLI     = (hlp10==0b1) && (hlp1513==0b100) && (c1_shamt!=0b0) && (hlp1110==0b00)  ;
    CSRAI     = (hlp10==0b1) && (hlp1513==0b100) && (c1_shamt!=0b0) && (hlp1110==0b01)  ;
    CANDI     = (hlp10==0b1) && (hlp1513==0b100) && (hlp1110==0b10)  ;
    CSUB      = (hlp10==0b1) && (hlp1513==0b100) && (hlp1210==0b011) && (hlp65==0b00)  ;
    CXOR      = (hlp10==0b1) && (hlp1513==0b100) && (hlp1210==0b011) && (hlp65==0b01)  ;
    COR       = (hlp10==0b1) && (hlp1513==0b100) && (hlp1210==0b011) && (hlp65==0b10)  ;
    CAND      = (hlp10==0b1) && (hlp1513==0b100) && (hlp1210==0b011) && (hlp65==0b11)  ;
    CJ        = (hlp10==0b1) && (hlp1513==0b101) ;
    CBEQZ     = (hlp10==0b1) && (hlp1513==0b110) ;
    CBNEZ     = (hlp10==0b1) && (hlp1513==0b111) ;

    c1_instr =    ((CNOP     ? 0xffffffff : 0) & 0x13) |
                  ((CADDI    ? 0xffffffff : 0) & (((slicebits(c1_nzimm,5,5)?0x3f:0)<<26)|(c1_nzimm<<20)|(c1_rs1<<15)|(0b0<<12)|(c1_rd<<7)|0x13)) |  // addi rd, rd, nzimm[5:0]
                  ((CJAL     ? 0xffffffff : 0) & ((slicebits(c1_jalimm111,11,11)<<31)|(slicebits(c1_jalimm111,10,1)<<21)|(slicebits(c1_jalimm111,11,11)<<20)|((slicebits(c1_jalimm111,11,11)?0xff:0)<<12)|(0x1<<7)|0x6f)) |  //JAL x1, offset[11:1]
                  ((CLI      ? 0xffffffff : 0) & (((slicebits(c1_imm,5,5)?0x3f:0)<<25)|(slicebits(c1_imm,5,0)<<20)|(0x0<<15),(0b0<<12)|(c1_rd<<7)|0x13)) |   //addi rd, x0, imm[5:0]
                  ((CADDI16SP? 0xffffffff : 0) & (((slicebits(c1_addi16sp_nzimm94,9,9)?0x3:0)<<30)|(slicebits(c1_addi16sp_nzimm94,9,4)<<24)|(0b0<<20)|(0x2<<15)|(0b0<<12)|(0x2<<7)|0x13)) |  //addi x2, x2, nzimm[9:4]
                  ((CLUI     ? 0xffffffff : 0) & (((slicebits(c1_lui_nzuimm,17,17)?0x3fff:0)<<18)|(slicebits(c1_lui_nzuimm,17,12)<<12)|(c1_rd<<7)|0x37)) |  //lui rd,  nzuimm[17:12]
                  ((CSRLI    ? 0xffffffff : 0) & ((0x00<<26)|(slicebits(c1_shamt,5,0)<<20)|(0b1<<18)|(c1_rdprime<<15)|(0b101<<12)|(0b1<<10)|(c1_rdprime<<7)|0x13)) |  //srli rd', rd',  shamt[5:0]
                  ((CSRAI    ? 0xffffffff : 0) & ((0x10<<26)|(slicebits(c1_shamt,5,0)<<20)|(0b1<<18)|(c1_rdprime<<15)|(0b101<<12)|(0b1<<10)|(c1_rdprime<<7)|0x13)) |  //srai rd', rd',  shamt[5:0]
                  ((CANDI    ? 0xffffffff : 0) & (((slicebits(c1_imm,5,5)?0x3f:0)<<26)|(slicebits(c1_imm,5,0)<<20)|(0b1<<18)|(c1_rdprime<<15)|(0b111<<12)|(0b1<<10)|(c1_rdprime<<7)|0x13)) |  //andi rd', rd',  imm[5:0]
                  ((CSUB     ? 0xffffffff : 0) & ((0x20<<25)|(0b1<<23)|(c1_rs2prime<<20)|(0b1<<18)|(c1_rdprime<<15)|(0b000<<12)|(0b1<<10)|(c1_rdprime<<7)|0x33)) |  //sub rd', rd', rs2' 
                  ((CXOR     ? 0xffffffff : 0) & ((0x00<<25)|(0b1<<23)|(c1_rs2prime<<20)|(0b1<<18)|(c1_rdprime<<15)|(0b100<<12)|(0b1<<10)|(c1_rdprime<<7)|0x33)) |  //xor rd', rd', rs2' 
                  ((COR      ? 0xffffffff : 0) & ((0x00<<25)|(0b1<<23)|(c1_rs2prime<<20)|(0b1<<18)|(c1_rdprime<<15)|(0b110<<12)|(0b1<<10)|(c1_rdprime<<7)|0x33)) |  //or rd', rd', rs2' 
                  ((CAND     ? 0xffffffff : 0) & ((0x00<<25)|(0b1<<23)|(c1_rs2prime<<20)|(0b1<<18)|(c1_rdprime<<15)|(0b111<<12)|(0b1<<10)|(c1_rdprime<<7)|0x33)) |  //and rd', rd', rs2' 
                  ((CJ       ? 0xffffffff : 0) & ((slicebits(c1_jalimm111,11,11)<<31)|(slicebits(c1_jalimm111,10,1)<<21)|(slicebits(c1_jalimm111,11,11)<<20)|((slicebits(c1_jalimm111,11,11)?0xff:0)<<12)|(0x0<<7)|0x6f)) |  //JAL x0, offset[11:1]
                  ((CBEQZ    ? 0xffffffff : 0) & (((slicebits(c1_bxx_offset81,8,8)?0x7:0)<<29)|(slicebits(c1_bxx_offset81,8,5)<<25)|(0b0<<20)|(0b1<<18)|(c1_rs1prime<<15)|(0b000<<12)|(slicebits(c1_bxx_offset81,4,1)<<8)|(slicebits(c1_bxx_offset81,8,8)<<7)|0x63)) |  //beq rs1', x0, offset[8:1] 
                  ((CBNEZ    ? 0xffffffff : 0) & (((slicebits(c1_bxx_offset81,8,8)?0x7:0)<<29)|(slicebits(c1_bxx_offset81,8,5)<<25)|(0b0<<20)|(0b1<<18)|(c1_rs1prime<<15)|(0b001<<12)|(slicebits(c1_bxx_offset81,4,1)<<8)|(slicebits(c1_bxx_offset81,8,8)<<7)|0x63)) ;  //bne rs1', x0, offset[8:1] 


    c2_shamt = ((slicebits(rv16,12,12)<<5)|slicebits(rv16,6,2));
    c2_lw_offset = ((slicebits(rv16,3,2)<<4)|(slicebits(rv16,12,12)<<3)|slicebits(rv16,6,4));
    c2_lw_offset72 = (c2_lw_offset<<2);
    c2_rs1 = slicebits(rv16,11,7);
    c2_rd = c2_rs1; //rv16[11:7];
    c2_rs2 = slicebits(rv16,6,2);
    c2_sw_offset = ((slicebits(rv16,8,7)<<4)|slicebits(rv16,12,9));
    c2_sw_offset72 = (c2_sw_offset<<2);

    CSLLI  = (hlp10==0b10) && (hlp1513==0b000) && (c2_shamt!=0b0) && (c2_rd!=0b0)  ;
    CLWSP  = (hlp10==0b10) && (hlp1513==0b010) && (c2_rd!=0b0)  ;
    CJR    = (hlp10==0b10) && (hlp1513==0b100) && (c2_shamt==0b0) && (c2_rd!=0x0)  ;
    CMV    = (hlp10==0b10) && (hlp1513==0b100) && (slicebits(rv16,12,12)==0b0) && (c2_rd!=0x0) && (c2_rs2!=0x0)  ;
    CBREAK = (slicebits(rv16,15,0)==0x9002)  ;
    CJALR  = (hlp10==0b10) && (hlp1513==0b100) && (c2_shamt==0x20) && (c2_rs1!=0x0)  ;
    CADD   = (hlp10==0b10) && (hlp1513==0b100) && (slicebits(rv16,12,12)==0b1) && (c2_rs1!=0x0) && (c2_rs2!=0x0)  ;
    CSWSP  = (hlp10==0b10) && (hlp1513==0b110)   ;

    c2_instr =         ((CSLLI  ? 0xffffffff:0) & ((0x00<<25)|(c2_shamt<<20)|(c2_rd<<15)|(0b001<<12)|(c1_rd<<7)|0x13)) |  //slli rd, rd, shamt[5:0]
                       ((CLWSP  ? 0xffffffff:0) & ((0b0<<28)|(c2_lw_offset<<22)|(0b0<<20)|(0x2<<15)|(0b010<<12)|(c2_rd<<7)|0x03)) |  //lw rd, offset[7:2](x2)
                       ((CJR    ? 0xffffffff:0) & ((0b0<<20)|(c2_rs1<<15)|(0b0<<12)|(0x0<<7)|0x67)) |  //JALR x0, rs1, 0
                       ((CMV    ? 0xffffffff:0) & ((0x00<<25)|(c2_rs2<<20)|(0x0<<15)|(0b0<<12)|(c2_rd<<7)|0x33)) |  //add rd, x0, rs2 
                       ((CBREAK ? 0xffffffff:0) & ((0b0<<20)|0x73)) |  // ebreak
                       ((CJALR  ? 0xffffffff:0) & ((0b0<<20)|(c2_rs1<<15)|(0b0<<12)|(0x1<<7)|0x67)) |  //JALR x1, rs1, 0
                       ((CADD   ? 0xffffffff:0) & ((0x00<<25)|(c2_rs2<<20)|(c2_rd<<15)|(0b0<<12)|(c2_rd<<7)|0x33)) |  //add rd, rd, rs2 
                       ((CSWSP  ? 0xffffffff:0) & ((0b0<<28)|(slicebits(c2_sw_offset72,7,5)<<25)|(c2_rs2<<20)|(0x2<<15)|(0b010<<12)|(slicebits(c2_sw_offset72,4,2)<<9)|(0b0<<7)|0x23)) ;  // sw, rs2, offset[7:2](x2)

    rv32 = c0_instr | c1_instr | c2_instr;

    return(rv32);

}

/*
module rv16torv32(rv16, rv32);

input [15:0] rv16;
output [31:0] rv32;

wire [2:0] c0_rdprime = rv16[4:2];
wire [2:0] c0_rs2prime = rv16[4:2];
wire [2:0] c0_rs1prime = rv16[9:7];
wire [6:2] c0_uimm = {rv16[5],rv16[12:10],rv16[6]};
wire [9:2] c0_nzuimm = {rv16[10:7],rv16[12:11],rv16[5],rv16[6]};

wire CADDI4SPN = (rv16[1:0]==2'b0) && (rv16[15:13]==3'b0) && (rv16[12:5]!=8'b0);
wire CLW = (rv16[1:0]==2'b0) && (rv16[15:13]==3'b010);
wire CSW = (rv16[1:0]==2'b0) && (rv16[15:13]==3'b110);

wire [31:0] c0_instr = ({32{CADDI4SPN}} & {2'b0,c0_nzuimm,2'b0,5'h2,3'b0,2'b01,c0_rdprime,7'h13}) |  // addi rd', x2, nzuimm[9:2]
                  ({32{CLW}} & {5'b0,c0_uimm,2'b0,2'b01,c0_rs1prime,3'b010,2'b01,c0_rdprime,7'h03}) |  //lw rd', offset[6:2](rs1')
                  ({32{CSW}} & {5'b0,c0_uimm[6:5],2'b01,c0_rs2prime,2'b01,c0_rs1prime,3'b010,c0_uimm[4:2],2'b0,7'h23}) ;  // sw, rs2', offset[6:2](rs1')

wire [2:0] c1_rs2prime = rv16[4:2];
wire [2:0] c1_rs1prime = rv16[9:7];
wire [2:0] c1_rdprime = rv16[9:7];
wire [4:0] c1_rs1 = rv16[11:7];
wire [4:0] c1_rd = rv16[11:7];
wire [5:0] c1_nzimm = {rv16[12],rv16[6:2]};
wire [11:1] c1_jalimm = {rv16[12],rv16[8],rv16[10:9],rv16[6],rv16[7],rv16[2],rv16[11],rv16[5:3]};
wire [5:0] c1_imm = {rv16[12],rv16[6:2]};
wire [9:4] c1_addi16sp_nzimm = {rv16[12],rv16[4:3],rv16[5],rv16[2],rv16[6]};
wire [17:12] c1_lui_nzuimm = {rv16[12],rv16[6:2]};
wire [5:0] c1_shamt = {rv16[12],rv16[6:2]};
wire [8:1] c1_bxx_offset = {rv16[12],rv16[6:5],rv16[2],rv16[11:10],rv16[4:3]};

wire CNOP = (rv16[15:0]==16'h1);
wire CADDI = (rv16[1:0]==2'b1) && (rv16[15:13]==3'h0) && (c1_nzimm[5:0]!=6'b0) && (c1_rd!=5'b0);
wire CJAL = (rv16[1:0]==2'b1) && (rv16[15:13]==3'b001) ;
wire CLI = (rv16[1:0]==2'b1) && (rv16[15:13]==3'b010) && (c1_rd!=5'b0);
wire CADDI16SP = (rv16[1:0]==2'b1) && (rv16[15:13]==3'b011) && (c1_addi16sp_nzimm[9:4]!=6'b0) && (c1_rd==5'h2) ;
wire CLUI = (rv16[1:0]==2'b1) && (rv16[15:13]==3'b011) && (c1_lui_nzuimm[17:12]!=6'b0) && (c1_rd!=5'h2) && (c1_rd!=5'h0) ;
wire CSRLI = (rv16[1:0]==2'b1) && (rv16[15:13]==3'b100) && (c1_shamt[5:0]!=6'b0) && (rv16[11:10]==2'b00)  ;
wire CSRAI = (rv16[1:0]==2'b1) && (rv16[15:13]==3'b100) && (c1_shamt[5:0]!=6'b0) && (rv16[11:10]==2'b01)  ;
wire CANDI = (rv16[1:0]==2'b1) && (rv16[15:13]==3'b100) && (rv16[11:10]==2'b10)  ;
wire CSUB = (rv16[1:0]==2'b1) && (rv16[15:13]==3'b100) && (rv16[12:10]==3'b011) && (rv16[6:5]==2'b00)  ;
wire CXOR = (rv16[1:0]==2'b1) && (rv16[15:13]==3'b100) && (rv16[12:10]==3'b011) && (rv16[6:5]==2'b01)  ;
wire COR =  (rv16[1:0]==2'b1) && (rv16[15:13]==3'b100) && (rv16[12:10]==3'b011) && (rv16[6:5]==2'b10)  ;
wire CAND = (rv16[1:0]==2'b1) && (rv16[15:13]==3'b100) && (rv16[12:10]==3'b011) && (rv16[6:5]==2'b11)  ;
wire CJ =    (rv16[1:0]==2'b1) && (rv16[15:13]==3'b101) ;
wire CBEQZ = (rv16[1:0]==2'b1) && (rv16[15:13]==3'b110) ;
wire CBNEZ = (rv16[1:0]==2'b1) && (rv16[15:13]==3'b111) ;

wire [31:0] c1_instr = ({32{CNOP}} & 32'h13) |
                  ({32{CADDI}} & {{6{c1_nzimm[5]}},c1_nzimm[5:0],c1_rs1,3'b0,c1_rd,7'h13}) |  // addi rd, rd, nzimm[5:0]
                  ({32{CJAL}} & {c1_jalimm[11],c1_jalimm[10:1],c1_jalimm[11],{8{c1_jalimm[11]}},5'h1,7'h6f}) |  //JAL x1, offset[11:1]
                  ({32{CLI}} & {{6{c1_imm[5]}},c1_imm[5:0],5'h0,3'b0,c1_rd,7'h13}) |   //addi rd, x0, imm[5:0]
                  ({32{CADDI16SP}} & {{2{c1_addi16sp_nzimm[9]}},c1_addi16sp_nzimm[9:4],4'b0,5'h2,3'b0,5'h2,7'h13}) |  //addi x2, x2, nzimm[9:4]
                  ({32{CLUI}} & {{14{c1_lui_nzuimm[17]}},c1_lui_nzuimm[17:12],c1_rd,7'h37}) |  //lui rd,  nzuimm[17:12]
                  ({32{CSRLI}} & {6'h00,c1_shamt[5:0],2'b1,c1_rdprime,3'b101,2'b1,c1_rdprime,7'h13}) |  //srli rd', rd',  shamt[5:0]
                  ({32{CSRAI}} & {6'h10,c1_shamt[5:0],2'b1,c1_rdprime,3'b101,2'b1,c1_rdprime,7'h13}) |  //srai rd', rd',  shamt[5:0]
                  ({32{CANDI}} & {{6{c1_imm[5]}},c1_imm[5:0],2'b1,c1_rdprime,3'b111,2'b1,c1_rdprime,7'h13}) |  //andi rd', rd',  imm[5:0]
                  ({32{CSUB}} & {7'h20,2'b1,c1_rs2prime,2'b1,c1_rdprime,3'b0,2'b1,c1_rdprime,7'h33}) |  //sub rd', rd', rs2' 
                  ({32{CXOR}} & {7'h00,2'b1,c1_rs2prime,2'b1,c1_rdprime,3'b100,2'b1,c1_rdprime,7'h33}) |  //xor rd', rd', rs2' 
                  ({32{COR}} & {7'h00,2'b1,c1_rs2prime,2'b1,c1_rdprime,3'b110,2'b1,c1_rdprime,7'h33}) |  //or rd', rd', rs2' 
                  ({32{CAND}} & {7'h00,2'b1,c1_rs2prime,2'b1,c1_rdprime,3'b111,2'b1,c1_rdprime,7'h33}) |  //and rd', rd', rs2' 
                  ({32{CJ}} & {c1_jalimm[11],c1_jalimm[10:1],c1_jalimm[11],{8{c1_jalimm[11]}},5'h0,7'h6f}) |  //JAL x0, offset[11:1]
                  ({32{CBEQZ}} & {{3{c1_bxx_offset[8]}},c1_bxx_offset[8:5],5'b0,2'b1,c1_rs1prime,3'b0,c1_bxx_offset[4:1],c1_bxx_offset[8],7'h63}) |  //beq rs1', x0, offset[8:1] 
                  ({32{CBNEZ}} & {{3{c1_bxx_offset[8]}},c1_bxx_offset[8:5],5'b0,2'b1,c1_rs1prime,3'b001,c1_bxx_offset[4:1],c1_bxx_offset[8],7'h63}) ;  //bne rs1', x0, offset[8:1] 


wire [5:0] c2_shamt = {rv16[12],rv16[6:2]};
wire [7:2] c2_lw_offset = {rv16[3:2],rv16[12],rv16[6:4]};
wire [4:0] c2_rs1 = rv16[11:7];
wire [4:0] c2_rd = rv16[11:7];
wire [4:0] c2_rs2 = rv16[6:2];
wire [7:2] c2_sw_offset = {rv16[8:7],rv16[12:9]};


wire CSLLI = (rv16[1:0]==2'b10) && (rv16[15:13]==3'b000) && (c2_shamt[5:0]!=6'b0) && (c2_rd!=5'b0)  ;
wire CLWSP = (rv16[1:0]==2'b10) && (rv16[15:13]==3'b010) && (c2_rd!=5'b0)  ;
wire CJR = (rv16[1:0]==2'b10) && (rv16[15:13]==3'b100) && (c2_shamt[5:0]==6'b0) && (c2_rd!=5'h0)  ;
wire CMV = (rv16[1:0]==2'b10) && (rv16[15:13]==3'b100) && (rv16[12]==1'b0) && (c2_rd!=5'h0) && (c2_rs2!=5'h0)  ;
wire CBREAK = (rv16[15:0]==16'h9002)  ;
wire CJALR = (rv16[1:0]==2'b10) && (rv16[15:13]==3'b100) && (c2_shamt[5:0]==6'h20) && (c2_rs1!=5'h0)  ;
wire CADD = (rv16[1:0]==2'b10) && (rv16[15:13]==3'b100) && (rv16[12]==1'b1) && (c2_rs1!=5'h0) && (c2_rs2!=5'h0)  ;
wire CSWSP = (rv16[1:0]==2'b10) && (rv16[15:13]==3'b110)   ;


wire [31:0] c2_instr = ({32{CSLLI}} & {7'h00,c2_shamt[5:0],c2_rd,3'b001,c1_rd,7'h13} ) |  //slli rd, rd, shamt[5:0]
                       ({32{CLWSP}} & {4'b0,c2_lw_offset[7:2],2'b0,5'h2,3'b010,c2_rd,7'h03}) |  //lw rd, offset[7:2](x2)
                       ({32{CJR}} & {12'b0,c2_rs1,3'b0,5'h0,7'h67}) |  //JALR x0, rs1, 0
                       ({32{CMV}} & {7'h00,c2_rs2,5'h0,3'b0,c2_rd,7'h33}) |  //add rd, x0, rs2 
                       ({32{CBREAK}} & {12'b0,20'h73}) |  // ebreak
                       ({32{CJALR}} & {12'b0,c2_rs1,3'b0,5'h1,7'h67}) |  //JALR x1, rs1, 0
                       ({32{CADD}} & {7'h00,c2_rs2,c2_rd,3'b0,c2_rd,7'h33}) |  //add rd, rd, rs2 
                       ({32{CSWSP}} & {4'b0,c2_sw_offset[7:5],c2_rs2,5'h2,3'b010,c2_sw_offset[4:2],2'b0,7'h23}) ;  // sw, rs2, offset[7:2](x2)

assign rv32 = c0_instr | c1_instr | c2_instr;

endmodule
*/