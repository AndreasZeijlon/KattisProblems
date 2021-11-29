#include <iostream>
#include <ios>
#include <iomanip>
#include <sstream>
#include <fstream>
#include <vector>
#include <string>

/*
Author: Andreas Zeijlon
Date: 2020-02-10
*/

using namespace std;


struct literal {
    int var;
    bool negated;

    literal() {}

    literal(int v, bool n) {
        var = v;
        negated = n;
    }

};

vector<vector<literal> > simplify(vector<vector<literal> > clauses, literal l) {
    // remove clauses where l is positive
    // remove negated l from clauses where it appears
    for (int i = 0; i < clauses.size(); i++)
    {
       for (int j = 0; j < clauses[i].size(); j++)
       {
           if(clauses[i][j].var == l.var && clauses[i][j].negated == l.negated) {
               clauses.erase(clauses.begin() + i);
               i--;
               break;
           } 
           else if(clauses[i][j].var == l.var && clauses[i][j].negated == !l.negated) {
               clauses[i].erase(clauses[i].begin()+j);
               j--;
           }
       }
    }
    return clauses;
    
}


bool DPLL(vector<vector<literal> > clauses) {
    //if clauses is empty return true
    if(clauses.empty()){
        return true;
    }
    //if a has an empty clause return false
    for (int i = 0; i < clauses.size(); i++)
    {
        if(clauses[i].empty()) {
            return false;
        }
    }

    //if clauses contains a unit clause
    for (int i = 0; i < clauses.size(); i++)
    {
        if(clauses[i].size() == 1) {
            literal l = clauses[i][0];
            return DPLL(simplify(clauses, l));
        }
    }

    // choose a variable v and test when it's negated and positive
    literal v = clauses[0][0];
    if(DPLL(simplify(clauses, v))) {
        return true;
    } else {
        v.negated = !v.negated;
        return DPLL(simplify(clauses, v));
    }
    
}

vector<literal> parse(string s) {
    vector<literal> clause;
    std::string delimiter = " v ";

    size_t last = 0; 
    size_t next = 0; 
    string string_literal;
    string var_char;
    int var;
    char negate;
    int i;
    while ((next = s.find(delimiter, last)) != string::npos) 
    { 
        string_literal = s.substr(last, next-last);

        i = string_literal.size()-1;
        while(std::isdigit(string_literal[i])) {
            i--;
        }

        var_char = string_literal.substr(i+1);
        var = stoi(var_char) - 1;

        if( string_literal.front() == '~'){
            clause.push_back(literal(var, true));
        } else {
            clause.push_back(literal(var, false));
        }
        last = next + delimiter.size();
    } 
    string_literal = s.substr(last);

    i = string_literal.size()-1;
    while(std::isdigit(string_literal[i])) {
        i--;
    }

    var_char = string_literal.substr(i+1);
    var = stoi(var_char) - 1;

    if( string_literal.front() == '~'){
        clause.push_back(literal(var, true));
    } else {
        clause.push_back(literal(var, false));
    }

    return clause;
}


int main(void) {
    //ifstream cin("input.txt");
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        int num_variables, num_clauses;
        
        cin >> num_variables >> num_clauses;
        cin.ignore();

        vector<vector<literal> > clauses;

        string clause;
        for (int i = 0; i < num_clauses; i++)
        {
            getline(cin, clause);
         //   cout << clause << endl;
            if(!clause.empty()){
                clauses.push_back(parse(clause));
            }
        }

        bool satisfied = DPLL(clauses);

        if(satisfied) {
            cout << "satisfiable" << endl;
        } else {
            cout << "unsatisfiable" << endl;
        }
       
    }

    return 0;
}