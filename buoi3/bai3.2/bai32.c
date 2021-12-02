
/*Viết một chương trình thực hiện ghi giá trị từ 
1-1000000 vào hai file riêng fileA.txt và fileB.txt. Tính toán thời gian thực hiện.*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <stdint.h>
#include <time.h>
#include <sys/sysmacros.h>

clock_t start, stop;
int fd;
void ghifile ()
{
	int fd1, fd2;
	int n = 1000000;
	int i;
	char str1[500000], str2[500000];
	//file A:
	fd1 = open ("fileA.txt", O_RDWR | O_CREAT | O_APPEND, S_IRUSR | S_IWUSR);
	for (i = 1; i <= 500000; i ++) {

		snprintf(str1, 500000 , "%d\n", i);
		write(fd1, str1, strlen(str1));

    }
	close (fd1);
	//file B
	
	fd2 = open ("fileB.txt", O_RDWR | O_CREAT | O_APPEND, S_IRUSR | S_IWUSR);
	for (i = 500000; i <= n; i ++) {

		snprintf(str2, 500000 , "%d\n", i);
		write(fd2, str2, strlen(str2));

    }
	close (fd2);




}
int main ()
{
	start = clock ();
	ghifile ();
	stop = clock ();
	double time_used = (stop - start) / CLOCKS_PER_SEC; 
	printf ("Thoi gian chay chuong trinh: %f", time_used);
}
