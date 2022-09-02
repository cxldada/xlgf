#include <pwd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/signal.h>
#include <unistd.h>

void sig_alarm(int signo)
{
    struct passwd* rootptr;
    printf("in signal handler\n");
    if ((rootptr = getpwnam("root")) == NULL) {
        printf("getpwnam(root) error\n");
        exit(1);
    }
    alarm(1);
}

int main()
{
    struct passwd* ptr;

    signal(SIGALRM, sig_alarm);
    alarm(1);
    for (;;) {
        if ((ptr = getpwnam("cxl")) == NULL) {
            printf("getpwnam(cxl) error\n");
            exit(1);
        }
        if (strcmp(ptr->pw_name, "cxl") != 0) {
            printf("return value corrupted!, pw_name = %s\n", ptr->pw_name);
        }
    }

    return 0;
}
