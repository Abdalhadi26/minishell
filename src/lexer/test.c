#include <stdio.h>
#include <stdlib.h>
 #include <sys/types.h>
       #include <sys/stat.h>
       #include <fcntl.h>
#include <string.h>
#include <errno.h>
int main()
{
    // int i = open("test.c", O_RDONLY);
    char *ptr = malloc(111111111110);
    if (!ptr)
        {
           printf("%s ",strerror(errno));
            perror("malloc");
            printf("errno: %d\n", errno);
            return 1;}
        free(ptr);
    int j = open("lexer.c", O_RDONLY);
    perror("open");
    printf("errno: %d\n", errno);
    printf("errno: %d\n", j);

    if (j ==-1 || j == 0)
    {
        printf("%s ",strerror(errno));
        return 1;
    }
  
    
    char *input = "cat > file1.txt";
     int i = 0;
    while (input[i])
    {
        printf("%c\n", input[i]);
        i++;
    }
    return (0);
}