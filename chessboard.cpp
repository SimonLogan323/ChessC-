// chessboard.cpp
// Display an 8x8 chessboard with alternating light and dark squares and starting chess pieces.
//
// Compile: g++ -std=c++17 chessboard.cpp -o chessboard
// Run: ./chessboard
//
// Note: Works in most terminals supporting UTF-8 and ANSI colors.

#include <iostream>
#include <string>
#include <vector>

int main() {
    // ANSI background colors for squares
    const std::string LIGHT = "\033[47m";   // white background
    const std::string DARK  = "\033[100m";  // dark gray background
    const std::string RESET = "\033[0m";    // reset color

    // Unicode chess symbols
    std::vector<std::string> whitePieces = {"♖", "♘", "♗", "♕", "♔", "♗", "♘", "♖"};
    std::vector<std::string> blackPieces = {"♜", "♞", "♝", "♛", "♚", "♝", "♞", "♜"};

    const int SIZE = 8;

    // Print top file labels
    std::cout << "    ";
    for (char f = 'a'; f < 'a' + SIZE; ++f)
        std::cout << ' ' << f << ' ';
    std::cout << "\n";

    for (int rank = SIZE; rank >= 1; --rank) {
        // Left rank label
        std::cout << ' ' << rank << "  ";

        for (int file = 0; file < SIZE; ++file) {
            bool isLight = ((rank + file) % 2 == 0);
            const std::string& bg = isLight ? LIGHT : DARK;

            std::string piece = " "; // default empty square

            // Place pieces in starting positions
            if (rank == 8) piece = blackPieces[file];
            else if (rank == 7) piece = "♟";
            else if (rank == 2) piece = "♙";
            else if (rank == 1) piece = whitePieces[file];

            // Print each square (two spaces for padding)
            std::cout << bg << " " << piece << RESET << " ";
        }

        // Right rank label
        std::cout << ' ' << rank << '\n';
    }

    // Print bottom file labels
    std::cout << "    ";
    for (char f = 'a'; f < 'a' + SIZE; ++f)
        std::cout << ' ' << f << ' ';
    std::cout << "\n";

    return 0;
}
