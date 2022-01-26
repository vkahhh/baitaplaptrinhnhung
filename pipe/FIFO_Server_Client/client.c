/*2. Tạo ra 1 FIFO để gửi nhận bản tin (FIFOclient).

template = ./fifoclient + PID
Client1 (101) ./fifoclient101
Client2 (102) ./fifoclient102

3. Đóng bản tin request để gửi tới Server
- Tên file fifo 
- Service đăng kí (là một số nguyên dương)
- Key: key_request

./fifoclient101 + 8 + key_request + <data kèm theo>

4. Gủi bản tin tới server thông qua well-know adress/name (FIFOserver)
7. Sau khi nhận ack
- Nếu request thành công: Thực hiện gửi nhận dữ liệu giữa client-server
- Nếu request không thành công: Thì báo lỗi, xóa file FIFO và kết thúc tiến trình.*/

#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>

#define GN_GT_0 02 /* Value must be > 0 */
#define GN_ANY_BASE 0100 /* Can use any base - like strtol(3) */
#define GN_BASE_8 0200 /* Value is expressed in octal */
#define GN_BASE_16 0400 

#define FIFO_SERVER  "./FIFOserver"
#define FIFO_CLIENT "./FIFOclient.%d" //FIFOclient.PID
#define CLIENT_FIFO_PATHNAME (sizeof (FIFO_CLIENT) + 10)

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

//bản tin ack để gửi từ server về phía client
struct response {
    int ack; //gồm ack
};


static char clientFifo[CLIENT_FIFO_PATHNAME];
static long getNum (const char *fname, const char *arg, int flags, const char *name) {
    long res;
    char *endptr;
    int base = (flags & GN_ANY_BASE) ? 0 : (flags & GN_BASE_8) ? 8 :  (flags & GN_BASE_16) ? 16 : 10;
    /* 
    - Kí hiệu ? và : :điều kiện trong C. 
    VD: result = (X>3) ? 'yes' : 'no' => nếu điều kiện (X<3) là ĐÚNG thì result trả về 'yes', SAI thì result trả về 'no'
    tương đương với if (X>3) result = 'yes'; else result = 'no'
    - &: bitwise AND: 1vs1 -> 1, còn lại ra 0*/
    /*
    - Ý nghĩa câu lệnh base (cơ số):
    1. Thực hiện phép AND với biến flags và 0100. nếu được thì cơ số = 0. nếu sai thì tiếp tục sd phép AND để có được các cơ số base = 8, 16, 10
    */
    res = strtol (arg, &endptr, base);
    //strol: tách chuỗi arg nhận được thành số nguyên (res) và chuỗi nội dung còn lại (endptr)
    return res;
}
//getInt: chuyển chuỗi arg thành kiểu int
int getInt (const char *arg, int flags, const char *name) {
    long res;
    res = getNum ("getInt", arg, flags, name);

    if (res > INT_MAX || res < INT_MIN) printf ("Loi\n");
    return (int) res;
}


int main (int argc, const char *argv [])
{

    struct request req;
    struct response resp;


/* 2. Tạo ra 1 FIFO để gửi nhận bản tin (FIFOclient).

template = ./fifoclient + PID
Client1 (101) ./fifoclient101
*/
    umask(0);
    snprintf (clientFifo, CLIENT_FIFO_PATHNAME, FIFO_CLIENT, (int) getpid());
    if (mkfifo (clientFifo, 0777) == -1) {
        printf ("Da xay ra loi trong qua trinh tao file  %s.\n", clientFifo);
        exit (1);
    } 

// 3. Đóng bản tin request để gửi tới Server
    req.pid = getpid ();
    req.service = (argc > 1) ? getInt (argv [1], GN_GT_0, "service") : 1; 
    //nếu argc > 1 thì biến req.service = getInt (argv [1], GN_GT_0, "service"). Ngược lại trả về 1
    req.key_request = 0;
    memcpy (req.msg, "hihihahahohohehe", 12);


//4. Gủi bản tin tới server thông qua well-know adress/name (FIFOserver)
    int serverFd = open (FIFO_SERVER, O_WRONLY);
    if (serverFd < 0) {
        printf ("Loi trong qua trinh mo file fifo phia server.\n");
        exit (1);
    }

    if (write (serverFd, &req, sizeof (struct request)) != sizeof (struct request)) {
        printf ("Loi ban tin request.\n");
        exit (1);
    }

/*
7. Sau khi nhận ack
- Nếu request thành công: Thực hiện gửi nhận dữ liệu giữa client-server
- Nếu request không thành công: Thì báo lỗi, xóa file FIFO và kết thúc tiến trình.
*/
    int clientFd = open (clientFifo, O_RDONLY);
    if (read (clientFd, &resp, sizeof (struct response)) != sizeof (struct response)) {
        printf ("Loi ban tin ack.\n");
        exit (1);
    }
       
    if (resp.ack < 0) {
        printf ("Request khong thanh cong.\n");
        close (serverFd);
        close (clientFd);
        unlink (FIFO_SERVER);
        unlink (clientFifo);
        exit (1);

    }
    else {
        printf ("Request thanh cong.\n");
        //In ra ack; Thực hiện gửi nhận dữ liệu giữa client-server
        printf("%d\n", resp.ack);
    
    

    }

}