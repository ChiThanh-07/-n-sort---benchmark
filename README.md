# Báo Cáo Đồ Án: Benchmark Sorting C++

## 1. Thông tin nhóm và cá nhân
* **Tên môn học:** Cấu trúc dữ liệu và giải thuật
* **Thời gian học:** Học kỳ 2, Năm học 2025-2026
* **Lớp:** 25CTT6 - Khoa Công nghệ Thông tin (FIT-HCMUS)
* **Danh sách thành viên:**
  1. **Đỗ Quang Thắng** - MSSV: 25120436
  2. **Nguyễn Chí Thành** - MSSV: 25120438
  3. **Nguyễn Ngọc Vũ** - MSSV: 25120471

---

## 2. Thuật toán cài đặt tốt nhất (Lần 1)

Ở Benchmark 1, bộ mã nguồn được tối ưu hóa ở mức độ thấp (low-level optimization) bằng cách sử dụng các chỉ thị `#pragma GCC optimize("O3,unroll-loops")` và tập lệnh `avx2,bmi,bmi2`. Cơ chế Fast I/O (sử dụng mảng đệm lớn) được áp dụng đồng bộ cho cả 3 bài nhằm loại bỏ hoàn toàn nút thắt cổ chai (bottleneck) của các hàm nhập/xuất chuẩn.

### Bài A (Integer Sort)
* **Thuật toán chính:** Radix Sort cơ số 256 (chạy 4 passes).
* **Chi tiết kỹ thuật & Tối ưu:** * Phân phối số nguyên vào 4 mảng đếm (tương ứng với 4 byte của số nguyên 32-bit).
  * Xử lý số âm bằng thủ thuật thao tác bit: `x ^ 0x80000000` (lật bit dấu) trước khi sắp xếp, và lật ngược lại khi xuất kết quả. Điều này giúp tránh việc phải chia mảng thành số âm/dương riêng biệt.
* **Lý do lựa chọn:** Độ phức tạp thời gian luôn ổn định ở mức $\mathcal{O}(N)$ thay vì $\mathcal{O}(N \log N)$ như QuickSort hay MergeSort, đặc biệt hiệu quả với giới hạn 100,000 phần tử.

### Bài B (Lexicographic Sort)
* **Thuật toán chính:** MSD (Most Significant Digit) Radix Sort.
* **Chi tiết kỹ thuật & Tối ưu:**
  * Thuật toán duyệt từ trái sang phải của chuỗi, đếm tần số các ký tự (28 bucket). 
  * Kết hợp ngắt đệ quy sớm (early cut-off): Khi kích thước mảng con cần xử lý $\le 48$, thuật toán tự động chuyển sang Insertion Sort tự cài đặt.
* **Lý do lựa chọn:** Giảm tối đa số lần phải so sánh lại các tiền tố (prefix) chung giữa các chuỗi, vượt trội so với việc dùng `std::sort` vốn tốn nhiều chi phí gọi hàm so sánh.

### Bài C (Length-aware Lexicographic String Sort)
* **Thuật toán chính:** Bucket Sort (theo độ dài) kết hợp Randomized QuickSort.
* **Chi tiết kỹ thuật & Tối ưu:**
  * Đọc chuỗi và băm trực tiếp vào mảng 2 chiều `buckets` dựa trên độ dài (từ 10 đến 100).
  * Viết lại hàm `my_strcmp` và `customSort` chỉ áp dụng cho các chuỗi trong cùng một bucket.
* **Lý do lựa chọn:** Bằng cách chia nhóm độ dài ngay từ lúc đọc (chi phí $\mathcal{O}(N)$), bài toán được thu nhỏ lại thành sắp xếp nội bộ từng nhóm, giúp giảm thiểu số lượt so sánh dư thừa.

---

## 3. Cách thức sinh Test Case (test_gen.cpp)

Bộ test case được thiết kế có chủ đích nhằm "bắt bài" các thuật toán sắp xếp ngây thơ (naive algorithms), lợi dụng các điểm yếu về phân hoạch và chi phí so sánh ký tự. Cụ thể:

### Bài A (int)
* **Test 1:** Dữ liệu ngẫu nhiên hoàn toàn từ `INT_MIN` đến `INT_MAX`.
* **Test 2:** Mảng chứa lượng lớn phần tử trùng lặp (chỉ gồm 5 giá trị ngẫu nhiên lặp lại hàng nghìn lần). Mục tiêu: Đánh gục các thuật toán QuickSort cơ bản không sử dụng phân hoạch 3-way, ép độ phức tạp lên $\mathcal{O}(N^2)$.
* **Test 3:** Tập trung vào các giá trị biên (`INT_MIN`, `INT_MAX`, `0`, `-1`, `1`). Mục tiêu: Kiểm tra các thuật toán xử lý bit hoặc Radix Sort bị lỗi tràn số học (overflow) khi ép kiểu.
* **Test 4, 5:** Mảng đã được sắp xếp hoàn toàn (tăng dần và giảm dần). Mục tiêu: Làm chậm các thuật toán QuickSort sử dụng pivot cố định ở đầu/cuối mảng.

