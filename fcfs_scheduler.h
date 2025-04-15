#ifndef FCFS_SCHEDULER_H
#define FCFS_SCHEDULER_H

#include <vector>
#include <queue>

struct process{
    int pid;
    int arr_time;
    int burst_time;
};

class FCFS_scheduler{
    public:
        FCFS_scheduler();
        void input_console();
        void run();

    private:
        std::vector<process> all;
        std::queue<process> queue;
        int time;
        int ind;
        bool cpu_is_free;
        process cur;
        void check();
        void start();
        void run_process();

};


#endif