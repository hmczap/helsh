#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

#define EXIT_OK             0
#define EXIT_ERR            1
#define EXIT_TERM           2
#define EXIT_STOP           3
#define ERR_CMD_NOT_FOUND   127
#define ERR_FILE_NOT_FOUND  128

#define LOOP_CMD_BUFSIZE    1024


char* readLine();
void loop();
int execute(char** args);