### Bài B (strlexi)
* **Test 1:** Các chuỗi có độ dài và ký tự ngẫu nhiên.
* **Test 2:** Lượng lớn chuỗi trùng lặp (chỉ chọn 5 chuỗi ngẫu nhiên rồi nhân bản lên điền đầy mảng).
* **Test 3:** Chuỗi có tiền tố (prefix) chung cực dài. Các chuỗi được nhồi toàn ký tự `'a'`, chỉ khác biệt ở 3 ký tự cuối cùng. Mục tiêu: Ép hàm `operator<` của thư viện chuẩn phải tốn chi phí duyệt qua toàn bộ chiều dài chuỗi trong mỗi lần so sánh, làm tăng hằng số thời gian đột biến.
* **Test 4, 5:** Mảng chuỗi đã được sắp xếp tăng dần và giảm dần từ trước.

### Bài C (strlenlexi)
* **Test 1, 2:** Tương tự như Bài B (Ngẫu nhiên và Trùng lặp cao).
* **Test 3:** Vô hiệu hóa lợi thế so sánh độ dài. Tất cả các chuỗi đều được ép về độ dài tối đa (100 ký tự) và có chung 97 ký tự `'a'` ở đầu. Test này đẩy bài toán về lại trường hợp xấu nhất của Bài B, triệt tiêu tốc độ của những bài nộp chỉ gom nhóm theo độ dài mà không tối ưu sắp xếp chuỗi bên trong nhóm.
* **Test 4, 5:** Mảng được sắp xếp tăng/giảm chuẩn xác theo cả 2 tiêu chí (độ dài trước, từ điển sau).

---

## 4. Thuật toán cài đặt tốt nhất (Lần 2)

Sau khi thiết kế bộ test đối kháng, các thuật toán ở Lần 1 được tái cấu trúc triệt để nhằm tối ưu sâu hơn về mặt quản lý bộ nhớ liên tục (Cache-conscious optimization) và xử lý chuỗi trùng lặp, tiền tố chung dài.

### Các phương thức tối ưu tiếp tục:

**1. Bài A (Integer Sort):**
* **Thuật toán cốt lõi:** Radix Sort cơ số 256 (4 passes) kết hợp thao tác bit (`v[i] ^ 0x80000000`).
* **Cải tiến:** Chuyển đổi sang sử dụng `std::vector` kết hợp cơ chế `swap()` mảng tối ưu bộ nhớ. Khâu nhập xuất áp dụng `ios_base::sync_with_stdio(0); cin.tie(0);` giúp giữ tốc độ ở mức tối đa mà mã nguồn vẫn ngắn gọn, tường minh, giảm thiểu rủi ro lỗi vùng nhớ khi chấm bài thực tế.

**2. Bài B (Lexicographic Sort):**
* **Thuật toán cốt lõi:** MSD Radix Sort đệ quy qua từng ký tự.
* **Cải tiến Memory Pool:** Áp dụng kỹ thuật **Contiguous Memory Allocation (Cấp phát bộ nhớ liên tục)**. Toàn bộ các chuỗi đầu vào được đọc nối tiếp trực tiếp vào mảng một chiều `string_pool`. Mảng con trỏ `a` và mảng tạm `tmp` chỉ quản lý các địa chỉ trỏ vào vùng nhớ liên tục này. Giải pháp này triệt tiêu hoàn toàn hiện tượng phân mảnh bộ nhớ (memory fragmentation) và tận dụng tối đa L1/L2 Cache của CPU.

**3. Bài C (Length-aware Lexicographic String Sort):**
* **Thuật toán cốt lõi:** Bucket Sort 1D theo độ dài kết hợp **3-way String Quicksort**.
* **Cải tiến 3-way Partitioning:** Đây là vũ khí chính để chống lại các test case có tiền tố chung dài. Hàm `str_quicksort` xét từng ký tự ở độ sâu `d` và chia mảng thành 3 phần rõ rệt: nhỏ hơn, bằng (tiền tố trùng nhau) và lớn hơn ký tự chốt (pivot). Đoạn mảng có tiền tố bằng nhau sẽ tiếp tục đệ quy xét ký tự tiếp theo (`d + 1`). Cơ chế này khắc chế hoàn toàn trường hợp mảng chứa nhiều chuỗi có tiền tố giống nhau.
* **Cải tiến Bucket 1D:** Thay vì dùng mảng 2 chiều tốn tài nguyên, thuật toán dùng mảng đếm tần suất `len_cnt` và vị trí bắt đầu `start_idx` để ánh xạ trực tiếp và phân lô toàn bộ chuỗi vào mảng một chiều `sorted_a`, giúp tối ưu hóa không gian bộ nhớ.
