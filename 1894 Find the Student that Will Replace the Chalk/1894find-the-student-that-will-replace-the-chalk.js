/**
 * @param {number[]} chalk
 * @param {number} k
 * @return {number}
 */
var chalkReplacer = function(chalk, k) {
    let i, len = chalk.length, sum = chalk.reduce((prev, curr) => prev + curr)
    k = k % sum
    for (i = 0; i < len; i++) {
        if (k < 0) {
            return i - 1
        }
        k -= chalk[i]
    }
    return i - 1
}