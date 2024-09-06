#ifndef SHELL_H
#define SHELL_H
#define MAX_VAR_COUNT 32
#define MAX_VAR_LEN 256
#define MAX_VAR 100
#define NULL 0
#include "../std/io.h"
#include "../std/str.h"

typedef struct {
    char name[MAX_VAR_COUNT];
    char val[MAX_VAR_LEN];
} Variables;

Variables vars[MAX_VAR];
int vc = 0;

void setvar(const char* name, const char* val) {
    for (int i = 0; i < vc; i++)
        if (cmpstr(vars[i].name, name) == 0) {
            cpybytes(vars[i].val, val, MAX_VAR_LEN);

            return;
        }

    if (vc < MAX_VAR) {
        cpybytes(vars[vc].name, name, MAX_VAR_COUNT);
        cpybytes(vars[vc].val, val, MAX_VAR_LEN);
        vc++;
    }
}

const char* getvar(const char* name) {
    for (int i = 0; i < vc; i++)
        if (cmpstr(vars[i].name, name) == 0)
            return vars[i].val;

    return NULL;
}

void procdef(char* input) {
    char* name = input + lenstr("def ");

    char* equals = chrstr(name, '=');
    if (equals != NULL) {
        *equals = '\0';
        char* val = equals + 1;
        
        while (*val == ' ') val++;
        trmchr(name, ' ');
        setvar(name, val);
    } else {
        writeln("Syntax error in `def` command.");

        println(1);
        writeln("\n");
    }
}

void parse(char* input) {
    char* start = input + 5;
    char output[8192];
    char* finalptr = output;

    while (*start)
        if (*start == '$') {
            start++;
            char* end = start;

            while (*end && *end != ' ' && *end != '\0' && *end != '$')
                end++;

            char var[MAX_VAR_COUNT];

            cpybytes(var, start, end - start + 1);
            var[end - start] = '\0'; 
            
            const char* var_val = getvar(var);

            if (var_val)
                finalptr += cpybytes(finalptr, var_val, MAX_VAR_LEN);

            else {
                writeln("Undefined Variables: ");
                writeln(var);
                println(1);

                return;
            }

            start = end;
        } else
            *finalptr++ = *start++;

    *finalptr = '\0';

    writeln(output);
    println(1);
}

void exec(char* input) {
    if (findsub(input, "def") == input)
        procdef(input);

    else if (findsub(input, "echo") == input)
        parse(input);

    else {
        writeln("Unknown command");
        println(1);
    }
}

#endif
