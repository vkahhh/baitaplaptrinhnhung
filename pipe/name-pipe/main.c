#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>


#define FIFO_FILE "./ff"

int main (int argc, const char *argv[]) {
    char buff [1024];

    //tao fifo
    mkfifo (FIFO_FILE, 0777);

    while (1) {
        //doc
        int fd = open (FIFO_FILE, O_RDONLY);
        read (fd, buff, 1024);

        printf ("Tin nhan den: %s", buff);
        close (fd);

        //ghi 
        printf ("\nPhan hoi: ");
        scanf  ("%s", buff);

        fd = open (FIFO_FILE, O_WRONLY);
        write (fd, buff, 1024);
        close (fd);
    }
    return 0;
}