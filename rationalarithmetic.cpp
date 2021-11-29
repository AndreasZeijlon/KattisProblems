#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>

using namespace std;

/*
Author: Andreas Zeijlon
Date: 22/5/2020

rational() is a data structure for performing arithmetic operations on rational numbers. It will always store the rational number as simplified as possible.

rational:
    fields:
        nom: The nominator of the rational number. (long long)
        denom: The denominator of the rational number. (long long)

    constructors:
        rational r()
        rational r(long long nominator, long long denominator)

    operators:
        rational + rational
        rational - rational
        rational * rational
        rational / rational
        rational == rational
        rational != rational
        rational < rational
        rational > rational
        rational <= rational
        rational >= rational
        ostream << rational
        istream >> rational

Time complexity:
O(1)
*/

struct rational { 
    long long nom, denom; 

    rational() {}

    rational(long long n, long long d) {
        nom=n;
        denom=d;
        simplify();
        correctMinus();
    }

    long long gcd(long long a, long long b)
    {
        long long r = 0;
        do
        {
            r = a % b;
            a = b;
            b = r;
        } 
        while (b != 0);
        
        return abs(a);
    }

    void simplify() {
        long long d = gcd(nom, denom);
        if(d > 1) {
            nom/=d;
            denom/=d;
        }
        
    }

    void correctMinus() {
        if(nom < 0 && denom < 0) {
            nom = -nom;
            denom = -denom;
        } else if(nom > 0 && denom < 0) {
            denom = -denom;
            nom = -nom;
        }
    }

    rational operator+(rational r) { 
        rational res(nom*r.denom + r.nom*denom, denom*r.denom);

        return res;
    }

    rational operator-(rational r) { 
        rational res(nom*r.denom - r.nom*denom, denom*r.denom);

        return res;
    }

    rational operator*(rational r) { 
        rational res(nom*r.nom, denom*r.denom);

        return res;
    }

    rational operator/(rational r) {
        rational res(nom*r.denom, denom*r.nom);

        return res;
    }

    bool operator==(rational r) {
        return (nom==r.nom && denom==r.denom);
    }

    bool operator<(rational r) {
        return (double)nom/denom<(double)r.nom/r.denom;
    }

    bool operator>(rational r) {
        return (double)nom/denom>(double)r.nom/r.denom;
    }

    bool operator!=(rational r) {
        return !(nom==r.nom && denom==r.denom);
    }

    bool operator<=(rational r) {
        return (double)nom/denom<=(double)r.nom/r.denom;
    }

    bool operator>=(rational r) {
        return (double)nom/denom>=(double)r.nom/r.denom;
    }
};

ostream& operator<<( ostream &output, rational &r) { 
        return output << r.nom << " / " << r.denom;            
}


istream &operator>>( istream  &input, rational &r ) { 
        return input >> r.nom >> r.denom;
}

int main() {
    //ifstream cin("input.txt");
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    long long n;
    char op;

    cin >> n;
    for (int i = 0; i < n; i++)
    {
        rational r1, r2, r;
        cin >> r1 >> op >> r2;

        if (op == '+')
        {
            r = r1+r2;
        }
        else if(op == '-')
        {
            r = r1-r2;
        }
        else if(op == '*')
        {
            r = r1*r2;
        }
        else {
            r = r1/r2;
        }

        cout << r << endl;
    }

    

    return 0;
}