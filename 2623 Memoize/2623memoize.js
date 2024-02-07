/**
 * @param {Function} fn
 * @return {Function}
 */
function memoize(fn) {
    let  keys = {};
    return function(...args) {
        let key = JSON.stringify(args);
        if (!(key in keys)) {
            keys[key] = fn(...args);
        }
         return keys[key];
    }
}


/** 
 * let callCount = 0;
 * const memoizedFn = memoize(function (a, b) {
 *	 callCount += 1;
 *   return a + b;
 * })
 * memoizedFn(2, 3) // 5
 * memoizedFn(2, 3) // 5
 * console.log(callCount) // 1 
 */