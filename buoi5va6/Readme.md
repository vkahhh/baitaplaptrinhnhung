Bài tập buổi 5 và 6: Process và Thread

1. Viết một chương trình A tạo ra một tiến trình con B, in ra PID và PPID của chúng.  Sử dụng system waitpid() để lấy được trạng thái kết thúc của tiến con B.

2. Viết một chương trình A tạo ra hai tiến trình con B và C. Ở tiến trình B, C tạo tiến trình con B’, C’. Thực hiện ghi nội dung “Hello I’m B process”  ( Đối với tiến trình B và tương tự với các process còn lại) theo thứ tự B’-> C’ -> B -> C vào file. Ở tiến trình A, dùng waitpid() để xác định xem khi nào B kết thúc thì ghi vào file.

3. Từ kiến thức đã học, sử dụng SIGCHLD để ngăn ngừa việc hình thành zombie process.

4. Viết một chương trình thực hiện tạo 2 threads. Cả hai threads này đều dùng chung một hàm handle. Kiểm tra nếu là thread1 đang thực hiện thì in ra thông điệp bất kì để thông báo. Nếu là thread2 thì truyền vào dữ liệu kiểu struct human được khởi tạo từ trước, với các thông tin: Họ tên, năm sinh, sdt, quê quán.

