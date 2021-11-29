#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>

using namespace std;

/*
Andreas zeijlon
25/5/2020
*/


struct platform{
    double x1, x2, y;


    platform(double X1, double X2, double Y) {
        x1=X1;
        x2=X2;
        y=Y;
    } 

};

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

int solve(vector<platform> p) {
    int total = 0;
    for (int i = 0; i < p.size(); i++)
    {
        int pillar1 = p[i].y;
        int pillar2 = p[i].y;

        point a(p[i].x1+0.5, p[i].y);
        point b(p[i].x1+0.5, 0.0);

        point c(p[i].x2-0.5, p[i].y);
        point d(p[i].x2-0.5, 0.0);

        for (int j = 0; j < p.size(); j++)
        {
            if(i==j) {
                continue;
            }
            point s(p[j].x1, p[j].y);
            point t(p[j].x2, p[j].y);    


            if(intersects(a,b,s, t)) {
                if(pillar1 > p[i].y - p[j].y) {
                    pillar1 = p[i].y -p[j].y;
                }
            }

            if(intersects(c, d, s, t)) {
                if(pillar2 > p[i].y - p[j].y) {
                    pillar2 = p[i].y -p[j].y;
                }
            }
        }
        total += pillar1 + pillar2;
        
    }
    return total;
    
}

int main() {
    //ifstream cin("input.txt");
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int N;
    cin >> N;

    vector<platform> platforms;
    for (int i = 0; i < N; i++)
    {
        int y, x1, x2;
        cin >> y >> x1 >> x2;
        platforms.push_back(platform(x1, x2, y));
    }

    int res = solve(platforms);
    cout << res << endl;
    

    return 0;
}