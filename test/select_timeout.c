
/*
ref
http://www.eyes-software.co.jp/news/archives/9
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <sys/select.h>
#include <sys/time.h>
#include <sys/timerfd.h>
#include <sys/types.h>

void error(char *msg){
    perror(msg);
    exit(1);
}

int main(void){
    int timer_fd = timerfd_create(CLOCK_MONOTONIC, 0);
    if(timer_fd < 0){
        error("timer");
    }
    struct itimerspec new_value;
    //struct timespec now;
    new_value.it_value.tv_sec = 2;
    new_value.it_value.tv_nsec = 0;
    new_value.it_interval.tv_sec = new_value.it_value.tv_sec;
    new_value.it_interval.tv_nsec = new_value.it_value.tv_nsec;
    if(timerfd_settime(timer_fd, 0, &new_value, NULL) == -1){
        error("settime");
    }

    fd_set fds;
    FD_ZERO(&fds);
    FD_SET(timer_fd, &fds);

    printf("timerfd = %d\n",timer_fd);

    int ret = select(timer_fd+1, &fds, NULL, NULL, NULL);
    if(ret < 0){
        error("select");
    }
    else{
        if(FD_ISSET(timer_fd,&fds)){
            puts("timerfd timeout");
            uint64_t exp;
            read(timer_fd, &exp, sizeof(uint64_t));
        }
    }

    puts("finished");
    close(timer_fd);
}


