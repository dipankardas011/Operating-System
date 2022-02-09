#include "syscall.h"

extern int sys_fork(void);
extern int sys_start(void);
extern int sys_close(void);

static int (*syscalls[])(void) = {
    [SYSCALL_fork]      sys_fork,
    [SYSCALL_start]     sys_start,
    [SYSCALL_close]     sys_close
}