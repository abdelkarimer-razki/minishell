
#include "./d1/get_next_line.h"

int main()
{
    int i;
    int j;
    int fd;
    char *arg[5] = {"karim","errazki","nrahim","oudija","chaimae"};
    int k;

    j = 0;
    k = -1;
        fd = open("git_branchs1.txt", O_RDWR | O_CREAT | O_APPEND, 0777);
        dup2(1, fd);
        printf("hey %s\n", get_next_line(1));
        
}