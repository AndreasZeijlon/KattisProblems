#include <iostream>
#include <fstream>
#include <vector>
#include <limits>

using namespace std;


/*
Author: Andreas Zeijlon
Date: 16/4/2020

shortest_path function is a direct implementation of dijkstras algorithm according to the pseudocode on wikipedia. (https://en.wikipedia.org/wiki/Dijkstra%27s_algorithm)

API:
    vector<int> shortest_path(vector<vector<edge> > edges, int start, int nodes, vector<int> &prev)

    parameters:
        edges: A 2d vector with information about the graph. Row Y contains the edges coming out from node Y. (vector<vector<edge> >) 
        start: The node where the algorithm will start searching paths from. (int)
        prev: An empty vector where the paths from start to each node will be stored. If edge from u to v, then prev[v] = u if that edge is used in the path so backtracking is possible to get full path. If no path is possible prev[v] is set to -1. (int)

    return value:
        A vector containing the distance from start node to each other node in the graph. If no path possible the distance is INT_MAX.

Data structures:
    edge:
        fields:
            u: The start node of the edge. (int)
            v: The end node of the edge. (int)
            w: The weight or distance of the edge. (int) 

Time complexity:
O(V + E*log(V)) where V=Number of nodes, E=Number of edges.

*/


struct edge {
    int u, v, w;

    edge() = default;

    edge(int from, int to, int weight) {
        u = from;
        v = to;
        w = weight;
    }


};

vector<int> shortest_path(vector<vector<edge> > edges, int start, vector<int> &prev) {
    int nodes = edges.size();
    vector<int> unvisited(nodes);
    vector<int> dist(nodes, numeric_limits<int>::max());
    dist[start] = 0;
    prev[start] = start;

    for (int i = 0; i < nodes; i++)
    {
        unvisited[i] = i;
    }

    while(!unvisited.empty()) {
        int min_distance = numeric_limits<int>::max();
        int u = -1;
        int min_index = -1;
        int node;

        for (int i = 0; i < unvisited.size(); i++)
        {
            node = unvisited[i];
            if(dist[node]<min_distance) {
                min_distance = dist[node];
                u = node;
                min_index = i;
            }
        }

        if(u == -1) {
            // no path
            break;
        } 

        unvisited.erase(unvisited.begin() + min_index);

        //for every neighbour v of u
        for (int i = 0; i < edges[u].size(); i++)
        {
            edge e = edges[u][i];
            int alt = dist[u] + e.w;
            if(alt < dist[e.v]) {
                dist[e.v] = alt;
                prev[e.v] = e.u;
            } 
        }
        

        
    }

    return dist;   
}

int main() {
    //std::ifstream cin("input.txt");
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int nodes, num_edges, num_queries, start;
    int u, v, w;
    int destination;

    while(cin >> nodes >> num_edges >> num_queries >> start) {
        if(nodes==0 && num_edges == 0 && num_queries == 0 && start == 0) {
            break;
        }
        vector<vector<edge> > edges(nodes);
        vector<int> queries(num_queries);

        for (int i = 0; i < num_edges; i++)
        {
            cin >> u >> v >> w;
            edge e(u, v, w);
            edges[e.u].push_back(e);
        }
        for (int i = 0; i < num_queries; i++)
        {
            cin >> destination;
            queries[i] = destination;
        }

        vector<int> prev(nodes, -1);

        vector<int> distance = shortest_path(edges, start, prev);

        for (int i = 0; i < num_queries; i++)
        {
            if(distance[queries[i]] == numeric_limits<int>::max()){
                cout << "Impossible" << "\n";
            } else {
                
                cout << distance[queries[i]] << "\n";
            }
        }
        cout << "\n";
    }
    return 0;
}