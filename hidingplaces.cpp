#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <queue>

using namespace std;

struct Node {
    int x, y, dist;
    Node(int col, int row, int distance) {
        x = col;
        y = row;
        dist = distance;
    }

    bool operator<(const Node& rhs) const {
        if(y < rhs.y) {
            return true;
        } else if(y == rhs.y) {
            return x > rhs.x;
        } else {
            return false;
        }
    }
};

vector<vector<int> > find_hiding_places(int row, int col) {
    vector<vector<int> > chess_board(8, vector<int>(8, -1));
    
    queue<Node> q;
    Node start(col, row, 0);
    q.push(start);
    while(!q.empty()) {
        Node next = q.front();
        q.pop();
        if(next.x >= 0 && next.x <=7 && next.y >= 0 && next.y <=7){
            // we are on the board
            if(chess_board[next.y][next.x] == -1) {
                // not visited
                chess_board[next.y][next.x] = next.dist;

                q.push(Node(next.x-2, next.y-1, next.dist+1));
                q.push(Node(next.x-2, next.y+1, next.dist+1));
                q.push(Node(next.x+2, next.y-1, next.dist+1));
                q.push(Node(next.x+2, next.y+1, next.dist+1));
                q.push(Node(next.x-1, next.y-2, next.dist+1));
                q.push(Node(next.x-1, next.y+2, next.dist+1));
                q.push(Node(next.x+1, next.y-2, next.dist+1));
                q.push(Node(next.x+1, next.y+2, next.dist+1));
                
            }
        }
    }
    return chess_board;

}

string to_chess_format(int row, int col) {
    string result;
    switch (col)
    {
        case 0:
            result = "a";
            break;
        case 1:
            result = "b";
            break;
        case 2:
            result = "c";
            break;
        case 3:
            result = "d";
            break;
        case 4:
            result = "e";
            break;
        case 5:
            result = "f";
            break;
        case 6:
            result = "g";
            break;
        case 7:
            result = "h";
            break;
        default:
            break;
    }
    return result + to_string(row);
}

int char_to_int(char c) {
    int result;
    switch (c)
    {
    case 'a':
        result = 0;
        break;
    case 'b':
        result = 1;
        break;
    case 'c':
        result = 2;
        break;
    case 'd':
        result = 3;
        break;
    case 'e':
        result = 4;
        break;
    case 'f':
        result = 5;
        break;
    case 'g':
        result = 6;
        break;
    case 'h':
        result = 7;
        break;
    default:
        break;
    }
    return result;
}

int main() {
    //ifstream cin("input.txt");
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n, row, col;
    char c_col;
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        cin >> c_col >> row;
        row -= 1;
        col = char_to_int(c_col);

        vector<vector<int> > result = find_hiding_places(row, col);
        int best = 0;
        for (int r = 0; r < 8; r++)
        {
            for (int c = 0; c < 8; c++)
            {
                if(result[r][c] > best) {
                    best = result[r][c];
                }
            }
            
        }

        priority_queue<Node> nodes;
        for (int r = 0; r < 8; r++)
        {
            for (int c = 0; c < 8; c++)
            {
                if(result[r][c] == best) {
                    nodes.push(Node(c, r, best));
                }
            }
            
        }

        cout << best << " ";


        while(!nodes.empty()) {
            Node n = nodes.top();
            nodes.pop();
            string coord = to_chess_format(n.y+1, n.x);
            cout << coord << " ";
        }
        cout << "\n";
    }
    return 0;
}