#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <utility>
#include <iomanip>


using namespace std;


/*
Author: Andreas Zeijlon
Date: 20/4/2020

polygon_area is a function that calculates the area of a polygon.

API:
    double polygon_area(vector<pair<int, int> > coords)

    paramters:
        coords: A vector containing all the coordinates of the corners in the polygon. The coordinates are stored in the pair structure as (x, y). vector<pair<int, int> >

    return value:
        The area of the polygon. If the value is negative if the polygon was given in Counter-clockwise order and positive if it was given in Clockwise order. The precision of the return value is exactly one decimal.


Time complexity:
O(n), where n=number of coordinates.

The function is an implementation of Carl Friedrich Gauss area formula. (https://en.wikipedia.org/wiki/Shoelace_formula)


*/

double polygon_area(vector<pair<int, int> > coords) {
    double area = 0.0;
    for (int i = 0; i < coords.size(); i++)
    {
        if(i==0) {
            area += coords[i].first*(coords[coords.size()-1].second - coords[i+1].second);

        } else if(i==coords.size()-1) {
            area += coords[i].first*(coords[i-1].second - coords[0].second);

        } else {
            area += coords[i].first*(coords[i-1].second - coords[i+1].second);

        }
    }

    return area/2;
    
}

int main() {
    //ifstream cin("input.txt");
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout << fixed;
    cout << setprecision(1);

    int n;
    int x, y;
    while(cin >> n) {
        if(n==0) {
            break;
        }

        vector<pair<int, int> > coords;

        for (int i = 0; i < n; i++)
        {
            cin >> x >> y;
            pair<int, int> p(x, y);
            coords.push_back(p);
        }
        
        
        double area = polygon_area(coords);

        if(area<0) {
            cout << "CCW " << abs(area) << "\n";
        }
        else{
            cout << "CW " << area << "\n";
        }
    }


    return 0;
}