#include <stdlib.h>
enum procState
{
    UNUSED,
    EMBRYO,
    SLEEPING,
    RUNNING,
    RUNNABLE,
    RUNNING,
    ZOMBIE
};

struct context {
    uint edi;
    uint esi;
    uint ebx;
    uint ebp;
    uint eip;
};

struct scheduling {
};

struct niceness {
};

/**
 * As it is simple system the process synchronization is not applyed
 */
struct proc {
    uint sz;                        // size of process memory(bytes)
    enum procState state;           // state of it
    int PID;                        // process ID
    struct proc *parent;            // parent Address
    struct context *contextSwitch;  // contextSwitch
    char name[16];                  // process name
    struct scheduling sched;
    struct niceness ni;
};