#include "switch.hpp"

Switch sw(PA_0);


int main(){
    while(1){
        //printf("%d\n", sw.total_count);
        printf("%d %d %d\n", sw.interruptin.read(), sw.get(), sw.total_count);
        wait_ns(100000);
    }
}