#include <SFML/Graphics.hpp>
#include <vector>

using namespace std;

const int width = 40;
const int height = 40;
const int cellsize = 20;

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
    sf::RenderWindow window(sf::VideoMode(width * cellsize, height * cellsize), "Conway's Game of Life");
    vector<vector<int>> grid(height, vector<int>(width, 0));
    bool paused = true;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space) {
                paused = !paused;
            }
            if (paused && event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                int x = event.mouseButton.y / cellsize;
                int y = event.mouseButton.x / cellsize;
                if (x >= 0 && x < height && y >= 0 && y < width) {
                    grid[x][y] = 1 - grid[x][y];
                }
            }
        }

        if (!paused) {
            nextgeneration(grid);
        }

        window.clear(sf::Color::White);
        for (int i = 0; i < height; ++i) {
            for (int j = 0; j < width; ++j) {
                sf::RectangleShape cell(sf::Vector2f(cellsize - 1, cellsize - 1));
                cell.setPosition(j * cellsize, i * cellsize);
                cell.setFillColor(grid[i][j] ? sf::Color::Black : sf::Color::White);
                cell.setOutlineColor(sf::Color(200, 200, 200));
                cell.setOutlineThickness(1);
                window.draw(cell);
            }
        }
        window.display();
        sf::sleep(sf::milliseconds(100));
    }

    return 0;
}
