unsigned char my_log2(unsigned long const n) {
    if (n <= 1) {
        return 0;
    }
    return 1 + my_log2(n / 2);
}

unsigned char my_sub(unsigned char const x, unsigned char const y) {
    return x - y;
}

unsigned char my_abs(signed char const x) {
    return x < 0 ? -x : x;
}
