#include <iostream>
#include <string>
using namespace std;

void print_string_permute(string s, string header = ""){
  int n = s.length();
  if (n == 0){
    cout << header << endl;
    return;
  }

  for (int i = 0; i < n; i++) {
    string s_next = string(s).erase(i,1);
    string header_next = header + s[i];
    print_string_permute (s_next, header_next);
  }
}

int main(int argc, char *argv[]){
  string s;
  while (cin >> s){
    print_string_permute(s);
  }
  return 0;
}
