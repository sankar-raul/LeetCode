class Solution {
public:
    vector<int> nextGreaterElement(vector<int>& nums1, vector<int>& nums2) {
        stack<int> st;
        vector<int> res;
        unordered_map<int, int> nxt;
        int n = nums2.size();
        for (int i = n - 1; i >= 0; --i) {
            
            while (st.size() && st.top() <= nums2[i]) {
                st.pop();
            }

            nxt[nums2[i]] = st.empty() ? -1 : st.top();
            st.push(nums2[i]);
        }

        for (int i = 0; i < nums1.size(); ++i) {
            res.push_back(nxt[nums1[i]]);
        }

        return res;
    }
};