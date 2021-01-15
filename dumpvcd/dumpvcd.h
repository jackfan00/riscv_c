#ifndef DUMPVCD_H
#define DUMPVCD_H
void dumpvcd();
void isconverge_h();
void isconverge_c();
char *strsep(char **stringp, const char *delim);
char *trimwhitespace(char *str);

#define MAXVARSIZE 9999
#define DEFINESIZE 100

int varindex;
char *varreferences[MAXVARSIZE], *varids[MAXVARSIZE];
int varsize[MAXVARSIZE], vararraysize[MAXVARSIZE];
int defnum[DEFINESIZE];
char *defstr[DEFINESIZE];

#endif //DUMPVCD_H
