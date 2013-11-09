/**
 * Author: Duo Zhao
 * for C++ review purpose
 * the Permutator class takes a vector of generic type T and
 * generating all permutations storing into a tank variable
 * A print function is used to show all permutations to standard output
 */
#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>
using namespace std;

template <class T>
class Permutator {
private:
	vector<T> &srcList; //not able to be const
	vector<T*> srcPtr;
	vector< vector<T*> > *tank;
public:
	Permutator(vector<T> &src) :
		srcList(src), // initialization list
		srcPtr (vector<T*> (srcList.size())) {
		transform(srcList.begin(), srcList.end(),
				srcPtr.begin(),
				[](T &t){ return &t;} //Lambda expression keep the pointers
		);
		tank = new vector< vector<T*> >();
	}

	~Permutator(){
		delete tank;
	}

	inline void get_permute(){
		get_permute(srcPtr, vector<T*>());
	}
	void get_permute(vector<T*> s, vector<T*> header);
	void print_permute_result();
};

int main(int argc, char *argv[]){
	string textLine;
	while (getline(cin, textLine)){
		stringstream lineStream (textLine);
		vector<int> srcList;
		int val;
		while (lineStream >> val){
			srcList.push_back(val);
		}
		Permutator<int> *p = new Permutator<int> (srcList); // with a template variable
		p->get_permute();
		p->print_permute_result();
		delete p;
	}
	return 0;
}

template <class T>
void Permutator<T>::get_permute(vector<T*> s, vector<T*> header){
	int n = s.size();
	if (n == 0){
		tank->push_back(header);
		return;
	}
	for (int i = 0; i < n; i++) {
		vector<T*> s_next = vector<T*>(s);
		s_next.erase(s_next.begin() + i);
		vector<T*> header_next = vector<T*>(header);
		header_next.push_back(s[i]);
		get_permute(s_next, header_next);
	}
}

template <class T>
void Permutator<T>::print_permute_result(){
	vector< vector<T*> > &tankr = *tank; //reference to de-pointing
	for (int i = 0; i < tankr.size(); i++){
		for (int j = 0; j < tankr[i].size(); j++){
			cout << *tankr[i][j] << " ";
		}
		cout << endl;
	}
}
