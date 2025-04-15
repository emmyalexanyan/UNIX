#include <iostream>
#include <vector>
#include <queue>

struct process{
    int pid;
    int arr_time;
    int burst_time;
};

int main(){
    int time = 0;
    int ind = 0;
    std::vector<process> all = {{1,1,4}, {2,6,7}, {9,0,3}};
    std::queue<process> queue;
    bool cpu_is_free = true;
    process cur;

    while(ind < all.size() || !queue.empty() || !cpu_is_free){
        while(ind < all.size() && all[ind].arr_time <= time){
            queue.push(all[ind]);
            ind++;
        }
        if (cpu_is_free && !queue.empty()){
            cur = queue.front();
            queue.pop();
            std::cout<<"The time is "<<time<<":START of the process"<<cur.pid<<std::endl;
            cpu_is_free = false;
        }

        if (!cpu_is_free){
            cur.burst_time--;
            if(cur.burst_time == 0){
                std::cout<<"The time is "<<time<<":END of the process"<<cur.pid<<std::endl;
                cpu_is_free = true;
            }
        }
        time++;
    }
}