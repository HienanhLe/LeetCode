// Solution: https://www.geeksforgeeks.org/dsa/add-two-numbers-represented-by-linked-list/
#include <iostream>
using namespace std;

// Định nghĩa cấu trúc của một nút (node) trong danh sách liên kết
class Node {
  public:
    int data;     // Lưu giá trị của chữ số
    Node *next;   // Con trỏ trỏ tới nút tiếp theo
    
    // Hàm khởi tạo (Constructor) tạo node mới với giá trị truyền vào
    Node(int val) {
        data = val;
        next = nullptr;
    }
};

// 1. Hàm đảo ngược danh sách liên kết (giúp đưa hàng đơn vị lên đầu để tiện tính toán)
Node *reverse(Node *head) {
    Node *prev = nullptr, *curr = head, *next;

    while (curr != nullptr) {
        next = curr->next; // Lưu lại node tiếp theo
        curr->next = prev; // Đảo chiều mũi tên trỏ ngược lại phía sau
        prev = curr;       // Dịch chuyển prev lên trước
        curr = next;       // Dịch chuyển curr sang node tiếp theo
    }
    return prev; // Trả về phần đầu mới của danh sách sau khi đảo ngược
}

// 2. Hàm loại bỏ các số 0 thừa ở đầu (Ví dụ: 00123 -> 123)
Node *trimLeadingZeros(Node* head) {
    // Bỏ qua các node có giá trị 0 ở đầu (miễn là không phải node cuối cùng)
    while(head->next != nullptr && head->data == 0)
        head = head->next;
    return head;
}

// 3. Hàm chính: Cộng hai số được biểu diễn bằng danh sách liên kết (thứ tự xuôi)
Node *addTwoLists(Node *num1, Node *num2) {
    Node *res = nullptr, *curr = nullptr; // res: node đầu tiên của kết quả, curr: con trỏ chạy để thêm node mới
    int carry = 0; // Biến lưu số nhớ qua các hàng

    // Bước 1: Loại bỏ số 0 thừa ở đầu của cả 2 danh sách
    num1 = trimLeadingZeros(num1);
    num2 = trimLeadingZeros(num2);
  
    // Bước 2: Đảo ngược cả 2 danh sách để hàng đơn vị nằm ở đầu (giống phép cộng tay từ phải sang trái)
    num1 = reverse(num1);
    num2 = reverse(num2);

    // Bước 3: Lặp qua từng chữ số từ phải sang trái và cộng dồn kèm theo số nhớ (carry)
    while (num1 != nullptr || num2 != nullptr || carry != 0) {
        int sum = carry; // Khởi tạo tổng bằng số nhớ của lần trước

        // Nếu num1 vẫn còn chữ số, cộng vào tổng và dịch chuyển num1
        if (num1 != nullptr) {
            sum += num1->data;
            num1 = num1->next;
        }

        // Nếu num2 vẫn còn chữ số, cộng vào tổng và dịch chuyển num2
        if (num2 != nullptr) {
            sum += num2->data;
            num2 = num2->next;
        }
      
        // Tạo node mới chứa chữ số hàng đơn vị của tổng (sum % 10)
        Node* newNode = new Node(sum % 10);

        // Cập nhật số nhớ cho lần cộng tiếp theo (sum / 10)
        carry = sum / 10;

        // Nếu đây là node đầu tiên của kết quả
        if(res == nullptr) {
            res = newNode;
            curr = newNode;
        }
        else {
            // Nối node mới vào danh sách kết quả và dịch chuyển con trỏ curr lên trước
            curr->next = newNode;
            curr = curr->next;
        }
    }

    // Bước 4: Do lúc đầu ta đã đảo ngược danh sách để cộng, kết quả tạo ra đang bị ngược.
    // Ta gọi lại hàm reverse() một lần nữa để trả về thứ tự xuôi chuẩn xác.
    return reverse(res);
}

// Hàm hỗ trợ in ra danh sách liên kết theo định dạng (vd: 1 -> 1 -> 2 -> 2)
void printList(Node* head) {
    while (head != nullptr) {
        cout << head->data;
        if (head->next != nullptr)
            cout << " -> ";
        head = head->next;
    }
    cout << '\n';
}

int main() {
    // Tạo danh sách số thứ nhất: 1 -> 2 -> 3 (Đại diện cho số 123)
    Node *head1 = new Node(1);
    head1->next = new Node(2);
    head1->next->next = new Node(3);

    // Tạo danh sách số thứ hai: 9 -> 9 -> 9 (Đại diện cho số 999)
    Node *head2 = new Node(9);
    head2->next = new Node(9);
    head2->next->next = new Node(9);

    // Thực hiện phép cộng: 123 + 999 = 1122
    Node* result = addTwoLists(head1, head2);
    printList(result); // In kết quả ra màn hình

    return 0;
}

