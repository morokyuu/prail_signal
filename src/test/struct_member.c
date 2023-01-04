#include <stdio.h>

typedef struct{
    int aho;
    int baka;
}iremon_t;

void kakikae(int *aho){
    *aho += 5; 
}

int main(void){
    iremon_t iremon = {
        .aho = 10,
        .baka = 3
    };
    kakikae(&(iremon.aho));

    printf("%d,%d\n",iremon.aho, iremon.baka);
}


