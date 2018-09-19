#include <iostream>
#include <thread>
#include <mutex>
#include <unistd.h>
#include "semaphore.h"
using namespace std;

int main(){
    semaphore _se;
    _se.start(2,6);
    while(true){
        sleep(2000);
    }
    return 1;
}