// Time Complexity: O(m + n)
// Space Complexity: O(max(m, n))

#include <iostream>
using namespace std;

// Định nghĩa cấu trúc của một node trong danh sách liên kết
class Node
{
  public:
    int data;     // Lưu giá trị của chữ số
    Node *next;   // Con trỏ trỏ tới node tiếp theo
    
    // Hàm khởi tạo node mới
    Node(int val)
    {
        data = val;
        next = nullptr;
    }
};

// 1. Hàm tính chiều dài của danh sách liên kết
int getLength(Node *head)
{
    int len = 0;
    while (head)
    {
        len++;
        head = head->next;
    }
    return len;
}

// 2. Hàm loại bỏ các số 0 thừa ở đầu danh sách (Ví dụ: 0063 -> 63)
Node *trimLeadingZeros(Node* head) {
    // Giữ lại ít nhất 1 node 0 nếu toàn bộ danh sách là số 0
    while(head->next != nullptr && head->data == 0)
        head = head->next;
    return head;
}

// 3. Hàm thêm các node chứa số 0 vào PHÍA TRƯỚC danh sách ngắn hơn
// Giúp 2 danh sách có chiều dài bằng nhau để dễ cộng từng cột tương ứng
Node *padList(Node *head, int diff)
{
    while (diff--)
    {
        Node *newNode = new Node(0); // Tạo node có giá trị 0
        newNode->next = head;        // Nối node 0 vào trước head cũ
        head = newNode;              // Cập nhật lại head mới
    }
    return head;
}

// 4. Hàm đệ quy cộng hai danh sách (tính từ phải qua trái nhờ cơ chế Call Stack)
Node *addListRec(Node *num1, Node *num2, int &carry)
{
    // Điều kiện dừng: Khi cả hai danh sách đã đi đến tận cùng (hết node)
    if (num1 == nullptr && num2 == nullptr)
        return nullptr;

    // Bước đi xuống: Gọi đệ quy tiến sâu đến tận cuối của 2 danh sách (hàng đơn vị ở cuối)
    Node *nextNode = addListRec(num1->next, num2->next, carry);

    // Bước đi lên (từ phải sang trái): Cộng giá trị tại node hiện tại kèm theo số nhớ (carry)
    int sum = num1->data + num2->data + carry;

    Node *curr = new Node(sum % 10); // Tạo node mới chứa phần đơn vị
    carry = sum / 10;                // Cập nhật lại số nhớ cho hàng bên trái

    curr->next = nextNode;           // Nối node hiện tại với chuỗi kết quả phía sau

    return curr;
}

// 5. Hàm chính: Điều phối toàn bộ quá trình cộng
Node *addTwoLists(Node *num1, Node *num2)
{
    // Bước 1: Tính chiều dài của 2 danh sách
    int len1 = getLength(num1);
    int len2 = getLength(num2);

    // Bước 2: Cân bằng chiều dài bằng cách chèn số 0 vào danh sách ngắn hơn
    if (len1 < len2)
        num1 = padList(num1, len2 - len1);
    else
        num2 = padList(num2, len1 - len2);

    int carry = 0;
    // Bước 3: Gọi hàm đệ quy để cộng hai danh sách đã được đồng bộ chiều dài
    Node *result = addListRec(num1, num2, carry);

    // Bước 4: Nếu sau khi cộng xong mà vẫn còn dư số nhớ (carry != 0) ở hàng cao nhất
    // Ta tạo thêm một node chứa giá trị carry và đặt nó lên đầu tiên
    if (carry)
    {
        Node *newNode = new Node(carry);
        newNode->next = result;
        result = newNode;
    }

    // Bước 5: Xóa các số 0 thừa ở đầu kết quả trước khi trả về
    return trimLeadingZeros(result);
}

// Hàm hỗ trợ in danh sách liên kết ra màn hình
void printList(Node* head) {
    while (head != nullptr) {
        cout << head->data;
        if (head->next != nullptr)
            cout << " -> ";
        head = head->next;
    }
    cout << '\n';
}

// Time Complexity: O(m + n)
// Space Complexity: O(max(m, n))

int main() {
    // Tạo danh sách số thứ 1: 0 -> 0 -> 6 -> 3 (Biểu diễn số 63)
    Node *head1 = new Node(0);
    head1->next = new Node(0);
    head1->next->next = new Node(6);
    head1->next->next->next = new Node(3);

    // Tạo danh sách số thứ 2: 0 -> 7 (Biểu diễn số 7)
    Node *head2 = new Node(0);
    head2->next = new Node(7);

    // Thực hiện phép cộng: 63 + 7 = 70
    Node* result = addTwoLists(head1, head2);
    printList(result); // In ra kết quả: 7 -> 0

    return 0;
}

#include <iostream>
using namespace std;

