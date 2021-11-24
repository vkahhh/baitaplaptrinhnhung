// Tạo file filesystem.txt và ghi một đoạn dự liệu bất kì. Thực hiện ghi ra màn hình các thông tin: Loại file,  thời gian chỉnh sửa file lần cuối, kích thước.

#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <stdint.h>
#include <time.h>
#include <sys/sysmacros.h>

int main (void) {
    int fd;
    struct stat sb;
    char buf[7] = "hihihi\n";
    fd = open ("filesystem.txt", O_RDWR | O_CREAT, 0777);
    if ( fd == -1 ) printf ("Loi");
    else {
        int rd = read (fd, buf, strlen (buf));
        stat ("filesystem.txt", &sb);
   
        printf("File type:                ");

           switch (sb.st_mode & S_IFMT) {
           case S_IFBLK:  printf("block device\n");            break;
           case S_IFCHR:  printf("character device\n");        break;
           case S_IFDIR:  printf("directory\n");               break;
           case S_IFIFO:  printf("FIFO/pipe\n");               break;
           case S_IFLNK:  printf("symlink\n");                 break;
           case S_IFREG:  printf("regular file\n");            break;
           case S_IFSOCK: printf("socket\n");                  break;
           default:       printf("unknown?\n");                break;
           }


           printf("Mode:                     %jo (octal)\n",
                   (uintmax_t) sb.st_mode);

           printf("File size:                %jd bytes\n",
                   (intmax_t) sb.st_size);

    	   printf("Last file modification:   %s", ctime(&sb.st_mtime));

    }   
}
