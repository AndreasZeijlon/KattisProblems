#include <iostream>
#include <fstream>
#include <bitset>

using namespace std;

/*
Author: Andreas Zeijlon
Date: 2020-02-10
*/

bitset<3> flipstone(bitset<3> stones, int index) {
    return stones.flip(index);
}


bitset<3> solve(bitset<3> stones, int priest, int num_of_priests, int preferences[][8], int cache[][8]) {
    if(priest==num_of_priests) {
        return stones;
    } else if(cache[priest][(int)stones.to_ullong()] != -1){
        return cache[priest][(int)stones.to_ullong()];
    }
    else {
        bitset<3> stones1 = solve(flipstone(stones, 0), priest+1, num_of_priests, preferences, cache);
        bitset<3> stones2 = solve(flipstone(stones, 1), priest+1, num_of_priests, preferences, cache);
        bitset<3> stones3 = solve(flipstone(stones, 2), priest+1, num_of_priests, preferences, cache);

        bitset<3> best = stones1;

        if(preferences[priest][(int)stones2.to_ullong()] < preferences[priest][(int)best.to_ullong()]) {
            best = stones2;
        }
        if(preferences[priest][(int)stones3.to_ullong()] < preferences[priest][(int)best.to_ullong()]) {
            best = stones3;
        }

        cache[priest][(int)stones.to_ullong()] = (int)best.to_ullong();
        return best;
    }
}

void printResult(bitset<3> stones) {
    int res = (int)stones.to_ullong();
    switch (res)
    {
    case 0b000:
        cout << "NNN" << endl;
        break;
    case 0b001:
        cout << "NNY" << endl;
        break;
    case 0b010:
        cout << "NYN" << endl;
        break;
    case 0b011:
        cout << "NYY" << endl;
        break;
    case 0b100:
        cout << "YNN" << endl;
        break;
    case 0b101:
        cout << "YNY" << endl;
        break;
    case 0b110:
        cout << "YYN" << endl;
        break;
    case 0b111:
        cout << "YYY" << endl;
        break;
    default:
        cout << "hasdfbjkn" << endl;
        break;
    }
}

int main() {
    ifstream cin("input.txt");
    int num_of_rounds;
    cin >> num_of_rounds;

    int i = 0;
    while(i<num_of_rounds) {
        int num_of_priests;
        cin >> num_of_priests;
        int priests[num_of_priests][8];
        int j=0;
        while(j<num_of_priests) {
            for (int k = 0; k < 8; k++)
            {
                int a;
                cin >> a;
                priests[j][k] = a;
            }
            j++;
        }

        int cache[num_of_priests][8];
        for (size_t i = 0; i < num_of_priests; i++)
        {
            for (size_t j = 0; j < 8; j++)
            {
                cache[i][j] = -1;
            }
            
        }
        


        bitset<3> stones(string("000"));
        bitset<3> res = solve(stones, 0, num_of_priests, priests, cache);
        printResult(res);

        
        i++;
    }


    return 0;
}