class Node
{
  public:
    int data;     // Giá trị của chữ số
    Node* next;   // Con trỏ trỏ tới node tiếp theo

    Node(int x) {
        data = x;
        next = nullptr;
    }
};

// 1. Hàm đảo ngược danh sách liên kết (giúp đưa hàng đơn vị về đầu)
Node* reverseList(Node* head) {
    Node* prev = nullptr;
    Node* curr = head;

    while (curr != nullptr) {
        Node* nextNode = curr->next;
        curr->next = prev;
        prev = curr;
        curr = nextNode;
    }

    return prev;
}

// 2. Hàm loại bỏ các số 0 thừa ở đầu danh sách (Ví dụ: 0063 -> 63)
Node* removeLeadingZeros(Node* head) {
    // Vừa dịch chuyển vừa giữ lại ít nhất một node 0 nếu toàn bộ danh sách là số 0
    while (head != nullptr && head->data == 0 &&
           head->next != nullptr) {
        head = head->next;
    }

    return head;
}

// 3. Hàm chính: Cộng hai danh sách liên kết theo kiểu tối ưu bộ nhớ trực tiếp (In-place)
Node* addTwoLists(Node* head1, Node* head2) {
    // Bước 1: Dọn dẹp số 0 thừa ở đầu của cả 2 danh sách
    head1 = removeLeadingZeros(head1);
    head2 = removeLeadingZeros(head2);

    int len1 = 0, len2 = 0;

    // Bước 2: Đếm chiều dài của danh sách thứ nhất
    for (Node* temp = head1; temp != nullptr; temp = temp->next)
        len1++;

    // Đếm chiều dài của danh sách thứ hai
    for (Node* temp = head2; temp != nullptr; temp = temp->next)
        len2++;

    // Bước 3: Đảm bảo head1 luôn trỏ vào danh sách CÓ CHIỀU DÀI LỚN HƠN.
    // Nếu head1 ngắn hơn, ta hoán đổi vị trí con trỏ của head1 và head2.
    if (len1 < len2) {
        Node* temp = head1;
        head1 = head2;
        head2 = temp;
    }

    // Bước 4: Đảo ngược cả hai danh sách để hàng đơn vị dịch chuyển lên đầu tiên
    head1 = reverseList(head1);
    head2 = reverseList(head2);

    Node* curr1 = head1; // Con trỏ chạy trên danh sách dài (nơi sẽ chứa kết quả)
    Node* curr2 = head2; // Con trỏ chạy trên danh sách ngắn hơn
    int carry = 0;       // Biến lưu số nhớ

    // Bước 5: Tiến hành cộng dọc từng chữ số từ phải qua trái
    while (curr1 != nullptr) {
        int sum = curr1->data + carry; // Lấy dữ liệu của danh sách dài cộng với số nhớ

        // Nếu danh sách ngắn hơn vẫn còn phần tử, cộng thêm giá trị của nó
        if (curr2 != nullptr) {
            sum += curr2->data;
            curr2 = curr2->next;
        }

        curr1->data = sum % 10; // Ghi đè trực tiếp kết quả hàng đơn vị vào node của head1
        carry = sum / 10;       // Cập nhật lại số nhớ cho lần cộng tiếp theo

        // Trường hợp đặc biệt: Đã đi đến node cuối cùng của danh sách dài nhưng vẫn còn số nhớ (carry > 0)
        // Ta cần cấp phát thêm một node mới chứa giá trị carry và nối vào cuối danh sách hiện tại.
        if (curr1->next == nullptr && carry > 0) {
            curr1->next = new Node(carry);
            carry = 0; // Đã dùng xong carry, reset về 0
        }

        curr1 = curr1->next; // Dịch chuyển con trỏ trên danh sách dài
    }

    // Bước 6: Đảo ngược danh sách kết quả (head1) trở lại chiều xuôi ban đầu
    head1 = reverseList(head1);

    // Bước 7: Dọn dẹp lại các số 0 thừa xuất hiện ở đầu kết quả (nếu có) rồi trả về
    return removeLeadingZeros(head1);
}

// Hàm hỗ trợ in danh sách liên kết ra màn hình
void printList(Node* head) {
    while (head != nullptr) {
        cout << head->data;
        if (head->next != nullptr)
            cout << " -> ";
        head = head->next;
    }
    cout << '\n';
}

int main() {
    Node *head1 = new Node(0);
    head1->next = new Node(0);
    head1->next->next = new Node(6);
    head1->next->next->next = new Node(3); // Đại diện số 63

    Node *head2 = new Node(0);
    head2->next = new Node(7); // Đại diện số 7

    Node* result = addTwoLists(head1, head2);
    printList(result); // In kết quả: 7 -> 0 (70)

    return 0;
}

// Time Complexity: O(m + n)
// Space Complexity: O(1)