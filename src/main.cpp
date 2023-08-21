#include "switch.hpp"

Switch sw(PA_0);


int main(){
    while(1){
        printf("%d\n", sw.get());
        wait_ns(100000);
    }
}