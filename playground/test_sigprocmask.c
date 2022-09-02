/**
 * 测试sigprocmask函数
 * 1. 查看默认值
 * */
#include <stdio.h>
#include <stdlib.h>
#include <sys/_types/_sigset_t.h>
#include <signal.h>
#include <sys/signal.h>
#include <unistd.h>
#include <errno.h>

int main(int argc, char* argv[])
{
    sigset_t sigset;
    int      errno_save;

    errno_save = errno;
    if (sigprocmask(0, NULL, &sigset) < 0) {
        printf("sigprocmake error\n");
        exit(1);
    }
    printf("SIGINT %d\n", sigismember(&sigset, SIGINT));
    printf("SIGQUIT %d\n", sigismember(&sigset, SIGQUIT));
    printf("SIGSTOP %d\n", sigismember(&sigset, SIGSTOP));
    printf("SIGUSER1 %d\n", sigismember(&sigset, SIGUSR1));
    printf("SIGALRM %d\n", sigismember(&sigset, SIGALRM));

    errno = errno_save;

    return 0;
}
