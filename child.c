#include "unistd.h"
#include "stdio.h"

int string_validation(char *line) {
    int i = 0;
    while (line[i] != '\0') {
        i++;
    }
    if (line[i-1] == '.' || line[i-1] == ';') {
        return 0;
    }
    return 1;
}

int main(int count, char* filename[]) {
    FILE *output = NULL;
    output = fopen(filename[0], "w");
    //printf("It's child %s", filename[0]);
    if (output == NULL) {
        printf("File error!\n");
        fclose(output);
        return 1;
    }
    char line [256];
    while(read(STDIN_FILENO, line, sizeof(line)) > 0) {
        //printf("Line = %s", line);
        if (string_validation(line) == 0) {
            fprintf(output, "%s\n", line);
            //fputs(line, output);
        }
        else {
            //printf("Error = %s\n", line);
            //dup2(fd2[0], STDIN_FILENO);
            //printf("Error string: %s", line);
            int i = 0;
            write(STDOUT_FILENO, "Error string: ", sizeof("Error string: "));
            while (line[i] != '\0') {
                write(STDOUT_FILENO, &line[i], sizeof(char));
                i++;
            }
            write(STDOUT_FILENO, "\n", sizeof("\n"));
        }
    }
    fclose(output);
}