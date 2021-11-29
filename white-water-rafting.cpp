#include <iostream>
#include <fstream>
#include <vector>
#include <utility>
#include <cmath>
#include <climits>
#include <iomanip>
using namespace std;


/*
Author: Andreas Zeijlon

Date: 2020-05-10
*/


const long double min_error = 0.000001;

struct point { 
    long double x, y; 

    point() {};

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
    point operator*(long double c) { 
        return point(x*c, y*c); 
    }
    point operator/(long double c) {
        return point(x/c, y/c); 
    }
};

struct line {
    point a, b;

    line(point A, point B) {
        a=A;
        b=B;
    }
};

long double dot(point a, point b) {
    return a.x*b.x + a.y*b.y;
}

// distance between two points
long double distance(point a, point b) {
    return sqrt(dot(b-a, b-a));
}

/* 
projects q on line segment (a,b)

Returns the point on (a,b) that is closest to point q
*/
point orthogonal_projection(point q, point a, point b){ 
    if(distance(a,b)==0) {
        return a;
    } else {
        long double k = dot(q-a,b-a)/distance(a, b);
        if (k < 0) {
            return a;
        } 
        if (k > distance(a,b)) {
            return b;
        }

        return a + (b-a)*k/distance(a, b);
    }
}

long double segment_dist(point a, point b, point c, point d) {
    point p1 = orthogonal_projection(a, c, d);
    point p2 = orthogonal_projection(b, c, d);
    point p3 = orthogonal_projection(c, a, b);
    point p4 = orthogonal_projection(d, a, b);

    long double dist1 = distance(a, p1);
    long double dist2 = distance(b, p2);
    long double dist3 = distance(c, p3);
    long double dist4 = distance(d, p4);
    
    return min(min(dist1, dist2), min(dist3, dist4));          
}

long double solve(vector<point > innerpoly, vector<point > outerpoly) {
    vector<line> innerpolylines, outerpolylines;

    for (int i = 0; i < innerpoly.size()-1; i++)
    {
        innerpolylines.push_back(line(innerpoly[i], innerpoly[i+1]));
    }
    innerpolylines.push_back(line(innerpoly[innerpoly.size()-1], innerpoly[0]));

    for (int i = 0; i < outerpoly.size()-1; i++)
    {
        outerpolylines.push_back(line(outerpoly[i], outerpoly[i+1]));
    }
    outerpolylines.push_back(line(outerpoly[outerpoly.size()-1], outerpoly[0]));

    long double min_distance = 99999999999;

    for (int i = 0; i < innerpolylines.size(); i++)
    {
        for (int j = 0; j < outerpolylines.size(); j++)
        {
            long double seg_dist = segment_dist(innerpolylines[i].a, innerpolylines[i].b, outerpolylines[j].a, outerpolylines[j].b);
            if(seg_dist < min_distance) {
                min_distance = seg_dist;
            }
        }
    }

    return min_distance/2;
    
    
}

int main() {
    //ifstream cin("input.txt");
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    long double n;
    cin >> n;
    for (long double i = 0; i < n; i++)
    {
        long double p;
        cin >> p;
        vector<point > innerpoly;
        for (int j = 0; j < p; j++)
        {
            long double x, y;
            cin >> x >> y;
            innerpoly.push_back(point(x, y));
        }

        cin >> p;
        vector<point > outerpoly;
        for (int j = 0; j < p; j++)
        {
            long double x, y;
            cin >> x >> y;
            outerpoly.push_back(point(x, y));
        }

        long double radius = solve(innerpoly, outerpoly);

        cout << radius << endl;

    }

    return 0;
}

