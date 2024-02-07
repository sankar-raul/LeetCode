/**
 * @param {Function[]} functions
 * @return {Function}
 */
var compose = function(functions) {
    
    return function(x) {
        let val = x,t;
        if (functions.length != 0) {
        for (let i = functions.length-1;i>=0;i--) {
            t = functions[i];
            val = t(val);
        }
      }
        return val;
    }
};

/**
 * const fn = compose([x => x + 1, x => 2 * x])
 * fn(4) // 9
 */