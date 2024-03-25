#include "defs.h"

char* readLine(){
    int bufSize = LOOP_CMD_BUFSIZE;
    char* buffer = malloc(sizeof(char) * bufSize);
    if (!buffer){
        printf("FAILURE TO ALLOCATE MEMORY");
        exit(EXIT_ERR);
    }    
    
    if (fgets(buffer, bufSize, stdin) == NULL){
        printf("ERROR OR EOF");
        exit(EXIT_ERR);
    }
    return buffer;
}

int execute(char** args){
    pid_t pid;
    pid_t wpid;
    int status = 0;

    pid = fork();
    if (pid == 0) {
        if (execvp(args[0],args) == -1){
            printf("ERROR: CANNOT EXECUTE");
            exit(EXIT_ERR);
        }
    } else if (pid < 0){
        printf("ERROR: CANNOT FORK");
        exit(EXIT_ERR);
    } else {
        do {
            wpid = waitpid(pid, &status, WUNTRACED);
        } while (!WIFEXITED(status) && !WIFSIGNALED(status));
    }
    return 1;
}


char** parseCommand(char* line){
    int bufSize = LOOP_CMD_BUFSIZE;
    int i = 0;
    char** tokens = malloc(bufSize*sizeof(char*));
    char* token;

    if (!tokens){
        printf("FAILURE TO ALLOCATE MEMORY");
        exit(EXIT_ERR);
    }

    token = strtok(line, " \n\r\a\t");
    while (token != NULL){
        tokens[i] = token;
        i++;

        if (i >= bufSize){
            bufSize += LOOP_CMD_BUFSIZE;
            tokens = realloc(tokens, bufSize * sizeof(char*));
            if (!tokens){
                printf("FAILURE TO REALLOCATE MEMORY");
                exit(EXIT_ERR);
            }
        }
        token = strtok(NULL, " \n\r\a\t");
    }
    tokens[i] = NULL;
    return tokens;
}

void loop() {
    char* line;
    char** args;
    int status = 1;

    do {
        printf("> ");
        line = readLine();
        args = parseCommand(line);
        if (strcmp(args[0], "exit") == 0){
            status = 0;
        } else if (strcmp(args[0], "echo") == 0){
            int i = 1;
            while (args[i] != NULL){
                printf("%s", args[i]);
                i++;
            }
            printf("\n");
        } else {
            printf("%s\n", args[0]);
        }
        free(line);
    } while (status);
}

int main(){
    loop();
    return EXIT_OK;
}
