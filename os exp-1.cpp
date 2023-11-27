#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
//main function begins
int main()
{
    fork();
    printf("the process is created using fork() system call\n");
    return 0;
}
