#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* readLine(){
    int bufSize = 64;
    char* buffer = malloc(sizeof(char) * bufSize);
    if (!buffer){
        printf("FAILURE TO ALLOCATE MEMORY");
        exit(1);
    }    
    
    if (fgets(buffer, bufSize, stdin) == NULL){
        printf("ERROR OR EOF");
        exit(1);
    }
    return buffer;
}

void loop() {
    char* line;
    int status = 1;

    do {
        printf("> ");
        line = readLine();
        if (strcmp(line, "exit\n") == 0){
            status = 0;
        } else {
            printf("%s\n", line);
        }
        free(line);
    } while (status);
}

int main(){
    loop();
    return 0;
}
