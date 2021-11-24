/*Viết một chương trình A tạo ra một tiến trình con B. Bên trong A thực hiện tạo ra file hello.txt nằm ở đường dẫn 
./log/hello.txt và ghi thông điệp vào file đấy. Ở B sẽ thực hiện đọc lại nội dung file và in ra màn hình.
*/
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main () {

  pid_t child_pid;
  child_pid = fork ();
  char *str = "hihihoho";

  if (child_pid == -1) {

    printf("Loi");
  }
  else if (child_pid > 0) {
    printf ("tt cha da ghi vao file txt\n");
	  int fd = open ("./log/hello.txt", O_RDWR | O_CREAT, 0777);
    write(fd , str , strlen(str));
	  close (fd);
  
  }
  else if (child_pid == 0) {
          printf ("tt con doc file:\n");
          execl ("/bin/cat", "cat", "./log/hello.txt", NULL);
          return 0;
  }
  

}


