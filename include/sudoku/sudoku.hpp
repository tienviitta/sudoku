#include <array>
#include <bitset>
#include <iostream>
#include <vector>

/**
 * @brief One line description of the adder library
 *
 * More information about the adder library
 * can go here.
 *
 * @see https://github.com/ssciwr/cpp-project-template
 */
#pragma once

namespace sudoku {

/**
 * @brief One line description of add_one goes here
 *
 * For a more complicated function, here
 * would be more information about what it does.
 *
 * @param x Description of the input parameter x
 *
 * @note Something particular to note about add_one
 *
 * @warning A warning about add_one
 */
int add_one(int x);

class Solution {
  public:
    void solveSudoku(std::vector<std::vector<char>> &board) const noexcept;

  private:
    static constexpr std::pair<std::size_t, std::size_t>
    next_empty_position(std::vector<std::vector<char>> &board, std::size_t row,
                        std::size_t col) noexcept;
    static bool solve(std::vector<std::vector<char>> &board,
                      std::size_t const row_start, std::size_t const col_start,
                      std::array<std::bitset<9>, 9> &row_contains,
                      std::array<std::bitset<9>, 9> &col_contains,
                      std::array<std::bitset<9>, 9> &cell_contains) noexcept;
};

} // namespace sudoku
