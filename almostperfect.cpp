#include <iostream>
#include <fstream>
#include <cmath>


using namespace std;


void solve(int n) {
    int res = 0;

    for (int i = 1; i <= sqrt(n); i++)
    {
        if(i == 1) {
            res+=1;
        }
        else if(n%i == 0) {
            if(n/i == i){
                res+=i;
            } else {
                res+=i;
                res+=n/i;
            }
        }
    }

    cout << n << " ";

    if(n==res) {
        cout << "perfect\n";
    }
    else if(n-2 <= res && res <= n+2) {
        cout << "almost perfect\n";
    } else {
        cout << "not perfect\n";
    }

}

int main() {
    //ifstream cin("input.txt");
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    while(cin >> n) {
        solve(n);
    }


    return 0;
}