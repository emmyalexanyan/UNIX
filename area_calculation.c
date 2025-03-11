#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

void calculate_rectangle_area() {
    double len = 5.0, wid = 3.0;
    double area = len * wid;
    printf("Child Process: Rectangle area = %.2f\n", area);
}

void calculate_triangle_area() {
    double side = 4.0, height = 6.0;
    double area = 0.5 * side * height;
    printf("Parent Process: Triangle area = %.2f\n", area);
}

int main(int argc, char *argv[]) {
    if (argc > 1) {
        if (strcmp(argv[1], "rectangle") == 0) {
            calculate_rectangle_area();
            return 0;
        } else if (strcmp(argv[1], "triangle") == 0) {
            calculate_triangle_area();
            return 0;
        }
    }

    pid_t pid = fork();

    if (pid < 0) 
    {
        perror("Fork failed");
        return 1;
    } 
    else if (pid == 0) 
    {
        execl("./area_calculation", "area_calculation", "rectangle", NULL);
        perror("execl failed"); 
        exit(1);
    } 
    else 
    {
        wait(NULL);
        execl("./area_calculation", "area_calculation", "triangle", NULL);
        perror("execl failed");
        exit(1);
    }
}
