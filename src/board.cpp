#include "board.h"
#include "role.h"
#include <iostream>
#include <algorithm>

namespace board {
  Board::Board() {
    repr.fill(kEmpty);
  }

  std::ostream &operator<<(std::ostream &os, const board::Board &board) {
    os << " " << board.GetChar(0) << " | " << board.GetChar(1) << " | " << board.GetChar(2) << " \n";
    static const std::string line = "---+---+---";
    os << line << "\n";
    os << " " << board.GetChar(3) << " | " << board.GetChar(4) << " | " << board.GetChar(5) << " \n";
    os << line << "\n";
    os << " " << board.GetChar(6) << " | " << board.GetChar(7) << " | " << board.GetChar(8) << " ";
    return os;
  }

  char Board::GetChar(int address) const {
    switch (repr[address]) {
      case kEmpty:
        return ' ';
      case kNought:
        return 'O';
      case kCross:
        return 'X';
      default:
        return '?';
    }
  }

  bool Board::IsEmptyAt(int address) const {
    return repr[address] == kEmpty;
  }

  void Board::ApplyMove(move::Move move) {
    if (move.role.GetType()) { // role::kCross
      repr[move.location] = kCross;
    } else { //role::kNought
      repr[move.location] = kNought;
    }
  }

  Board::Board(const Board &rhs, move::Move move) {
    for (size_t i = 0; i < 9; ++i) {
      repr[i] = rhs.repr[i];
    }
    ApplyMove(move);
  }

  Result Board::GetResult(role::Role role) const {
    static constexpr std::array<std::array<int, 3>, 8> groups = {{{0, 1, 2},
                                                                  {3, 4, 5},
                                                                  {6, 7, 8},
                                                                  {0, 3, 6},
                                                                  {1, 4, 7},
                                                                  {2, 5, 8},
                                                                  {0, 4, 8},
                                                                  {2, 4, 6}}};
    for (const std::array<int, 3> &group: groups) {
      if (repr[group[0]] == repr[group[1]] && repr[group[1]] == repr[group[2]] && repr[group[2]] != kEmpty) {
        if (Matched(repr[group[2]], role)) {
          return {true, Result::max};
        } else {
          return {true, Result::min};
        }
      }
    }
    for (int mark: repr) {
      if (mark == kEmpty) {
        return {false, 0};
      }
    }
    return {true, 0};
  }

  bool Board::Matched(int mark, role::Role role) {
    if (role.GetType()) {
      return mark == kCross;
    } else {
      return mark == kNought;
    }
  }
}