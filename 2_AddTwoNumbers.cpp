#include <iostream>

// Định nghĩa cấu trúc cho danh sách liên kết đơn
struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class SolutionRecursive {
public:
    ListNode* add(ListNode* l1, ListNode* l2, int carry) {
        // Điều kiện dừng: cả hai danh sách đều hết node và không còn số nhớ
        if (!l1 && !l2 && carry == 0) {
            return nullptr;
        }

        // Lấy giá trị của node hiện tại, nếu danh sách đã hết thì mặc định là 0
        int v1 = (l1 != nullptr) ? l1->val : 0;
        int v2 = (l2 != nullptr) ? l2->val : 0;

        // Tính tổng giá trị của hai node cộng với số nhớ từ bước trước
        int sum = v1 + v2 + carry;
        int newCarry = sum / 10;     // Tính phần nhớ cho lần gọi tiếp theo
        int nodeValue = sum % 10;    // Giá trị thực tế của node hiện tại (hàng đơn vị)

        // Gọi đệ quy cho các node tiếp theo của l1 và l2
        ListNode* nextNode = add(
            (l1 ? l1->next : nullptr),
            (l2 ? l2->next : nullptr),
            newCarry
        );

        // Tạo node mới chứa giá trị vừa tính và liên kết nó với phần phía sau (nextNode)
        return new ListNode(nodeValue, nextNode);
    }

    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        return add(l1, l2, 0); // Bắt đầu đệ quy với số nhớ ban đầu bằng 0
    }
};
// Time Complexity: O(max(m, n)) ~ O(m + n)
// Space Complexity: O(max(m, n)) (bao gồm recursion call stack và output list)
// Trong đó: m và n lần lượt là độ dài của l1 và l2.

class SolutionIterative {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        // Tạo một node giả (dummy node) để dễ dàng quản lý việc thêm node mới vào danh sách kết quả
        ListNode* dummy = new ListNode();
        ListNode* cur = dummy; // Con trỏ 'cur' dùng để duyệt và nối các node kết quả phía sau

        int carry = 0; // Biến lưu số nhớ giữa các lần cộng

        // Vòng lặp chạy tiếp tục khi: l1 chưa hết, l2 chưa hết, hoặc vẫn còn số nhớ (carry != 0)
        while (l1 != nullptr || l2 != nullptr || carry != 0) {
            // Lấy giá trị của node hiện tại (nếu node tồn tại, ngược lại lấy 0)
            int v1 = (l1 != nullptr) ? l1->val : 0;
            int v2 = (l2 != nullptr) ? l2->val : 0;

            // Tính tổng giá trị tại hàng hiện tại kèm theo số nhớ
            int val = v1 + v2 + carry;
            
            carry = val / 10;   // Cập nhật lại số nhớ cho lần lặp tiếp theo (ví dụ: 15 / 10 = 1)
            val = val % 10;     // Lấy chữ số hàng đơn vị để đưa vào node mới (ví dụ: 15 % 10 = 5)

            // Tạo node mới chứa kết quả phép cộng và gắn vào đuôi của danh sách kết quả
            cur->next = new ListNode(val);

            // Dịch chuyển con trỏ 'cur' sang node tiếp theo vừa tạo
            cur = cur->next;

            // Dịch chuyển l1 và l2 sang node tiếp theo (nếu còn)
            l1 = (l1 != nullptr) ? l1->next : nullptr;
            l2 = (l2 != nullptr) ? l2->next : nullptr;
        }

        // Lưu lại địa chỉ node kết quả thực sự (bỏ qua node dummy khởi tạo ban đầu)
        ListNode* res = dummy->next;
        
        // Giải phóng bộ nhớ của node dummy để tránh rò rỉ bộ nhớ (memory leak)
        delete dummy; 

        return res; // Trả về danh sách kết quả hoàn chỉnh
    }
};
// Time Complexity: O(max(m, n)) ~ O(m + n)
// Space Complexity: O(1) extra space | O(max(m, n)) cho output list
// Trong đó: m và n lần lượt là độ dài của l1 và l2.

// Hàm hỗ trợ in danh sách liên kết ra màn hình dạng: a -> b -> c
void printList(ListNode* head) {
    while (head != nullptr) {
        std::cout << head->val;
        if (head->next != nullptr) {
            std::cout << " -> ";
        }
        head = head->next;
    }
    std::cout << std::endl;
}

// Hàm hỗ trợ giải phóng bộ nhớ của danh sách liên kết sau khi dùng xong
void deleteList(ListNode* head) {
    while (head != nullptr) {
        ListNode* temp = head;
        head = head->next;
        delete temp;
    }
}

int main() {
    std::cout << "=== TEST CACH 1: DE QUY (RECURSION) ===" << std::endl;
    {
        // l1 biểu diễn số 342 (đảo ngược: 2 -> 4 -> 3)
        ListNode* l1 = new ListNode(2, new ListNode(4, new ListNode(3)));
        // l2 biểu diễn số 465 (đảo ngược: 5 -> 6 -> 4)
        ListNode* l2 = new ListNode(5, new ListNode(6, new ListNode(4)));

        SolutionRecursive sol1;
        ListNode* result1 = sol1.addTwoNumbers(l1, l2);

        std::cout << "Ket qua 342 + 465 = 807 (Dao nguoc): ";
        printList(result1); // Mong đợi: 7 -> 0 -> 8

        // Dọn dẹp bộ nhớ
        deleteList(l1);
        deleteList(l2);
        deleteList(result1);
    }

    std::cout << "\n----------------------------------------\n" << std::endl;

    std::cout << "=== TEST CACH 2: VONG LAP (ITERATIVE) ===" << std::endl;
    {
        // l1 biểu diễn số 342 (đảo ngược: 2 -> 4 -> 3)
        ListNode* l1 = new ListNode(2, new ListNode(4, new ListNode(3)));
        // l2 biểu diễn số 465 (đảo ngược: 5 -> 6 -> 4)
        ListNode* l2 = new ListNode(5, new ListNode(6, new ListNode(4)));

        SolutionIterative sol2;
        ListNode* result2 = sol2.addTwoNumbers(l1, l2);

        std::cout << "Ket qua 342 + 465 = 807 (Dao nguoc): ";
        printList(result2); // Mong đợi: 7 -> 0 -> 8

        // Dọn dẹp bộ nhớ
        deleteList(l1);
        deleteList(l2);
        deleteList(result2);
    }

    return 0;
}