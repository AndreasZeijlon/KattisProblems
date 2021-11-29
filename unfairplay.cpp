#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <climits>

using namespace std;


/*
Author: Andreas Zeijlon
Date: 1/4/2020
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

int max_flow(vector<vector<edge*> > graph, int source, int sink){
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

    return max_flow;
}

int main() {
    //ifstream cin("input.txt");
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int num_teams, num_matches, p, t1, t2;
    while(cin >> num_teams >> num_matches && num_teams != -1) {
        vector<int> points;
        vector<pair<int, int> > matches;

        for (int i = 0; i < num_teams; i++)
        {
            cin >> p;
            points.push_back(p);
        }

        for (int i = 0; i < num_matches; i++)
        {
            cin >> t1 >> t2;
            pair<int, int> match(t1, t2);
            matches.push_back(match);
        }
        
        if(num_matches == 0) {
            bool wonSeason = true;
            for (int i = 0; i < num_teams-1; i++)
            {
                if(points[i] >= points[points.size()-1]) {
                    wonSeason = false;
                    break;
                }
            }
            if(wonSeason) {
                //printf("\n");
            } else {
                //printf("NO\n");
                cout << "NO\n";
            }
        } else {
            int num_nodes = 2 + num_matches + num_teams;
            int myTeamIndex = num_teams-1;
            int totalFlowForSolution = 0;
            int source = 0;
            int sink = 1;
            vector<vector<edge*> > graph(num_nodes);
            vector<edge* > matchList(num_matches);

            //add edges from source to matches
            for (int i = 0; i < num_matches; i++)
            {
                if(matches[i].first == myTeamIndex + 1 || matches[i].second == myTeamIndex + 1) {
                    points[myTeamIndex] += 2;
                    edge *e = new edge(source, 2+i, 0);
                    edge *r = new edge(2+i, source, 0);

                    e->reverse = r;
                    r->reverse = e;

                    graph[source].push_back(e);
                    graph[2+i].push_back(r);

                    edge *team1 = new edge(2+i, 2+num_matches+matches[i].first-1, 0);
                    edge *team1reverse = new edge(2+num_matches+matches[i].first-1, 2+i, 0);
                    team1->reverse = team1reverse;
                    team1reverse->reverse = team1;

                    graph[2+i].push_back(team1);
                    graph[2+num_matches+matches[i].first-1].push_back(team1reverse);
                    
                    edge *team2 = new edge(2+i, 2+num_matches+matches[i].second-1, 0);
                    edge *team2reverse = new edge(2+num_matches+matches[i].second-1, 2+i, 0);
                    team2->reverse = team2reverse;
                    team2reverse->reverse = team2;

                    graph[2+i].push_back(team2);
                    graph[2+num_matches+matches[i].second-1].push_back(team2reverse);

                    matchList[i] = team1;

                } else {
                    totalFlowForSolution+=2;
                    edge *e = new edge(source, 2+i, 2);
                    edge *r = new edge(2+i, source, 0);

                    e->reverse = r;
                    r->reverse = e;

                    graph[source].push_back(e);
                    graph[2+i].push_back(r);


                    edge *team1 = new edge(2+i, 2+num_matches+matches[i].first-1, 2);
                    edge *team1reverse = new edge(2+num_matches+matches[i].first-1, 2+i, 0);
                    team1->reverse = team1reverse;
                    team1reverse->reverse = team1;

                    graph[2+i].push_back(team1);
                    graph[2+num_matches+matches[i].first-1].push_back(team1reverse);
                    
                    edge *team2 = new edge(2+i, 2+num_matches+matches[i].second-1, 2);
                    edge *team2reverse = new edge(2+num_matches+matches[i].second-1, 2+i, 0);
                    team2->reverse = team2reverse;
                    team2reverse->reverse = team2;

                    graph[2+i].push_back(team2);
                    graph[2+num_matches+matches[i].second-1].push_back(team2reverse);

                    matchList[i] = team1;
                }
            }

            // add edges from teams to sink
            for (int i = 0; i < num_teams; i++)
            {
                int teamIndex = 2 + num_matches + i;
                edge *e = new edge(teamIndex, sink, points[myTeamIndex]-1-points[i]);
                edge *r = new edge(sink, teamIndex, 0);
                e->reverse = r;
                r->reverse = e;

                graph[teamIndex].push_back(e);
                graph[sink].push_back(r);

            }
            
            int maximum_flow = max_flow(graph, source, sink);

            if(maximum_flow == totalFlowForSolution) {
                for (int i = 0; i < num_matches; i++)
                {
                    if(matches[i].first == myTeamIndex+1) {
                        //printf("0 ");
                        cout << "0 ";
                    } else if(matches[i].second == myTeamIndex+1) {
                        //printf("2 ");
                        cout << "2 ";
                    } else {
                        edge *match1 = matchList.at(i);
                        if(match1->flow == 0){
//                            printf("2 ");
                        cout << "2 ";


                        } else if(match1->flow == 1) {
                            //printf("1 ");
                        cout << "1 ";

                        } else {
                            //printf("0 ");
                        cout << "0 ";

                        }
                    }
                }
                //printf("\n");
                cout << "\n";
            } else {
                //printf("NO\n");
                cout << "NO\n";
            }

            // free all memory
            for (int i = 0; i < graph.size(); i++)
            {
                for (int j = 0; j < graph[i].size(); j++)
                {
                    free(graph[i][j]);
                }
            }


            
        }
        
    }

}