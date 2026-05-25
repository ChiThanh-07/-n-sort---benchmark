# Đồ án sort - benchmark
# Báo Cáo Đồ Án: Benchmark Sorting C++

## 1. Thông tin cá nhân
* **Tên môn học:** Cấu trúc dữ liệu và giải thuật
* **Thời gian học:** Học kỳ 2, Năm học 2025-2026
* **Họ tên sinh viên:** Đỗ Quang Thắng
* **MSSV:** [Điền MSSV của bạn vào đây]
* **Lớp:** 25CTT6 - Khoa Công nghệ Thông tin (FIT-HCMUS)

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

### Bài C (Length-aware Lexicographic Sort)
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

Sau khi thiết kế bộ test đối kháng, các thuật toán ở Lần 1 cần được tối ưu sâu hơn về mặt bộ nhớ đệm (Cache-conscious optimization) để tăng tốc độ thực thi.

### Các phương thức tối ưu tiếp tục:
1. **Tinh gọn bộ nhớ đệm (Bài A & B):**
   * Chuyển từ việc cấp phát động nhiều mảng nhỏ sang gom toàn bộ chuỗi vào một mảng 1D liên tục (Contiguous Memory Allocation). Thao tác hoán vị lúc này chỉ thực hiện trên các chỉ số (index), giúp tăng Locality of Reference và tận dụng tối đa L1/L2 Cache của CPU.
2. **Nâng cấp Bài C (strlenlexi):**
   * Chuyển từ QuickSort ngẫu nhiên sang **3-way Radix Quicksort** cho từng bucket độ dài. Thuật toán mới xử lý cực kỳ mượt mà Test 3 (chuỗi có tiền tố dài giống hệt nhau), tránh việc gọi hàm so sánh chuỗi lặp đi lặp lại.
3. **Loop Unrolling thủ công:**
   * Các vòng lặp tính tần số đếm được mở cuộn thủ công (xử lý nhiều phần tử mỗi vòng) nhằm giảm chi phí kiểm tra điều kiện nhảy (jump instruction overhead) ở cấp độ assembly.

