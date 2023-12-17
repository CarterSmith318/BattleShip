
/*
#include <iostream>
#include <vector>
#include <random>
#include <ctime>
#include <string>
using namespace std;

// Define some constants
const int BOARD_SIZE = 10; // The size of the board
const int NUM_SHIPS = 5; // The number of ships
const int SHIP_SIZES[] = { 5, 4, 3, 3, 2 }; // The sizes of the ships
const char WATER = '~'; // The symbol for water
const char SHIP = '#'; // The symbol for ship
const char HIT = 'H'; // The symbol for hit
const char MISS = 'M'; // The symbol for miss

// Define a class for the board
class Board {
private:
    vector<vector<char>> grid; // The grid of the board
    vector<bool> ships_sunk; // The status of the ships
    int num_hits; // The number of hits
    int num_misses; // The number of misses
public:
    // Constructor
    Board() {
        // Initialize the grid with water
        grid = vector<vector<char>>(BOARD_SIZE, vector<char>(BOARD_SIZE, WATER));
        // Initialize the ships as not sunk
        ships_sunk = vector<bool>(NUM_SHIPS, false);
        // Initialize the hits and misses as zero
        num_hits = 0;
        num_misses = 0;
    }

    // A method to print the board
    void print() {
        // Print the column labels
        cout << "  ";
        for (int i = 0; i < BOARD_SIZE; i++) {
            cout << i << " ";
        }
        cout << "\n";
        // Print the rows
        for (int i = 0; i < BOARD_SIZE; i++) {
            // Print the row label
            cout << i << " ";
            // Print the cells
            for (int j = 0; j < BOARD_SIZE; j++) {
                cout << grid[i][j] << " ";
            }
            cout << "\n";
        }
    }

    // A method to place a ship on the board
    bool place_ship(int ship_num, int x1, int y1, int x2, int y2) {
        // Check if the coordinates are valid
        if (x1 < 0 || x1 >= BOARD_SIZE || y1 < 0 || y1 >= BOARD_SIZE ||
            x2 < 0 || x2 >= BOARD_SIZE || y2 < 0 || y2 >= BOARD_SIZE) {
            return false;
        }
        // Check if the ship size matches the distance
        int dx = abs(x2 - x1);
        int dy = abs(y2 - y1);
        if (dx + dy + 1 != SHIP_SIZES[ship_num]) {
            return false;
        }
        // Check if the ship is horizontal or vertical
        if (dx > 0 && dy > 0) {
            return false;
        }
        // Check if the ship overlaps with another ship or goes off the board
        int x = x1;
        int y = y1;
        while (x != x2 || y != y2) {
            if (grid[y][x] != WATER) {
                return false;
            }
            if (x < x2) {
                x++;
            }
            else if (x > x2) {
                x--;
            }
            else if (y < y2) {
                y++;
            }
            else if (y > y2) {
                y--;
            }
        }
        // Place the ship on the board
        x = x1;
        y = y1;
        while (x != x2 || y != y2) {
            grid[y][x] = SHIP;
            if (x < x2) {
                x++;
            }
            else if (x > x2) {
                x--;
            }
            else if (y < y2) {
                y++;
            }
            else if (y > y2) {
                y--;
            }
        }
        grid[y][x] = SHIP;
        return true;
    }

    // A method to randomly place all the ships on the board
    void randomize() {
        // Create a random number generator
        mt19937 rng(time(0));

        // For each ship
        for (int i = 0; i < NUM_SHIPS; i++) {
            bool valid = false;

            // Loop until a valid placement is found
            while (!valid) {
                int x1, y1, x2, y2;

                // Generate random coordinates
                x1 = rng() % BOARD_SIZE;
                y1 = rng() % BOARD_SIZE;
                int dir = rng() % 4; // 0 = right, 1 = down, 2 = left, 3 = up

                // Calculate the ending coordinates based on direction and ship size
                switch (dir) {
                case 0:
                    x2 = x1 + SHIP_SIZES[i] - 1;
                    y2 = y1;
                    break;
                case 1:
                    x2 = x1;
                    y2 = y1 + SHIP_SIZES[i] - 1;
                    break;
                case 2:
                    x2 = x1 - SHIP_SIZES[i] + 1;
                    y2 = y1;
                    break;
                case 3:
                    x2 = x1;
                    y2 = y1 - SHIP_SIZES[i] + 1;
                    break;
                }

                // Check if the coordinates are within bounds
                if (x2 >= 0 && x2 < BOARD_SIZE && y2 >= 0 && y2 < BOARD_SIZE) {
                    valid = true;

                    // Check if the cells for the ship are empty (water)
                    int x = x1, y = y1;
                    while (x != x2 || y != y2) {
                        if (grid[y][x] != WATER) {
                            valid = false;
                            break;
                        }
                        if (x < x2) {
                            x++;
                        }
                        else if (x > x2) {
                            x--;
                        }
                        else if (y < y2) {
                            y++;
                        }
                        else if (y > y2) {
                            y--;
                        }
                    }
                }

                // If the placement is valid, place the ship on the board
                if (valid) {
                    place_ship(i, x1, y1, x2, y2);
                }
            }
        }
    }



    bool fire(int x, int y) {
        // Check if the coordinates are valid
        if (x < 0 || x >= BOARD_SIZE || y < 0 || y >= BOARD_SIZE) {
            return false;
        }
        // Check if the cell has been fired before
        if (grid[y][x] == HIT || grid[y][x] == MISS) {
            return false;
        }
        // Check if the cell has a ship
        if (grid[y][x] == SHIP) {
            // Mark the cell as hit
            grid[y][x] = HIT;
            // Increment the number of hits
            num_hits++;

            // Check if any ship is sunk
            for (int ship_num = 0; ship_num < NUM_SHIPS; ship_num++) {
                int shipSize = SHIP_SIZES[ship_num];
                int hits = 0;
                for (int i = 0; i < BOARD_SIZE; i++) {
                    for (int j = 0; j < BOARD_SIZE; j++) {
                        if (grid[i][j] == HIT && SHIP_SIZES[ship_num] > 0) {
                            hits++;
                        }
                    }
                }
                if (hits == shipSize && !ships_sunk[ship_num]) {
                    // Mark the ship as sunk and display a message
                    ships_sunk[ship_num] = true;
                    cout << "You sunk my battleship of size " << shipSize << "!\n";
                }
            }

            // Check if all ships are sunk and the total hits reach 17
            int total_hits = get_hits();
            if (total_hits >= 17 && all_sunk()) {
                return true; // Game over
            }

            return true; // Return true for hit
        }
        else {
            // Mark the cell as miss
            grid[y][x] = MISS;
            // Increment the number of misses
            num_misses++;

            // Check if the total hits reach 17
            int total_hits = get_hits();
            if (total_hits >= 17) {
                return true; // Game over
            }

            return false; // Return false for miss
        }
    }






    // A method to check if all the ships are sunk
    bool all_sunk() {
        // Check each ship
        for (int i = 0; i < NUM_SHIPS; i++) {
            // If any ship is not sunk, return false
            if (!ships_sunk[i]) {
                return false;
            }
        }
        // Otherwise, return true
        return true;
    }

    // A method to get the number of hits
    int get_hits() {
        return num_hits;
    }

    // A method to get the number of misses
    int get_misses() {
        return num_misses;
    }
};

class Player {
private:
    Board board; // The player's board
    bool human; // Flag to determine if the player is human or computer
public:
    // Constructor
    Player(bool human) {
        this->human = human;
    }

    // Method to get the player's board
    Board& get_board() {
        return board;
    }

    // Method to check if the player is human
    bool is_human() {
        return human;
    }

    // Method to place a ship on the board for both human and computer players
    bool place_ship(int ship_num, int x1, int y1, int x2, int y2) {
        if (x1 < 0 || x1 >= BOARD_SIZE || y1 < 0 || y1 >= BOARD_SIZE ||
            x2 < 0 || x2 >= BOARD_SIZE || y2 < 0 || y2 >= BOARD_SIZE) {
            return false; // Invalid coordinates
        }

        return board.place_ship(ship_num, x1, y1, x2, y2);
    }

    // Method to handle ship placement for the player
    void handle_ship_placement() {
        cout << "Player, place your battleships:\n";
        for (int i = 0; i < NUM_SHIPS; ++i) {
            bool placed = false;
            while (!placed) {
                board.print();
                int x1, y1, x2, y2;
                cout << "Enter the coordinates for ship of size " << SHIP_SIZES[i] << " (x1 y1 x2 y2): ";
                cin >> x1 >> y1 >> x2 >> y2;
                placed = place_ship(i, x1, y1, x2, y2);
                if (!placed) {
                    cout << "Invalid placement. Try again.\n";
                }
            }
        }
    }

    // Method to get the input from the player
    void get_input(int& x, int& y) {
        if (human) {
            cout << "Enter the coordinates to fire (x y), or 'Q' to quit: ";
            string input;
            cin >> input;

            // Check if the input is 'Q' or 'q' to quit the game
            if (input == "Q" || input == "q") {
                cout << "Quitting the game...\n";
                exit(0); // Exit the game
            }

            // Convert input to integers if not quitting
            x = stoi(input);
            cin >> y;
        }
        else {
            mt19937 rng(time(0));
            x = rng() % BOARD_SIZE;
            y = rng() % BOARD_SIZE;
        }
    }


    // Method to play a turn for the player (firing at opponent's board)
    bool play_turn(Player& opponent) {
        int x, y;
        cout << "Player's turn:\n";
        get_board().print();
        get_input(x, y);
        bool hit = opponent.get_board().fire(x, y);
        if (hit) {
            cout << "Hit!\n";
        }
        else {
            cout << "Miss!\n";
        }
        return hit;
    }

    // Method to check if all of the player's ships are sunk
    bool all_ships_sunk() {
        return board.all_sunk();
    }


};


// Define a function to play the game
void play_game() {
    // Create two players
    Player p1(true); // Human player
    Player p2(false); // Computer player

    // Randomize the boards of the players
    p1.get_board().randomize();
    p2.get_board().randomize();


}

int main() {
    // Initialize random seed
    srand(time(0));

    // Create two players
    Player p1(true); // Human player
    Player p2(false); // Computer player

    // Human player places the battleships
    p1.handle_ship_placement();
    // Computer player randomly places battleships
    p2.get_board().randomize();

    // Computer player randomly places battleships
    // Ensure computer player also uses the same ship placement rules
    // Implement logic here to randomize the computer player's ship placement

    // Play the game
    bool game_over = false;
    while (!game_over) {
        int x, y;

        // Player 1's turn
        cout << "Player 1's turn:\n";
        p1.get_board().print();
        p1.get_input(x, y);
        bool hit = p2.get_board().fire(x, y);
        if (hit) {
            cout << "Hit!\n";
        }
        else {
            cout << "Miss!\n";
        }
        if (p2.get_board().all_sunk() && p2.get_board().get_hits() >= 17) {
            cout << "Player 1 wins!\n";
            game_over = true;
            break;
        }

        // Player 2's turn
        cout << "Player 2's turn:\n";
        p2.get_board().print();
        p2.get_input(x, y);
        hit = p1.get_board().fire(x, y);
        if (hit) {
            cout << "Hit!\n";
        }
        else {
            cout << "Miss!\n";
        }
        if (p1.get_board().all_sunk() && p1.get_board().get_hits() >= 17) {
            cout << "Player 2 wins!\n";
            game_over = true;
            break;
        }
    }

    return 0;
}
*/