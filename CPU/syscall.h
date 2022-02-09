#include <stdlib.h>

/**
 * TODO: to be filled
 */
// these are dummy values
#define SYSCALL_fork      1
#define SYSCALL_exit      2
#define SYSCALL_start     3
#define SYSCALL_close     4
#define SYSCALL_end       5
#define SYSCALL_interrupt 6
#define SYSCALL_time      7

static int (*syscalls)