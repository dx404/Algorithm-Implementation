#include <iostream>
#include <vector>

using namespace std;

vector<int> mergeSort(vector<int> &x, int a, int b) {
    if (a == b) {
        return {x[a]};
    }
    int mid = (a+b)/2;
    vector<int> left  = mergeSort(x, a, mid);
    vector<int> right = mergeSort(x, mid+1, b);
    vector<int> merged;
    int i = 0, j = 0, m = left.size(), n = right.size();
    while (i < m && j < n) {
        if (left[i] < right[j]) 
            merged.push_back(left[i++]);
        else 
            merged.push_back(right[j++]);
    }
    while (i < m)
        merged.push_back(left[i++]);
    while (j < n)
        merged.push_back(right[j++]);
    return merged;
}


int main()
{
  cout << "Hello MergeSort!" << endl; 
//vector<int> x = {9, 2,1,3};
  vector<int> x = {59,50,73,5,1,48,26,72,13,53,1,27,78,32,52,21,11,95,38,80,35,59,98,65,96,77,58};
    vector<int> y = mergeSort(x, 0, x.size()-1);
    for (auto v : y) {
      cout << v << endl;
      
  }
   return 0;
}
