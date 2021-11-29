#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
#include <cmath>
#include <algorithm>
#include <utility>
#include <climits>
using namespace std;

/*
/*
Author: Andreas Zeijlon
Date: 25/5/2020

intersect() function will calculate the intersection point of two line segments, if there are any.

API:
    intersect(point a, point b, point c, point d)

    parameters:
        point a, b: The endpoints of the first line segment. (point)
        point c, d: The endpoints of the second line segment. (point)

    return value:
        Returns an array with 0, 1 or 2 points depending on if the line segments do not intersect, intersects in one point or intersects in two points, i.e. they are colinear. (vector<point>)

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
            point = point
            point == point
            point < point
            point != point


The intersect algorithm first checks if the line segments are intersecting anywhere with help_function intersects(). If they are intersecting, the intersection point is calculated. In special cases where the two line segments are colinear there are two intersection points.

Time complexity:
O(1)

*/

const int INF = INT_MAX;
const double eps = 0.0001;

struct point { 
    long double x, y; 

    point(long double X, long double Y) {
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

    point& operator= (const point& other) {
        x = other.x, y = other.y;
        return *this;
    }


    bool operator<(const point& rhs) const {
        if (abs(x-rhs.x) < eps){
            return y<rhs.y;
        } else if(x<rhs.x) {
            return true;
        } else {
            return false;
        }
    }

    bool operator!=(const point& rhs) const {
        return !(abs(x-rhs.x) < eps && abs(y-rhs.y) < eps);
    }

    bool operator==(const point& rhs) const {
        return (abs(x-rhs.x) < eps && abs(y-rhs.y) < eps);
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
    return (q.x <= max(p1.x, p2.x) && q.x >= min(p1.x, p2.x) && q.y <= max(p1.y, p2.y) && q.y >= min(p1.y, p2.y));
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

    if(abs(ori)<eps) {
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
    if(distance(a, c) < eps || distance(a, d) < eps || distance(b, c) < eps || distance(b, d) < eps) {
        return true;
    }
    if (distance(a,b) < eps && distance(c,d) < eps) {
        return false;
    }

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
help function intersection_point(point a, point b, point c, point d)
Calculates the point of intersection between two lines. If the line segments 
are colinear it returns a point with infinite values.

return value:
    struct point
*/
point intersection_point(point a, point b, point c, point d) {
    // a1x + b1y = c1
    double a1 = b.y - a.y;
    double b1 = a.x - b.x;
    double c1 = a1*a.x + b1*a.y;

    // a2x + b2y = c2
    double a2 = d.y - c.y;
    double b2 = c.x - d.x;
    double c2 = a2*c.x + b2*c.y;

    //determinant
    double D = a1*b2 - b1*a2;

    if(abs(D)<eps) { // colinear
        return point(INF, INF);
    }

    double x = (b2*c1-b1*c2)/D;
    double y = (a1*c2-a2*c1)/D;
    return point(x, y);

}

vector<point> intersect(point a, point b, point c, point d){
    vector<point> result;
    if(intersects(a, b, c, d)) {
        point p = intersection_point(a, b, c, d);
        if(p.x == INF && p.y == INF) { //colinear
            if(b<a) {
                // swap a and b
                point temp = a;
                a = b;
                b = temp;
            }
            if(d<c) {
                // swap d and c
                point temp = c;
                c = d;
                d = temp;
            }

            if(a<c){
                result.push_back(c);
            } else {
                result.push_back(a);
            }
            if(b<d) {
                result.push_back(b);
            } else {
                result.push_back(d);
            }
        }
        else {
            result.push_back(p);
        }
    }
    if(result.size() == 2){
        if(result[0] == result[1]){
            result.erase(result.end()-1);
        }
    }
    sort(result.begin(), result.end());
    for (int i = 0; i < result.size(); i++)
    {
        if(result[i].x == -0.00) {
            result[i].x = 0.00;
        }
        if(result[i].y == -0.00) {
            result[i].y = 0.00;
        }
    }
    
    return result;
}

int main() {
    //ifstream cin("input.txt");
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(2);
    cout << fixed;

    int n, x1, x2, x3, x4, y1, y2, y3, y4;
    vector<point> intersection;
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3 >> x4 >> y4;
        intersection = intersect(point(x1, y1), point(x2, y2), point(x3, y3), point(x4, y4));

        if(intersection.empty()) {
            cout << "none" << endl;
        } else if(intersection.size() == 1) {
            cout << intersection[0].x << " " << intersection[0].y << endl;
        } else {
            cout << intersection[0].x << " " << intersection[0].y << " " << intersection[1].x << " " << intersection[1].y << endl;
        }
    }
    return 0;
}