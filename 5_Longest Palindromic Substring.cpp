#include <iostream>
#include <string>
#include <vector>
#include <algorithm> // Dùng cho hàm min()

using namespace std;

// =========================================================================
// CÁCH 1: VÉT CẠN (BRUTE FORCE)
// Độ phức tạp thời gian: O(n^3) | Không gian: O(1)
// =========================================================================
class SolutionBruteForce {
public:
    string longestPalindrome(string s) {
        string res = ""; // Lưu chuỗi đối xứng dài nhất tìm được
        int resLen = 0;  // Lưu độ dài của chuỗi đối xứng dài nhất

        // Duyệt qua tất cả các điểm bắt đầu i của chuỗi con
        for (int i = 0; i < s.size(); i++) {
            // Duyệt qua tất cả các điểm kết thúc j của chuỗi con
            for (int j = i; j < s.size(); j++) {
                int l = i, r = j;
                
                // Dùng 2 con trỏ l và r chạy từ ngoài vào trong để kiểm tra đối xứng
                while (l < r && s[l] == s[r]) {
                    l++;
                    r--;
                }

                // Nếu l >= r nghĩa là đoạn s[i...j] đối xứng hoàn toàn
                // Cập nhật kết quả nếu độ dài mới (j - i + 1) lớn hơn kỷ lục cũ
                if (l >= r && resLen < (j - i + 1)) {
                    res = s.substr(i, j - i + 1);
                    resLen = j - i + 1;
                }
            }
        }

        return res;
    }
};

// =========================================================================
// CÁCH 2: QUY HOẠCH ĐỘNG (DYNAMIC PROGRAMMING)
// Độ phức tạp thời gian: O(n^2) | Không gian: O(n^2)
// =========================================================================
class SolutionDP {
public:
    string longestPalindrome(string s) {
        int resIdx = 0, resLen = 0; // Lưu vị trí bắt đầu và độ dài kết quả
        int n = s.size();

        // dp[i][j] = true nếu chuỗi con từ vị trí i đến j là chuỗi đối xứng
        vector<vector<bool>> dp(n, vector<bool>(n, false));

        // Duyệt i từ cuối chuỗi về đầu chuỗi để đảm bảo bài toán con dp[i+1][j-1] đã được tính trước
        for (int i = n - 1; i >= 0; i--) {
            for (int j = i; j < n; j++) {
                // Điều kiện đối xứng: 2 đầu mút bằng nhau VÀ
                // (độ dài <= 3 [tức j - i <= 2] HOẶC phần lõi bên trong dp[i+1][j-1] cũng đối xứng)
                if (s[i] == s[j] && (j - i <= 2 || dp[i + 1][j - 1])) {
                    dp[i][j] = true;
                    
                    // Cập nhật kỷ lục độ dài
                    if (resLen < (j - i + 1)) {
                        resIdx = i;
                        resLen = j - i + 1;
                    }
                }
            }
        }

        return s.substr(resIdx, resLen);
    }
};

// =========================================================================
// CÁCH 3: MỞ RỘNG TỪ TÂM (EXPAND AROUND CENTER)
// Độ phức tạp thời gian: O(n^2) | Không gian: O(1)
// =========================================================================
class SolutionExpandCenter {
public:
    string longestPalindrome(string s) {
        int resLen = 0, resIdx = 0;

        // Xem mỗi vị trí i là tâm của chuỗi đối xứng và mở rộng ra 2 phía
        for (int i = 0; i < s.size(); i++) {
            // Trường hợp 1: Chuỗi đối xứng có độ dài LẺ (tâm là 1 ký tự tại i, VD: "aba")
            int l = i, r = i;
            while (l >= 0 && r < s.size() && s[l] == s[r]) {
                if (r - l + 1 > resLen) {
                    resIdx = l;
                    resLen = r - l + 1;
                }
                l--; // Mở rộng sang trái
                r++; // Mở rộng sang phải
            }

            // Trường hợp 2: Chuỗi đối xứng có độ dài CHẴN (tâm là khe giữa i và i+1, VD: "abba")
            l = i;
            r = i + 1;
            while (l >= 0 && r < s.size() && s[l] == s[r]) {
                if (r - l + 1 > resLen) {
                    resIdx = l;
                    resLen = r - l + 1;
                }
                l--;
                r++;
            }
        }

        return s.substr(resIdx, resLen);
    }
};

