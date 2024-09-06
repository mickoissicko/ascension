#ifndef ECHO_H
#define ECHO_H
#include "write.h"
#include "../str.h"

// PUTMSG IS DEPRECATED
// PLEASE USE ECHO

int putmsg(int n, char** args) {
    if (n < 2) {
        writeln("Usage: <cmd> (<args>)");
        return 1;
    }

    int newline = 0;

    Command cmd;
    Command* ptr = &cmd;

    cpystruct(ptr, "echo");

    if (cmpstr(args[1], ptr->e) == 0) {
        if (n > 2) {
            writeln(args[2]);
        }

        else
            writeln("No argument provided");
    } else
        writeln("Invalid command");

    cpystruct(ptr, "::n");

    if (n > 3)
        if (cmpstr(args[3], ptr->e) == 0)
            return 1; // newline

    return 0; // no newline
}

#endif
