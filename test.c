#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

#define DEVICE "/dev/dev_driver"

int main()
{
    int fd;
    char buffer[1024];

    // puts("before open");
    fd = open(DEVICE, O_RDONLY);
    // puts("opened");


    if(fd < 0)
    {
        printf("Failed to open the device\n");
        return -1;
    }

    
    // puts("before reading");
    printf("%d\n", read(fd, buffer, 1024));
    // puts("read");

    printf("Read from device: %s\n", buffer);


    close(fd);

    return 0;
}
