cd src/ || return 1

gcc -o ../bin/bin                  \
    main.c                         \
    proc.c                         \
    interpreter/cmds/ls.c          \
    interpreter/cmds/sysrun.c      \
    interpreter/cmds/cd.c          \
    interpreter/helper/chklsarg.c  \
    interpreter/helper/err.c       \
    interpreter/helper/getsz.c     \
    interpreter/getmod.c           \
    interpreter/prepare.c          \
    interpreter/read.c             \
    interpreter/interpreter.c      \
    interpreter/stdparse.c
