#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;


bool is_prime(int n) {
    if(n==1) {
        return false;
    }
    int m=n/2;  
    for(int i = 2; i <= m; i++)  
    {  
        if(n % i == 0)  
        {  
            return false;
        }  
    }  
    return true;  
}

string is_happy(string s, vector<string> seen_numbers) {
    if(stoi(s) == 1){
        return "YES";
    } else if(find(seen_numbers.begin(), seen_numbers.end(), s) != seen_numbers.end()){
        return "NO";
    }

    int res = 0;

    for (int i = 0; i < s.size(); i++)
    {
        int a = (int)s[i] - 48;
        res += a*a;
    }
    seen_numbers.push_back(s);
    return is_happy(to_string(res), seen_numbers);
}

string solve(string s){

    if(!is_prime(stoi(s))) {
        return "NO";
    }

    vector<string> seen_numbers;
    string res = is_happy(s, seen_numbers);


    return res;
    
}

int main() {
    //ifstream cin("input.txt");
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int P, K;
    string m;
    cin >> P;

    for (int i = 0; i < P; i++)
    {
        cin >> K >> m;

        string res = solve(m);


        printf("%d %s %s\n", K, m.c_str(), res.c_str());

    }
    



    return 0;
}

