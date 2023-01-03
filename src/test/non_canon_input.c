#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>

struct termios prev_term;
struct termios modif_term;

//SIGINT
void handler(int a){
    printf("\nhandler is called!!\n");
    tcsetattr(STDIN_FILENO,TCSANOW,&prev_term);
    printf("%d %d\n",prev_term.c_cc[VMIN], prev_term.c_cc[VTIME]);
    exit(0);
}

int main(void){
    signal(SIGINT, handler);

    tcgetattr(STDIN_FILENO,&prev_term);
    printf("%d %d\n",prev_term.c_cc[VMIN], prev_term.c_cc[VTIME]);

    modif_term = prev_term;
    modif_term.c_cc[VMIN] = 0;
    modif_term.c_lflag &= ~(ICANON);
    tcsetattr(STDIN_FILENO,TCSANOW,&modif_term);

    struct termios temp;
    tcgetattr(STDIN_FILENO,&temp);
    printf("%d %d\n",temp.c_cc[VMIN], temp.c_cc[VTIME]);


    char buf[256];
    while(1){
        ssize_t len = read(STDIN_FILENO,buf,sizeof(buf));
        if(len < 0){
            puts("error occured");
            exit(1);
        }

        if(len > 1){
            buf[len] = '\0';
            printf("%s\n",buf);
        }

        usleep(1000000);
        puts("del");
    }

}
