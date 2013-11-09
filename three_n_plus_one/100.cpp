/**
 * 3n+1 problem,
 * Collatz conjecture
 * iterative
 * brute-force
 */
#include <iostream>
using namespace std;

int down2one(int n){
  int c = 1;
  while (n > 1){
    n = (n & 1) ? (3*n+1):(n/2);
    c++;
  }
  return c;
}

// precondition i <= j
int maxDown2one(int i, int j){
  int cmax = 0;
  for (int n = i; n <= j; n++){
    int c = down2one(n);
    if (c > cmax)
      cmax = c;
  }
  return cmax;
}

int main(int argc, char * argv[]){
  int i, j, count = 0;
  while (cin >> i >> j){
    count = (i<=j) ? maxDown2one(i, j):maxDown2one(j, i);
    cout << i << " " << j << " " <<count << endl;
  }
  return 0;
}
