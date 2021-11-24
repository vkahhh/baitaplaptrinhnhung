//ct a tao ct b roi in ra pid, ppid
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main (void) 
{    
    pid_t child_pid;    
    child_pid = fork();
    
    if (child_pid == 0) 
    { 

        //child_pid: dinh danh (kp so pid); gt 0 cho biet dang o tt con
        printf ("Day la tien trinh b, pid = %d\n", getpid());     
        exit(1);

    }
    else if (child_pid > 0) 
    {
        // > 0 cho biet dang o tt cha
        printf ("Tien trinh a co pid = %d\n", getppid());
        
	}
    else 
    {
        printf ("Loi\n");
        exit(1);
    }
    return 0;
}