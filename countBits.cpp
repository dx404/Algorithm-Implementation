#include <iostream>

int countBits(int x) {
    int n = 0;
    while (x) {
        n += (x & 1);
        x >>= 1;
    }
    return n;
}

int countBits_r (int x) {
    return x ? countBits_r(x>>1) + (x & 1) : 0;
}

int countBits_op (int x) {
    int n = 0;
    while (x) {
        n++;
        x &= x-1;
    }
    return n;
}

int main() {
   int x = 111534534;
   cout << countBits (x) << endl;
   cout << countBits_op(x) << endl;
   cout << countBits_r(x) << endl;
   return 0;
}
