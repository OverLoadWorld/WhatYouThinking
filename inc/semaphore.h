#ifndef SEMAPHORE_H
#define SEMAPHORE_H
#include <iostream>
#include <mutex>
#include <deque>
#include <thread>
#include <vector>
#include <condition_variable>
using namespace std;

class semaphore{
    public:
        semaphore(){
            _data.clear();
            count = 0;
        }
        void start(int product_num,int consume_num){
             vector<thread> threads;
             threads.clear();
             for(int index = 0;index < product_num;index++){
                threads.push_back(std::thread(&semaphore::product_thread,this));
             }
             for(int index = product_num;index < product_num + consume_num;index++){
                threads.push_back(std::thread(&semaphore::consume_thread,this));
             }

             for(auto& t:threads){
                t.detach();
             }
        }
    private:
        void product_thread(){
                while(true){
                    {
                        unique_lock<mutex> lck(_mutex);
                        if(_data.size() > 10){
                            cv.wait(lck);
                        }else{
                            cout<<"current product thread:"<<this_thread::get_id()<<" product "<<count<<endl;
                            count++;
                            count = count%10;
                            _data.push_back(count);
                            cv.notify_all();
                        }
                    }
                    chrono::milliseconds dura(1000);
			        this_thread::sleep_for(dura);
                }
        }        
        void consume_thread(){
                while(true){
                    {
                        unique_lock<mutex> lck(_mutex);
                        if(_data.empty()){
                            cv.wait(lck);
                        }else{
                            cout<<"current consume thread:"<<this_thread::get_id()<<" consume "<<_data.front()<<endl;
                            _data.pop_front();
                        }
                    }
                    chrono::milliseconds dura(2000);
                    this_thread::sleep_for(dura);
                }
        }
    private:
        int count;
        deque<int> _data;
        mutex _mutex;
        condition_variable cv; 
};
#endif  //SEMPHORE_H
