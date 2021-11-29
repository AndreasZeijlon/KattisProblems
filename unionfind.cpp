#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

/*
Author: Andreas Zeijlon
Date: 2020-02-25

The union_tree data structure lets you merge two integers into a union and check if two integers belong to the same union.

Structure:
    fields: 
        union_sets: A tree graph where the index is a child to the value on that index. (vector<int>)
        ranks: A list containing the level of depth that each node has in the tree graph.

    methods:
        void union_(int a, int b):
            Merge union of a and union of b together. Chooses the union root node with least depth as parent to the other node.
        int find_root(int x):
            Finds and returns the root node of the union that x belongs to.
        bool same(int a, int b):
            Checks if a and b belong to the same union.

Time complexity:
O(n)
*/


struct union_tree {
    vector<int> union_sets;
    vector<int> ranks;

    union_tree(int N) {
        union_sets.resize(N);
        ranks.resize(N, 0);

        for (int i = 0; i < N; i++) {
            union_sets[i] = i;
        }
    }

    void union_(int a, int b) {
        int aroot = find_root(a);
        int broot = find_root(b);

        if(aroot != broot) {
            if(ranks[aroot] < ranks[broot]) {
            union_sets[aroot] = broot;
            } else {
                union_sets[broot] = aroot;
                if(ranks[aroot] == ranks[broot]) {
                    ranks[aroot] += 1;
                }
            }
        } 
    }

    int find_root(int x) {
        int init_x = x;
        while(union_sets[x] != x) {
            x = union_sets[x];
        }
        union_sets[init_x] = x;
        return x;
    }

    bool same(int a, int b) {
        return find_root(a) == find_root(b);
    }

};

int main() {
    //ifstream cin("input.txt");
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int N, Q, a, b;
    char q;
    
    while(cin >> N >> Q) {
        union_tree my_union_tree(N);
    
        for (int i = 0; i < Q; i++) {
            cin >> q >> a >> b;
            if(q=='?') {
                if(my_union_tree.same(a, b)) {
                    cout << "yes\n";
                } else {
                    cout << "no\n";
                }
            } else if(q=='=') {
                my_union_tree.union_(a, b);
            }
        }
    }
    
    
    return 0;
}
    

