/**
 * @param {...(null|boolean|number|string|Array|Object)} args
 * @return {number}
 */
var argumentsLength = function(...args) {
    let c = 0;
    for (let arg of args) {
        c++;
    }
    return c;
};

/**
 * argumentsLength(1, 2, 3); // 3
 */