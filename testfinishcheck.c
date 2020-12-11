#include <stdio.h>

#include "testfinishcheck.h"
#include "regfile.h"
#include "csrreg.h"
#include "ext_write_coderam.h"
#include "memwb.h"


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

int testfinishcheck()
{
    BIT testpass;

    if (HAS_REFERENCEOUT==1){

    }
    else{
        testpass = regfileffs_clked[3];
    }
    //
    teststart_cyclecount = downloadper_clked & downloadcomplete ? mcycle_clked : teststart_cyclecount_clked;

    //
    write_tohost_counter = (memwb_pc == PC_WRITE_TOHOST) ? write_tohost_counter_clked+1 : write_tohost_counter_clked;

    if (write_tohost_counter_clked >= 8)
    {
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
