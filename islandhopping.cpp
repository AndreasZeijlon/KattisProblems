#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <algorithm>
#include <string>
#include <math.h>
#include <iomanip>

using namespace std;

struct endpoint{

    float x, y;

    endpoint() = default;

    endpoint(float X, float Y) {
        x = X;
        y = Y;
    }
};

struct bridge{

    float length;
    float a, b;

    bridge(float A, float B, float L) {
        a = A;
        b = B;
        length = L;
    }

    bool operator<(const bridge& rhs) const
    {
        return length > rhs.length;
    }
};

int find_(int x, vector<int> &union_tree) {
    while(union_tree[x] != x) {
        x = union_tree[x];
    }
    return x;
}

void union_(vector<int> &union_tree, int a, int b, vector<int> &ranks) {
    int aroot = find_(a, union_tree);
    int broot = find_(b, union_tree);

    if(aroot != broot) {
        if(ranks[aroot] < ranks[broot]) {
        union_tree[aroot] = broot;
        } else {
            union_tree[broot] = aroot;
            if(ranks[aroot] == ranks[broot]) {
                ranks[aroot] += 1;
            }
        }
    } 
}

float min_span_tree(priority_queue<bridge> &bridges, vector<int> &union_tree, vector<int> ranks, int &nodes, int &num_of_bridges) {
    float cost = 0;

    while(!bridges.empty() && num_of_bridges < nodes-1) {
        bridge best = bridges.top();
        bridges.pop();

        if(find_(best.a, union_tree) == find_(best.b, union_tree)) {
            // they have the same root, toss the edge
        } else {
            cost += best.length;
            num_of_bridges++;
            union_(union_tree, best.a, best.b, ranks);
        }
    }
    return cost;
}


int main() {
    //ifstream cin("input.txt");
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n, nr_islands;
    cin >> n;
    for (size_t i = 0; i < n; i++)
    {
        cin >> nr_islands;

        vector<int> union_tree(nr_islands);
        vector<int> ranks(nr_islands, 0);
        vector<endpoint> endpoints(nr_islands);
        priority_queue<bridge> bridges;

        for (size_t j = 0; j < nr_islands; j++)
        {
            float x, y;
            cin >> x >> y;
            endpoints[j] = endpoint(x, y);
            union_tree[j] = j;
        }

        for (size_t i = 0; i < nr_islands; i++)
        {
            for (size_t j = 0; j < nr_islands; j++)
            {
                if(i != j) {
                    float length = hypot(endpoints[i].x - endpoints[j].x, endpoints[i].y - endpoints[j].y);
                    bridges.push(bridge(i, j, length));

                }
            }
            
        }
        int num_of_bridges = 0;
        float result = min_span_tree(bridges, union_tree, ranks, nr_islands, num_of_bridges);
        if(num_of_bridges != nr_islands-1) {
            cout << "Impossible\n";
        } else {
            cout << fixed;
            cout << std::setprecision(5);
            cout << result << "\n";
        }       
    }
    return 0;
}