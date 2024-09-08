#ifndef INCL_H
#define INCL_H
#define DEFAULT_INDENT_SZ 4
#define INCL "include "
#define BEGIN "begin."
#define ENTRY "begin def start"
#define F_END "end"
#define VIA "via "
#define ATH "ath."
#define END "end."
#define DEF "def "

#ifdef MAIN
#include <stdio.h>
void getsh(FILE* fp, char file[]);
int parse(FILE* fp, int _sz);
#endif

void stdparse(char str[], char label[]);
int checklsarg(const char program[]);
int _throw(char var1[], char var2[]);
void _read(char filename[]);
void ls(const char path[]);
int getindentsz(char f[]);
void exec(char program[]);
void cd(char path[]);

#ifdef VAR
char* var(int var);
#endif
#endif
