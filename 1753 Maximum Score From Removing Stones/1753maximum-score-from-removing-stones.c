int maximumScore(int a, int b, int c) {
    if (a == b && b == c) {
        return a + (a / 2);
    }
    if (((a == 0) + (b == 0) + (c == 0)) >= 2) {
        return 0;
    }
    if (a >= b && a <= c && b != 0 && c != 0) {
        --b;
        --c;
    } else if (b >= a && b <= c && a != 0 && c != 0) {
        --a;
        --c;
    } else if (c >= a && c <= b && a != 0 && b != 0) {
        --a;
        --b;
    } else {
        if (a==0) {
            --b;
            --c;
        } else if (b == 0) {
            --a;
            --c;
        } else {
            --a;
            --b;
        }
    }
    return maximumScore(a,b,c) + 1;
}