#include <iostream>
#include <fstream>

using namespace std;


/*
Author: Andreas Zeijlon

Date: 2020-05-10
*/

long long zeros(long long n) {
    long long result = 0;
    long long index = 1;

    while(1) {
        long long q = n/index;
        long long r = n%index;

        long long a = q/10;
        q = q%10;

        if (a==0) {
            return result;
        }
        else if(q==0) {
            result+=(a-1)*index+r+1;
        }
        else {
            result += a*index;
        }
        index*=10;
    }
}

int count_zeros(long long m) {
    int count = 0;
    long long m_cp = m;
    if(m==0) {
        return 1;
    }
    while (m_cp>0) {
        if(m_cp%10==0) {
            count+=1;
        }
        m_cp = m_cp/10;;
    }
    return count;
}

int main() {
    //ifstream cin("input.txt");
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    long long m, n;
    while(cin >> m >> n) {
        if(m == -1 && n == -1) {
            return 0;
        }

        long long result = zeros(n) - zeros(m);

        int count = count_zeros(m);
        
        result += count;

        cout << result << endl;

    }
    return 0;
}

