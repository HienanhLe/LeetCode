#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

/**
 * @namespace MedianSolver
 * Thư viện tổng hợp các thuật toán giải bài toán: 
 * "Median of Two Sorted Arrays" (Tìm trung vị của hai mảng đã sắp xếp)
 */
namespace MedianSolver {

    // ==========================================
    // CÁCH 1: BRUTE FORCE (Gộp mảng & Sắp xếp)
    // ==========================================
    class BruteForce {
    public:
        double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
            int len1 = nums1.size();
            int len2 = nums2.size();
            vector<int> merged(len1 + len2);
            
            // Gộp hai mảng lại với nhau
            copy(nums1.begin(), nums1.end(), merged.begin());
            copy(nums2.begin(), nums2.end(), merged.begin() + len1);
            
            // Sắp xếp lại toàn bộ mảng gộp
            sort(merged.begin(), merged.end());

            int totalLen = merged.size();
            // Nếu tổng số phần tử là chẵn, lấy trung bình cộng 2 phần tử giữa
            if (totalLen % 2 == 0) {
                return (merged[totalLen / 2 - 1] + merged[totalLen / 2]) / 2.0;
            } else {
                // Nếu lẻ, lấy phần tử ở chính giữa
                return merged[totalLen / 2];
            }
        }
    };
    // - Time Complexity: O((n + m) log(n + m)) do sử dụng hàm sort()
    // - Space Complexity: O(n + m) để lưu trữ mảng gộp mới

    // ==========================================
    // CÁCH 2: HAI CON TRỎ (Two Pointers / Linear Scan)
    // ==========================================
    class TwoPointers {
    public:
        double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
            int len1 = nums1.size(), len2 = nums2.size();
            int i = 0, j = 0;
            int median1 = 0, median2 = 0;

            // Duyệt tịnh tiến từ đầu đến vị trí giữa của tổng số phần tử
            for (int count = 0; count < (len1 + len2) / 2 + 1; count++) {
                median2 = median1;
                if (i < len1 && j < len2) {
                    if (nums1[i] > nums2[j]) {
                        median1 = nums2[j];
                        j++;
                    } else {
                        median1 = nums1[i];
                        i++;
                    }
                } else if (i < len1) {
                    median1 = nums1[i];
                    i++;
                } else {
                    median1 = nums2[j];
                    j++;
                }
            }

            // Trả về kết quả tùy thuộc vào tổng độ dài chẵn hay lẻ
            if ((len1 + len2) % 2 == 1) {
                return (double) median1;
            } else {
                return (median1 + median2) / 2.0;
            }
        }
    };
    // - Time Complexity: O(n + m) vì duyệt qua các phần tử đến vị trí trung vị
    // - Space Complexity: O(1) chỉ dùng các biến đếm và con trỏ

    // ==========================================
    // CÁCH 3: TÌM KIẾM NHỊ PHÂN K-TH ELEMENT (Đệ quy)
    // ==========================================
    class BinarySearchKth {
    public:
        double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
            int left = (nums1.size() + nums2.size() + 1) / 2;
            int right = (nums1.size() + nums2.size() + 2) / 2;
            return (getKth(nums1, nums1.size(), nums2, nums2.size(), left, 0, 0) +
                    getKth(nums1, nums1.size(), nums2, nums2.size(), right, 0, 0)) / 2.0;
        }

    private:
        int getKth(vector<int>& a, int m, vector<int>& b, int n, int k, int aStart, int bStart) {
            // Đảm bảo mảng a luôn nhỏ hơn hoặc bằng mảng b để dễ xử lý
            if (m > n) {
                return getKth(b, n, a, m, k, bStart, aStart);
            }
            if (m == 0) {
                return b[bStart + k - 1];
            }
            if (k == 1) {
                return min(a[aStart], b[bStart]);
            }

            int i = min(m, k / 2);
            int j = min(n, k / 2);

            // Thu hẹp phạm vi tìm kiếm của k phần tử nhỏ nhất
            if (a[aStart + i - 1] > b[bStart + j - 1]) {
                return getKth(a, m, b, n - j, k - j, aStart, bStart + j);
            } else {
                return getKth(a, m - i, b, n, k - i, aStart + i, bStart);
            }
        }
    };
    // - Time Complexity: O(log(m + n)) do dùng tìm kiếm nhị phân chia đôi k
    // - Space Complexity: O(log(m + n)) do không gian bộ nhớ của stack đệ quy

    // ==========================================
    // CÁCH 4: TÌM KIẾM NHỊ PHÂN TRÊN PHÂN HOẠCH (Tối ưu nhất)
    // ==========================================
    class BinarySearchPartition {
    public:
        double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
            vector<int>& A = nums1;
            vector<int>& B = nums2;
            int total = A.size() + B.size();
            int half = (total + 1) / 2;

            // Luôn đảm bảo A là mảng nhỏ hơn để tối ưu binary search
            if (B.size() < A.size()) {
                swap(A, B);
            }

            int l = 0;
            int r = A.size();
            while (l <= r) {
                int i = (l + r) / 2; // Điểm cắt trên mảng A
                int j = half - i;    // Điểm cắt trên mảng B

                // Lấy các giá trị biên quanh điểm cắt (phòng hờ trường hợp biên cực đại/cực tiểu)
                int Aleft = i > 0 ? A[i - 1] : INT_MIN;
                int Aright = i < A.size() ? A[i] : INT_MAX;
                int Bleft = j > 0 ? B[j - 1] : INT_MIN;
                int Bright = j < B.size() ? B[j] : INT_MAX;

                // Kiểm tra xem đã phân hoạch đúng vị trí trung vị chưa
                if (Aleft <= Bright && Bleft <= Aright) {
                    if (total % 2 != 0) {
                        return max(Aleft, Bleft);
                    }
                    return (max(Aleft, Bleft) + min(Aright, Bright)) / 2.0;
                } else if (Aleft > Bright) {
                    r = i - 1; // Cần dịch điểm cắt A sang trái
                } else {
                    l = i + 1; // Cần dịch điểm cắt A sang phải
                }
            }
            return -1.0;
        }
    };
    // - Time Complexity: O(log(min(n, m))) vì tìm kiếm nhị phân trên mảng nhỏ hơn
    // - Space Complexity: O(1) chỉ sử dụng các biến phụ trợ
}

