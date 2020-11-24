#include <stdio.h>
#include <string.h>
#include <time.h>

#define MAXVARSIZE 1000
#define DEFINESIZE 100

int varindex;
char *varreferences[MAXVARSIZE], *varids[MAXVARSIZE];
int varsize[MAXVARSIZE];
int defnum[DEFINESIZE];
char *defstr[DEFINESIZE];

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
}
void initvars()
{
    int i;
    int idx2, idx1,idx0;
    char *idchar = "<!@#$>^&*|";
    char tmp[4];

    //generate varids
    varindex=0;
    for (i=0;i<MAXVARSIZE;i++)
    { 
        varsize[i]=-1;
        //
        idx2 = i/100;
        idx1 = (i%100)/10;
        idx0 = i%10;
        tmp[0] = idchar[idx2];
        tmp[1] = idchar[idx1];
        tmp[2] = idchar[idx0];
        tmp[3] = '\0';
        varids[i] = strdup(tmp);
        //
    }
}

void initdefinevar(char * ff)
{
    int index, tmpi;
    FILE * fp;
    char str[100];
    char *token1s, *token2s;

    fp = fopen(ff,"r");
    index=0;
    while (fgets(str,100,fp)!=NULL)
    {
        char * strp = strdup(trimwhitespace(str));
        token1s = strsep(&strp, "//");
        if (*token1s==NULL)
            continue;
        //
        token2s = strsep(&token1s, " ");
        if (strcmp(trimwhitespace(token2s),"#define")==0){
            token2s = strsep(&token1s, " ");
            if (token1s!=NULL){
                tmpi= atoi(trimwhitespace(token1s));
                if (tmpi<=32){
                    defnum[index] = tmpi;
                    defstr[index] = strdup(token2s);
                    index++;
                }
            }
        }

    }

}
int getdefinevalue(char * kw, char * fn)
{
    int i;
    if (atoi(kw)>0){
        return(atoi(kw));
    }
    for(i=0;i<DEFINESIZE;i++){
        if (defstr[i]!=0 && strcmp(kw,defstr[i])==0){
            return(defnum[i]);
        }
    }
    printf("error: can not find define %s, filename=%s\n", kw, fn);
    return -1;
}


int getbitnumber(char * kw)
{
    if (strcmp(kw,"BIT")==0){
        return 1;
    }
    else if (strcmp(kw,"REG8")==0){
        return 8;
    }
    else if (strcmp(kw,"REG16")==0){
        return 16;
    }
    else if (strcmp(kw,"REG32")==0){
        return 32;
    }
    else {
        return -1;
    }

}

void parsevars(char * filename)
{

    //local
    int i,arraysize,bitnumber,j;
    char str[100];
    FILE *fp;
    char *token1s, *token2s, *tmp, *tmpcp, *tmp2;
    char iend[32][5];

    for (i=0;i<32;i++){
        j = i/10;
        iend[i][0]='[';
        iend[i][1]=j+'0';
        iend[i][2]=(i%10)+'0';
        iend[i][3]=']';
        iend[i][4]='\0';
    }

    fp = fopen(filename,"r");
    while (fgets(str,100,fp)!=NULL)
    {
        char * strp = strdup(trimwhitespace(str));

        //
        if (varindex>=MAXVARSIZE){
            continue;
        }
        //
        token1s = strsep(&strp, "//");
        if (*token1s==NULL)
            continue;
        //
        token2s = strsep(&token1s, " ");
        bitnumber = getbitnumber(trimwhitespace(token2s));
        if (bitnumber!=-1){  //valid
            token1s = strsep(&token1s, ";");
            tmp = strsep(&token1s, "[");
            if (token1s!=0 && *token1s!= NULL){
                tmp2 = strsep(&token1s, "]");
                arraysize = getdefinevalue(tmp2, filename);
                for (i=0;i<arraysize;i++){
                    tmpcp = strdup(tmp);
                    varreferences[varindex] = strcat(tmpcp,iend[i]);
                    varsize[varindex] =bitnumber;
                    varindex++;
                }
            }
            else{
                varreferences[varindex] = tmp;
                varsize[varindex] =bitnumber;
                varindex++;
            }
             
        }

        
        //
        
    }
    fclose(fp);
    printf("filename=%s, varindex=%d\n", filename, varindex);

}

