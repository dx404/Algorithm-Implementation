#include <iostream>
#include <map>
#include <vector>
using namespace std;

map<int, int> cMap;

int down2one(int n){
  if (cMap.count(n)>0)
    return cMap[n];
  else if (n == 1)
    return cMap[1] = 1;
  else if (n & 1)
    return cMap[n] = down2one(3*n+1) + 1;
  else
    return cMap[n] = down2one(n/2) + 1;
}

int down2onei(int n){
  int b = 0, c;
  vector<int> tr;
 
  while (cMap.count(n) == 0){
    tr.push_back(n);
    n = (n&1)? (3*n+1):(n/2);
  }
  b = cMap[n];
  c = tr.size();
  for (int i = 0; i < c; i++){
    cMap[tr[i]] = c - i + b;
  }
  return c + b;
}

// precondition i <= j
inline int maxDown2one(int i, int j){
  int cmax = 0;
  cMap[1] = 1;
  for (int n = i; n <= j; n++){
    int c = down2onei(n);
    if (c > cmax)
      cmax = c;
  }
  return cmax;
}

int main(int argc, char * argv[]){
  int i, j, count = 0;

  while (cin >> i >> j){
    count = (i<=j) ? maxDown2one(i, j):maxDown2one(j, i);
    cout << i << " " << j << " " << count << endl;
  }
  return 0;
}
