
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
int flag_1, flag_2, fd;

void ghifile ()
{
	int msg[1000000];

	for (int i = 1; i <= 1000000; i++)
	{	

		if(i <= 500000)
		{ 

		    fd = open ("fileA.txt", O_RDWR | O_CREAT, 0777);
			flag_1 += 1;
			if ( flag_1 % 20 == 0) {
				fprintf (fd,"\n");}
			
		}

		if (500000 < i && i <= 1000000)
		{
			fd = open ("fileA.txt", O_RDWR | O_CREAT, 0777);
			flag_2 += 1;
			if ( flag_2 % 20 == 0) {
				fprintf (fd,"\n");}
		
		}
    }

	if (fd == NULL)
	   {
	      printf ("Error!");   
	      exit (1);             
	   }

    close (fd);

}
int main ()
{
	start = clock ();
	ghifile ();
	stop = clock ();
	double time_used = (stop - start) / CLOCKS_PER_SEC; 
	printf ("Thoi gian chay chuong trinh: %f", time_used);
}
