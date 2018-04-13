#include <stdio.h>
#include <unistd.h>
#include <signal.h>
void sig_alarm(int signo)
{
    //Do Nothing
}
unsigned int my_sleep(unsigned int nsec)
{
    struct sigaction new_act;
    struct sigaction old_act;
    sigset_t newmask,oldmask,suspmask;
    unsigned int unslept=0;
    new_act.sa_handler=sig_alarm;
    sigemptyset(&new_act.sa_mask);
    new_act.sa_flags=0;
    sigaction(SIGALRM,&new_act,&old_act);//注册信号处理函数
    sigemptyset(&newmask);
    sigaddset(&newmask,SIGALRM);
    sigprocmask(SIG_BLOCK,&newmask,&oldmask);
    alarm(nsec);//设定闹钟
    suspmask=oldmask;
    sigdelset(&suspmask,SIGALRM);
    sigsuspend(&suspmask);
    unslept=alarm(0);//取消闹钟
    sigaction(SIGALRM,&old_act,NULL);//恢复默认信号处理处理动作
    sigprocmask(SIG_SETMASK,&oldmask,NULL);
    return unslept;

}
int main()
{
    while(1)
    {
        my_sleep(5);
        printf("5 seconds!\n");
        break;
    }
    return 0;
}
