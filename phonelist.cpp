#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <string>
#include <utility>
#include <algorithm>

using namespace std;

/*
Andreas zeijlon
25/5/2020
*/

string solve(vector<string> n) {
    for (int i = 0; i < n.size()-1; i++)
    {
        string numb1 = n[i];
        string numb2 = n[i+1].substr(0,numb1.length());

        if(numb1 == numb2) {
            return "NO";
        }
    }
    return "YES";
    

}

int main() {
    //ifstream cin("input.txt");
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int t;
    cin >> t;

    for (int i = 0; i < t; i++)
    {
        int n;
        vector<string> numbers;
        cin >> n;
        for (int i = 0; i < n; i++)
        {
            string number;
            cin >> number;
            numbers.push_back(number);
        }
        sort(numbers.begin(), numbers.end());

        string res = solve(numbers);
        cout << res << "\n";
    }
    

    return 0;
}