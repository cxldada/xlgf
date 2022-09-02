#include <stdio.h>
#include <stdlib.h>
#include <sys/signal.h>
#include <unistd.h>

void sigUser(int signo)
{
    if (signo == SIGUSR1) { printf("received SIGUSR1\n"); }
    else if (signo == SIGUSR2) {
        printf("received SIGUSR2\n");
    }
    else {
        printf("received signal %d\n", signo);
    }
}

int main(int argc, char* args[])
{
    if (signal(SIGUSR1, sigUser) == SIG_ERR) {
        printf("can't catch SIGUSER1\n");
        return 1;
    }
    if (signal(SIGUSR2, sigUser) == SIG_ERR) {
        printf("can't catch SIGUSER1\n");
        return 2;
    }

    for (;;) pause();

    return 0;
}
