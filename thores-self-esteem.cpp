#include <iostream>
#include <fstream>
#include <cmath>
#include <string>
#include <vector>


using namespace std;

string thores = "ThoreHusfeldt";


string string_match(string name, int i) {
    if(name.size()==0 || i > thores.size()-1) {
        return "";
    }
    else if(name[0] == thores[i]) {
        return name[0] + string_match(name.substr(1), i+1);
    } else {
        return "";
    }
}


int main() {
    //ifstream cin("input.txt");
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    vector<string> all_names;
    int n;
    cin >> n;
    string longest_prefix = "";
    string prefix;
    for (int i = 0; i < n; i++)
    {
        string name;

        cin >> name;


        if(name == "ThoreHusfeldt") {
            if(i==0) {
                cout << "Thore is awesome" << endl;
                return 0;
            }
            break;
        }

        prefix = string_match(name, 0);

        if(prefix.substr(0, prefix.size()-1) == "ThoreHusfeld" || prefix == "ThoreHusfeld") {
            cout << "Thore sucks\n";
            return 0;
        }
        

        if(prefix.size() > longest_prefix.size()) {
            longest_prefix = prefix;
        }
   }

    cout << longest_prefix + thores[longest_prefix.size()] << endl;

   

    


    return 0;
}