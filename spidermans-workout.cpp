#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <numeric>

/*
Author: Andreas Zeijlon
Date: 2020-04-22
*/

using namespace std;

const string impossible = "IMPOSSIBLE";

struct workout {
    string solution;
    int max_height;
    int current_height;
    int distance_left;

    workout(string s, int h, int c, int dl) {
        solution = s;
        max_height = h;
        current_height = c;
        distance_left = dl;
    }

};


workout solve_workout(workout w, vector<int> distances, int index, vector<vector<workout> > &cache) {
   if(w.current_height<0 || w.current_height>w.distance_left) {
        w.solution = impossible;
        return w;
    }

    if(index == distances.size() && w.current_height != 0) {
        w.solution = impossible;
        return w;
    }

    if(w.max_height<w.current_height){
        w.max_height = w.current_height;
    }

    if(index == distances.size() && w.current_height == 0){
        return w;
    }

    if(cache[index][w.current_height].solution != "null") {
        w.solution+=cache[index][w.current_height].solution;
        w.max_height = max(w.max_height, cache[index][w.current_height].max_height);
        
        return w;
    }

    int next_distance = distances[index];

    workout w1 = w;
    workout w2 = w;
    w1.solution+="D";
    w1.current_height -= next_distance;
    w2.solution+="U";
    w2.current_height += next_distance;
    w1.distance_left -= next_distance;
    w2.distance_left -= next_distance;

    w1.max_height = 0;
    w2.max_height = 0;

    workout w3 = solve_workout(w1, distances, index + 1, cache);
    workout w4 = solve_workout(w2, distances, index + 1, cache);

    if(w3.solution == impossible && w4.solution == impossible) {
        return w3;
    } else if (w3.solution != impossible && w4.solution != impossible) {

        if(w3.max_height<w4.max_height){
            cache[index][w.current_height].solution = w3.solution.substr(index);
            cache[index][w.current_height].max_height = w3.max_height;
            cache[index][w.current_height].current_height = w3.current_height;
            w3.max_height = max(w3.max_height, w.max_height);
            return w3;
        } else {
            cache[index][w.current_height].solution = w4.solution.substr(index);
            cache[index][w.current_height].max_height = w4.max_height;
            cache[index][w.current_height].current_height = w4.current_height;
            w4.max_height = max(w4.max_height, w.max_height);

            return w4;
        }
    } else if(w3.solution == impossible) {
        cache[index][w.current_height].solution = w4.solution.substr(index);
        cache[index][w.current_height].max_height = w4.max_height;
        cache[index][w.current_height].current_height = w4.current_height;

        w4.max_height = max(w4.max_height, w.max_height);

        return w4;
    } else {
        cache[index][w.current_height].solution = w3.solution.substr(index);
        cache[index][w.current_height].max_height = w3.max_height;
        cache[index][w.current_height].current_height = w3.current_height;

        w3.max_height = max(w3.max_height, w.max_height);

        return w3;
    }
}


int main(void) {
    //ifstream cin("input.txt");
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        int num_distances;
        
        cin >> num_distances;

        vector<int> distances;

        int total_distance = 0;
        for (int i = 0; i < num_distances; i++)
        {
            int distance;
            cin >> distance;
            distances.push_back(distance);
            total_distance+=distance;
        }

        if(total_distance%2 != 0) {
            cout << impossible << "\n";
        } else{
            vector<vector<workout> > cache(num_distances, vector<workout>(1001, workout("null", 0, 0, total_distance)));
            workout w("", 0, 0, total_distance);
            workout sol = solve_workout(w, distances, 0, cache);
            cout << sol.solution << "\n";
            
        }
        
    }

    return 0;
}