#include <iostream>
#include <vector>
using namespace std;

/*

g++ -std=c++11 m-construct-perm.cpp -o k

 */

int main() {

    int a, b; 
    cin >> a >> b;

    int k = 0;
    cout << a*b << endl;
    for(int i = a*b - a + 1; i <= a*b; i++) {
        for(int j = 0; j < b; j++) {
            k++;
            cout << i - a*j << (k == a*b ? "" : " ");
        }
    }
    cout << endl;

    return 0;
}


