#ifndef SHELL_H
#define SHELL_H
#define MAX__var_COUNT 32
#define MAX__var_LEN 256
#define MAX__var 100
#define NULL 0
#include "../std/symbols/map.h"
#include "../std/io/write.h"
#include "../decl/decl.h"
#include "../std/str.h"
#include "../std/num.h"

typedef struct
{
    char name[MAX__var_COUNT];
    char val[MAX__var_LEN];
} _variables;

static _variables _vars[MAX__var];
static int vc = 0;

void set_var(const char* name, const char* val)
{
    for (int i = 0; i < vc; i++)
        if (cmpstr(_vars[i].name, name) == 0)
        {
            cpybytes(_vars[i].val, val, MAX__var_LEN);
            return;
        }

    if (vc < MAX__var)
    {
        cpybytes(_vars[vc].name, name, MAX__var_COUNT);
        cpybytes(_vars[vc].val, val, MAX__var_LEN);
        vc++;
    }
}

const char* get_var(const char* name)
{
    for (int i = 0; i < vc; i++)
        if (cmpstr(_vars[i].name, name) == 0)
            return _vars[i].val;

    return NULL;
}

void procdef(char* input)
{
    char* name = input + lenstr("def ");
    char* equals = chrstr(name, '=');

    if (equals != NULL)
    {
        *equals = '\0';
        char* val = equals + 1;
        
        while (*val == ' ') val++;
        trmchr(name, ' ');
        set_var(name, val);
    }
    else
    {
        writeln("Syntax error in def command.");
        println(1);
        writeln("\n");
    }
}

void extractval(char* input, char* outpt)
{
    char* start = input;
    char* finalptr = outpt;

    while (*start)
    {
        if (*start == '$')
        {
            start++;
            char* end = start;

            while (*end && *end != ' ' && *end != '\0' && *end != '$')
                end++;

            char _var[MAX__var_COUNT];
            cpybytes(_var, start, end - start + 1);

            _var[end - start] = '\0'; 
            const char* _var_val = get_var(_var);

            if (_var_val)
                finalptr += cpybytes(finalptr, _var_val, MAX__var_LEN);

            else
            {
                writeln("Undefined _variable: ");
                writeln(_var);
                println(1);
                return;
            }

            start = end;
        }

        else
            *finalptr++ = *start++;
    }

    *finalptr = '\0';
}

void parse(char* input)
{
    char outpt[8192];
    extractval(input + 5, outpt);

    writeln(outpt);
    println(1);
}

char* run(char* input)
{
    static char _var[8192];
    
    extractval(input, _var);

    if (findsub(_var, var(2)) == _var)
        procdef(_var);

    else if (findsub(_var, var(1)) == _var)
        parse(_var);

    else if (findsub(_var, var(0)) == _var)
        return _var;

    else
    {
        writeln("Unknown command");
        println(1);
    }

    return NO_EXIT_EVENT;
}

#endif
