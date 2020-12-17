#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "testfinishcheck.h"
#include "regfile.h"
#include "csrreg.h"
#include "ext_write_coderam.h"
#include "memwb.h"
#include "itcm.h"
#include "dtcm.h"
#include "init_rom.h"

void print_testresult()
{
    REG32 cycle_count;
    REG32 valid_ir_cycle;
    REG8 pc_write_to_host_cycle;

    cycle_count = mcycle_clked - teststart_cyclecount_clked;
    valid_ir_cycle = minstret_clked;
    pc_write_to_host_cycle = write_tohost_counter_clked;

        printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
        printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
        printf("~~~~~~~~~~~~~ Test Result Summary ~~~~~~~~~~~~~~~~~~~~~\n");
        printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
        printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
        printf("~~~~~~~~~~~~~~~~~~~~~TESTCASE: %s ~~~~~~~~~~~~~~~~~~~~~\n", testcase);
        printf("~~~~~~~~~~~~~~Total cycle_count value: %d ~~~~~~~~~~~~~\n", cycle_count);
        printf("~~~~~~~~~~The valid Instruction Count: %d ~~~~~~~~~~~~~\n", valid_ir_cycle);
        printf("~~~~~The test ending reached at cycle: %d ~~~~~~~~~~~~~\n", pc_write_to_host_cycle);
        printf("~~~~~~~~~~~~~~~The final x3 Reg value: %d ~~~~~~~~~~~~~\n", regfileffs_clked[3]);
        printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
}

void print_testpass()
{
        printf("~~~~~~~~~~~~~~~~ TEST_PASS ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
        printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
        printf("~~~~~~~~~ #####     ##     ####    #### ~~~~~~~~~~~~~~~~\n");
        printf("~~~~~~~~~ #    #   #  #   #       #     ~~~~~~~~~~~~~~~~\n");
        printf("~~~~~~~~~ #    #  #    #   ####    #### ~~~~~~~~~~~~~~~~\n");
        printf("~~~~~~~~~ #####   ######       #       #~~~~~~~~~~~~~~~~\n");
        printf("~~~~~~~~~ #       #    #  #    #  #    #~~~~~~~~~~~~~~~~\n");
        printf("~~~~~~~~~ #       #    #   ####    #### ~~~~~~~~~~~~~~~~\n");
        printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");    
}

void print_testfail()
{
        printf("~~~~~~~~~~~~~~~~ TEST_FAIL ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
        printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
        printf("~~~~~~~~~~######    ##       #    #     ~~~~~~~~~~~~~~~~\n");
        printf("~~~~~~~~~~#        #  #      #    #     ~~~~~~~~~~~~~~~~\n");
        printf("~~~~~~~~~~#####   #    #     #    #     ~~~~~~~~~~~~~~~~\n");
        printf("~~~~~~~~~~#       ######     #    #     ~~~~~~~~~~~~~~~~\n");
        printf("~~~~~~~~~~#       #    #     #    #     ~~~~~~~~~~~~~~~~\n");
        printf("~~~~~~~~~~#       #    #     #    ######~~~~~~~~~~~~~~~~\n");
        printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");    
}

int checksignature(REG32 * signature_ref, int index)
{
    int i, pass;
    REG32 signature;
    REG32 ramaddr;
    REG32 ramstartaddr;
    BIT itcmen;
    //
    pass=1;
    itcmen =  ((signature_startaddr & 0xff000000)==ITCM_ADDR_BASE);
    ramstartaddr = signature_startaddr & 0x00ffffff;
    printf("begin_signature at %x\n", signature_startaddr);
    printf("end_signature at %x\n", signature_startaddr+index*4);
    printf("Generate signature file\n");
    for (i=0;i<index;i++){
        ramaddr = ramstartaddr + i*4;
        signature = itcmen ? 
            (itcmRAM3[ramaddr>>2]<<24)|(itcmRAM2[ramaddr>>2]<<16)|(itcmRAM1[ramaddr>>2]<<8)|itcmRAM0[ramaddr>>2] :
            (dtcmRAM3[ramaddr>>2]<<24)|(dtcmRAM2[ramaddr>>2]<<16)|(dtcmRAM1[ramaddr>>2]<<8)|dtcmRAM0[ramaddr>>2] ;
        if (signature_ref[i]!=signature){
            pass=0;
            printf("%08x*%08x$", signature,signature_ref[i]);
        }
        else{
            printf("%08x-", signature);
        }
        //
        if ((i%4)==3){
            printf("\n");
        }
    }
    printf("\n");
    return(pass);
}

int testfinishcheck()
{
    BIT testpass;
    FILE *fp;
    char str[12];
    int index;
    REG32 signature_ref[256];

    //
    teststart_cyclecount = downloadper_clked & downloadcomplete ? mcycle_clked : teststart_cyclecount_clked;

    //
    write_tohost_counter = (memwb_pc == PC_WRITE_TOHOST) ? write_tohost_counter_clked+1 : write_tohost_counter_clked;

    if (write_tohost_counter_clked >= 8)
    {
        //
        printf("Intercept write_tohost.\n");
        if (HAS_REFERENCEOUT==1){
            fp = fopen(referenceout,"r");
            index=0;
            while (fgets(str,sizeof(str),fp)!=NULL){
                signature_ref[index]=strtoul(trimwhitespace(str), NULL, 16);
                index++;
            }
            fclose(fp);
            //
            testpass = checksignature(signature_ref, index);
        }
        else{
            testpass = regfileffs_clked[3];
        }
        //
        print_testresult();
        if (testpass){
            print_testpass();
        }
        else{
            print_testfail();
        }
        return(1);
    }

    //not finish
    return(0);
}
