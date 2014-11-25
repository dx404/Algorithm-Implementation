#include <iostream>
#include <bitset>
using namespace std;

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

int countBits_builtIn (int x) {
    return bitset<8*sizeof(x)>(x).count();
}

int main(int argc, char *argv[]) {
   int x = 111534534;
   cout << countBits (x) << endl;
   cout << countBits_op(x) << endl;
   cout << countBits_r(x) << endl;
   cout << countBits_builtIn(x) << endl;
   return 0;
}

