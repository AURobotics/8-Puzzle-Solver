#include <iostream>
#include <vector>
#include <math.h>

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
    int size, g;
    double h;
public:
    vector <vector <int>> state;

    Board () {
        this->userSetSize();
        this->userSetState();
    }

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
    

};


int main () {
    cout << "Enter what type of heuristic you want: \nEuclidean Distance: 0\nManhattan Distance: 1\n";
    cin >> typeOfHeuristic;
    Board initBoard;
    initBoard.printState();
    
}