// =========================================================================
// CÁCH 4: THUẬT TOÁN MANACHER (MANACHER'S ALGORITHM)
// Độ phức tạp thời gian: O(n) | Không gian: O(n)
// =========================================================================
class SolutionManacher {
public:
    // Hàm tiền xử lý và tính mảng bán kính đối xứng p
    vector<int> manacher(string& s) {
        if (s.empty()) return {};
        
        // Chèn ký tự '#' xen kẽ để biến mọi chuỗi (chẵn lẫn lẻ) thành độ dài LẺ
        // Ví dụ: "abba" -> "#a#b#b#a#"
        string t = "#" + string(1, s[0]);
        for (int i = 1; i < s.size(); ++i)
            t += "#" + string(1, s[i]);
        t += "#";

        int n = t.size();
        vector<int> p(n, 0); // p[i] lưu bán kính đối xứng lớn nhất tại tâm i trên chuỗi t
        int l = 0, r = 0;    // [l, r] là biên trái và biên phải của chuỗi đối xứng xa nhất về bên phải

        for (int i = 0; i < n; i++) {
            // Tận dụng tính chất đối xứng gương qua tâm của [l, r] để khởi tạo nhanh p[i]
            // Điểm đối xứng của i qua tâm là: l + (r - i)
            p[i] = (i < r) ? min(r - i, p[l + (r - i)]) : 0;

            // Tiếp tục mở rộng bán kính p[i] ra 2 phía nếu các ký tự vẫn khớp nhau
            while (i + p[i] + 1 < n && i - p[i] - 1 >= 0 &&
                   t[i + p[i] + 1] == t[i - p[i] - 1]) {
                p[i]++;
            }

            // Nếu chuỗi đối xứng tại i vươn xa hơn biên phải r hiện tại, cập nhật lại [l, r]
            if (i + p[i] > r) {
                l = i - p[i];
                r = i + p[i];
            }
        }
        return p;
    }

    string longestPalindrome(string s) {
        if (s.empty()) return "";
        
        vector<int> p = manacher(s);
        int resLen = 0, center_idx = 0;

        // Tìm tâm có bán kính đối xứng lớn nhất
        // Lưu ý: Bán kính p[i] trên chuỗi t chính bằng độ dài chuỗi đối xứng thực tế trên chuỗi s
        for (int i = 0; i < p.size(); i++) {
            if (p[i] > resLen) {
                resLen = p[i];
                center_idx = i;
            }
        }

        // Quy đổi ngược tọa độ tâm trên chuỗi t về vị trí bắt đầu trên chuỗi s ban đầu
        int resIdx = (center_idx - resLen) / 2;
        return s.substr(resIdx, resLen);
    }
};

// =========================================================================
// HÀM MAIN ĐỂ KIỂM THỬ CẢ 4 THUẬT TOÁN
// =========================================================================
int main() {
    // Khởi tạo các bộ test case
    vector<string> testCases = {
        "babad",      // Kết quả mong đợi: "bab" hoặc "aba"
        "cbbd",       // Kết quả mong đợi: "bb"
        "racecar",    // Kết quả mong đợi: "racecar"
        "a",          // Kết quả mong đợi: "a"
        "forgeeksskeegfor" // Kết quả mong đợi: "geeksskeeg"
    };

    SolutionBruteForce sol1;
    SolutionDP sol2;
    SolutionExpandCenter sol3;
    SolutionManacher sol4;

    for (const string& s : testCases) {
        cout << "Chuoi dau vao: \"" << s << "\"\n";
        cout << "  1. Brute Force   : " << sol1.longestPalindrome(s) << "\n";
        cout << "  2. Dynamic Prog  : " << sol2.longestPalindrome(s) << "\n";
        cout << "  3. Expand Center : " << sol3.longestPalindrome(s) << "\n";
        cout << "  4. Manacher      : " << sol4.longestPalindrome(s) << "\n";
        cout << "----------------------------------------\n";
    }

    return 0;
}