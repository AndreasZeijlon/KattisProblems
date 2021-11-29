#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

/*
Author: Andreas Zeijlon
Date: 12/5/2020

inside_poly() function will check if a point is inside, outside or on the border of a polygon.

API:
    inside_poly(point p, vector<point> polygon)

    parameters:
        p: The point to check. (point)
        polygon: A vector of points giving the corners of a polygon. The points are given in clockwise or counter-clockwise order. (vector<point>)

    return value:
        Returns -1, 0, 1 if the point is either outside, on or inside the polygon. (int)

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
            point == point

The inside_poly function implements the ray casting algorithm. First it checks if the point is on the border of polygon. Then it draws a line from point p to infinity in x-axis. Then it counts the number of intersections between the line and the polygon.  If the number of intersections are odd the point is inside. If it is even it is outside. 

Time complexity:
O(n) where n is the number of points in polygon
*/

const int INF = 10001;

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

    bool operator==(point p) {
        return (x==p.x && y==p.y);
    }

    
};

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
help function intersection_point(point a, point b, point c, point d)
Calculates the point of intersection between two lines.


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

    if(D==0) { // colinear
        return point(INF, INF);
    }

    double x = (b2*c1-b1*c2)/D;
    double y = (a1*c2-a2*c1)/D;
    return point(x, y);

}

int inside_poly(point p, vector<point> polygon) {
    point extreme(INF, p.y);

    int count = 0;
    for (int i = 0, j = polygon.size()-1; i < polygon.size(); i++, j=i-1)
    {
        if(orientation(p, polygon[i], polygon[j]) == 0)
        {
            if (onSegment(polygon[i], polygon[j], p)) {
                return 0; //on
            }
        }

        if(intersects(p, extreme, polygon[i], polygon[j])) {
             point point_of_intersection = intersection_point(p, extreme, polygon[i], polygon[j]);

            if(point_of_intersection.x != INF) {
                if(polygon[i] == point_of_intersection && polygon[j].y >= p.y) {
                    continue;
                }
                else if(polygon[j] == point_of_intersection && polygon[i].y >= p.y) {
                    continue;
                }
                else {
                    count++;

                }
            }
        }
    }
    if(count%2==1) {
        return 1;
    } else {
        return -1;
    } 
}

int main() {
    //ifstream cin("input.txt");
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n, x, y, m;
    
    while(cin >> n) {
        if(n==0) {
            break;
        }
        vector<point> polygon;
        for (int i = 0; i < n; i++)
        {
            cin >> x >> y;
            polygon.push_back(point(x, y));
        }
        cin >> m;
        for (int j = 0; j < m; j++)
        {
            cin >> x >> y;
            int res = inside_poly(point(x, y), polygon);

            if(res == -1) {
                cout << "out\n";
            } else if(res == 0) {
                cout << "on\n";
            } else {
                cout << "in\n";
            }
        }
        
    }
    return 0;
}