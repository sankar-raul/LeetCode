/**
 * @param {number[]} original
 * @param {number} m
 * @param {number} n
 * @return {number[][]}
 */
var construct2DArray = function(original, m, n) {
    const arr = []
    if (m * n != original.length) {
        return []
    }
    let index = 0
    for (let i = 0; i < m; i++) {
        arr.push([])
        for (let j = 0; j < n; j++) {
            arr[i][j] = original[index++]
        }
    }
    return arr
};