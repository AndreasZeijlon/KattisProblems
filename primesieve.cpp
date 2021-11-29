#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>


using namespace std;

/*
Author: Andreas Zeijlon
Date: 21/05/2020

eratosthenes(int n) will find all prime numbers ranging from 2 to integer n.

API:
    eratosthenes(int n)

    parameters:
        n: an integer > 1. (int)

    return value:
        Returns all prime numbers up to n in the form of a lookup vector. (vector<bool>)

eratosthenes function implements eratosthenes algorithm exactly. https://en.wikipedia.org/wiki/Sieve_of_Eratosthenes

Time complexity:
O(nloglogn)
*/

vector<bool> eratosthenes(int n) {
    vector<bool> A(n+1, true);
    A[0] = false;
    A[1] = false;

    for (int i = 2; i < sqrt(n+1); i++)
    {
        if(A[i] == true) {
            for (int j = pow(i, 2); j < n+1; j+=i)
            {
                A[j] = false;
            }
            
        }
    }
    return A;
    
    
}

int main() {
    //ifstream cin("input.txt");
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n, q, x;
    cin >> n >> q;

    vector<bool> result = eratosthenes(n);

    int total = 0;
    for (int i = 0; i < result.size(); i++)
    {
        if(result[i] == true) {
            total++;
        }
    }

    cout << total << "\n";

    for (int i = 0; i < q; i++)
    {
        cin >> x;

        if(result[x]) {
            cout << 1 << endl;
        } else {
            cout << 0 << endl;
        }
    }

    return 0;
}