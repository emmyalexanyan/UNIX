#include "fcfs_scheduler.h"
#include <iostream>

FCFS_scheduler::FCFS_scheduler() : time(0),ind(0), cpu_is_free(true){}

void FCFS_scheduler::input_console(){
    int n;
    std::cout<<"Please give number of processes and the input:";
    std::cin>>n;
    for(int i = 0;i < n; ++i){
        process temp;
        std::cin>>temp.pid >> temp.arr_time >> temp.burst_time;
        all.push_back(temp);
    }

}

void FCFS_scheduler::check(){
     while(ind < all.size() && all[ind].arr_time <= time){
            queue.push(all[ind]);
            ind++;
        }
}

void FCFS_scheduler::start(){
    if(cpu_is_free && !queue.empty()){
        cur = queue.front();
            queue.pop();
            std::cout<<"The time is "<<time<<":START of the process"<<cur.pid<<std::endl;
            cpu_is_free = false;
    }
}

void FCFS_scheduler::run_process(){
     if (!cpu_is_free){
            cur.burst_time--;
            if(cur.burst_time == 0){
                std::cout<<"The time is "<<time + 1<<":END of the process"<<cur.pid<<std::endl;
                cpu_is_free = true;
            }
        }
}

void FCFS_scheduler::run(){
    while (ind < all.size() || !queue.empty() || !cpu_is_free){
        check();
        start();
        run_process();
        time++;
    }
    
}

int main(){
    FCFS_scheduler scheduler;
    scheduler.input_console();
    scheduler.run();
       
}