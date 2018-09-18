#include <iostream>
#include <thread>
#include <mutex>
#include <unistd.h>
#include "semaphore.h"
using namespace std;

mutex m_mutex;
int current_number = 0;

void hello1(){
     for(int index = 0;index < 10;index++){
            {
                lock_guard<mutex> lck(m_mutex);
                cout<<"try lock:"<<m_mutex.try_lock()<<endl;
                cout<<"current thread1 id:" <<this_thread::get_id()<<"   current_number:"<<current_number++<<endl;
            }
            if(m_mutex.try_lock()){
                cout<<"try lock success"<<endl;
                m_mutex.unlock();
            }
            this_thread::sleep_for(chrono::seconds(1));
            sleep(1);
     }
}
void test(){

     m_mutex.lock();
     cout<<"加锁完毕!"<<endl;
     {
        m_mutex.lock();
        cout<<"再次加锁"<<endl;
        m_mutex.unlock();
     }
     m_mutex.unlock();
}

void t(){}

int main(){
    //thread t1(hello1);
    //t1.detach();

    //thread t2(hello1);
    //t2.detach();

    //while(true){
      //  sleep(2);
    //}
    semaphore _se;
    _se.start(2,6);
    while(true){
        sleep(2000);
        // test for dev
         // tttt
         // lalallalaladadfadsf
    }
    return 1;
}
