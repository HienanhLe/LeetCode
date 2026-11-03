#include <iostream>

// Định nghĩa cấu trúc cho danh sách liên kết đơn
struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

// class Solution {
// public:
//     ListNode* add(ListNode* l1, ListNode* l2, int carry) {
//         // Điều kiện dừng: cả hai danh sách đều hết node và không còn số nhớ
//         if (!l1 && !l2 && carry == 0) {
//             return nullptr;
//         }

//         int v1 = 0;
//         int v2 = 0;
//         if (l1) {
//             v1 = l1->val;
//         }
//         if (l2) {
//             v2 = l2->val;
//         }

//         int sum = v1 + v2 + carry;
//         int newCarry = sum / 10;     // Tính phần nhớ cho lần gọi tiếp theo
//         int nodeValue = sum % 10;    // Giá trị của node hiện tại

//         // Gọi đệ quy cho các node tiếp theo
//         ListNode* nextNode = add(
//             (l1 ? l1->next : nullptr),
//             (l2 ? l2->next : nullptr),
//             newCarry
//         );

//         // Tạo node mới và liên kết với kết quả đệ quy phía sau
//         return new ListNode(nodeValue, nextNode);
//     }

//     ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
//         return add(l1, l2, 0);
//     }
// };

// Time Complexity: O(max(m, n)) ~ O(m + n)
// Space Complexity: O(max(m, n)) (bao gồm recursion call stack và output list)
// Trong đó: m và n lần lượt là độ dài của l1 và l2.

class Solution {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        ListNode* dummy = new ListNode();
        ListNode* cur = dummy;

        int carry = 0;
        while (l1 != nullptr || l2 != nullptr || carry != 0) {
            int v1 = (l1 != nullptr) ? l1->val : 0;
            int v2 = (l2 != nullptr) ? l2->val : 0;

            int val = v1 + v2 + carry;
            carry = val / 10;
            val = val % 10;
            cur->next = new ListNode(val);

            cur = cur->next;
            l1 = (l1 != nullptr) ? l1->next : nullptr;
            l2 = (l2 != nullptr) ? l2->next : nullptr;
        }
        ListNode* res = dummy->next;
        delete dummy;
        return res;
    }
};

// Time Complexity: O(max(m, n)) ~ O(m + n)
// Space Complexity: O(1) extra space | O(max(m, n)) cho output list
// Trong đó: m và n lần lượt là độ dài của l1 và l2.

// Hàm hỗ trợ in danh sách liên kết
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

int main() {
    Solution sol;

    // Ví dụ: 342 + 465 = 807
    // l1 biểu diễn số 342 (đảo ngược: 2 -> 4 -> 3)
    ListNode* l1 = new ListNode(2, new ListNode(4, new ListNode(3)));
    
    // l2 biểu diễn số 465 (đảo ngược: 5 -> 6 -> 4)
    ListNode* l2 = new ListNode(5, new ListNode(6, new ListNode(4)));

    ListNode* result = sol.addTwoNumbers(l1, l2);

    std::cout << "Ket qua (807): ";
    printList(result); // Mong đợi: 7 -> 0 -> 8

    return 0;
}