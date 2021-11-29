#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <algorithm>
#include <string>

using namespace std;


/*
Author: Andreas Zeijlon
Date: 15/4/2020

min_span_tree is a function that creates a minimum spanning tree of a graph.

API:
    int min_span_tree(priority_queue<edge> edge_list, vector<edge> &result, int nodes).

    parameters:
        edge_list: A priority queue with edges sorted by the weight of each edge. Less weight -> top. (priority_queue<edge>)
        result: A result vector where the edges used in solution will be stored. (vector<edge>)
        nodes: Number of nodes in graph. (int)

    return value:
        The total weight of all the edges spanning up the minimum tree. (int)

min_span_tree algorithm will take the edge with the lowest weight and check if its two nodes are in the same union. If they are then the edge would create a circle so don't add it to solution. Otherwise, add it to solution and make the two nodes belong to the same union.

Structures:
    union_tree:
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
    
    edge:
        fields:
            u: Start node of edge. (int)
            v: End node of edge. (int)
            w: Weight of the edge. (int)

Time_complexity:
    O(E*log(N)), where E=number of edges, N=number of nodes

*/

struct edge{

    int u, v, w;
    edge(int start, int end, int weight) {
        u = start;
        v = end;
        w = weight;
    }

    bool operator<(const edge& rhs) const
    {
        return w > rhs.w;
    }
};

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

bool compare_edge(edge &e1, edge &e2)
{
    if(e1.u == e2.u) {
        return e1.v<e2.v;
    }
    return e1.u < e2.u;
}

int min_span_tree(priority_queue<edge> edge_list, vector<edge> &result, int nodes) {
    union_tree my_union_tree(nodes);
    int cost = 0;

    while(!edge_list.empty() && result.size() < nodes-1) {
        edge best = edge_list.top();
        edge_list.pop();

        if(my_union_tree.same(best.u, best.v)) {
            // they have the same root, toss the edge
        } else {
            cost += best.w;
            result.push_back(best);
            my_union_tree.union_(best.u, best.v);
        }
    }
    return cost;
}


int main() {
    //ifstream cin("input.txt");
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int nodes, edges, u, v, w;
    while(cin >> nodes >> edges) {
        
        if (nodes == 0 && edges == 0) {
            break;
        }

        priority_queue<edge> edge_list;

        for (size_t i = 0; i < edges; i++)
        {
            cin >> u >> v >> w;
            if(v<u) {
                edge_list.push(edge(v, u, w));
            } else {
                edge_list.push(edge(u, v, w));
            }
        }
        
        if(edges < nodes-1) {
            cout << "Impossible\n";
        } else {
            vector<edge> result; 
            int cost = min_span_tree(edge_list, result, nodes);
            if(result.size() != nodes-1) {
                cout << "Impossible\n";
            } else {
                std::sort(result.begin(), result.end(), compare_edge);
                cout << cost << "\n";
                for (size_t i = 0; i < result.size(); i++)
                {
                    cout << result[i].u << " " << result[i].v << "\n";
                }
            }       
        } 
    }
    return 0;
}