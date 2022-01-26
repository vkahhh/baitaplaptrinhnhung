#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

char *msg = "mikasa";
int fds [2];
char buff [10];

int main (int argc, const char *argv [1]) {
    if (pipe (fds) < 0) printf ("Loi. \n");

    write (fds [1], msg, strlen (msg));
    read (fds [0], buff, 10);
    printf ("tin nhan: %s\n", buff);

    return 0;
}