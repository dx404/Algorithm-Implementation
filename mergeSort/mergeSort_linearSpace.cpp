#include <iostream>
#include <vector>

using namespace std;

// O(n) space version
void mergeSort(vector<int> &x, int a, int b, vector<int> &scratch) {
    if (a == b) {
        scratch[a] = x[a];
        return;
    }
    int mid = (a + b) / 2;
    mergeSort(x, a, mid, scratch);
    mergeSort(x, mid+1, b, scratch);
    int i = a, j = mid+1, k = a;
    while (i <= mid && j <= b) {
        if (x[i] < x[j])
            scratch[k++] = x[i++];
        else
            scratch[k++] = x[j++];
    }
    while (i <= mid)
        scratch[k++] = x[i++];
    while (j <= b)
        scratch[k++] = x[j++];
    for (int i = a; i <= b; i++) {
        x[i] = scratch[i];
    }
}


int main()
{
  cout << "Hello MergeSort!" << endl; 
//   vector<int> x = {9,1,2};
  vector<int> x = {59,50,73,5,1,48,26,72,13,53,1,27,78,32,52,21,11,95,38,80,35,59,98,65,96,77,58};
  vector<int> y (x.size(), 0);
  mergeSort(x, 0, x.size()-1, y);
    for (auto v : x) {
      cout << v << endl;
      
  }
   return 0;
}
