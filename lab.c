// Лабораторная работа №2
// Вариант 16 
#include "stdio.h"
#include "unistd.h"

int main() {
    printf("Введите имя файла: ");
    //fflush(stdout);
    char filename [256];
    scanf("%s", filename);
    int fd2[2]; // Указатель на массив из двух целых переменных 
    int fd1[2];
    if (pipe(fd2) < 0) {
        printf("Pipe error!");
        return -1;
    }
    if (pipe(fd1) < 0) {
        printf("Pipe error!");
        return -1;
    }
    int ID = fork();
    if (ID < 0) {
        printf("Fork error!\n");
        return 1;
    }
    else if (ID > 0) {
        close(fd1[0]);
        close(fd2[1]);
        char line [256];
        /*
        if (read(fd2[0], line, sizeof(line)) > 0) {
            printf("Error string: ");
        }
        */

        while (scanf("%s", line) > 0) {
            write(fd1[1], line, sizeof(line));
        }

        //fflush(stdout);
        //printf("Error string: \n");
        
        close(fd1[1]);
        close(fd2[0]);
    }
    else {
        //fflush(stdout);
        close(fd1[1]);
        close(fd2[0]);
        dup2(fd1[0], STDIN_FILENO);
        if (!execl("child.out", filename, NULL)) {
            return -1;
        }
        //execl("child.out", filename, NULL);
        close(fd1[0]);
        close(fd2[1]);
    }
    return 0;
}