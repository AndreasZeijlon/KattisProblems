#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>

using namespace std;

/*
Author: Andreas Zeijlon
Date: 2020-05-18
*/

struct point { 
    double x, y; 

    point(double X, double Y) {
        x=X;
        y=Y;
    }

    point operator+(point p) { 
        return point(x+p.x, y+p.y); 
    }
    point operator-(point p) { 
        return point(x-p.x, y-p.y); 
    }
    point operator*(double c) { 
        return point(x*c, y*c); 
    }
    point operator/(double c) {
        return point(x/c, y/c); 
    }
};

double dot(point a, point b) {
    return a.x*b.x + a.y*b.y;
}

// distance between two points
double distance(point a, point b) {
    return sqrt(dot(b-a, b-a));
}

bool onSegment(point p1, point p2, point q) {
    return(q.x <= max(p1.x, p2.x) && q.x >= min(p1.x, p2.x) && q.y <= max(p1.y, p2.y) && q.y >= min(p1.y, p2.y));
}

/*
help function orientation()
Returns orientation of the order of three points.
return value:
    0: Colinear
    1: Clockwise
    -1: Counter clockwise
*/
int orientation(point p1, point p2, point p3) {
    int ori = (p2.y - p1.y)*(p3.x - p2.x) - (p3.y - p2.y)*(p2.x - p1.x);

    if(ori==0) {
        return 0;
    } else if(ori>0) {
        return 1;
    } else {
        return -1;
    }
}

bool is_line(point p1, point p2, point p3) {

    if(orientation(p1, p2, p3) == 0) {// colinear 
        return true;
    }
    return false;

}

int main() {
    //ifstream cin("input.txt");
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    vector<point> letters;

    int n;
    cin >> n;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            char c;
            cin >> c;
            if(c != '.') {
                letters.push_back(point(i, j));
            }
        }
    }

    n = letters.size();
    int total = 0;
    for(int i = 0; i < n; i++) {
        for(int j = i+1; j < n; j++) {
            for(int k = j+1; k < n; k++) {
                if(is_line(letters[i], letters[j], letters[k])) {
                    total++;
                }
            }
        }
    }

    cout << total << "\n";

    return 0;
}