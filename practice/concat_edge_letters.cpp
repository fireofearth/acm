#include <bits/stdc++.h>
using namespace std;

vector<string> str_fn(vector<string> v) {
  vector<string> out;
  string s1, s2, s;
  for(int i = 0; i < v.size(); i++) {
    s1 = v[i];
    s2 = v[(i + 1) % v.size()];
    s = s1.substr(0,1) + s2.substr(s2.size() - 1, s2.size());
    out.push_back(s);
  }
  return out;
}

int main() {
  vector<string> sin, sout;
  string s;
  s = "apples";
  sin.push_back(s);
  s = "tulip";
  sin.push_back(s);
  s = "cucumber";
  sin.push_back(s);
  sout = str_fn(sin);
  for(const auto &s : sout) {
    cout << s << " ";
  }
  cout << endl;
  return 0;
}
