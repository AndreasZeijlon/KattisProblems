#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <climits>


using namespace std;


/*
Author: Andreas Zeijlon
Date: 1/4/2020

max_flow is a function that will find the maximum flow of a graph with max capacity edges. It is an implementation of the Edmonds-karp-algorithm (https://en.wikipedia.org/wiki/Edmonds%E2%80%93Karp_algorithm).

API:
    vector<vector<edge> > min_span_tree(vector<vector<edge*> > graph, int source, int sink)

    parameters:
        graph: A 2d vector with every node's neighbours as edges. (vector<vector<edge> >)
        source: The start node where flow will come from. (int)
        sink: End node where flow will end up. (int)

    return value:
        The resulting 2d vector of edges with flow. (vector<vector<edge> >)

Edge structure:
    fields:
        start: The start node of the edge. (int)
        end: The end node of the edge. (int)
        flow: The current flow on the edge. (int)
        capacity: The maximum amount of flow that is allowed on the edge. (int)
        *reverse: A pointer to the reversed(pointing the other way) edge struct. (edge)

Time complexity:  
O(V*E^2)
*/

struct edge{
    edge() = default;
    edge(int s, int e, int c) {
        start=s;
        end=e;
        flow=0;
        capacity=c;
    }
    int start, end, flow, capacity;
    edge *reverse;
};

void print_flow_graph(vector<edge*> allEdges, int source, int sink, int num_nodes) {
    int flow_edges = 0;
    int maximum_flow = 0;

    for (int i = 0; i < allEdges.size(); i++)
    {
        if(allEdges[i]->flow > 0) {
            flow_edges += 1;
            if(allEdges[i]->end == sink) {
                maximum_flow += allEdges[i]->flow;
            }
        }
    }

    printf("%d %d %d\n", num_nodes, maximum_flow, flow_edges);
    for (int i = 0; i < allEdges.size(); i++)
    {
        if(allEdges[i]->flow > 0) {
            printf("%d %d %d\n", allEdges[i]->start, allEdges[i]->end, allEdges[i]->flow);
        }
    }

    
}


bool bfs(vector<vector<edge*> > graph, int source, int sink, int num_nodes, vector<edge*> &path) {
    queue<int> q;
    q.push(source);
    vector<bool> visited(num_nodes, false);
    visited[source] = true;
    path[source] = new edge(-1, source, 0);

    while(!q.empty()) {
        int curr = q.front();
        q.pop();

        for(edge *e : graph[curr]){
            if(visited[e->end] == false && e->end!=source && e->capacity > e->flow) {
                q.push(e->end);
                path[e->end] = e;
                visited[e->end] = true;
            }
        }
        if(visited[sink]) {
            break;
        }
    }
    if(visited[sink]) {
        return true;
    } else {
        return false;
    }
}

vector<vector<edge*> > max_flow(vector<vector<edge*> > graph, int source, int sink){
    int max_flow = 0;
    int u, v;
    int num_nodes = graph.size();
    
    vector<edge*> path(num_nodes);
    
    while(bfs(graph, source, sink, num_nodes, path)) {
        //send the minimum of the residual capacities on the path
        int path_flow = INT_MAX;
        int u, v;

        v = sink;
        while(v!=source) {
            edge *cur = path[v];
            path_flow = min(path_flow, cur->capacity - cur->flow);
            v = cur->start;
        }

        v = sink;
        while(v!=source) {
            edge *cur = path[v];
            cur->flow += path_flow;
            cur->reverse->flow -= path_flow;
            v = cur->start;
        }
        max_flow += path_flow;
    }

    return graph;
}


int main() {
    //ifstream cin("input.txt");
    ios::sync_with_stdio(false);
    cin.tie(NULL);

        
    int num_nodes, num_edges, source, sink;
    cin >> num_nodes >> num_edges >> source >> sink;

    int u, v, capacity;
    vector<vector<edge*> > graph(num_nodes);
    vector<edge*> allEdges;

    for (int i = 0; i < num_edges; i++)
    {
        cin >> u >> v >> capacity;

        edge *e = new edge(u, v, capacity);
        edge *r = new edge(v, u, 0);

        e->reverse = r;
        r->reverse = e;

        graph[u].push_back(e);
        graph[v].push_back(r);
        allEdges.push_back(e);
        allEdges.push_back(r);
    }

    // Edmond-karp algorithm
    vector<vector<edge*> > flow_graph = max_flow(graph, source, sink);
    
    print_flow_graph(allEdges, source, sink, num_nodes);

    return 0;
}