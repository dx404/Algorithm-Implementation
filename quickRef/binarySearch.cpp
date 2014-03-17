#include <iostream>
#include <vector>
#include <cassert>

using namespace std;

/** e.g.
 *  vector <int> a = {3, 5, 7};
 *  The indices:      0, 1, 2
 *      x <= 3  -> returns 0
 *  3 < x <= 5  -> returns 1
 *  5 < x <= 7  -> returns 2
 *      x >  7  -> returns 3
 */
int binSearch(vector <int> &a, int x){
    int n = (int) a.size();
    int start = 0, end = n - 1;
    int mid = (start + end) / 2;
    while (start <= end) { // "=" inclusive
        assert(mid >=0 && mid < n);
        if (x > a[mid]){
            start = mid + 1;
        }
        else if (x < a[mid]){
            end = mid - 1;
        }
        else {
            return mid;
        }
        mid = (start + end) / 2;
    }
    return start;  // start > end, return the larger one
}

/**
 * equivalently in seqential iterative version
 */
int seqSearch(vector <int> &a, int x){
    int n = (int) a.size();
    int i = 0;
    while (i < n && x > a[i])
        i++;
    return i;
}


int main()
{
    cout << "Hello World" << endl;
    vector <int> a = {3,5,7};
    
    for (int i = 1; i < 9; i++){
        cout << i << ": " << binSearch(a, i) << "\t" << seqSearch(a, i)<< "\t" << (binSearch(a, i) == seqSearch(a, i)) << endl;
    }
    return 0;
}
