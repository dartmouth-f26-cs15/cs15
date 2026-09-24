void add_one(int * p) {
    p += 1;
}

int main(void) {
    int i = 0;
    add_one(i);
    return i;
}
