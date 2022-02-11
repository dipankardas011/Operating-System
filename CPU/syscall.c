#include "syscall.h"

extern int sys_fork(void);
extern int sys_start(void);
extern int sys_close(void);

static int (*syscalls[])(void) = {
    [SYSCALL_fork] sys_fork,
    [SYSCALL_start] sys_start,
    [SYSCALL_close] sys_close
};

enum LOCK
{
    Free,
    Allocated
};

extern enum LOCK keyIsAvailable = Free;

inline void acquire_lock() {
    keyIsAvailable = Allocated;
}

inline void release_lock() {
    keyIsAvailable = Free;
}