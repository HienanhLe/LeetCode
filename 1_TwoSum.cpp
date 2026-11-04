#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>

using namespace std;

class SolutionBruteForce {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        // Vòng lặp ngoài: chọn phần tử thứ nhất tại vị trí i
        for (int i = 0; i < nums.size(); i++) {
            // Vòng lặp trong: chọn phần tử thứ hai tại vị trí j (luôn đứng sau i để tránh lặp)
            for (int j = i + 1; j < nums.size(); j++) {
                // Kiểm tra nếu tổng hai phần tử bằng target
                if (nums[i] + nums[j] == target) {
                    return {i, j}; // Trả về cặp chỉ số ngay lập tức
                }
            }
        }
        // Nếu duyệt hết mà không tìm thấy, trả về mảng rỗng
        return {};
    }
};
// Time Complexity: O(n^2), Space Complexity: O(1)

class SolutionSorting {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        // Tạo vector chứa các cặp {giá_trị, chỉ_số_gốc} 
        // để khi sắp xếp không bị mất đi vị trí ban đầu của phần tử trong mảng nums.
        vector<pair<int, int>> A;
        for (int i = 0; i < nums.size(); i++) {
            A.push_back({nums[i], i});
        }

        // Sắp xếp mảng A tăng dần dựa theo giá trị (first)
        sort(A.begin(), A.end());

        // Đặt 2 con trỏ: i ở đầu mảng (giá trị nhỏ nhất), j ở cuối mảng (giá trị lớn nhất)
        int i = 0, j = nums.size() - 1;
        while (i < j) {
            // Tính tổng giá trị của 2 phần tử tại con trỏ i và j
            int cur = A[i].first + A[j].first; 

            if (cur == target) {
                // Nếu tổng bằng target, trả về 2 chỉ số gốc (second). 
                // Dùng min/max để đảm bảo chỉ số nhỏ hơn luôn đứng trước.
                return {min(A[i].second, A[j].second),
                        max(A[i].second, A[j].second)};
            } else if (cur < target) {
                i++; // Nếu tổng nhỏ hơn target -> tăng con trỏ trái lên để tổng lớn hơn
            } else {
                j--; // Nếu tổng lớn hơn target -> giảm con trỏ phải xuống để tổng nhỏ hơn
            }
        }
        // Trả về mảng rỗng nếu không tìm thấy
        return {};
    }
};
// Time Complexity: O(nlogn), Space Complexity: O(n)

class SolutionTwoPassMap {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        // Khởi tạo một bảng băm (hash map) để lưu trữ:
        // Key: Giá trị của phần tử (nums[i])
        // Value: Chỉ số vị trí của phần tử đó (i)
        unordered_map<int, int> indices;  // val -> index

        // --- BƯỚC 1: Xây dựng toàn bộ danh bạ (Hash Map) ---
        // Duyệt qua từng phần tử của mảng và cất vào map
        for (int i = 0; i < nums.size(); i++) {
            indices[nums[i]] = i; 
            // Lưu ý: Nếu mảng có các số trùng nhau, 
            // giá trị ở index lớn hơn sẽ ghi đè lên index nhỏ hơn ở bước này.
        }

        // --- BƯỚC 2: Kiểm tra và tìm kiếm cặp số thỏa mãn ---
        // Duyệt lại mảng từ đầu để tìm số còn thiếu
        for (int i = 0; i < nums.size(); i++) {
            // Tính số còn thiếu (diff) để đạt đến target
            int diff = target - nums[i];

            // Kiểm tra 2 điều kiện quan trọng:
            // 1. indices.count(diff): Số 'diff' có tồn tại trong map không?
            // 2. indices[diff] != i: Đảm bảo số tìm thấy không phải là chính nó 
            //    (tránh trường hợp target = 6, nums[i] = 3, map nhận diện nhầm chính nó).
            if (indices.count(diff) && indices[diff] != i) {
                // Nếu thỏa mãn, trả về vị trí hiện tại i và vị trí của số diff trong map
                return {i, indices[diff]};
            }
        }

        // Nếu duyệt hết mà không tìm thấy cặp nào, trả về mảng rỗng
        return {};
    }
};
// Time Complexity: O(n), Space Complexity: O(n)

class SolutionOnePassMap {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        int n = nums.size();
        
        // Tạo một bảng băm (hash map) để lưu trữ các phần tử ĐÃ DUYỆT QUA.
        // Cấu trúc: {giá_trị_phần_tử -> chỉ_số_index}
        unordered_map<int, int> prevMap;

        // Duyệt qua mảng chỉ 1 lần duy nhất từ trái sang phải
        for (int i = 0; i < n; i++) {
            // Bước 1: Tính số còn thiếu (complement) cần thiết để đạt đến target
            int diff = target - nums[i];

            // Bước 2: Kiểm tra xem số cần tìm (diff) ĐÃ TỪNG xuất hiện trước đó chưa?
            if (prevMap.find(diff) != prevMap.end()) {
                // Nếu tìm thấy, trả về cặp chỉ số: {chỉ_số_cũ_trong_map, chỉ_số_hiện_tại_i}
                return {prevMap[diff], i};
            }

            // Bước 3: Nếu chưa tìm thấy, đưa số hiện tại và index của nó vào map
            // để phục vụ cho các số đứng phía sau tra cứu.
            prevMap.insert({nums[i], i});
        }
        
        // Nếu duyệt hết mảng mà không tìm thấy cặp nào thỏa mãn
        return {};
    }
};
// Time Complexity: O(n), Space Complexity: O(n)

int main() {
    vector<int> nums = {3, 4, 5, 6};
    int target = 7;

    cout << "=== KIEM TRA DU LIEU DAU VAO ===" << endl;
    cout << "Nums: {3, 4, 5, 6}, Target = " << target << "\n\n";

    // 1. Kiểm tra cách Brute Force
    SolutionBruteForce s1;
    vector<int> r1 = s1.twoSum(nums, target);
    cout << "1. Brute Force O(n^2):        ";
    if (!r1.empty()) cout << "Indices: " << r1[0] << " and " << r1[1] << endl;
    else cout << "Khong tim thay" << endl;

    // 2. Kiểm tra cách Sorting + Two Pointers
    SolutionSorting s2;
    vector<int> r2 = s2.twoSum(nums, target);
    cout << "2. Sorting + Two Pointers:    ";
    if (!r2.empty()) cout << "Indices: " << r2[0] << " and " << r2[1] << endl;
    else cout << "Khong tim thay" << endl;

    // 3. Kiểm tra cách Two-pass Hash Map
    SolutionTwoPassMap s3;
    vector<int> r3 = s3.twoSum(nums, target);
    cout << "3. Two-pass Hash Map:         ";
    if (!r3.empty()) cout << "Indices: " << r3[0] << " and " << r3[1] << endl;
    else cout << "Khong tim thay" << endl;

    // 4. Kiểm tra cách One-pass Hash Map
    SolutionOnePassMap s4;
    vector<int> r4 = s4.twoSum(nums, target);
    cout << "4. One-pass Hash Map (Optimal): ";
    if (!r4.empty()) cout << "Indices: " << r4[0] << " and " << r4[1] << endl;
    else cout << "Khong tim thay" << endl;

    return 0;
}