void dumpcmdfile()
{
    int i;
    FILE *dc = fopen("../printtrace.c", "w");
    //
    fprintf(dc, "#include <stdio.h>\n");
    fprintf(dc, "#include \"reg.h\"\n");
    fprintf(dc, "#include \"fetch.h\"\n");
    fprintf(dc, "#include \"decode.h\"\n");
    fprintf(dc, "#include \"execu.h\"\n");
    fprintf(dc, "#include \"memwb.h\"\n");
    fprintf(dc, "#include \"regbus.h\"\n");
    fprintf(dc, "#include \"codebus.h\"\n");
    fprintf(dc, "#include \"databus.h\"\n");
    fprintf(dc, "#include \"memwb_bus.h\"\n");
    fprintf(dc, "#include \"mul.h\"\n");
    fprintf(dc, "#include \"lif.h\"\n");
    fprintf(dc, "#include \"dumpvars.h\"\n");
    fprintf(dc, "\n");
    fprintf(dc, "void printtrace(FILE * fp){\n");
    for (i=0;i<MAXVARSIZE;i++)
    {
        if ((varsize[i])==1)
        {
            fprintf(dc, "fprintf(fp,\"%%d%s\\n\",%s);\n",varids[i],varreferences[i]);
            //printf("printf(\"%%d%s\\n\",%s);\n",varids[i],varreferences[i]);
        }
        else if ((varsize[i])!=-1)
        {
            fprintf(dc, "fprintfb(fp,\"%02db%s\\n\",%s);\n",varsize[i],varids[i],varreferences[i]);
            //printf("printfb(\"%%%02db%s\\n\",%s);\n",varsize[i],varids[i],varreferences[i]);
        }
    }
    fprintf(dc, "}\n");
    fclose(dc);
    //
    dc = fopen("varids.txt", "w");
    for (i=0;i<MAXVARSIZE;i++)
    {
        if ((varsize[i])!=-1){
            fprintf(dc, "$var wire %d %s %s $end\n",varsize[i],varids[i],varreferences[i]);
        }
    }
    fclose(dc);

}

int main()
{
    initvars();
    //
    initdefinevar("../reg.h");
    //
    parsevars("../reg.h");
    parsevars("../fetch.h");
    parsevars("../decode.h");
    parsevars("../execu.h");
    parsevars("../memwb.h");
    parsevars("../regbus.h");
    parsevars("../codebus.h");
    parsevars("../databus.h");
    parsevars("../memwb_bus.h");
    parsevars("../mul.h");
    parsevars("../lif.h");
    //
    dumpcmdfile();

}

/*
void dumpvcd()
{
    FILE *vcdfp = fopen("riscv.vcd", "w");
    fprintf(vcdfp, "$version Generated by c $end\n");
    time_t t = time(NULL);
    struct tm *tm = localtime(&t);
    fprintf(vcdfp, "$date %s", asctime(tm));fprintf(vcdfp, "$end\n");
    fprintf(vcdfp, "$timescale 1ns $end\n");
    fprintf(vcdfp, "$scope module TOP $end\n");
    //
    parsevars("fetch.h");
    fprintf(vcdfp, "$scope module fetch $end\n");
    fprintf(vcdfp, "$upscope $end\n");
    //
    fprintf(vcdfp, "$scope module decode $end\n");
    fprintf(vcdfp, "$upscope $end\n");
    //
    fprintf(vcdfp, "$scope module execu $end\n");
    fprintf(vcdfp, "$upscope $end\n");
    //
    fprintf(vcdfp, "$scope module mul $end\n");
    fprintf(vcdfp, "$upscope $end\n");
    //
    fprintf(vcdfp, "$scope module memwb $end\n");
    fprintf(vcdfp, "$upscope $end\n");
    //
    fprintf(vcdfp, "$scope module codebus $end\n");
    fprintf(vcdfp, "$upscope $end\n");
    //
    fprintf(vcdfp, "$scope module databus $end\n");
    fprintf(vcdfp, "$upscope $end\n");
    //
    fprintf(vcdfp, "$scope module memwb_bus $end\n");
    fprintf(vcdfp, "$upscope $end\n");
    //
    fprintf(vcdfp, "$scope module regwbus $end\n");
    fprintf(vcdfp, "$upscope $end\n");
    //
    fprintf(vcdfp, "$scope module rs1bus $end\n");
    fprintf(vcdfp, "$upscope $end\n");
    //
    fprintf(vcdfp, "$scope module rs2bus $end\n");
    fprintf(vcdfp, "$upscope $end\n");

    fprintf(vcdfp, "$upscope $end\n");
    fprintf(vcdfp, "$enddefinitions $end\n");
    fprintf(vcdfp, "$dumpvars\n");

}*/