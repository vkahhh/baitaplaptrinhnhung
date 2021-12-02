#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main (int argc, char const *argv[]) { //cấp phát stack frame cho main
    pid_t child_pid; //lưu trong stack frame
    int status, rv;

    child_pid = fork ();
    if (child_pid >= 0) {
        if (child_pid == 0) printf ("Day la tien trinh con B, PID = %d\n", getpid ());
        else {
            rv = wait (&status);
            if (rv == -1) printf ("wait () ko thanh cong"); // wait () trả về lỗi (-1)
            else {
                    waitpid (child_pid, &status, 0);
                    printf ("Day la tien trinh A, PID = %d; Tien trinh B co PID = %d\n", getpid (), rv); 
                    if      (WIFSIGNALED (status)) printf("Loi\n, %d\n", WTERMSIG (status));
                    else if (WIFEXITED (status)) printf("Tien trinh B ket thuc binh thuong, stt = %d\n", WEXITSTATUS (status));
            /*
            WIFSIGNALED (status): ra gt khác 0 nếu status trả về do bị kill /WTERMSIG (status): gt signal gây ra kết thúc: kt do lệnh kill -9 thì ra value 9?
            WIFEXITED (status): ra gt khác 0 nếu tt kết thúc bthg /WEXITSTATUS (status): exit ()
            rv hoặc child_pid đều được tại vì khi chạy thành công ( trả về gt > 0 ), wait () trả về pid của tt con.*/
            } 
            
        }
    } else printf ("Tao tt con khong thanh cong"); //fork () == -1

    return 0;
}
