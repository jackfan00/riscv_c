#ifndef DOWNLOADCODE_H
#define DOWNLOADCODE_H

void downloadCode(char * filename);

#include "reg.h"

#define MAXHEXFILE_CODESIZE 65536
REG32 HEXcodeaddr[MAXHEXFILE_CODESIZE];
REG32 HEXcodedata[MAXHEXFILE_CODESIZE];


#endif //DOWNLOADCODE_H