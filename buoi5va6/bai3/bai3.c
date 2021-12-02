#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <unistd.h>
/* chống zombie process: sử dụng signal để kiểm tra khi nào có sigchld thì thực hiện hàm func callback
*/
void func (int signal)
{
	wait(NULL);
	
}

int main()
{
	
    pid_t child_pid = fork ();

	if (child_pid >= 0) {

        if (child_pid == 0) {
            printf ("Dang o chuong trinh con. PID = %d", getpid ());
            while (1);
        }
		else {
            signal (SIGCHLD, func); 
            printf ("Dang o tien trinh cha. PID = %d", getpid ());   
            while (1);
        }
	}
	else printf ("Loi");
	return 0;
}