#include <signal.h>
#include <stdio.h>
#include <stdlib.h>


//SIGINT
void handler(int a){
    printf("\nhandler is called!!\n");
    exit(0);
}

int main(void){
    printf("hello\n");

    signal(SIGINT, handler);

    while(1);
    return 0;
}
