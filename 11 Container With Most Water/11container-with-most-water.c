int maxArea(int* height, int heightSize) {
    int ans = 0, left = 0, right = heightSize - 1, w, curr;
    while (left < right) {
        w = right - left;
        curr = height[right] > height[left] ? height[left] * w : height[right] * w;
        if (ans < curr) {
            ans = curr;
        }
        height[left] > height[right] ? right-- : left++;
    }
    return ans;
}