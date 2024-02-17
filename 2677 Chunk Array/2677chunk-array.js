/**
 * @param {Array} arr
 * @param {number} size
 * @return {Array}
 */
var chunk = function(arr, size) {
     let len = arr.length,res = [],temp = [];
    let i = 0,j;
while (i < len) {
    temp = [];
for (j =  0; j < size && i < len; j++) {
    temp[j] = arr[i];
    i++;
    }
    res.push(temp)
}
   return res; 
};
