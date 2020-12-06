#include "regfile.h"

void regfile_clked()
{
    regfileffs_clked[regfileffs_adr] = regfileffs_cs & regfileffs_wr ? regfileffs_wdat : regfileffs_clked[regfileffs_adr];

}