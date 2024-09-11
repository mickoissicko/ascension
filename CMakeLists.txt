set(CMAKE_MINIMUM_REQUIRED_VERSION 3.29)
project(ascension)

add_executable(ascension/bin
    src/main.c
    src/proc.c
    src/interpreter/cmds/ls.c
    src/interpreter/cmds/sysrun.c
    src/interpreter/cmds/cd.c
    src/interpreter/helper/chklsarg.c
    src/interpreter/helper/err.c
    src/interpreter/helper/getsz.c
    src/interpreter/getmod.c
    src/interpreter/prepare.c
    src/interpreter/read.c
    src/interpreter/stdparse.c
    src/interpreter/interpreter.c
        src/interpreter/tokens/tokens.h
)
