#include <iostream>
#include <vector>

using namespace std;

void quicksort(vector<int> &x, int a, int b) {
    if (a >= b) 
        return;
    int i = a;
    for (int j = a; j <= b-1; j++) {
        if (x[j] <= x[b]) 
            swap(x[i++], x[j]);
    }
    swap(x[i], x[b]);
    quicksort(x, a, i-1);
    quicksort(x, i+1, b);
}

void quicksort(vector<int> &x) {
    quicksort(x, 0, x.size()-1);
}

int main()
{
   cout << "Hello Quicksort!" << endl; 
   vector<int> x = {87,59,50,73,5,1,48,26,72,13,53,1,27,78,32,52,21,11,95,38,80,35,59,98,65,96,77,58};
   quicksort(x);
   for (auto v : x) {
       cout << v << endl;
   }
   return 0;
}
