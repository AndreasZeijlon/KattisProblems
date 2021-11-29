#include <iostream>
#include <cmath>
#include <algorithm>
#include <cassert>
#include <cstdio>
#include <vector>
#include <iomanip>
#include <fstream>


using namespace std;


/*
Author: Andreas Zeijlon
Date: 21/4/2020

segment_dist() function will calculate the shortest distance between two line segments.

API:
    segment_dist(point a, point b, point c, point d)

    parameters:
        point a, b: The endpoints of the first line segment. (point)
        point c, d: The endpoints of the second line segment. (point)

    return value:
        Returns the shortest distance between the two line segments. (double)

Data structures:
    point:
        fields:
            x: The x-coordinate of the point. (double)
            y: The y-coordinate of the point. (double)

        operators:
            point + point
            point - point
            point * const
            point / const

The segment_dist algorithm first checks if the line segments are intersecting anywhere with help_function intersects(). If they are intersecting, return distance 0. If not it checks the orthagonal projections of line 2's endpoints onto line 1 and vice versa, and returns the shortest distance from those projections.

Time complexity:
O(1)

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

/*

help function intersects(point a, point b, point c, point d)
Checks if two line segments are intersecting by checking the following cases:

general case: (a, b, c) and (a, b, d) have different orientations and
                (c, d, a) and (c, d, a) have different orientations

special cases: The orientation of (p1, p2, p3) is colinear and p3 is on the line segment (p1, p2)

return value:
    boolean
*/
bool intersects(point a, point b, point c, point d) {

    int o1 = orientation(a, b, c);
    int o2 = orientation(a, b, d);
    int o3 = orientation(c, d, a);
    int o4 = orientation(c, d, b);

    if(o1!=o2 && o3!=o4) {
        return true;
    }
    if(o1==0 && onSegment(a, b, c)){
        return true;
    }
    if(o2==0 && onSegment(a, b, d)){
        return true;
    }
    if(o3==0 && onSegment(c, d, a)){
        return true;
    }
    if(o4==0 && onSegment(c, d, b)){
        return true;
    }
    return false;

}

/* 
projects q on line segment (a,b)

Returns the point on (a,b) that is closest to point q
*/
point orthogonal_projection(point q, point a, point b){ 
    if(distance(a,b)==0) {
        return a;
    } else {
        double k = dot(q-a,b-a)/distance(a, b);
        if (k < 0) {
            return a;
        } 
        if (k > distance(a,b)) {
            return b;
        }

        return a + (b-a)*k/distance(a, b);
    }
}

double segment_dist(point a, point b, point c, point d) {
    if(intersects(a, b, c, d)){
        return 0.0;
    }   

    point p1 = orthogonal_projection(a, c, d);
    point p2 = orthogonal_projection(b, c, d);
    point p3 = orthogonal_projection(c, a, b);
    point p4 = orthogonal_projection(d, a, b);

    double dist1 = distance(a, p1);
    double dist2 = distance(b, p2);
    double dist3 = distance(c, p3);
    double dist4 = distance(d, p4);
    
    return min(min(dist1, dist2), min(dist3, dist4));          
}

int main() {
    //ifstream cin("input.txt");
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout << fixed;
    cout << setprecision(2);

    int n;
    int x1, x2, x3, x4, y1, y2, y3, y4; 
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3 >> x4 >> y4;

        point a(x1, y1);
        point b(x2, y2);
        point c(x3, y3);
        point d(x4, y4);

        double distance = segment_dist(a, b, c, d);

        cout << distance << "\n";
    }

    return 0;
}