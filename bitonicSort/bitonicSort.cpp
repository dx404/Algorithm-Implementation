//
//  main.cpp
//  bitonicSort
//  Created by Duo Donald Zhao on 11/16/13.
//  Copyright (c) 2013 Duo Donald Zhao. All rights reserved.
//  A C++ implementation of Bitonic Sort Algorithm
// 
/** Sample
 * 17
 * 4 3 17 1 5 8 11 13 2 7 9 14 6 12 10 16 15
 * 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 
*/

#include <iostream>
using namespace std;
/**
 * s: starting index, inclusive
 * e: ending index, exclusive
 */
void bitonicSort(int a[], int s, int e, bool up, bool bitonic);
void bitonicSplit(int a[], int s, int e, bool up);

int main(int argc, const char * argv[]){
    int size;
    cin >> size;
    int *a = new int[size];
    for (int i = 0; i < size; i++){
        cin >> a[i];
    }
    bitonicSort(a, 0, size, true, false);
    for (int i = 0; i < size; i++){
        cout << a[i] << " ";
    }
    cout << endl;
    delete a;
    return 0;
}

void bitonicSort(int a[], int s, int e, bool up, bool bitonic){
    int d = e - s;
    if (d <= 1)
        return;
    //The left partition is the larger
    int mid = (s+e)/2 + (d & 1); //ceiling
    if (!bitonic && d > 2){
        bitonicSort(a, s, mid, up, false);
        bitonicSort(a, mid, e, !up, false);
    }
    bitonicSplit(a, s, e, up);
    bitonicSort(a, s, mid, up, true);
    bitonicSort(a, mid, e, up, true);
}

void bitonicSplit(int a[], int s, int e, bool up){
    int d = e - s;
    int offset = (d & 1)? up : 0;
    int mid = (s+e)/2 + (d & 1);
    int iLeft = s + offset;
    int iRight = mid;
    while (iLeft < mid && iRight < e){
        if ((a[iLeft] > a[iRight]) == up){
            int temp = a[iLeft];
            a[iLeft] = a[iRight];
            a[iRight] = temp;
        }
        iLeft++;
        iRight++;
    }
}

