#include "switch.hpp"
#include <chrono>

Switch::Switch(PinName pin, unsigned int interval, unsigned int detectionThreshold): interruptin(pin), interval(interval), detectionThreshold(detectionThreshold)
{
    monitoring = false;
    status = interruptin.read();
    interruptin.rise([this] {riseInterrupt();});
    interruptin.fall([this] {fallInterrupt();});
}

//押されてるか否か
bool Switch::get(){
    return status;
}

//立ち上がり割り込み
void Switch::riseInterrupt(){
    if(monitoring || status){
        return;
    }
    monitoring = true;
    ticker.attach([this] {riseCheck();}, std::chrono::milliseconds(interval));
}

//サンプリング．チャタリング対策
void Switch::riseCheck(){
    if(interruptin.read()){
        counter++;
        if(counter >= detectionThreshold){
            status = true;
            ticker.detach();
            monitoring = false;
            total_count++;
        }
    }else{
        counter=0;
        ticker.detach();
        monitoring = false;
    }
}


void Switch::fallInterrupt(){
    /*
    if(!monitoring){
        status = false;
    }
    */
    status = false;
    counter = 0;
    ticker.detach();
    monitoring = false;
}

