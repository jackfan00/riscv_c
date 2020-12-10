#include "divrem.h"
#include "decode.h"
#include "execu.h"

//
void divrem()
{
  REG32 divisor;
  BIT result_signed;
  
  divregidx = div_cmd_valid & div_cmd_ready ? div_cmd_regidx : divregidx_clked;
  divrden   = div_cmd_valid & div_cmd_ready ? div_cmd_rden   : divrden_clked;

  if (div_cmd_valid & div_cmd_ready){
    //
    //
    divsigned = (div_cmd_opmode==1) | (div_cmd_opmode==4);  //div/rem
    dividend = div_cmd_opd1;
    divisor = div_cmd_opd2;
    div0 = (divisor==0);
    ovflow = (divisor==1) & (dividend==0x80000000) & divsigned;
    divisor_signed = divsigned & (divisor>>31);
    dividend_signed = divsigned & (dividend>>31);
    divisor_undivsigned  = divisor_signed  ? ~(divisor)+1  : divisor;
    dividend_undivsigned = dividend_signed ?~(dividend)+1 : dividend;
//
    diven_p =1;
    divorrem = (div_cmd_opmode==1) | (div_cmd_opmode==2);  //div/divu
//
  if (((divisor_undivsigned>>31)&0x01) | div0 | ovflow)  //div0 
    inik = 31;
  else if ((divisor_undivsigned>>30)&0x01)
    inik = 30;
  else if ((divisor_undivsigned>>29)&0x01)
    inik = 29;
  else if ((divisor_undivsigned>>28)&0x01)
    inik = 28;
  else if ((divisor_undivsigned>>27)&0x01)
    inik = 27;
  else if ((divisor_undivsigned>>26)&0x01)
    inik = 26;
  else if ((divisor_undivsigned>>25)&0x01)
    inik = 25;
  else if ((divisor_undivsigned>>24)&0x01)
    inik = 24;
  else if ((divisor_undivsigned>>23)&0x01)
    inik = 23;
  else if ((divisor_undivsigned>>22)&0x01)
    inik = 22;
  else if ((divisor_undivsigned>>21)&0x01)
    inik = 21;
  else if ((divisor_undivsigned>>20)&0x01)
    inik = 20;
  else if ((divisor_undivsigned>>19)&0x01)
    inik = 19;  
  else if ((divisor_undivsigned>>18)&0x01)
    inik = 18;  
  else if ((divisor_undivsigned>>17)&0x01)
    inik = 17;  
  else if ((divisor_undivsigned>>16)&0x01)
    inik = 16;  
  else if ((divisor_undivsigned>>15)&0x01)
    inik = 15;  
  else if ((divisor_undivsigned>>14)&0x01)
    inik = 14;  
  else if ((divisor_undivsigned>>13)&0x01)
    inik = 13;  
  else if ((divisor_undivsigned>>12)&0x01)
    inik = 12;  
  else if ((divisor_undivsigned>>11)&0x01)
    inik = 11;  
  else if ((divisor_undivsigned>>10)&0x01)
    inik = 10;
  else if ((divisor_undivsigned>>9)&0x01)
    inik = 9;  
  else if ((divisor_undivsigned>>8)&0x01)
    inik = 8;  
  else if ((divisor_undivsigned>>7)&0x01)
    inik = 7;  
  else if ((divisor_undivsigned>>6)&0x01)
    inik = 6;  
  else if ((divisor_undivsigned>>5)&0x01)
    inik = 5;  
  else if ((divisor_undivsigned>>4)&0x01)
    inik = 4;  
  else if ((divisor_undivsigned>>3)&0x01)
    inik = 3;  
  else if ((divisor_undivsigned>>2)&0x01)
    inik = 2;  
  else if ((divisor_undivsigned>>1)&0x01)
    inik = 1;  
  else //if (divisor>>0])
    inik = 0;    
  //
  //
  //
  if ((divisor_undivsigned>>31)&0x01)
    iniminued = dividend_undivsigned>>0;
  else if ((divisor_undivsigned>>30)&0x01)
    iniminued = (dividend_undivsigned>>1);
  else if ((divisor_undivsigned>>29)&0x01)
    iniminued = (dividend_undivsigned>>2);
  else if ((divisor_undivsigned>>28)&0x01)
    iniminued = (dividend_undivsigned>>3);
  else if ((divisor_undivsigned>>27)&0x01)
    iniminued = (dividend_undivsigned>>4);
  else if ((divisor_undivsigned>>26)&0x01)
    iniminued = (dividend_undivsigned>>5);
  else if ((divisor_undivsigned>>25)&0x01)
    iniminued = (dividend_undivsigned>>6);
  else if ((divisor_undivsigned>>24)&0x01)
    iniminued = (dividend_undivsigned>>7);
  else if ((divisor_undivsigned>>23)&0x01)
    iniminued = (dividend_undivsigned>>8);
  else if ((divisor_undivsigned>>22)&0x01)
    iniminued = (dividend_undivsigned>>9);
  else if ((divisor_undivsigned>>21)&0x01)
    iniminued = (dividend_undivsigned>>10);
  else if ((divisor_undivsigned>>20)&0x01)
    iniminued = (dividend_undivsigned>>11);
  else if ((divisor_undivsigned>>19)&0x01)
    iniminued = (dividend_undivsigned>>12);  
  else if ((divisor_undivsigned>>18)&0x01)
    iniminued = (dividend_undivsigned>>13);  
  else if ((divisor_undivsigned>>17)&0x01)
    iniminued =(dividend_undivsigned>>14);  
  else if ((divisor_undivsigned>>16)&0x01)
    iniminued = (dividend_undivsigned>>15);  
  else if ((divisor_undivsigned>>15)&0x01)
    iniminued =(dividend_undivsigned>>16);  
  else if ((divisor_undivsigned>>14)&0x01)
    iniminued = (dividend_undivsigned>>17);  
  else if ((divisor_undivsigned>>13)&0x01)
    iniminued = (dividend_undivsigned>>18);  
  else if ((divisor_undivsigned>>12)&0x01)
    iniminued = (dividend_undivsigned>>19);  
  else if ((divisor_undivsigned>>11)&0x01)
    iniminued = (dividend_undivsigned>>20);  
  else if ((divisor_undivsigned>>10)&0x01)
    iniminued =(dividend_undivsigned>>21);
  else if ((divisor_undivsigned>>9)&0x01)
    iniminued =(dividend_undivsigned>>22);  
  else if ((divisor_undivsigned>>8)&0x01)
    iniminued = (dividend_undivsigned>>23);  
  else if ((divisor_undivsigned>>7)&0x01)
    iniminued = (dividend_undivsigned>>24);  
  else if ((divisor_undivsigned>>6)&0x01)
    iniminued = (dividend_undivsigned>>25);  
  else if ((divisor_undivsigned>>5)&0x01)
    iniminued = (dividend_undivsigned>>26);  
  else if ((divisor_undivsigned>>4)&0x01)
    iniminued = (dividend_undivsigned>>27);  
  else if ((divisor_undivsigned>>3)&0x01)
    iniminued = (dividend_undivsigned>>28);  
  else if ((divisor_undivsigned>>2)&0x01)
    iniminued = (dividend_undivsigned>>29);  
  else if ((divisor_undivsigned>>1)&0x01)
    iniminued = (dividend_undivsigned>>30);  
  else if ((divisor_undivsigned>>0)&0x01)
    iniminued = (dividend_undivsigned>>31);    
  else
    iniminued = 0;

  }   //cmd_valid/cmd_ready
  else{
    diven_p =0;

  }

    //
 div_end_p = (divremcnt_clked == 31) & diven_clked;

  //div main body
 qbit = (minued_clked >= divisor_undivsigned_clked);
 newminued = minued_clked - divisor_undivsigned_clked;
 nxt_minued = qbit ? (newminued<<1)   + ((dividend_undivsigned_clked>>(31-divremcnt_clked-1))&0x01) : 
                     (minued_clked<<1)+ ((dividend_undivsigned_clked>>(31-divremcnt_clked-1))&0x01);
 nxt_q = (q_clked<<1)+qbit;  //shift in left
 nxtrem = div_end_p ? (qbit ? newminued : minued_clked) : 0;  
//

// be careful about rem :
// ex: 101/-100 = (q=-1, rem=1), -101/100=(q=-1,rem=-1)
// ex: -1/-100 = (0,-1)
result_signed = divisor_signed_clked ^ dividend_signed_clked;

remsigned = (quo_undivsigned_clked==0) ? dividend_clked :
            result_signed & dividend_signed_clked ? ~(rem_undivsigned_clked)+1 : rem_undivsigned_clked;
quosigned = result_signed ? ~(quo_undivsigned_clked)+1 : quo_undivsigned_clked;

remres = div0_clked ? dividend_clked : 
             ovflow_clked ? 0 : remsigned;
quores = div0_clked   ? 0xffffffff : 
             ovflow_clked ? 0x80000000 : quosigned;

if (div_end_p_clked){
  div_rsp_valid = 1;
  div_rsp_rdata = divorrem_clked ? quores : remres;
  div_rsp_regidx = divregidx_clked;
  div_rsp_rden = divrden_clked;
}
else{
  div_rsp_valid = 0;
  div_rsp_rdata = 0;
  div_rsp_regidx = 0;
  div_rsp_rden = 0;
}
div_rsp_read = div_rsp_valid;

//different from mul/sram, it need more than 1 cycle to finish task
div_cmd_ready = !diven_clked | (div_rsp_valid&div_rsp_ready);


}



