1. Stream Socket còn được gọi là socket TCP. Nó hoạt động dựa trên giao thức hướng kết nối. Tức là chỉ sử dụng được khi máy chủ và máy khách có sự liên kết.
Stream Socket giúp quá trình truyền gửi diễn ra nhanh chóng và đúng hạn. Ngoài ra, với yếu tố đảm bảo, người dùng cũng có thể yên tâm rằng dữ liệu sẽ được 
chuyển đến đúng người nhận với độ tin cậy tuyệt đối. Mỗi hành động diễn ra trong quá trình dịch chuyển thông tin đều sẽ được ghi lại kết quả và truyền về 
cho người dùng dù có thành công hay không. Các bản ghi dữ liệu cũng không hề có giới hạn nào, bạn có thể thoải mái truyền bao nhiêu thông tin tùy thích. 
Song song với đó, Stream Socket còn sở hữu 2 cơ chế bao gồm quản lý luồng lưu thông trên mạng và chống tắc nghẽn nhằm tối ưu hóa thời gian truyền dữ liệu.

2. Datagram Socket hoạt động dựa trên giao thức UDP về việc truyền thông tin không yêu cầu sự kết nối. Để hoạt động này diễn ra, nó cung cấp connection-less 
point cho việc gửi và nhận thông tin. Chính vì thế mà Datagram Socket còn được gọi là socket không hướng kết nối.
Hai tiến trình có thể liên lạc với nhau thông quan Datagram Socket mà không cần IP chung. Thông điệp muốn gửi đi phải kèm theo thông điệp người nhận. Có 
thể gửi một thông điệp nhiều lần, tuy nhiên không thể gửi cùng một lúc. Ngoài ra, thứ tự hoàn thành dịch chuyển cũng không cố định, thông điệp gửi sau 
có thể đến trước và ngược lại.
Datagram Socket không đảm bảo tuyệt đối kết quả của tiến trình. Một số trường hợp ghi nhận thông điệp không thể đến tay của bên nhận. Cùng với đó, điều 
kiện để thực hiện các cuộc trao đổi 2 đầu là 1 trong 2 tiến trình phải công bố port của socket mà mình đang sử dụng.
Tuy nhiên vì không yêu cầu kết nối của 2 tiến trình nên quá trình truyền dữ liệu diễn ra vô cùng nhanh chóng, phù hợp để ứng dụng trong cách hoạt động 
như nhắn tin, chat game online… 
