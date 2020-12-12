#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "downloadCode.h"
#include "ext_write_coderam.h"
#include "init_rom.h"
/*
char *strsep(char **stringp, const char *delim) {
    char *rv = *stringp;
    if (rv) {
        *stringp += strcspn(*stringp, delim);
        if (**stringp)
            *(*stringp)++ = '\0';
        else
            *stringp = 0; }
    return rv;
}

char *trimwhitespace(char *str)
{
  char *end;

  // Trim leading space
  while(isspace((unsigned char)*str)) str++;

  if(*str == 0)  // All spaces?
    return str;

  // Trim trailing space
  end = str + strlen(str) - 1;
  while(end > str && isspace((unsigned char)*end)) end--;

  // Write new null terminator character
  end[1] = '\0';

  return str;
}*/

void downloadCode(char * filename)
{
    REG32 linecode[16];
    int at_address, addrindex;
    int lineaddr, index, ii, codesize;
    FILE * fp;
    char str[200];
    char *token1s, *token2s, *tmp, *tmpcp, *tmp2;

    printf("init coderam via hex file %s\n",filename);

    fp = fopen(filename,"r");
    index=0;
    codesize=0;
    while (fgets(str,200,fp)!=NULL)
    {
        char * strp = strdup(trimwhitespace(str));

        token1s = strsep(&strp, "//");
        if ((*token1s)=='\0')//NULL)
            continue;
        //init
        for (ii=0;ii<sizeof(linecode)/sizeof(linecode[0]);ii++)
        {
            linecode[ii]=0;
        }
        //
        if (token1s[0]=='@'){  //code start address
            token2s = strsep(&token1s, "@");
            at_address = (int)strtol(trimwhitespace(token1s), NULL, 16);
            addrindex=0;
        }
        else{  // code body
            lineaddr=0;
            token2s = strsep(&token1s, " ");
            while((*token2s)!='\0')//NULL)
            {

                if (lineaddr>=sizeof(linecode)/sizeof(linecode[0])){
                    printf("Error: downloadCode excess linecode array size\n");
                    return;
                }
                //
                linecode[lineaddr] = (REG32)strtol(trimwhitespace(token2s), NULL, 16);
                lineaddr++;
                //
                if (token1s!=0 && (*token1s)!='\0'){//NULL){
                    token2s = strsep(&token1s, " ");
                }
                else{
                    break;
                }
                
            }
            codesize += lineaddr;
            //put in codearray
            ii=0;
            while (ii<lineaddr){
                HEXcodeaddr[index] = at_address+addrindex;
                HEXcodedata[index] = (linecode[ii+3]<<24)|(linecode[ii+2]<<16)|(linecode[ii+1]<<8)|linecode[ii];
                ii = ii+4;
                index++;
                addrindex+=4;
            }
            
        }
    }
    //
    if (codesize>=(MAXHEXFILE_CODESIZE*4)){
        printf("Error:Download Code: size=%d bytes, MAXHEXFILE_CODESIZE=%d bytes\n", codesize, MAXHEXFILE_CODESIZE*4);
        return;
    }
    printf("Download Code: size=%d bytes\n", codesize);
    download_codesize=(codesize>>2) + (codesize&0x03 ? 1 : 0);  // add reminder

}

