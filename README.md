# 22026507_MaiTienManh

Quá trình code game:

Đầu tiên, em xem các video trên youtube và trang lazyfoo để hiểu và xây dựng những điều nền tảng, cơ bản của game. 
Sau đó em tự thêm các chức năng như menu, tạo ra thêm các loại quái vật khác nhau,...

Tiếp theo em tối ưu code của mình. Em tạo ra nhiều file, hàm khác nhau xử lí từng nhiệm vụ riêng biệt. Ví dụ như:
        Em tạo Menu.h và Menu.cpp để quản lí menu.
        Em tạo nhiều hàm với nhiệm vụ riêng biệt như handleCollison() thì sẽ xử lí khi va chạm thì ra sao...
Và ở main.cpp em chỉ gọi game.init(), game.runGameLoop() để chạy game và game.cleanup() để xóa.

Ý tưởng của game

Game được dựa trên ý tưởng từ tựa game cổ điển 2d "Contra" đã từng rất nổi tiếng trên điện thoại bàn phím. 
Trong game, người chơi sẽ hóa thân vào nhân vật chính, vượt qua các thử thách và tiêu diệt các quái vật gặp trên cuộc hành trình để dành chiến thắng.

Lý do chọn game
Lý do em chọn game này là thể loại này em từng rất hay chơi hồi còn nhỏ và một lí do nữa là trên mạng có một series video hướng dẫn khá kĩ về những phần cơ bản của game này.

Các chức năng chính của game

Điều khiển nhân vật di chuyển trái, phải, lên, xuống để vượt qua các chướng ngại vật, tránh né đạn của quái vật và tránh va chạm với chúng.
Có một con rồng đuổi theo đằng sau và có giới hạn thời gian. Vậy nên người chơi cần điều khiển nhân vật một cách hiệu quả để hoàn thành thử thách.
Có các cấp độ khó khác nhau cho người chơi lựa chọn.

Đề xuất hướng cải thiện game tiếp theo
Thêm tính năng nhặt súng, đạn. Khi nhặt được sẽ thay đổi loại đạn bắn ra.
Thêm một con boss ở cuối game.
Thêm các vật phẩm, ví dụ như ăn vào tăng tốc độ, miễn thương, thêm mạng sống...
Thêm bảng xếp hạng lưu giữ điểm số

Tài liệu tham khảo
Lazy Foo' SDL2 Tutorials

Series video trên trang youtube: Phát Triển Phần Mềm 123A-Z. https://www.youtube.com/@PhatTrienPhanMem123AZ
