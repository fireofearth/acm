#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <map>

using namespace std;

/*
g++ -std=c++11 -o k sga.cpp
10
JOSH
JAD
JENNIFER
JENNIFER
JALEN
HASAAN
ALI
TIM
ALEX
TRAVIS
*/

long combi(int n,int k)
{
    long ans=1;
    k=k>n-k?n-k:k;
    int j=1;
    for(;j<=k;j++,n--)
    {
        if(n%j==0)
        {
            ans*=n/j;
        }else
        if(ans%j==0)
        {
            ans=ans/j*n;
        }else
        {
            ans=(ans*n)/j;
        }
    }
    return ans;
}

int main() {
    int n;
    long a = 0;
    string s;
    map<char, int> m;

    cin >> n;
    for(int i = 0; i < n; i++) {
        cin >> s;
        m[s[0]] += 1;
    }

    for(auto const& x : m)
        a += 2*combi(x.second, 2);
    cout << a << endl;

    return 0;
}
