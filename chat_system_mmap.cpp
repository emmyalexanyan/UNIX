#include <iostream>
#include <sys/mman.h>
#include <sys/types.h>
#include <unistd.h>
#include <cstring>


#define MSG_SIZE 256 

int main() {
    void* shared_mem = mmap(nullptr, MSG_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    if (shared_mem == MAP_FAILED) 
    {
        perror("mmap failed");
        return 1;
    }

    pid_t pid = fork();

    if (pid < 0) {
        perror("fork failed");
        return 1;
    }

    if (pid == 0) 
    { 
        while (true) 
        {
            sleep(1);
            std::cout << "Child on reading process: " << static_cast<char*>(shared_mem) << std::endl;
            std::cout << "Child message: "<<std::endl;
            std::cin.getline(static_cast<char*>(shared_mem), MSG_SIZE);
        }
    } 
    else 
    { 
        while (true) 
        {
            std::cout << "Parent message: "<< std::endl;
            std::cin.getline(static_cast<char*>(shared_mem), MSG_SIZE);
            sleep(1);
            std::cout << "Parent on reading process: " << static_cast<char*>(shared_mem) << std::endl;
        }

        wait(nullptr);
        munmap(shared_mem, MSG_SIZE);
    }

    return 0;
}