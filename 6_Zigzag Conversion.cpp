#include <iostream>
#include <string>
#include <vector>

using namespace std;

class SolutionMath {
public:
    string convert(string s, int numRows) {
        // Trường hợp đặc biệt: Nếu chỉ có 1 hàng, chuỗi không bị biến dạng
        if (numRows == 1) {
            return s;
        }

        string res;
        int len = s.size();

        // Duyệt từng hàng từ trên xuống dưới (từ hàng 0 đến numRows - 1)
        for (int r = 0; r < numRows; r++) {
            // Khoảng cách giữa 2 cột thẳng đứng liên tiếp trong hình Zigzag
            // Ví dụ: numRows = 4 -> bước nhảy là 2 * (4 - 1) = 6
            int increment = 2 * (numRows - 1);

            // Duyệt qua các ký tự nằm trên cột thẳng đứng của hàng r
            for (int i = r; i < len; i += increment) {
                res += s[i]; // Lấy ký tự ở cột thẳng đứng

                // Nếu là các hàng ở giữa (không phải hàng đầu r=0 và hàng cuối r=numRows-1)
                // Sẽ có thêm các ký tự nằm trên đường chéo đi lên của Zigzag
                int diagIdx = i + increment - 2 * r;
                if (r > 0 && r < numRows - 1 && diagIdx < len) {
                    res += s[diagIdx]; // Lấy ký tự ở đường chéo
                }
            }
        }

        return res;
    }
};

// - Time Complexity: O(n) - Duyệt qua đúng n ký tự.
// - Space Complexity: O(1) - Không tốn bộ nhớ phụ (ngoài chuỗi kết quả).

class SolutionSimulation {
public:
    string convert(string s, int numRows) {
        // Nếu chỉ có 1 hàng hoặc số hàng >= độ dài chuỗi, kết quả chính là s
        if (numRows == 1 || numRows >= s.size()) {
            return s;
        }

        // Tạo mảng gồm numRows chuỗi rỗng, mỗi phần tử đại diện cho 1 hàng
        vector<string> res(numRows);
        
        int row = 0; // Vị trí hàng hiện tại (bắt đầu từ hàng 0)
        int dir = 1; // Hướng di chuyển: 1 là đi xuống, -1 là đi lên

        // Duyệt từng ký tự trong chuỗi ban đầu
        for (char& c : s) {
            res[row] += c; // Đưa ký tự vào hàng hiện tại
            row += dir;    // Di chuyển sang hàng tiếp theo theo hướng dir

            // Khi chạm biên trên (row == 0) hoặc biên dưới (row == numRows - 1)
            // Đảo ngược hướng di chuyển (đang xuống thành lên, đang lên thành xuống)
            if (row == 0 || row == numRows - 1) {
                dir *= -1;
            }
        }

        // Nối tất cả các hàng lại từ trên xuống dưới để tạo thành kết quả
        string result;
        for (string& rowString : res) {
            result += rowString;
        }
        
        return result;
    }
};

// - Time Complexity: O(n) - Duyệt chuỗi s một lần.
// - Space Complexity: O(n) - Lưu trữ các ký tự vào vector các hàng.

int main() {
    string s = "PAYPALISHIRING";
    int numRows = 3;

    // Khởi tạo đối tượng từ 2 class
    SolutionMath sol1;
    SolutionSimulation sol2;

    // Gọi hàm và in kết quả
    string ans1 = sol1.convert(s, numRows);
    string ans2 = sol2.convert(s, numRows);

    cout << "Chuoi goc: " << s << " | So hang: " << numRows << endl;
    cout << "Ket qua Cach 1 (Toan hoc): " << ans1 << endl;
    cout << "Ket qua Cach 2 (Mo phong): " << ans2 << endl;

    // Test case 2 với numRows = 4
    numRows = 4;
    cout << "\nChuoi goc: " << s << " | So hang: " << numRows << endl;
    cout << "Ket qua Cach 1 (Toan hoc): " << sol1.convert(s, numRows) << endl;
    cout << "Ket qua Cach 2 (Mo phong): " << sol2.convert(s, numRows) << endl;

    return 0;
}