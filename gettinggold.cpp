#include <iostream>
#include <fstream>
#include <vector>


enum Origin {up, down, left, right, start};

std::vector<std::vector<char> > grid;
std::vector<std::vector<int> > searched_area;


int getting_gold(int x, int y, Origin origin) {
    char symbol = grid[y][x];
    //std::cout << symbol << " " << x << " " << y << std::endl;
    if(searched_area[y][x]==1) {
        return 0;
    }
    else if(symbol == '#') {
        // we hit a wall
        searched_area[y][x] = 1;
        return 0;
    } else if (symbol == 'G') {
        // we hit a gold
        if (grid[y][x+1] == 'T' || grid[y][x-1] == 'T' || grid[y+1][x] == 'T' || grid[y-1][x] == 'T'){
            // we sense a draft
            searched_area[y][x] = 1;
            return 1;
        } else {
            searched_area[y][x] = 1;
            switch (origin)
            {
            case up:
                return 1 + getting_gold(x+1, y, left) + getting_gold(x-1, y, right) + getting_gold(x, y+1, up);
                break;
            case down:
                return 1 + getting_gold(x+1, y, left) + getting_gold(x-1, y, right) + getting_gold(x, y-1, down);
                break;
            case left:
                return 1 + getting_gold(x+1, y, left) + getting_gold(x, y+1, up) + getting_gold(x, y-1, down);
                break;
            case right:
                return 1 + getting_gold(x-1, y, right) + getting_gold(x, y+1, up) + getting_gold(x, y-1, down);
                break;
            default:
                return 1 + getting_gold(x+1, y, left) + getting_gold(x-1, y, right) + getting_gold(x, y+1, up) + getting_gold(x, y-1, down);
                break;
            }
            
        }
    } else if (grid[y][x+1] == 'T' || grid[y][x-1] == 'T' || grid[y+1][x] == 'T' || grid[y-1][x] == 'T') {
        // we sense a draft and there is no gold
        searched_area[y][x] = 1;
        return 0;
    } else {
        // normal floor or starting position
        searched_area[y][x] = 1;
        switch (origin)
            {
            case up:
                return getting_gold(x+1, y, left) + getting_gold(x-1, y, right) + getting_gold(x, y+1,  up);
                break;
            case down:
                return getting_gold(x+1, y, left) + getting_gold(x-1, y,  right) + getting_gold(x, y-1,  down);
                break;
            case left:
                return getting_gold(x+1, y, left) + getting_gold(x, y+1,  up) + getting_gold(x, y-1,  down);
                break;
            case right:
                return getting_gold(x-1, y, right) + getting_gold(x, y+1,  up) + getting_gold(x, y-1,  down);
                break;
            default:
                return getting_gold(x+1, y, left) + getting_gold(x-1, y,  right) + getting_gold(x, y+1,  up) + getting_gold(x, y-1,  down);
                break;
            }
    }
}


int main() {
    //std::ifstream cin("input.txt");
    int W, H;
    std::cin >> W >> H;
    
    int x, y;
    grid.resize(H, std::vector<char>(W));
    searched_area.resize(H, std::vector<int>(W, -1));


    for (int i = 0; i < H; i++)
    {
        for (int j = 0; j < W; j++)
        {
            char symbol;
            std::cin >> symbol;
            grid[i][j] = symbol;
            if(symbol=='P'){
                x = j;
                y = i;
            }
        }
        
    }
    Origin o = start;

    int gold = getting_gold(x, y, o);

    std::cout << gold << std::endl;
    

    return 0;
}