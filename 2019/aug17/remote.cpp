#include <iostream>
#include <string>
#include <vector>
#include <map>

using namespace std;

/*
g++ -std=c++11 -o k remote.cpp
*/
enum Check {above, below};
enum Hit {above, below, both};

void proc_one(int *tt, int *b) {
    int j = 0;
    int k = tt[0];
    while(true) {
        if((k + j < 10 && b[k + j]) || (k - j >= 0 && b[k - j]))
            break;
        j++;
    }
    cout << j << endl;

}

int main() {
    int n, a, l, j, k;
    string t;
    int b[10];
    for(int i = 0; i < 10; i++)
        b[i] = true;

    cin >> n;
    for(int i = 0; i < n; i++) {
        cin >> a;
        b[a] = false;
    }

    cin >> t;
    l = t.length();

    int tt[l];
    int kk[l];
    Hit h; 
    for(int i = 0; i < l; i++)
        tt[i] = t[i] - '0';

    if(l == 1) {
        proc_one(tt, b);
        return 0;
    }

    if(l == 2) {
        j = 0;
        k = tt[1];
        while(true) {
            if(k + j < 10 && b[k + j]) {
                if(k - j == 0 || (k - j > 0 && b[k - j]))
                    h == both;
                else
                    h == above;
                break;
            } else if(k - j == 0 || (k - j > 0 && b[k - j])) {
                h == below;
                break;
            }
            j++;
        }

        if(j == 0) {
            proc_one(tt, b);
            return 0;
        }

        kk[1] = j;
        j = 1;
        while(true) {
            if(h == both)
                if(b[j - 1] || b[10 - j])
                    break;
            else if(h == above)
                if(b[j - 1])
                    break;
            else // if(h == below)
                if(b[10 - j])
        }
        //h = ((h == both || h == above) && b[j - 1]) ? ((h == both && b[10 - j]) ? both : above) : below
        kk[0] = j;
        cout << kk[0] + (kk[1] * 10) << endl;
        return 0;
    }

    for(int i = l - 1; i >= 0; i--) {
        if(b[k[i]]) continue;
        else {
            c = above;
            h = not_yet;
            j = 1;
            while(true) {
                
            }
        }
    }

    return 0;
}















