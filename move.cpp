#include <iostream>
#include <string>
#include <vector>
#include <cctype>

struct Move {
    int fromRow, fromCol;
    int toRow, toCol;
};

// Converts a square like "e2" into board coordinates
Move parseMove(const std::string& from, const std::string& to) {
    Move m;
    m.fromCol = from[0] - 'a';
    m.fromRow = from[1] - '1';
    m.toCol   = to[0] - 'a';
    m.toRow   = to[1] - '1';
    return m;
}

void printBoard(const std::vector<std::vector<std::string>>& board) {
    const std::string LIGHT = "\033[47m";
    const std::string DARK  = "\033[100m";
    const std::string RESET = "\033[0m";
    const int SIZE = 8;

    // Top file labels
    std::cout << "    ";
    for (char f = 'a'; f < 'a' + SIZE; ++f)
        std::cout << ' ' << f << ' ';
    std::cout << "\n";

    for (int r = SIZE - 1; r >= 0; --r) {
        std::cout << ' ' << (r + 1) << "  ";
        for (int c = 0; c < SIZE; ++c) {
            bool isLight = ((r + c) % 2 == 0);
            const std::string& bg = isLight ? LIGHT : DARK;
            std::cout << bg << " " << board[r][c] << RESET << " ";
        }
        std::cout << ' ' << (r + 1) << "\n";
    }

    std::cout << "    ";
    for (char f = 'a'; f < 'a' + SIZE; ++f)
        std::cout << ' ' << f << ' ';
    std::cout << "\n";
}

int main() {
    const int SIZE = 8;
    std::vector<std::vector<std::string>> board(SIZE, std::vector<std::string>(SIZE, " "));

    std::vector<std::string> whitePieces = {"♖", "♘", "♗", "♕", "♔", "♗", "♘", "♖"};
    std::vector<std::string> blackPieces = {"♜", "♞", "♝", "♛", "♚", "♝", "♞", "♜"};

    // Setup pieces
    for (int c = 0; c < SIZE; ++c) {
        board[0][c] = whitePieces[c];
        board[1][c] = "♙";
        board[6][c] = "♟";
        board[7][c] = blackPieces[c];
    }

    while (true) {
        printBoard(board);
        std::string from, to;
        std::cout << "\nEnter move (e.g. e2 e4, or 'quit'): ";
        std::cin >> from;
        if (from == "quit") break;
        std::cin >> to;

        // Validate basic input
        if (from.size() != 2 || to.size() != 2 ||
            from[0] < 'a' || from[0] > 'h' ||
            to[0] < 'a' || to[0] > 'h' ||
            from[1] < '1' || from[1] > '8' ||
            to[1] < '1' || to[1] > '8') {
            std::cout << "Invalid input. Try again.\n";
            continue;
        }

        Move m = parseMove(from, to);

        std::string piece = board[m.fromRow][m.fromCol];
        if (piece == " ") {
            std::cout << "No piece at " << from << "!\n";
            continue;
        }

        // Move the piece
        board[m.toRow][m.toCol] = piece;
        board[m.fromRow][m.fromCol] = " ";
    }

    return 0;
}
