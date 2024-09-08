cd src/

gcc -o ../bin/bin               \
    main.c                      \
    proc.c                      \
    compiler/cmds/ls.c          \
    compiler/cmds/sysrun.c      \
    compiler/cmds/cd.c          \
    compiler/helper/chklsarg.c  \
    compiler/helper/err.c       \
    compiler/helper/getsz.c     \
    compiler/getmod.c           \
    compiler/prepare.c          \
    compiler/read.c             \
    compiler/parse.c            \
    compiler/stdparse.c
