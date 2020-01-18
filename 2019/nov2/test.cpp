#include<iostream>
using namespace std;

void test(int **a, int h, int w) {
    for(int i = 0; i < h; i++) {
        for(int j = 0; j < w; j++)
            cout << a[i][j] << " ";
        cout << endl;
    }
}

/*
g++ --std=c++11 -o k test.cpp

*/
int main() {
    int h, w;
    cin >> h >> w;
    int arr[h][w];
    int *brr[h];
    for(int i = 0; i < h; i++) {
        brr[i] = arr[i];
        for(int j = 0; j < w; j++)
            arr[i][j] = (i + 1) * (j + 1);
    }

    int (*ptr)[h][w];
    ptr = &arr;
    for(int i = 0; i < h; i++) {
        for(int j = 0; j < w; j++)
            cout << (*ptr)[i][j] << " ";
        cout << endl;
    }
    cout << endl;
    test(brr, h, w);

    return 0;
}
