/**
 * @param {string} s
 * @return {string}
 */
var frequencySort = function(s) {
    let repeat = {};
    s = s.split("");
    for (let char of s) {
        if (repeat[char] == undefined) {
             repeat[char] = 1;
            } else {
             repeat[char] += 1;
            }
    }
    s = "";
    let p = Object.entries(repeat).sort((a, b) => a[1] - b[1]);
    for ([key, value] of p) {
        for (let i = 0; i <= value - 1;i++) {
            s += key;
        }
    }
    return s.split('').reverse().join('');
};