// ==========================================
// HÀM MAIN KIỂM THỬ (TESTING)
// ==========================================
int main() {
    vector<int> nums1 = {1, 3};
    vector<int> nums2 = {2};

    // Khởi tạo các đối tượng từ thư viện
    MedianSolver::BruteForce sol1;
    MedianSolver::TwoPointers sol2;
    MedianSolver::BinarySearchKth sol3;
    MedianSolver::BinarySearchPartition sol4;

    cout << "=== KET QUA TEST LEETCODE 4 ===" << endl;
    cout << "Test 1: nums1 = {1, 3}, nums2 = {2}" << endl;
    cout << "  - Cach 1 (Brute Force):             " << sol1.findMedianSortedArrays(nums1, nums2) << endl;
    cout << "  - Cach 2 (Two Pointers):            " << sol2.findMedianSortedArrays(nums1, nums2) << endl;
    cout << "  - Cach 3 (Binary Search Kth):       " << sol3.findMedianSortedArrays(nums1, nums2) << endl;
    cout << "  - Cach 4 (Binary Search Partition): " << sol4.findMedianSortedArrays(nums1, nums2) << endl;

    vector<int> nums3 = {1, 2};
    vector<int> nums4 = {3, 4};
    cout << "\nTest 2: nums1 = {1, 2}, nums2 = {3, 4}" << endl;
    cout << "  - Cach 4 (Optimal Partition):       " << sol4.findMedianSortedArrays(nums3, nums4) << endl;

    return 0;
}