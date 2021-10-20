#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include "get_next_line.h"

int main(void)
{
    int fd = open("text.txt", O_RDONLY);
    //int fd2 = open("text2.txt", O_RDONLY);
    printf("gnl: %s", get_next_line(fd));
    //printf("----------------\n");
    printf("gnl: %s", get_next_line(fd));
   
    printf("gnl: %s", get_next_line(fd));
}