#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

// #include <string.h>

#define DEVICE "/dev/dev_driver"
#define LEN 1024

int main()
{
    int fd;
    char buffer[LEN];

    fd = open(DEVICE, O_WRONLY);//###############
    // fd = open(DEVICE, O_RDONLY);


    if(fd < 0)
    {
        printf("Failed to open the device\n");
        return -1;
    }

    puts("input what you want to write:");

    // char ch;
    // int i = 0;
    // while ((ch = getchar()) != '\n')
    // {
    //     buffer[i] = ch;
    //     i++;
    // }
    
    fgets(buffer,LEN,stdin);// #################
    // cut the '\n'

    printf("This is your message: %s\n",buffer);
    // printf("This is your message: ");
    // for (int i = 0; i < 5; i++)
    // {
    //     putchar(buffer[i]);
    // }
    
    
    int ret = 0;
    ret = write(fd, (const char*)buffer, 1024);

    // printf("Read from device: %s\n", buffer);
    printf("Wrote: %d\n",ret);

    close(fd);

    return 0;
}
