#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

/*
Author: Andreas Zeijlon
Date: 23/5/2020

kmp_search() function will search for patterns in a text sequence. It uses a help function kmp_table() to precompute a lookup table for faster searching. kmp_search and kmp_table are implementations of the Knuth–Morris–Pratt algorithm (https://en.wikipedia.org/wiki/Knuth%E2%80%93Morris%E2%80%93Pratt_algorithm) 

API:
    kmp_search(string sequence, string word)

        parameters:
            sequence: The text sequence to be searched. (string)
            word: The word or pattern to use when searching. (string)

        return value:
            P: an array of integers with the positions in sequence where pattern is found. (vector<int>)
            
    kmp_table(string word)

        parameters:
            word: The word or pattern to use when searching. (string)

        return value:
            T: an array of integers that is to be used in kmp_search()(vector<int>)


Time complexity:
O(text + pattern)
*/

vector<int> kmp_table(string word) {
    int pos = 1;
    int cnd = 0;

    vector<int> T(word.length()+1);
    T[0] = -1;

    while (pos < word.length()) {
        if(word[pos] == word[cnd]) {
            T[pos] = T[cnd];
        }
        else {
            T[pos] = cnd;
            cnd = T[cnd];
            while(cnd >= 0 && word[pos] != word[cnd]) {
                cnd = T[cnd];
            }
        }
        pos++;
        cnd++;
    }
    T[pos] = cnd;

    return T;
}

vector<int> kmp_search(string seq, string word) {
    int j=0;
    int k=0;
    vector<int> P;
    vector<int> T = kmp_table(word);

    while (j < seq.length()) {
        if(word[k] == seq[j]) {
            j++;
            k++;
            if(k==word.length()) {
                P.push_back(j-k);
                k = T[k];
            }
        }
        else {
            k = T[k];
            if (k<0) {
                j++;
                k++;
            }
        }
    }
    return P;
}

int main() {
    ifstream cin("input.txt");
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    string pattern, text;

    while(getline(cin, pattern)){
        getline(cin, text);
        vector<int> p = kmp_search(text, pattern);

        for (int i = 0; i < p.size(); i++)
        {
            cout << p[i] << " ";
        }
        cout << "\n";
        
    }
    
    return 0;
}