#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

/*

Author: Andreas Zeijlon
Date: 14/4/2020

Knapsack algorithm will find the optimal way to pack a bag with a maximum capacity.

API:
    vector<int> knapsack(int capacity, vector<Item> items)

    parameters:
        1) The max capacity of the bag. (int)
        2) A list of the items. Item is a data structure with parameters value(int), weight(int), index(int). (vector<Item> items)
    
    return value:
        A vector of the indexes of the items that make up the optimal solution for packing the bag. (vector<int>)


The function knapsack will take a list of items with value and weight and calculate the optimal way to pack a bag with a max weight capacity so that the total value is maximized. 

Time complexity:
O(n*capacity)


*/


struct Item {
    Item(int v, int w, int i) {
        value = v;
        weight = w;
        index = i;
    }

    int weight;
    int value;
    int index;
};
 
int max(int a, int b) { 
    if(a>b) {
        return a;
    } else {
        return b;
    }
}

vector<int> knapsack(int capacity, vector<Item> items) {
    int num_of_items = items.size();

    int Knapsack[num_of_items+1][capacity+1];

    //build table Knapsack in bottom up manner
    for (int item = 0; item <= num_of_items; item++)
    {
        for (int weight = 0; weight <= capacity; weight++)
        {
            if(item == 0 || weight == 0) {
                Knapsack[item][weight] = 0;
            } else if(items.at(item-1).weight <=  weight) {
                Knapsack[item][weight] = max(items.at(item-1).value + Knapsack[item-1][weight-items.at(item-1).weight], Knapsack[item-1][weight]);
            } else {
                Knapsack[item][weight] = Knapsack[item-1][weight];
            }
        }
        
    }
    

    // backtrack to get solution
    int maximum_value = Knapsack[num_of_items][capacity];
    vector<int> items_in_solution;
    int weight = capacity;

    for (int i = num_of_items; i > 0 && maximum_value > 0; i--)
    {
        if(maximum_value == Knapsack[i-1][weight]) {
            continue;
        } else {
            items_in_solution.push_back(items.at(i-1).index);
            maximum_value -= items.at(i-1).value;
            weight -= items.at(i-1).weight;
        }
    }

    return items_in_solution;

}

int main() {
    //ifstream cin("input.txt");
    int capacity, num_of_items;
    
    while(cin >> capacity >> num_of_items) {
        int i = 0;
        vector<Item> items;
        while (i<num_of_items)
        {
            int value, weight;
            cin >> value >> weight;
            Item item(value, weight, i);
            items.push_back(item);
            ++i;
        }

        vector<int> items_in_solution = knapsack(capacity, items); 

        cout << items_in_solution.size() << "\n";
        for(int i : items_in_solution) {
            cout << i << " ";
        }
        cout << "\n";
    }
    return 0;
}