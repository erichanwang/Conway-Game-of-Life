#include <iostream>
#include <vector>
#include <thread>
#include <chrono>

using namespace std;

const int width = 20;
const int height = 20;

void printgrid(const vector<vector<int>>& grid) {
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            cout << (grid[i][j] ? '*' : ' ');
        }
        cout << endl;
    }
}

int countneighbors(const vector<vector<int>>& grid, int x, int y) {
    int count = 0;
    for (int i = -1; i <= 1; ++i) {
        for (int j = -1; j <= 1; ++j) {
            if (i == 0 && j == 0) continue;
            int nx = x + i;
            int ny = y + j;
            if (nx >= 0 && nx < height && ny >= 0 && ny < width) {
                count += grid[nx][ny];
            }
        }
    }
    return count;
}

void nextgeneration(vector<vector<int>>& grid) {
    vector<vector<int>> newgrid = grid;
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            int neighbors = countneighbors(grid, i, j);
            if (grid[i][j] == 1) {
                if (neighbors < 2 || neighbors > 3) {
                    newgrid[i][j] = 0;
                }
            } else {
                if (neighbors == 3) {
                    newgrid[i][j] = 1;
                }
            }
        }
    }
    grid = newgrid;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    vector<vector<int>> grid(height, vector<int>(width, 0));

    grid[1][2] = 1;
    grid[2][3] = 1;
    grid[3][1] = 1;
    grid[3][2] = 1;
    grid[3][3] = 1;

    while (true) {
        system("cls");
        printgrid(grid);
        nextgeneration(grid);
        this_thread::sleep_for(chrono::milliseconds(100));
    }

    return 0;
}
