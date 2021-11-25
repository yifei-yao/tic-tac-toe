#include "minimax.h"
#include <iostream>

namespace minimax {

  Minimax::Minimax(const board::Board &from, move::Move move, bool prev_is_maximize, role::Role role) : is_maximize(
    !prev_is_maximize), board(from, move), move(move), own_role(role) {
  }

  Minimax::~Minimax() {
    delete pVal;
  }

  int Minimax::GetVal() {
    if (pVal != nullptr) {
      return *pVal;
    }
    if (board::Result result = board.GetResult(own_role);result.is_ended) {
      pVal = new int(result.val);
      return result.val;
    }
    SpawnChildren();
    if (is_maximize) {
      int value = FindMaximum() - 1;
      pVal = new int(value);
      return value;
    } else {
      int value = FindMinimum() + 1;
      pVal = new int(value);
      return value;
    }
  }

  void Minimax::SpawnChildren() {
    for (int i = 0; i < 9; ++i) {
      if (board.IsEmptyAt(i)) {
        if (is_maximize) {
          children.push_back(Minimax(board, {i, own_role}, is_maximize, own_role));
        } else {
          children.push_back(Minimax(board, {i, !own_role}, is_maximize, own_role));
        }
      }
    }
  }

  move::Move Minimax::GetMove() const {
    return move;
  }

  int Minimax::FindMaximum() {
    int local_max = std::numeric_limits<int>::min();
    for (minimax::Minimax child: children) {
      if (int val = child.GetVal(); val > local_max) {
        local_max = val;
      }
    }
    return local_max;
  }

  int Minimax::FindMinimum() {
    int local_min = std::numeric_limits<int>::max();
    for (minimax::Minimax child: children) {
      if (int val = child.GetVal(); val < local_min) {
        local_min = val;
      }
    }
    return local_min;
  }

//  void Minimax::DebugPrint() const {
//    std::cout << board << "\n";
//    std::cout << is_maximize;
//    std::cout << move.location << "\n";
//  }
}
