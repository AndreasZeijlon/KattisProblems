#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <map>
#include <tgmath.h>
#include <utility>


using namespace std;

/*
Author: Andreas Zeijlon
Date: 7/4/2020
*/

int count_swaps(string &word, int left, int right) {
    int next_left = left+1;
    int next_right = right-1;
    int swaps = 0;
    while(word[left]!=word[right]) {
        if(word[left] == word[next_right]){
            while(next_right<right) {
                swap(word[next_right], word[next_right+1]);
                next_right += 1;
                swaps += 1;
            }
        } else if (word[right] == word[next_left])
        {
            while(next_left>left) {
                swap(word[next_left], word[next_left-1]);
                next_left -= 1;
                swaps += 1;
            }
        } else {
            next_left += 1;
            next_right -= 1;
        }
    }
    return swaps;
}

void solve(string word){
    int word_size = word.size();
    char odd_char;
    map<char, int> char_freq;

    for (int i = 0; i < word_size; i++)
    {
        char_freq[word[i]] += 1;
    }
    
    int odd_count = 0;
    bool possible = true;
    for(auto &x : char_freq) {
        if (x.second%2 != 0)
        {
            odd_count += 1;
            odd_char = x.first;
            if(odd_count > 1) {
                possible = false;
                break;
            }
        }
    }
    if(!possible) {
        cout << "Impossible\n";
    } else
    {
        int left = 0, right = word_size-1, total_swaps = 0;
        while(left<right) {
            if(word[left] == word[right]) {
                left++;
                right--;
            } else
            {
                int swaps = count_swaps(word, left, right);
                total_swaps += swaps;
                left++;
                right--;
            }
        }

        cout << total_swaps << "\n";
    }
}

int main() {
    ifstream cin("input.txt");
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        string word;
        cin >> word;
        solve(word);
    }
    
    return 0;
}