/***
 * 测试alarm函数
 * 1. 第二次设置的值 < 第一次设置的值，检测返回值
 * 2. 直接设置为0会不会产生信号
 * */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/signal.h>

void sig_alarm(int signo)
{
    printf("int signal handler. signo: %d\n", signo);
}

void test1()
{
    if (signal(SIGALRM, sig_alarm) == SIG_ERR) {
        printf("signal SIGALRM error\n");
        exit(1);
    }

    unsigned int uiLostSec = alarm(50);
    printf("first alarm return: %u\n", uiLostSec);
    uiLostSec = alarm(10);
    printf("second alarm return: %u\n", uiLostSec);
}

void test2()
{
    if (signal(SIGALRM, sig_alarm) == SIG_ERR) {
        printf("signal SIGALRM error\n");
        exit(1);
    }

    unsigned int uiLostSec = alarm(0);
    printf("test2 return: %u\n", uiLostSec);
}

int main(int argc, char* argv[])
{
    test1();

    pause();

    test2();

    return 0;
}
