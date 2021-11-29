#include <iostream>
#include <fstream>
#include <vector>

using namespace std;


/*
Author: Andreas Zeijlon
Date: 2020-02-09
 
Cover algorithm will find minimum number of given intervals to completely cover an interval.

API: 
    vector<int> cover(double low, double high, vector<Interval> intervals)

    parameters:
        1) low: Beginning of interval to cover. (double)
        2) high: Ending of interval to cover. (double)
        3) intervals: Vector of intervals to use. Interval is a data struct with parameters start(double), end(double) and index(int). (vector<Interval>)

    return value:
        Vector with indexes of intervals in solution (vector<int>)

The function cover() will take an interval IV along with a list of intervals and return the indexes of the intervals in the list that make up the minimum number of intervals needed to completely cover interval IV. 

Time complexity: 
O(n^2)

*/

struct Interval
{
    double begin;
    double end;
    int index;
    Interval(double b, double e, int i) {
        begin = b;
        end = e;
        index = i;
    }
    
};

vector<int> cover(double low, double high, vector<Interval> ivs) {
    vector<int> result;
    bool impossible = false;
    // If low and high are equal, check if there is an interval that covers them.
    if (low == high) {
        impossible = true;
        for(Interval n : ivs) {
            if(n.begin<=low && n.end>=high) {
                // Found the best interval.
                result.push_back(n.index);
                impossible = false;
                break;
            }
        }
        
    } else {
        
        double covered = low;
        while(covered < high) {

            auto it = ivs.begin();
            auto best_interval_it = it;

            double longest_distance = 0;
            int longest_distance_index = -1;

            Interval best_interval(-1, -1 ,-1);

            // find best interval
            while(it != ivs.end()) {
                Interval n = *it;
                if(n.begin<=covered) {
                    double current_distance = n.end-covered;
                    if(current_distance > longest_distance){
                        longest_distance = current_distance;
                        longest_distance_index = n.index;
                        best_interval_it = it;
                        best_interval = n;
                    }
                }
                ++it;
            }

            if(longest_distance_index == -1) {
                impossible = true;
                break;
            } else {
                result.push_back(longest_distance_index);
                covered = best_interval.end;
                ivs.erase(best_interval_it);
            }
        }
    }

    if(impossible) {
        result.clear();
        return result;
    } else {
        return result;
    }
}


int main() {

    //ifstream cin("ic.txt");
    double low, high;
    while(cin >> low >> high){
        int num_of_intervals;
        cin >> num_of_intervals;

        int i=0;
        double a, b;

        double longest_distance = 0;
        double covered;
        double longest_distance_index = -1;
        
        vector<Interval> intervals;

        bool done = false;

        while(i<num_of_intervals) {
            cin >> a >> b;
            if(b>=low && a<=high) {
                intervals.push_back(Interval(a, b, i));
            }
            
            i++;
        }

        vector<int> result = cover(low, high, intervals);

        if(result.empty()) {
            printf("impossible\n");
        } else {
            printf("%lu\n",result.size());
            for(int i : result) {
                printf("%d ", i);
            }
            printf("\n");
        }

    }
    return 0;
}