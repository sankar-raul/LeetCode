/**
 * @param {number[]} nums
 * @return {number}
 */
var findMaxK = function(nums) {
    nums = nums.sort((a,b) => a - b) 
    for (num of nums) {
        for (n of nums) {
            if (num + n === 0) return num < 0 ? n : num
        }
    }
    return -1
};