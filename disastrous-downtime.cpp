#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <utility>
#include <string>       
#include <iostream>     

using namespace std;

/*
Author: Andreas Zeijlon
Date: 2020-03-30
*/

struct my_pair{
    int v;
    char type;
    my_pair(char t, int value){
        v=value;
        type = t;
    }

    bool operator<(const my_pair& rhs) const {
        
        if(v > rhs.v) {
            return true;
        } else if(v==rhs.v) {
            if (type == 'x') {
                return false;
            } else {
                return true;
            }
        }
        else {
            return false;
        }
    }
};


int solve(int K, vector<int> ts) {
    priority_queue<my_pair > q;
    
    for (int i = 0; i < ts.size(); i++)
    {
        my_pair p1('x', ts[i]);
        my_pair p2('y', ts[i]+999);
        q.push(p1);
        q.push(p2);
    }
    int count = 0;
    int ans = 0; 
    while(!q.empty()) {

        my_pair p = q.top();
        q.pop();

        if (p.type == 'x') 
            count++; 
  
        if (p.type == 'y') 
            count--; 
  
        ans = max(ans, count); 
    }

    return ans/K + (ans % K != 0);
    
}

int main() {
    //ifstream cin("input1.txt");
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int N, K;
    cin >> N >> K;

    vector<int> timestamps;

    for (int i = 0; i < N; i++)
    {
        int t;
        cin >> t; 
        timestamps.push_back(t);

    }

    int res = solve(K, timestamps);
    cout << res << endl;

    return 0;
}