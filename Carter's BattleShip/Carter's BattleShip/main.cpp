/*#include <iostream>
#include <vector>
#include <random>
#include <numeric>

using namespace std;

// Constants for the board size
const int rows = 10;
const int cols = 10;

// 2D vector to represent the game board
vector<vector<char>> board(rows, vector<char>(cols, '-'));

// Ship sizes and names
const int ship_sizes[] = { 2, 3, 3, 4, 5 };
const char ship_names[] = { 'A', 'B', 'C', 'D', 'E' };
const int num_ships = 5;

// Random number generator
random_device rd;
mt19937 gen(rd());

// Function to check if a ship can fit in a given position
bool canFit(vector<vector<char>>& board, int row, int col, int size, bool horizontal) {
    if (horizontal) {
        if (col + size > cols) return false;
    }
    else {
        if (row + size > rows) return false;
    }
    for (int i = 0; i < size; i++) {
        if (horizontal) {
            if (board[row][col + i] != '-') return false;
        }
        else {
            if (board[row + i][col] != '-') return false;
        }
    }
    return true;
}

// Function to place a ship on the board
void placeShip(vector<vector<char>>& board, int size, char name) {
    uniform_int_distribution<int> row_dist(0, rows - 1);
    uniform_int_distribution<int> col_dist(0, cols - 1);
    uniform_int_distribution<int> dir_dist(0, 1);
    int row = row_dist(gen);
    int col = col_dist(gen);
    bool horizontal = dir_dist(gen);

    while (!canFit(board, row, col, size, horizontal)) {
        row = row_dist(gen);
        col = col_dist(gen);
        horizontal = dir_dist(gen);
    }

    for (int i = 0; i < size; i++) {
        if (horizontal) {
            board[row][col + i] = name;
        }
        else {
            board[row + i][col] = name;
        }
    }
}

// Function to display the game board
void displayBoard(vector<vector<char>>& board) {
    cout << "  ";
    for (int i = 0; i < cols; i++) {
        cout << i << " ";
    }
    cout << "\n";
    for (int i = 0; i < rows; i++) {
        cout << i << " ";
        for (int j = 0; j < cols; j++) {
            cout << board[i][j] << " ";
        }
        cout << "\n";
    }
}

// Function to update progress when a ship is hit
void updateProgress(vector<int>& ship_cells, char name, int& shipsSunk) {
    int index = -1;
    for (int i = 0; i < num_ships; i++) {
        if (ship_names[i] == name) {
            index = i;
            break;
        }
    }
    if (index != -1) {
        ship_cells[index]--;
        if (ship_cells[index] == 0) {
            cout << "You sunk the " << name << "!\n";
            shipsSunk++;
        }
    }
}

// Function to check the user's guess and update the game state
void checkGuess(vector<vector<char>>& board, vector<int>& ship_cells, int row, int col, int& hits, int& misses, int& shipsSunk) {
    if (row < 0 || row >= rows || col < 0 || col >= cols) {
        cout << "Invalid guess, out of bounds.\n";
        return;
    }
    switch (board[row][col]) {
    case '-':
        cout << "Miss!\n";
        board[row][col] = 'O';
        misses++;
        break;
    case 'O':
    case 'X':
        cout << "Already guessed, try again.\n";
        break;
    default:
        cout << "Hit!\n";
        char name = board[row][col];
        board[row][col] = 'X';
        updateProgress(ship_cells, name, shipsSunk);
        hits++;
        break;
    }
}

// Function to run the game
void runGame() {
    // Initializing variables for the game
    vector<vector<char>> board(rows, vector<char>(cols, '-'));
    int total_cells = 0;
    vector<int> ship_cells(num_ships);
    for (int i = 0; i < num_ships; i++) {
        total_cells += ship_sizes[i];
        ship_cells[i] = ship_sizes[i];
    }
    int hits = 0;
    int misses = 0;
    int shipsSunk = 0;

    // Main game loop
    while (shipsSunk < num_ships) {
        displayBoard(board);
        int row, col;
        cout << "Enter the row and column to guess (separated by a space): ";
        cin >> row >> col;
        checkGuess(board, ship_cells, row, col, hits, misses, shipsSunk);
    }

    // Game Over message with stats
    cout << "Game Over!\n";
    cout << "Hits: " << hits << ", Misses: " << misses << ", Ships Sunk: " << shipsSunk << endl;
}

// Main function
int main() {
    runGame(); // Start the game
    return 0;
}
*/