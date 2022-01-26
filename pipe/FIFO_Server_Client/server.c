/* Server
1. Tạo  FIFOserver để lắng nghe request (well-know adress/name)
5. Có bản tin tới, thực bóc tách dữ liệu.
- ./fifoclient101
- 8
- key_request 
- <data kèm theo>

6. Kiểm tra dữ liệu
- hợp lệ: Gửi lại một bản tin ack thông báo request thành công tới ./fifoclient101 
	key hợp lệ
	service hợp lệ
- không hợp lệ: Gửi lại một bản tin ack thông báo request không thành công tới ./fifoclient101 */

#include <fcntl.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

#define FIFO_SERVER  "./FIFOserver"
#define FIFO_CLIENT "./FIFOclient.%d" //tên file: FIFOclient.PID
#define CLIENT_FIFO_PATHNAME (sizeof (FIFO_CLIENT)+ 10) //pathname FIFO client

/* 
Bản tin request để gửi tới Server:
- Tên file fifo 
- Service đăng kí (là một số nguyên dương)
- Key: key_request
- <data kèm theo>
*/
struct request {
    pid_t pid; //-> tên file fifo: FIFOClient thêm PID
    int service; //service đăng kí
    int key_request; //key 
    char msg[1024]; // data kèm theo
    
};

//bản tin response để gửi từ phía server về client
struct response {
    int ack; // bao gồm ack
};

int main (int argc, const char *argv [])
{
	char clientFifo[CLIENT_FIFO_PATHNAME];
	struct request req;
    struct response resp;
    int ack = 0; 

    //1. Tạo FIFOserver để lắng nghe request (well-know adress/name)
    if (mkfifo (FIFO_SERVER, 0777) == -1) {
        printf ("Da xay ra loi trong qua trinh tao FIFOServer.\n");
        exit (1);
    } 
    
    int serverFd = open (FIFO_SERVER, O_RDONLY);
    if (serverFd < 0) {
        printf ("Loi trong qua trinh mo file fifo phia server.\n");
        exit (1);
    }
    
/*
5. Có bản tin tới, thực hiện bóc tách dữ liệu.
- ./fifoclient101
- 8
- key_request 
- <data kèm theo>

6. Kiểm tra dữ liệu
- hợp lệ: Gửi lại một bản tin ack thông báo request thành công tới ./fifoclient101 
	key hợp lệ
	service hợp lệ
- không hợp lệ: Gửi lại một bản tin ack thông báo request không thành công tới ./fifoclient101 
*/
    while (1) 
{
    if (read (serverFd, &req, sizeof (struct request)) != sizeof (struct request)) {
         printf ("Loi doc request.\n");
         exit (1);
    }
    
    snprintf (clientFifo, CLIENT_FIFO_PATHNAME, FIFO_CLIENT, (int) req.pid);
    
    int clientFd = open (clientFifo, O_WRONLY);
    if (clientFd < 0) {
        printf("Loi trong qua trinh mo client %s", clientFifo);
        exit (1);
    }

    
    if ((req.key_request < 0) || (req.service < 0)) ack = -1;
    resp.ack = ack;

    if (write (clientFd, &resp, sizeof (struct response)) != sizeof (struct response)) {
        printf ("Loi viet respone cho %s.\n", clientFifo);
    } 
    
    close (clientFd);

    ack += req.service; 

    read (serverFd, req.msg, 1024);
    printf ("%s \t", req.msg);
    }
    close (serverFd);


}