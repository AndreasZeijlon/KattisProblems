#include <iostream>
#include <ios>
#include <iomanip>
#include <sstream>

/*
Author: Andreas Zeijlon
Date: 2020-02-10
*/

using namespace std;

int main(void) {
    long long n;
    cin >> n;


    long long result = 1;
    long long num_fives = 0;
    long long num_twos = 0;

    for (long long i = 1; i <= n; i++)
    {
        long long tmp = i;
        // count all fives
        while(tmp%5==0) {
            tmp /= 5;
            num_fives++;
        }
    }

    for (long long i = 1; i <= n; i++)
    {
        long long tmp = i;
        // remove all factors of fives
        while(tmp%5 == 0) {
            tmp/=5;
        }

        // remove all twos, but not more than fives
        while(tmp%2 == 0 && num_twos < num_fives) {
            tmp/=2;
            num_twos++;
        }

        result = result*tmp%1000;
    }

    if(n>=7) {
        cout << setfill('0') << setw(3) << result << endl;
    } else{
        cout << result << endl;
    }
    return 0;
}