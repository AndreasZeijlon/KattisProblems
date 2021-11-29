#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>
#include <math.h>

#define _USE_MATH_DEFINES

using namespace std;

const double PI = 3.14;


double get_length(int x1, int y1, int x2, int y2) {
    return sqrt((x1-x2)*(x1-x2) + (y1-y2)*(y1-y2));
}


string solve(int x1,int y1,int x2,int y2,int x3,int y3){
    double p12 = get_length(x1, y1, x2, y2);
    double p13 = get_length(x1, y1, x3, y3); 
    double p23 = get_length(x2, y2, x3, y3);


    vector<double> sides;
    sides.push_back(p12);
    sides.push_back(p13);
    sides.push_back(p23);

    sort(sides.begin(), sides.end());

    double a = sides[0];
    double b = sides[1];
    double c = sides[2];

    string internal_angle;
    string relative;

    if(c + 0.000001 >= a + b) {
        return "not a triangle";
    }

    if(a == b || a == c || b == c) {
        relative = "isosceles";
    } else {
        relative = "scalene";
    }

    if (abs(a * a + b * b - c * c) <= 0.000001)
    {
        internal_angle = "right";
    }
    else if(a*a + b*b < c*c) {
        internal_angle = "obtuse";
    }
    else {
        internal_angle = "acute";
    }

    

    return relative + " " + internal_angle + " triangle";
    
    
}

int main() {
    //ifstream cin("input.txt");
    ios::sync_with_stdio(false);
    cin.tie(NULL);


    int N, x1, y1, x2, y2, x3, y3;
    cin >> N;

    for (int i = 0; i < N; i++)
    {
        cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3;

        string res = solve(x1, y1, x2, y2, x3, y3);

        printf("Case #%d: %s\n", i+1, res.c_str());
    }
    



    return 0;
}

