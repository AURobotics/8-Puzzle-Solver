#include <iostream>
#include <vector>
#include <math.h>
#include <queue>
#include <set>

using namespace std;

/*
goalState will start with the empty tile (0)

012...
.\....
..\...
...\..
....\.
.....(size ^ 2) - 1

*/

bool typeOfHeuristic; // 0 --> euclidean, 1 --> manhattan


class Board
{
private:
    static int size;
    double h;
    vector <vector <int>> state;
    int emptyTileRow = -1, emptyTileCol = -1, g;
public:

    Board () {
        this->userSetSize();
        this->userSetState();
        // find the empty tile
        for (int i = 0; i < this->size; i ++) {
            for (int j = 0; j < this->size; j ++) {
                if (this->state[i][j] == 0) {
                    this->emptyTileRow = i;
                    this->emptyTileCol = j;
                    break ;
                }
            }
            if (this->emptyTileRow != -1 && this->emptyTileCol != -1) {
                break ;
            }
        }
    }

    static bool isValid (int row, int col) {
        if (row >= 0 && row < size && col >= 0 && col < size) return 1;
        return 0;
    }

    bool operator<(const Board& other) const {
        return state < other.state;
    }

    struct compare {
        bool operator () (Board &a, Board &b) {
            return ((a.getG() + a.getH()) > (b.getG() + b.getH()));
        }
    };

    void setSize (int size) {
        this->size = size;
    }
    int getSize () {
        return this->size;
    }

    void userSetSize () {
        cout << "Enter the size of the board: \n";
        cin >> this->size;
    }

    void setG (int g) {
        this->g = g;
    }
    int getG () {
        return this->g;
    }

    void setH (int h) {
        this->h = h;
    }
    int getH () {
        return this->h;
    }

    vector < vector <int>>& getState () {
        return this->state;
    }

    int getEmptyTileRow () {
        return this->emptyTileRow;
    }
    void setEmptyTileRow (int n) {
        this->emptyTileRow = n;
    }

    int getEmptyTileCol () {
        return this->emptyTileCol;
    } 
    void setEmptyTileCol (int n) {
        this->emptyTileCol = n;
    }

    void userSetState () {
        cout << "Enter the initial state: \n";
        state = vector <vector <int>> (this->size);
        int x;
        for (int i = 0; i < this->size; i ++) {
            for (int j = 0; j < this->size; j ++) {
                cin >> x;
                state[i].push_back(x);
            }
        }
    }

    void printState () {
        for (int i = 0; i < this->size; i ++) {
            for (int j = 0; j < this->size; j ++) {
                cout << this->state [i][j] << " ";
            }
            cout << "\n";
        }
    }

    void calculateH () {
        double h = 0;
        for (int i = 0; i < size; i ++) {
            for (int j = 0; j < size; j ++) {
                int goalRow = this->state [i][j] / size;
                int goalCol = this->state [i][j] % size;
                if (typeOfHeuristic) {
                    h += abs (i - goalRow) + abs (j - goalCol);
                } 
                else {
                    h += sqrt((i - goalRow) * (i - goalRow) + (j - goalCol) * (j - goalCol)); 
                }
            }
        }
        this->h = h;
    }

    static Board moveRight (Board b) {
        swap (b.state[b.getEmptyTileRow()][b.getEmptyTileCol() + 1], b.state[b.getEmptyTileRow()][b.getEmptyTileCol()]);
        b.setEmptyTileCol(b.getEmptyTileCol() + 1);
        return b;
    }
    static Board moveLeft (Board b) {
        swap (b.state[b.getEmptyTileRow()][b.getEmptyTileCol() - 1], b.state[b.getEmptyTileRow()][b.getEmptyTileCol()]);
        b.setEmptyTileCol(b.getEmptyTileCol() - 1);
        return b;
    }
    static Board moveUp (Board b) {
        swap (b.state[b.getEmptyTileRow()- 1][b.getEmptyTileCol()], b.state[b.getEmptyTileRow()][b.getEmptyTileCol()]);
        b.setEmptyTileRow(b.getEmptyTileRow() - 1);
        return b;
    }
    static Board moveDown (Board b) {
        swap (b.state[b.getEmptyTileRow() + 1][b.getEmptyTileCol()], b.state[b.getEmptyTileRow()][b.getEmptyTileCol()]);
        b.setEmptyTileRow(b.getEmptyTileRow() + 1);
        return b;
    }
    
    bool solve () {
        priority_queue <Board, vector <Board>, compare> q;
        set <Board> s;

        this->calculateH();
        q.push(*this);

        while (q.size() > 0) {
            // cout << "here 30000000000\n";
            Board current = q.top();
            q.pop();
            s.insert(current);

            // cout << "////////////////////////////////\ncurrent\n";
            current.printState();

            if (current.getH() == 0) {
                // cout << "here 1\n";
                return 1;
            }
            
            if (Board::isValid(current.getEmptyTileRow(), current.getEmptyTileCol() + 1)) {
                Board rightBoard = Board::moveRight(current);
                // cout << "here 2.1\n";
                if (!s.count(rightBoard)) {
                    // cout << "here 2\n";
                    rightBoard.printState();
                    rightBoard.calculateH();
                    q.push(rightBoard);
                }
            }

            if (Board::isValid(current.getEmptyTileRow(), current.getEmptyTileCol() - 1)) {
                Board leftBoard = Board::moveLeft(current);
                if (!s.count(leftBoard)) {
                    // cout << "here 3\n";
                    leftBoard.printState();
                    leftBoard.calculateH();
                    q.push(leftBoard);
                }
            }

            if (Board::isValid(current.getEmptyTileRow() - 1, current.getEmptyTileCol())) {
                Board upBoard = Board::moveUp(current);
                if (!s.count(upBoard)) {
                    // cout << "here 4\n";
                    upBoard.printState();
                    upBoard.calculateH();
                    q.push(upBoard);
                }
            }

            if (Board::isValid(current.getEmptyTileRow() + 1, current.getEmptyTileCol())) {
                Board downBoard = Board::moveDown(current);
                if (!s.count(downBoard)) {
                    // cout << "here 5\n";
                    downBoard.printState();
                    downBoard.calculateH();
                    q.push(downBoard);
                }
            }
        }
        // cout << "here 700\n";
        return 0;
    }

};

int Board::size;


int main () {
    cout << "Enter what type of heuristic you want: \nEuclidean Distance: 0\nManhattan Distance: 1\n";
    cin >> typeOfHeuristic;
    Board initBoard;
    cout << "//////////////////////////////\n";
    initBoard.printState();
    cout << "//////////////////////////////\n";
    if (initBoard.solve()) cout << "Solvable\n";
    else cout << "Unsolvable\n";
}