//
/*
module divrem(
clk, cpurst,
divider, dividend,
diven_p,
div0, ovflow,
//
divout_valid, diven,
rem, quo, 

);

input clk, cpurst;
input [31:0] divider, dividend;
input diven_p;
input div0, ovflow;
//output
output divout_valid, diven;
output [31:0] rem, quo;

//
reg [4:0] inik;
always @*
begin
  if (divider[31] | div0 | ovflow)  //div0 
    inik = 5'd31;
  else if (divider[30])
    inik = 5'd30;
  else if (divider[29])
    inik = 5'd29;
  else if (divider[28])
    inik = 5'd28;
  else if (divider[27])
    inik = 5'd27;
  else if (divider[26])
    inik = 5'd26;
  else if (divider[25])
    inik = 5'd25;
  else if (divider[24])
    inik = 5'd24;
  else if (divider[23])
    inik = 5'd23;
  else if (divider[22])
    inik = 5'd22;
  else if (divider[21])
    inik = 5'd21;
  else if (divider[20])
    inik = 5'd20;
  else if (divider[19])
    inik = 5'd19;  
  else if (divider[18])
    inik = 5'd18;  
  else if (divider[17])
    inik = 5'd17;  
  else if (divider[16])
    inik = 5'd16;  
  else if (divider[15])
    inik = 5'd15;  
  else if (divider[14])
    inik = 5'd14;  
  else if (divider[13])
    inik = 5'd13;  
  else if (divider[12])
    inik = 5'd12;  
  else if (divider[11])
    inik = 5'd11;  
  else if (divider[10])
    inik = 5'd10;
  else if (divider[9])
    inik = 5'd9;  
  else if (divider[8])
    inik = 5'd8;  
  else if (divider[7])
    inik = 5'd7;  
  else if (divider[6])
    inik = 5'd6;  
  else if (divider[5])
    inik = 5'd5;  
  else if (divider[4])
    inik = 5'd4;  
  else if (divider[3])
    inik = 5'd3;  
  else if (divider[2])
    inik = 5'd2;  
  else if (divider[1])
    inik = 5'd1;  
  else //if (divider[0])
    inik = 5'd0;    
end
//
wire div_end;
reg diven;
always @(posedge clk)
begin
  if (cpurst)
    diven <= 0;
  else if (div_end)
    diven <= 1'b0;  
  else if (diven_p)
    diven <= 1'b1;  
end

reg [4:0] cnt;
always @(posedge clk)
begin
  if (cpurst)
    cnt <= 0;
  else if (diven_p)
    cnt <= inik;
  else if (diven)
    cnt <= cnt+1'b1;  
end
assign div_end = (cnt == 5'd31) & diven;
//
reg [31:0] minued;
reg [32:0] q;

wire qbit = (minued >= divider[31:0]);
wire [31:0] newminued = minued - divider[31:0];
wire [31:0] nxt_minued = qbit ? {newminued,dividend[5'd31-cnt-1'b1]} : {minued,dividend[5'd31-cnt-1'b1]};
wire [32:0] nxt_q = {q[31:0],qbit};  //shift in right

wire [31:0] nxtrem = div_end ? (qbit ? newminued : minued) : 32'b0;

//wire [31:0] iniminued = dividend[31:(5'd31-inik)];
reg [31:0] iniminued;
always @*
begin
  if (divider[31])
    iniminued = dividend[31:0];
  else if (divider[30])
    iniminued = {1'b0,dividend[31:1]};
  else if (divider[29])
    iniminued = {2'b0,dividend[31:2]};
  else if (divider[28])
    iniminued = {3'b0,dividend[31:3]};
  else if (divider[27])
    iniminued = {4'b0,dividend[31:4]};
  else if (divider[26])
    iniminued = {5'b0,dividend[31:5]};
  else if (divider[25])
    iniminued = {6'b0,dividend[31:6]};
  else if (divider[24])
    iniminued = {7'b0,dividend[31:7]};
  else if (divider[23])
    iniminued = {8'b0,dividend[31:8]};
  else if (divider[22])
    iniminued = {9'b0,dividend[31:9]};
  else if (divider[21])
    iniminued = {10'b0,dividend[31:10]};
  else if (divider[20])
    iniminued = {11'b0,dividend[31:11]};
  else if (divider[19])
    iniminued = {12'b0,dividend[31:12]};  
  else if (divider[18])
    iniminued = {13'b0,dividend[31:13]};  
  else if (divider[17])
    iniminued = {14'b0,dividend[31:14]};  
  else if (divider[16])
    iniminued = {15'b0,dividend[31:15]};  
  else if (divider[15])
    iniminued = {16'b0,dividend[31:16]};  
  else if (divider[14])
    iniminued = {17'b0,dividend[31:17]};  
  else if (divider[13])
    iniminued = {18'b0,dividend[31:18]};  
  else if (divider[12])
    iniminued = {19'b0,dividend[31:19]};  
  else if (divider[11])
    iniminued = {20'b0,dividend[31:20]};  
  else if (divider[10])
    iniminued = {21'b0,dividend[31:21]};
  else if (divider[9])
    iniminued = {22'b0,dividend[31:22]};  
  else if (divider[8])
    iniminued = {23'b0,dividend[31:23]};  
  else if (divider[7])
    iniminued = {24'b0,dividend[31:24]};  
  else if (divider[6])
    iniminued = {25'b0,dividend[31:25]};  
  else if (divider[5])
    iniminued = {26'b0,dividend[31:26]};  
  else if (divider[4])
    iniminued = {27'b0,dividend[31:27]};  
  else if (divider[3])
    iniminued = {28'b0,dividend[31:28]};  
  else if (divider[2])
    iniminued = {29'b0,dividend[31:29]};  
  else if (divider[1])
    iniminued = {30'b0,dividend[31:30]};  
  else if (divider[0])
    iniminued = {31'b0,dividend[31:31]};    
  else
    iniminued = 32'b0;
end

always @(posedge clk)
  begin
    if (cpurst | !diven)
      begin
        minued <= iniminued;
        q      <= 0;
      end
    else
      begin
        minued <= nxt_minued;
        q      <= nxt_q;
      end      
  end
//
reg [31:0] rem, quo;
always @(posedge clk)
  begin
    if (cpurst)
      begin
        rem <= 0;
        quo <= 0;
      end
    else if (div_end)
      begin
        rem <= nxtrem;
        quo <= nxt_q;
      end      
  end
reg divout_valid;
always @(posedge clk)
  begin
    if (cpurst)
      begin
        divout_valid <= 0;
      end
    else 
      begin
        divout_valid <= div_end;
      end      
  end

endmodule
*/