#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>

using namespace std;

// class Solution {
// public:
//     vector<int> twoSum(vector<int>& nums, int target) {
//         for (int i = 0; i < nums.size(); i++) {
//             for (int j = i + 1; j < nums.size(); j++) {
//                 if (nums[i] + nums[j] == target) {
//                     return {i, j};
//                 }
//             }
//         }
//         return {};
//     }
// };
// Time Complexity: O(n^2), Space Complexity: O(1)

// class Solution {
// public:
//     vector<int> twoSum(vector<int>& nums, int target) {
//         vector<pair<int, int>> A;
//         for (int i = 0; i < nums.size(); i++) {
//             A.push_back({nums[i], i});
//         }

//         sort(A.begin(), A.end());

//         int i = 0, j = nums.size() - 1;
//         while (i < j) {
//             int cur = A[i].first + A[j].first;
//             if (cur == target) {
//                 return {min(A[i].second, A[j].second),
//                         max(A[i].second, A[j].second)};
//             } else if (cur < target) {
//                 i++;
//             } else {
//                 j--;
//             }
//         }
//         return {};
//     }
// };
// Time Complexity: O(nlogn), Space Complexity: O(n)

// class Solution {
// public:
//     vector<int> twoSum(vector<int>& nums, int target) {
//         unordered_map<int, int> indices;

//         for (int i = 0; i < nums.size(); i++) {
//             indices[nums[i]] = i;
//         }

//         for (int i = 0; i < nums.size(); i++) {
//             int diff = target - nums[i];
//             if (indices.count(diff) && indices[diff] != i) {
//                 return {i, indices[diff]};
//             }
//         }

//         return {};
//     }
// };
// Time Complexity: O(n), Space Complexity: O(n)

class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        int n = nums.size();
        unordered_map<int, int> prevMap;

        for (int i = 0; i < n; i++) {
            int diff = target - nums[i];
            if (prevMap.find(diff) != prevMap.end()) {
                return {prevMap[diff], i};
            }
            prevMap.insert({nums[i], i});
        }
        return {};
    }
};
// Time Complexity: O(n), Space Complexity: O(n)

int main() {
    Solution solution;
    vector<int> nums = {3, 4, 5, 6};
    int target = 7;
    vector<int> result = solution.twoSum(nums, target);
    if (!result.empty()) {
        cout << "Indices: " << result[0] << " and " << result[1] << endl;
    } else {
        cout << "Cannot find two numbers that add up to the target." << endl;
    }
    return 0;
}