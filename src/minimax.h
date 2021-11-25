#ifndef TIC_TAC_TOE_MINIMAX_H
#define TIC_TAC_TOE_MINIMAX_H

#include "board.h"
#include "move.h"
#include "role.h"
#include <vector>

namespace minimax {
  class Minimax;

  class Minimax {
  public:
    Minimax(const board::Board &, move::Move, bool prev_is_maximize, role::Role);

    ~Minimax();

    int GetVal();

    [[nodiscard]] move::Move GetMove() const;

  private:
    void SpawnChildren();

    int FindMaximum();

    int FindMinimum();

//    void DebugPrint() const;

    board::Board board;
    move::Move move;
    role::Role own_role;
    bool is_maximize;
    std::vector<Minimax> children;
    int *pVal = nullptr;
  };
}

#endif //TIC_TAC_TOE_MINIMAX_H
