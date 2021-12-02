#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <fcntl.h>

int main (int argc, char const *argv[]) { //cấp phát stack frame cho main
    pid_t tt_b, tt_c, tt_b1, tt_c1; //lưu trong stack frame
    int status;
    char *str_a  = "Hello I'm A  Process\n",
         *str_b  = "Hello I'm B  Process\n",
         *str_c  = "Hello I'm C  Process\n",
         *str_b1 = "Hello I'm B' Process\n",
         *str_c1 = "Hello I'm C' Process\n";
    int fd = open ("./bt.txt", O_RDWR | O_CREAT, 0777);

    tt_b = fork (); // tạo tt B từ A
    tt_c = fork (); // tạo tt C từ A

    if (tt_b >= 0 && tt_c >= 0) {
        if (tt_b == 0 && tt_c > 0) {
            // đang ở tiến trình B, giờ tạo tiến trình B'
            tt_b1 = fork ();
            if (tt_b1 > 0) {
                //đang ở tiến trình B, nhưng B phải đợi B' và C' in xong mới được in B
                waitpid (tt_b1, &status, 0);
                waitpid (tt_c1, &status, 0);
                write(fd , str_b , strlen(str_b));
            } 
            else if (tt_b1 == 0)
            {
                write(fd , str_b1 , strlen(str_b1));  
            } 
            else printf ("Loi");
        }
        else if (tt_b > 0 && tt_c == 0) {
            //đang ở tiến trình C, giờ tạo tiến trình C'
            tt_c1 = fork ();
            if (tt_c1 > 0) { //đang ở tiến trình C; nhưng C phải đợi B', C', B  in xong mới được in.
               // waitpid (tt_b1, &status, 0);
               // waitpid (tt_c1, &status, 0);   
                waitpid (tt_b, &status, 0);   
                waitpid (-1, &status, 0);        
                write(fd , str_c , strlen(str_c));
            }
            else if (tt_c1 == 0) { //đang ở tt C'; C' phải đợi B'
            waitpid (tt_b1, &status, 0);
            write(fd , str_c1 , strlen(str_c1));
        }
            else printf ("Loi");
        }
        else if (tt_b > 0 && tt_c > 0) {
            //đang ở tiến trình A. tiến trình A đợi B kết thúc rồi ghi
            waitpid(tt_b, &status, 0);
            waitpid(tt_b1 , &status, 0);  
            waitpid(tt_c1, &status, 0);          


            write(fd , str_a , strlen(str_a));
        }

    } else printf ("Tao tt con khong thanh cong"); //fork () == -1

    close (fd);
    return 0;
}
