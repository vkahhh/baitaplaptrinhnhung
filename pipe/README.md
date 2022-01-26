

>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> Server
1. Tạo tạo FIFOserver để lắng nghe request (well-know adress/name)
5. Có bản tin tới, thực bóc tách dữ liệu.
- ./fifoclient101
- 8
- key_request 
- <data kèm theo>

6. Kiểm tra dữ liệu
- hợp lệ: Gửi lại một bản tin ack thông báo request thành công tới ./fifoclient101 
	key hợp lệ
	service hợp lệ
- không hợp lệ: Gửi lại một bản tin ack thông báo request không thành công tới ./fifoclient101 

>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> Client

2. Tạo ra 1 FIFO để gửi nhận bản tin (FIFOclient).

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
- Nếu request không thành công: Thì báo lỗi, xóa file FIFO và kết thúc tiến trình.



>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> Cách đóng bản tin

kkkkkkkkkkkkkkkkkkkkkkkkkkkklllllllllllllllllllllllllllllllllvvvvvvvvvvvvvvvvvvvvvvvv
C1: kkkkkkkkkkkkkkkkkkkkkkkkkkkkFlllllllllllllllllllllllllllllllllFvvvvvvvvvvvvvvvvvvvvvvvvF
client 1: kkkkkkkkkkkkkkkkkkkkkkkkkkkk 
client 2: lllllllllllllllllllllllllllllllll
client 3: vvvvvvvvvvvvvvvvvvvvvvvv
- Kí tự phân tách bản tin thì không bao giờ được xuất hiện trong toàn bộ bản tin.
- Check tuần tự từng byte một. (tốn chi phí)

C2: Thêm header vào bản tin gửi đi. Bao gồm kích thước bản tin
20kkkkkkkkkkkkkkkkkkkkkkkkkkk15lllllllllllllllllllllllllllllllll10vvvvvvvvvvvvvvvvvvvvvvvv
- Qui ước độ dài bản tin là 2bytes. -> đọc 2 bytes đầu tiên từ FIFO
Client 1: 20 -> đọc tiếp 20 bytes tiếp theo: kkkkkkkkkkkkkkkkkkkkkkkkkkkk
Client 2: 15 -> đọc tiếp 15bytes tiếp theo: lllllllllllllllllllllllllllllllll
Client 3: 10-> đọc tiếp 10bytes tiếp theo: vvvvvvvvvvvvvvvvvvvvvvvv

- Ưu điểm: độ dài bản tin có thể thay đổi tùy ý.
- Bản tin có thể bị sai lệch nếu độ dài không đúng với 2 bytes header
C3: Sử dụng 1 độ dài cố định cho mỗi bản tin.
Qui định 10bytes 1 bản tin.
kkkkkkkkkkllllllllllmmmmmmmmmm
Client 1, 2, 3: Cứ đọc 10 bytes 1 là ra 1 bản tin.

Ưu điểm: Dễ có dễ triển khai.
Nhược điểm: 
kkkxxxxxxxllllllllllmmmmmmmmmm
- Băng thông dữ liệu bị gửi lãng phí
- Bản tin có thể bị sai lệch nếu có độ dài k phù hợp






















