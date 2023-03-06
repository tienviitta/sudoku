#include "sudoku/sudoku.hpp"
#include <array>
#include <bitset>
#include <iostream>
#include <vector>

namespace sudoku {

int add_one(int x) { return x + 1; }

constexpr std::size_t get_cell(std::size_t row, std::size_t col) noexcept {
    return (row / 3) * 3 + col / 3;
}

constexpr std::size_t get_next_row(std::size_t row, std::size_t col) noexcept {
    return row + (col + 1) / 9;
}

constexpr std::size_t get_next_col(std::size_t col) noexcept {
    return (col + 1) % 9;
}

class Solution {
  public:
    void solveSudoku(std::vector<std::vector<char>> &board) const noexcept {
        /* Note: input is guaranteed to be a valid board using only '1'-'9' and
           '.' with a unique solution. Solution should modify board, not return
           a new one. */

        std::array<std::bitset<9>, 9> row_contains = {0, 0, 0, 0, 0,
                                                      0, 0, 0, 0};
        std::array<std::bitset<9>, 9> col_contains = {0, 0, 0, 0, 0,
                                                      0, 0, 0, 0};
        std::array<std::bitset<9>, 9> cell_contains = {0, 0, 0, 0, 0,
                                                       0, 0, 0, 0};

        for (std::size_t row = 0; row < 9; ++row) {
            for (std::size_t col = 0; col < 9; ++col) {
                char digit;
                if ((digit = board[row][col]) != '.') {
                    std::size_t digit_idx = digit - '1';
                    row_contains[row].set(digit_idx);
                    col_contains[col].set(digit_idx);
                    std::size_t cell = get_cell(row, col);
                    cell_contains[cell].set(digit_idx);
                }
            }
        }
        solve(board, 0, 0, row_contains, col_contains, cell_contains);
    }

  private:
    static constexpr std::pair<std::size_t, std::size_t>
    next_empty_position(std::vector<std::vector<char>> &board, std::size_t row,
                        std::size_t col) noexcept {
        while (row != 9) {
            if (board[row][col] == '.') {
                return {row, col};
            }
            row = get_next_row(row, col);
            col = get_next_col(col);
        }

        return {9, 0};
    }

    static bool solve(std::vector<std::vector<char>> &board,
                      std::size_t const row_start, std::size_t const col_start,
                      std::array<std::bitset<9>, 9> &row_contains,
                      std::array<std::bitset<9>, 9> &col_contains,
                      std::array<std::bitset<9>, 9> &cell_contains) noexcept {
        auto [row, col] = next_empty_position(board, row_start, col_start);

        if (row == 9) // end of board
        {
            return true;
        }

        std::size_t const cell = get_cell(row, col);
        std::bitset<9> const contains =
            row_contains[row] | col_contains[col] | cell_contains[cell];
        if (contains.all()) {
            return false;
        }

        for (std::size_t digit_idx = 0; digit_idx < 9; ++digit_idx) {
            if (!contains[digit_idx]) {
                board[row][col] = static_cast<char>(digit_idx + '1');
                row_contains[row].set(digit_idx);
                col_contains[col].set(digit_idx);
                cell_contains[cell].set(digit_idx);
                if (solve(board, row, col, row_contains, col_contains,
                          cell_contains)) {
                    return true;
                }

                row_contains[row].reset(digit_idx);
                col_contains[col].reset(digit_idx);
                cell_contains[cell].reset(digit_idx);
            }
        }
        board[row][col] = '.';
        return false;
    }
};

void print_board(std::vector<std::vector<char>> board) {
    for (std::size_t row = 0; row < 9; ++row) {
        for (std::size_t col = 0; col < 9; ++col) {
            std::cout << board[row][col] << ", ";
        }
        std::cout << "\n";
    }
}

std::vector<std::vector<char>>
flat_board_to_vec_vec(std::array<char, 81> const flat_board) {
    std::vector<std::vector<char>> board;
    board.reserve(9);
    for (std::size_t row = 0; row < 9; ++row) {
        std::vector<char> this_row;
        this_row.reserve(9);
        for (std::size_t col = 0; col < 9; ++col) {
            this_row.push_back(flat_board[row * 9 + col]);
        }
        board.push_back(this_row);
    }
    return board;
}

} // namespace sudoku
