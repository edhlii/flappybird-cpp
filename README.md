# 🐦 Flappy Bird Ứng dụng A.I và Giải thuật di truyền (C++ & raylib)

Một bản clone đơn giản của trò chơi **Flappy Bird**, được viết bằng **C++** và sử dụng thư viện đồ họa **raylib**. Nhóm chúng tôi đã tăng độ khó gameplay bằng cách di chuyển các ống nước theo chiều dọc. Bên cạnh đó, nhóm chúng tôi áp dụng **Mạng nơ-ron và Giải thuật di truyền (Neural Network, Genetic Algorithm)** để tạo ra A.I tự động chơi.  
Về phần A.I, có 2 loại A.I được ứng dụng. Đầu tiên là A.I truyền thống (**Agent0**). Tiếp đó là A.I dùng Neural Network (**Agent1**).  
Dự án này nhằm mục đích học tập và thực hành lập trình game cơ bản.
Thành viên dự án:
- Lê Đình Hiếu (B24DCAT095): Quản lý dự án, xử lý đồ hoạ, A.I.
- Nguyễn Thành Đạt (B24DCAT049): Xử lý logic, tính toán, A.I.
- Lưu Việt Hoàng (B24DCAT107): Xử lý bug, tester.

---

## 🎮 Gameplay

- Người chơi điều khiển chú chim bay qua các cột ống.
- Nhấn phím **Space** để làm chim bay lên.
- Nếu va chạm với ống hoặc rơi xuống đất → Game Over.
- Mỗi lần vượt qua một ống sẽ được +1 điểm.
- Xem A.I chơi