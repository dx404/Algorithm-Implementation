/** 
 * Implementation of arbituray dimensional array in Morton order layout
 * Created by Duo Donald Zhao on 4/21/15.
 * Copyright (c) 2015 Duo Donald Zhao. All rights reserved.
 */
#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

class Morton {
public:
    int num_of_dim;
    vector<int> dim;
    vector<int> bit_length;
    
    Morton(const vector<int> &dim) {
        this->dim = dim;
        num_of_dim = (int) dim.size();
        bit_length.resize(num_of_dim);
        dim_padded.resize(num_of_dim);
        mask.resize(num_of_dim);
        interleave.resize(num_of_dim);
        compact.resize(num_of_dim);
        structure_pad();
        for (int i = 0; i < num_of_dim; i++) {
            interleave[i].resize(dim_padded[i]);
        }
        init_mask();
        init_interleave();
    }
    // Translation from Spatial Index to Morton Index
    int mortonIndex(const vector<int> &pos){
        int index = 0;
        for (int i = 0; i < num_of_dim; i++) {
            index |= interleave[i][pos[i]];
        }
        return index;
    }
    // Transalation from Morton Index to Spatial Index
    vector<int> spatialIndex(int index) {
        vector<int> spatialIndex(num_of_dim);
        for(int i = 0; i < num_of_dim; i++) {
            spatialIndex[i] = compact[i][index & mask[i]];
        }
        return spatialIndex;
    }
    // Traverse a direction from a give Morton Index
    int move(int mortonIndex, const vector<int> &dir){
        int newMortonIndex = mortonIndex;
        for (int i = 0; i < num_of_dim; i++) {
            int indexElse = newMortonIndex & (~mask[i]);
            int indexRead;
            if (dir[i] > 0) {
                indexRead = ((mortonIndex | ~mask[i]) + interleave[i][dir[i]]) & mask[i];
            }
            else {
                indexRead = ((mortonIndex & mask[i]) - interleave[i][-dir[i]]) & mask[i];
            }
            newMortonIndex = indexRead | indexElse;
            
        }
        return newMortonIndex;
    }

private:
    vector<int> dim_padded;
    vector<int> mask;
    vector<vector<int> > interleave;
    vector<unordered_map<int,int> > compact;
    
    void structure_pad() {
        for (int i = 0; i < num_of_dim; i++) {
            int t = dim[i] - 1;
            int n = 0;
            while (t) {
                t >>= 1;
                n++;
            }
            bit_length[i] = n;
            dim_padded[i] = 1 << n;
        }
    }

    void init_mask() {
        int longest = bit_length[0];
        for (int j = longest-1; j >= 0; j--) {
            for (int i = 0; i < num_of_dim && j < bit_length[i]; i++) {
                for (int k = 0; k < num_of_dim; k++) {
                    mask[k] =  (mask[k] << 1) + (k == i);
                }
            }
        }
    }
    
    void init_interleave() {
        for (int i = 0; i < num_of_dim; i++) {
            int zID = 0;
            int offset = num_of_dim - i - 1;
            for (int j = 0; j < dim_padded[i]; j++) {
                interleave[i][j] = zID;
                compact[i][zID] = j;
                zID = ((zID | ~mask[i]) + (1 << offset)) & (mask[i]);
            }
        }
    }
    
};

int main(int argc, char *argv[]) {
    vector<int> dims = {63, 15, 7};
    Morton mt (dims);
    int zID = mt.mortonIndex({47, 10, 5});
    cout << dec << zID << endl;
    int s = mt.move(6005, {-2, 3,-2});
    for (auto wi : mt.spatialIndex(s)) {
        cout << wi << endl;
    }
    return 0;
}
