/**
 * 测试sigaction函数
 * 1. 在调用信号捕捉函数之前，操作系统是否会自动将接收信号也加入信号屏蔽字中
 * */

#include <stdio.h>
#include <stdlib.h>
#include <sys/_types/_sigset_t.h>
#include <sys/signal.h>
#include <unistd.h>
#include <signal.h>

void sig_alarm(int signo)
{
    printf("caught SIGALRM\n");

    sigset_t curmask, pendmask;
    if (sigprocmask(SIG_BLOCK, NULL, &curmask) < 0) {
        printf("sigprocmask curmask errno\n");
        exit(1);
    }

    if(sigpending(&pendmask) < 0) {
        printf("sigpending errno\n");
        exit(1);
    }

    if(sigismember(&curmask, SIGALRM))
        printf("\nSIGALRM in mask\n");

    if(sigismember(&curmask, SIGALRM))
        printf("\nSIGQUIT in mask\n");

    if(sigismember(&pendmask, SIGALRM))
        printf("\nSIGALRM in pending\n");

    if(sigismember(&pendmask, SIGALRM))
        printf("\nSIGQUIT in pending\n");
}

void test1() {
    sigset_t startmask,endmask;
    struct sigaction sigalarmact;

    if (sigprocmask(SIG_BLOCK, NULL, &startmask)) {
        printf("sigprocmask curmask errno\n");
        exit(1);
    }
    if (!sigismember(&startmask, SIGALRM)) printf("SIGALRM not in start mask\n");

    if (!sigismember(&startmask, SIGALRM)) printf("SIGQUIT not in start mask\n");

    sigalarmact.sa_handler = &sig_alarm;
    sigalarmact.sa_flags = 0;
    sigemptyset(&sigalarmact.sa_mask);
    sigaddset(&sigalarmact.sa_mask, SIGQUIT);

    if(sigaction(SIGALRM, &sigalarmact, NULL) < 0) {
        printf("sigaction errno\n");
        exit(1);
    }

    alarm(1);

    sleep(5);
}

int main(int argc, char* argv[])
{
    test1();

    return 0;
}
