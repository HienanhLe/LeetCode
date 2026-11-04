#include <iostream>
#include <string>
#include <unordered_set>
#include <unordered_map>
#include <algorithm>

using namespace std;

class BruteForceSolution {
public:
    int lengthOfLongestSubstring(string s) {
        int res = 0;
        // Duyệt qua tất cả các vị trí bắt đầu `i` của chuỗi con
        for (int i = 0; i < s.size(); i++) {
            unordered_set<char> charSet;
            // Duyệt tiếp từ vị trí `i` đến cuối chuỗi để tạo chuỗi con
            for (int j = i; j < s.size(); j++) {
                // Nếu gặp ký tự trùng lặp trong tập hợp, dừng lại
                if (charSet.find(s[j]) != charSet.end()) {
                    break;
                }
                charSet.insert(s[j]);
            }
            // Cập nhật kết quả lớn nhất tìm được
            res = max(res, (int)charSet.size());
        }
        return res;
    }
    // Time Complexity: O(N^2)
    // Space Complexity: O(min(N, K)) với K là kích thước bảng mã ký tự
};

class SlidingWindowSetSolution {
public:
    int lengthOfLongestSubstring(string s) {
        unordered_set<char> charSet;
        int l = 0; // Con trỏ trái của cửa sổ
        int res = 0; // Kết quả độ dài lớn nhất

        // Con trỏ phải `r` duyệt qua từng ký tự của chuỗi
        for (int r = 0; r < s.size(); r++) {
            // Khi ký tự s[r] đã tồn tại trong cửa sổ, dịch con trỏ trái `l` sang phải
            // và xóa các ký tự cũ cho đến khi không còn trùng lặp
            while (charSet.find(s[r]) != charSet.end()) {
                charSet.erase(s[l]);
                l++;
            }
            // Thêm ký tự mới vào cửa sổ
            charSet.insert(s[r]);
            // Cập nhật độ dài cửa sổ lớn nhất hiện tại
            res = max(res, r - l + 1);
        }
        return res;
    }
    // Time Complexity: O(N) (mỗi ký tự được thăm tối đa 2 lần bởi l và r)
    // Space Complexity: O(min(N, K))
};

class OptimizedMapSolution {
public:
    int lengthOfLongestSubstring(string s) {
        unordered_map<char, int> mp; // Lưu vị trí xuất hiện gần nhất của mỗi ký tự
        int l = 0, res = 0;

        for (int r = 0; r < s.size(); r++) {
            // Nếu ký tự s[r] đã xuất hiện trước đó
            if (mp.find(s[r]) != mp.end()) {
                // Nhảy trực tiếp con trỏ `l` đến vị trí ngay sau lần xuất hiện trước của s[r]
                // Dùng hàm max để đảm bảo con trỏ `l` không bị thụt lùi về phía sau
                l = max(mp[s[r]] + 1, l);
            }
            // Cập nhật vị trí mới nhất của ký tự s[r]
            mp[s[r]] = r;
            // Cập nhật độ dài lớn nhất
            res = max(res, r - l + 1);
        }
        return res;
    }
    // Time Complexity: O(N) (chỉ cần 1 vòng lặp duy nhất qua chuỗi)
    // Space Complexity: O(min(N, K))
};


int main() {
    // Khởi tạo các đối tượng từ 3 cách giải
    BruteForceSolution sol1;
    SlidingWindowSetSolution sol2;
    OptimizedMapSolution sol3;

    // Danh sách các test cases
    string testCases[] = {
        "abcabcbb",
        "bbbbb",
        "pwwkew",
        "a",
        "",
        "abba"
    };

    cout << "=== KIỂM THỬ THUẬT TOÁN TÌM XÂU CON DÀI NHẤT KHÔNG TRÙNG LẶP ===\n\n";

    for (int i = 0; i < 6; i++) {
        string s = testCases[i];
        cout << "Test " << i + 1 << ": s = \"" << s << "\"\n";
        cout << "Brute Force: " << sol1.lengthOfLongestSubstring(s) << "\n";
        cout << "Sliding Window: " << sol2.lengthOfLongestSubstring(s) << "\n";
        cout << "Optimized Map: " << sol3.lengthOfLongestSubstring(s) << "\n";
        cout << "--------------------------------------------------\n";
    }

    return 0;
}