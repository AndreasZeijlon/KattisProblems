#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <queue>
#include <algorithm>

using namespace std;

/*
Author: Andreas Zeijlon
Date: 11/4/2020
*/

struct suffix {
    int position;
    string data;

    suffix(int p, string s) {
        position = p;
        data = s;
    }

    bool operator<(const suffix& rhs) const {
        return data.size() > rhs.data.size();
    }
};

bool suffix_fits(int start, string s, string text) {
    int suffix_index = 0;
    for (int i = start; i < start+s.size(); i++)
    {
        if(text[i] != '0') {
            if(text[i] != s[suffix_index]) {
                return false;
            }
        }
        suffix_index++;
    }
    return true;
    
}

string reconstruct_suffix(int length, priority_queue<suffix> pq) {
    string output_s(length, '0');
    vector<suffix> suffix_with_asterisk;

    while (!pq.empty())
    {
        suffix suff = pq.top();
        pq.pop();

        string::iterator it = find(suff.data.begin(), suff.data.end(), '*');

        if(it != suff.data.end()) {
            int index = it-suff.data.begin();

            string before_asterisk = suff.data.substr(0, index);
            string after_asterisk = suff.data.substr(index+1);

            suffix_with_asterisk.push_back(suffix(suff.position+index, after_asterisk));
            pq.push(suffix(suff.position, before_asterisk));
            continue;
        } 
        
        if (suffix_fits(suff.position, suff.data, output_s))
        {
            int suffix_index = 0;
            for (int i = suff.position; i < suff.position+suff.data.size(); i++)
            {
                output_s[i] = suff.data[suffix_index];
                suffix_index++;
            }
            
        } else {
            return "IMPOSSIBLE";
        }
    }

    for(suffix suf : suffix_with_asterisk)
    {
        int i = output_s.size()-1;
        for (int suffix_index = suf.data.size()-1; suffix_index >= 0; suffix_index--)
        {
            if(output_s[i] == '0') 
            {
                output_s[i] = suf.data[suffix_index];
            } 
            else if(output_s[i] != suf.data[suffix_index])
            {
                return "IMPOSSIBLE";
            }

            i--;
        }
    }


    for (int i = 0; i < output_s.size(); i++)
    {
        if(output_s[i] == '0') {
            return "IMPOSSIBLE";
        }
    }

    return output_s;


}

int main() {
    //ifstream cin("input.txt");
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;
    
    for (int i = 0; i < n; i++)
    {
        int length, num_suffixes;
        cin >> length >> num_suffixes;

        priority_queue<suffix> pq;


        for (int j = 0; j < num_suffixes; j++)
        {
            int position;
            string sfx;
            cin >> position >> sfx;

            pq.push(suffix(position-1, sfx));    
        }

        string original_message = reconstruct_suffix(length, pq);

        cout << original_message << "\n";
        
    }
    
}