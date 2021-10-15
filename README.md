# riscv_c
This is a riscv(RV32IMC) implementation via C language.

It is a 4 stage (fetch, decode, execute, mem/wb) pipe line one-issue in-order architecture.

In order to simulate hardware clock behavoir, the code divided to two parts which are combinational and sequential.

It include .vcd format hardware waveform generatation for debug purpose (using gtkwave). 

Which the files' name include _clked are sequential part (i.e. flipflop output)

This implementation include RV32IMC core, PLIC, CLINT, UART, PWM, AHB-like BUS.



