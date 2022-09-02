/**
 * 测试系统是否支持信号排队
 * */

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/signal.h>
#include <unistd.h>

void sig_quit(int signo)
{
    printf("caught SIGQUIT\n");
    if (signal(SIGQUIT, SIG_DFL) == SIG_ERR) {
        printf("can't reset SIGQUIT\n");
        exit(1);
    }
}

int main(int argc, char* argv[])
{
    sigset_t newmask,oldmask,pendmask;

    if (signal(SIGQUIT, sig_quit) < 0) {
        printf("can't set SIGQUIT\n");
        exit(1);
    }

    sigemptyset(&newmask);
    sigaddset(&newmask, SIGQUIT);
    if (sigprocmask(SIG_BLOCK, &newmask, &oldmask) < 0) {
        printf("sigprocmask error\n");
        exit(1);
    }

    sleep(5);

    if (sigpending(&pendmask) < 0) {
        printf("sigpending error\n");
        exit(1);
    }

    if (sigismember(&pendmask, SIGQUIT))
        printf("\nSIGQUIT pending\n");
    else
        printf("\nSIGQUIT not pending\n");

    if (sigprocmask(SIG_SETMASK, &oldmask, NULL) < 0) {
        printf("sigprocmask restore error\n");
        exit(1);
    }
    printf("unblock SIGQUIT\n");

    sleep(5);
    return 0;
}
